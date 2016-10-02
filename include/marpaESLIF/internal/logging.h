#ifndef MARPAESLIF_INTERNAL_LOGGING_H
#define MARPAESLIF_INTERNAL_LOGGING_H
#include <stdio.h>

#undef  MARPAESLIF2LOG
#define MARPAESLIF2LOG(marpaESLIFp, rest) do {				\
    genericLogger_t *genericLoggerp = ((marpaESLIFp) != NULL) ? (marpaESLIFp)->option.genericLoggerp : NULL; \
    if (genericLoggerp != NULL) {					\
      rest;								\
    }									\
  } while (0)

#ifndef MARPAESLIF_NTRACE
#define MARPAESLIF_TRACEF(marpaESLIFp, funcs, fmts, ...) MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_TRACEF(genericLoggerp, "[%s] " fmts, funcs, __VA_ARGS__))
#define MARPAESLIF_TRACE(marpaESLIFp, funcs, msgs)       MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_TRACEF(genericLoggerp, "[%s] %s", funcs, msgs))
#else
#define MARPAESLIF_TRACEF(marpaESLIFp, funcs, fmts, ...)
#define MARPAESLIF_TRACE(marpaESLIFp, funcs, msgs)
#endif

#define MARPAESLIF_DEBUGF(marpaESLIFp, fmts, ...)     MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_DEBUGF    ((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_DEBUG(marpaESLIFp, ...)            MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_DEBUG     ((genericLoggerp),         __VA_ARGS__))
#define MARPAESLIF_INFOF(marpaESLIFp, fmts, ...)      MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_INFOF     ((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_INFO(marpaESLIFp, ...)             MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_INFO      ((genericLoggerp),         __VA_ARGS__))
#define MARPAESLIF_NOTICEF(marpaESLIFp, fmts, ...)    MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_NOTICEF   ((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_NOTICE(marpaESLIFp, ...)           MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_NOTICE    ((genericLoggerp),         __VA_ARGS__))
#define MARPAESLIF_WARNF(marpaESLIFp, fmts, ...)      MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_WARNF     ((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_WARN(marpaESLIFp, ...)             MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_WARN      ((genericLoggerp),         __VA_ARGS__))
#define MARPAESLIF_ERRORF(marpaESLIFp, fmts, ...)     MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_ERRORF    ((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_ERROR(marpaESLIFp, ...)            MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_ERROR     ((genericLoggerp),         __VA_ARGS__))
#define MARPAESLIF_CRITICALF(marpaESLIFp, fmts, ...)  MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_CRITICALF ((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_CRITICAL(marpaESLIFp, ...)         MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_CRITICAL  ((genericLoggerp),         __VA_ARGS__))
#define MARPAESLIF_ALERTF(marpaESLIFp, fmts, ...)     MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_ALERTF    ((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_ALERT(marpaESLIFp, ...)            MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_ALERT     ((genericLoggerp),         __VA_ARGS__))
#define MARPAESLIF_EMERGENCYF(marpaESLIFp, fmts, ...) MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_EMERGENCYF((genericLoggerp), (fmts), __VA_ARGS__))
#define MARPAESLIF_EMERGENCY(marpaESLIFp, ...)        MARPAESLIF2LOG(marpaESLIFp, GENERICLOGGER_EMERGENCY ((genericLoggerp),         __VA_ARGS__))

#endif /* MARPAESLIF_INTERNAL_LOGGING_H */
