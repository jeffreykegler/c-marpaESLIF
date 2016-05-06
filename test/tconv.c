/* A tconv version of iconv, using only tconv API */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <tconv.h>
#include <optparse.h>
#include <genericLogger.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef _WIN32
#  include <unistd.h>
#else
#  include <io.h>
#endif

#ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
#endif
#ifndef O_BINARY
#  ifdef _O_BINARY
#    define O_BINARY _O_BINARY
#  endif
#endif

#ifndef S_IREAD
#  ifdef S_IRUSR
#    define S_IREAD S_IRUSR
#  else
#    ifdef _S_IREAD
#      define S_IREAD _S_IREAD
#    endif
#  endif
#endif

#ifndef S_IWRITE
#  ifdef S_IWUSR
#    define S_IWRITE S_IWUSR
#  else
#    ifdef _S_IWRITE
#      define S_IWRITE _S_IWRITE
#    endif
#  endif
#endif

#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

static void _usage(char *argv0, short helpb);
#ifndef TCONV_NTRACE
static void traceCallback(void *userDatavp, const char *msgs);
#endif
static void fileconvert(int outputFd, char *filenames,
			char *tocodes, char *fromcodes,
			size_t bufsizel,
			short fromPrintb, short toPrintb
#ifndef TCONV_NTRACE
			, short verbose
#endif
			);

/*****************************************************************************/
int main(int argc, char **argv)
/*****************************************************************************/
{
  int                  longindex  = 0;

  short                fromPrintb = 0;
  char                *fromcodes  = NULL;
  short                helpb      = 0;
  char                *outputs    = NULL;
  size_t              bufsizel    = BUFSIZ;
  char                *tocodes    = NULL;
  short                toPrintb   = 0;
  short                usageb     = 0;
#ifndef TCONV_NTRACE
  short                verbose    = 0;
#endif
  struct optparse_long longopts[] = {
    {  "bufsize",  'b', OPTPARSE_REQUIRED},
    {"from-code",  'f', OPTPARSE_REQUIRED},
    {"from-print", 'F', OPTPARSE_OPTIONAL},
    {     "help",  'h', OPTPARSE_OPTIONAL},
    {   "output",  'o', OPTPARSE_REQUIRED},
    {  "to-code",  't', OPTPARSE_REQUIRED},
    {  "to-print", 'T', OPTPARSE_OPTIONAL},
    {    "usage",  'u', OPTPARSE_OPTIONAL},
#ifndef TCONV_NTRACE
    {  "verbose",  'v', OPTPARSE_OPTIONAL},
#endif
    {  "version",  'V', OPTPARSE_OPTIONAL},
    {0}
  };

  char                *args;
  int                  outputFd;
  int                  option;
  struct optparse      options;

  optparse_init(&options, argv);
  while ((option = optparse_long(&options, longopts, &longindex)) != -1) {
    switch (option) {
    case 'b':
      bufsizel = atoi(options.optarg);
      break;
    case 'f':
      fromcodes = options.optarg;
      break;
    case 'F':
      fromPrintb = 1;
      break;
    case 'h':
      helpb= 1;
      break;
    case 'o':
      outputs = options.optarg;
      break;
    case 't':
      tocodes = options.optarg;
      break;
    case 'T':
      toPrintb = 1;
      break;
    case 'u':
      usageb = 1;
      break;
#ifndef TCONV_NTRACE
    case 'v':
      verbose = 1;
      break;
#endif
    case 'V':
      printf("tconv %s\n", TCONV_VERSION);
      exit(EXIT_SUCCESS);
      break;
    case '?':
      fprintf(stderr, "%s: %s\n", argv[0], options.errmsg);
      _usage(argv[0], 0);
      exit(EXIT_FAILURE);
    }
  }

  if ((helpb != 0) || (usageb != 0) || (bufsizel <= 0)) {
    int rci = ((helpb != 0) || (usageb != 0)) ? EXIT_SUCCESS : EXIT_FAILURE;
    _usage(argv[0], helpb);
    exit(rci);
  }
  
  if (outputs != NULL) {
    if (strlen(outputs) > 0) {
      outputFd = open(outputs,
                      O_RDWR|O_CREAT|O_TRUNC
#ifdef O_BINARY
                      |O_BINARY
#endif
                      , S_IREAD|S_IWRITE);
      if (outputFd < 0) {
	fprintf(stderr, "Failed to open %s: %s\n", outputs, strerror(errno));
	exit(EXIT_FAILURE);
      }
    } else {
      outputFd = -1;
    }
  } else {
    outputFd = fileno(stdout);
  }

  while ((args = optparse_arg(&options)) != NULL) {
    fileconvert(outputFd, args,
		tocodes, fromcodes,
		bufsizel,
		fromPrintb, toPrintb
#ifndef TCONV_NTRACE
		, verbose
#endif
		);
  }

  if (outputFd >= 0) {
    if (close(outputFd) != 0) {
      fprintf(stderr, "Failed to close %s: %s\n", outputs, strerror(errno));
    }
  }

  exit(EXIT_SUCCESS);
}

/*****************************************************************************/
static void fileconvert(int outputFd, char *filenames,
			char *tocodes, char *fromcodes,
			size_t bufsizel,
			short fromPrintb, short toPrintb
#ifndef TCONV_NTRACE
			, short verbose
#endif
			)
/*****************************************************************************/
{
  char           *inbuforigp  = NULL;
  char           *outbuforigp = NULL;
  size_t          outsizel = bufsizel;
  tconv_t         tconvp = NULL;
  int             fd;
  tconv_option_t  tconvOption;
  size_t          nconvl;
  size_t          nwritel;

  inbuforigp = malloc(bufsizel);
  if (inbuforigp == NULL) {
    fprintf(stderr, "malloc: %s\n", strerror(errno));
    goto end;
  }

  /* We start with an outbuf size the same as inbuf */
  outbuforigp = malloc(outsizel);
  if (outbuforigp == NULL) {
    fprintf(stderr, "malloc: %s\n", strerror(errno));
    goto end;
  }

  fd = open(filenames,
            O_RDONLY
#ifdef O_BINARY
            |O_BINARY
#endif
            );
  if (fd < 0) {
    fprintf(stderr, "Failed to open %s: %s\n", filenames, strerror(errno));
    goto end;
  }

  tconvOption.charsetp = NULL;
  tconvOption.convertp = NULL;
  tconvOption.traceCallbackp =
#ifndef TCONV_NTRACE
    (verbose != 0) ? traceCallback :
#endif
    NULL;
  tconvOption.traceUserDatavp = NULL;
  
  tconvp = tconv_open_ext(tocodes, fromcodes, &tconvOption);
  if (tconvp == (tconv_t) -1) {
    fprintf(stderr, "tconv_open_ext: %s\n", strerror(errno));
    goto end;
  }

#ifndef TCONV_NTRACE
  if (verbose != 0) {
    tconv_trace_on(tconvp);
  }
#endif

  while (1) {
    char *inbufp    = inbuforigp;
    char *outbufp   = outbuforigp;
    size_t outleftl = outsizel;
    short  eofb     = 0;
    size_t inleftl  = (size_t) read(fd, inbuforigp, bufsizel);
   
    if (inleftl == (size_t)-1) {
      fprintf(stderr, "Failed to read from %s: %s\n", filenames, strerror(errno));
      goto end;
    } else if (inleftl == 0) {
      eofb = 1;
    }

    while (eofb || (inleftl > 0)) {
    again:
      nconvl = tconv(tconvp, eofb ? NULL : &inbufp, eofb ? NULL : &inleftl, &outbufp, &outleftl);

      if (fromPrintb != 0) {
	GENERICLOGGER_INFOF(NULL, "from codeset: %s", tconv_fromcode(tconvp));
	fromPrintb = 0;
      }
      if (toPrintb != 0) {
	GENERICLOGGER_INFOF(NULL, "to codeset: %s", tconv_tocode(tconvp));
	toPrintb = 0;
      }
      nwritel = outsizel - outleftl;
      if (nwritel > 0) {
	if (outputFd >= 0) {
	  if (write(outputFd, outbuforigp, nwritel) != nwritel) {
	    fprintf(stderr, "Failed to write output: %s\n", strerror(errno));
	    goto end;
	  }
	}
        outbufp  = outbuforigp;
        outleftl = outsizel;
      }

      if (nconvl == (size_t) -1) {
	switch (errno) {
	case E2BIG:
          /* We realloc only if we wrote nothing */
	  if (nwritel <= 0) {
	    char *tmp;
	    
	    tmp = realloc(outbuforigp, outsizel + bufsizel);
	    if (tmp == NULL) {
	      fprintf(stderr, "realloc: %s\n", strerror(errno));
	      goto end;
	    }
	    outbufp    = outbuforigp = tmp;
            outsizel  += bufsizel;
            outleftl   = outsizel;
	  }
          goto again;
	  break;
	default:
	  fprintf(stderr, "%s: %s\n", filenames, tconv_error(tconvp));
	  goto end;
	}
      }

      if (eofb) {
        break;
      }
    }

    if (eofb) {
      break;
    }
  }

  if (tconv_close(tconvp) != 0) {
    fprintf(stderr, "Failed to close tconv: %s\n", strerror(errno));
  }
  tconvp = NULL;

  end:
  if (fd >= 0) {
    if (close(fd) != 0) {
      fprintf(stderr, "Failed to close %s: %s\n", filenames, strerror(errno));
    }
  }
  if (tconvp != (tconv_t)-1) {
    if (tconv_close(tconvp) != 0) {
      fprintf(stderr, "Failed to close tconv: %s\n", strerror(errno));
    }
  }
  if (outbuforigp != NULL) {
    free(outbuforigp);
  }
  if (inbuforigp != NULL) {
    free(inbuforigp);
  }
}

/*****************************************************************************/
static void traceCallback(void *userDatavp, const char *msgs)
/*****************************************************************************/
{
  GENERICLOGGER_TRACE(NULL, msgs);
}

/*****************************************************************************/
static void _usage(char *argv0, short helpb)
/*****************************************************************************/
{
  printf("Usage:\n"
	 "  %s [-b numberOfBytes] [-f fromcode] [-o filename] -t tocode "
	 "[-FhTuV"
#ifndef TCONV_NTRACE
	 "v"
#endif
	 "] input...\n"
	 ,
	 argv0
	 );
  if (helpb != 0) {
    printf("\n");
    printf("  Options with arguments:\n");
    printf("\n");
    printf("  -b, --bufsize   BUFSIZE     Internal buffer size.       Default: %d. Must be > 0.\n", (int) BUFSIZ);
    printf("  -f, --from-code FROM-CODE   Original code set.          Default: guessed from first read buffer.\n");
    printf("  -o, --output    OUTPUT      Output filename.            Default: standard output. An empty value disables output.\n");
    printf("  -t, --to-code   TO-CODE     Destination code set.       Default: FROM-CODE.\n");
    printf("\n");

    printf("  Options without argument:\n");
    printf("\n");
    printf("  -F, --from-print            Print original code set.\n");
    printf("  -h, --help                  Print this help and exit.\n");
    printf("  -T, --to-print              Print destination code set.\n");
    printf("  -u, --usage                 Print usage and exit.\n");
    printf("  -V, --version               Print version and exit.\n");
#ifndef TCONV_NTRACE
    printf("  -v, --verbose               Verbose mode.\n");
#endif

    printf("\n");
    printf("Examples:");
    printf("\n");
    printf("  Validate that a file is in ISO-8859-1\n");
    printf("  %s -f ISO-8859-1 input\n", argv0);
    printf("\n");
    printf("  Transform a file from TIS-620 to UTF-16\n");
    printf("  %s -f TIS-620 -t \"UTF-16//IGNORE//TRANSLIT\" input\n", argv0);
    printf("\n");
    printf("  Print and validate the guessed encoding of a file\n", argv0);
    printf("  %s -o \"\" -F input\n");
  }
}

