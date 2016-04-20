#ifndef TCONV_CHARSET_ICU_H
#define TCONV_CHARSET_ICU_H

#include <stddef.h>

#include "tconv/export.h"

typedef struct tconv_charset_ICU_option {
  int confidencei;                    /* Default: 10 */
} tconv_charset_ICU_option_t;

#include "tconv.h"
#include "tconv/export.h"

TCONV_NO_EXPORT void *tconv_charset_ICU_new(genericLogger_t *genericLoggerp, void *optionp);
TCONV_NO_EXPORT char *tconv_charset_ICU_run(void *contextp, char *bytep, size_t bytel);
TCONV_NO_EXPORT void  tconv_charset_ICU_free(void *contextp);

#endif /*  TCONV_CHARSET_ICU_H */
