#ifndef MARPAWRAPPER_GRAMMAR
#define MARPAWRAPPER_GRAMMAR

#include <stddef.h>

#include "marpaWrapper/export.h"
#include "genericLogger.h"

/* ---------------- */
/* Opaque structure */
/* ---------------- */
typedef struct marpaWrapperGrammar       marpaWrapperGrammar_t;
typedef struct marpaWrapperGrammarSymbol marpaWrapperGrammarSymbol_t;
typedef struct marpaWrapperGrammarRule   marpaWrapperGrammarRule_t;

/* --------------- */
/* General options */
/* --------------- */
typedef struct marpaWrapperGrammarOption {
  genericLogger_t *genericLoggerp;        /* Default: NULL.                                      */
  short            warningIsErrorb;       /* Default: 0. Have precedence over warningIsIgnoredb  */
  short            warningIsIgnoredb;     /* Default: 0.                                         */
} marpaWrapperGrammarOption_t;

/* ------------------------------------------ */
/* For every symbol there can be three events */
/* ------------------------------------------ */
typedef enum marpaWrapperGrammarEventType {
  MARPAWRAPPERGRAMMAR_EVENTTYPE_NONE       = 0x00,
  MARPAWRAPPERGRAMMAR_EVENTTYPE_COMPLETION = 0x01,
  MARPAWRAPPERGRAMMAR_EVENTTYPE_NULLED     = 0x02,
  MARPAWRAPPERGRAMMAR_EVENTTYPE_PREDICTION = 0x04,
} marpaWrapperGrammarEvent_t;

/* ------------------ */
/* Options per symbol */
/* ------------------ */
typedef struct marpaWrapperGrammarSymbolOption {
  void      *datavp;      /* Default: NULL. User's opaque data pointer for this symbol  */
  short      terminalb;   /* Default: 0. Eventually force symbol to be terminal         */
  short      startb;      /* Default: 0. Eventually force symbol to be the start symbol */
  int        eventSeti;   /* Default: MARPAWRAPPERGRAMMAR_EVENTTYPE_NONE.               */
} marpaWrapperGrammarSymbolOption_t;

/* ---------------- */
/* Options per rule */
/* ---------------- */
typedef struct marpaWrapperGrammarRuleOption {
  void                        *datavp;         /* Default: NULL. User's opaque data pointer for this rule */
  int                          ranki;          /* Default: 0. Rank                                        */
  short                        nullRanksHighb; /* Default: 0. Null variant pattern                        */
  short                        sequenceb;      /* Default: 0. Sequence ?                                  */
  marpaWrapperGrammarSymbol_t *separatorSymbolp; /* Default: NULL. Eventual separator symbol              */
  short                        properb;        /* Default: 0. Proper flag                                 */
  int                          minimumi;       /* Default: 0. Mininimum - must be 0 or 1                  */
} marpaWrapperGrammarRuleOption_t;

#ifdef __cplusplus
extern "C" {
#endif
  marpaWrapper_EXPORT marpaWrapperGrammar_t       *marpaWrapperGrammar_newp(marpaWrapperGrammarOption_t *marpaWrapperGrammarOptionp);
  marpaWrapper_EXPORT marpaWrapperGrammar_t       *marpaWrapperGrammar_clonep(marpaWrapperGrammar_t *marpaWrapperGrammarp);
  marpaWrapper_EXPORT void                         marpaWrapperGrammar_freev(marpaWrapperGrammar_t *marpaWrapperGrammarp);

  marpaWrapper_EXPORT marpaWrapperGrammarSymbol_t *marpaWrapperGrammarSymbol_newp(marpaWrapperGrammar_t *marpaWrapperGrammarp, marpaWrapperGrammarSymbolOption_t *marpaWrapperGrammarSymbolOptionp);
  marpaWrapper_EXPORT marpaWrapperGrammarRule_t   *marpaWrapperGrammarRule_newp(marpaWrapperGrammar_t *marpaWrapperGrammarp, marpaWrapperGrammarRuleOption_t *marpaWrapperGrammarRuleOptionp,
										marpaWrapperGrammarSymbol_t *lhsSymbolp,
										size_t rhsSymboll, marpaWrapperGrammarSymbol_t **rhsSymbolpp
										);
#ifdef __cplusplus
}
#endif

#endif /* MARPAWRAPPER_GRAMMAR */
