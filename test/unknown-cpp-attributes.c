#include "../hedley.h"

#include <stdio.h>

#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define UNPREDICTABLE \
       HEDLEY_DIAGNOSTIC_PUSH \
       HEDLEY_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES \
       HEDLEY_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[unpredictable]]) \
       HEDLEY_DIAGNOSTIC_POP
#  endif
#endif
#if !defined(UNPREDICTABLE)
#  define UNPREDICTABLE
#endif

int main(int argc, char* argv[]) {
  (void) argv;

  if (argc == 1) UNPREDICTABLE {
    fputs("Argument required\n", stderr);
    return -1;
  }

  printf("Arguments: %d\n", argc);

  return 0;
}
