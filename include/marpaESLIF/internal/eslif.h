#ifndef MARPAESLIF_INTERNAL_ESLIF_H
#define MARPAESLIF_INTERNAL_ESLIF_H

typedef struct bootstrap_grammar_terminal {
  int                        idi;                 /* Identifier */
  char                      *descs;               /* Description */
  marpaESLIF_terminal_type_t terminalType;        /* Terminal type */
  marpaESLIF_uint32_t        optioni;             /* Terminal option */
  PCRE2_SPTR                 originp;             /* UTF-8 encoding */
  PCRE2_SPTR                 substitutionp;       /* UTF-8 encoding */
  char                      *testFullMatchs;
  char                      *testPartialMatchs;
} bootstrap_grammar_terminal_t;

typedef struct bootstrap_grammar_meta {
  int   idi;                /* Identifier */
  char *descs;              /* Description */
} bootstrap_grammar_meta_t;

typedef enum bootstrap_grammar_rule_type {
  MARPAESLIF_RULE_TYPE_ALTERNATIVE,
  MARPAESLIF_RULE_TYPE_SEQUENCE
} bootstrap_grammar_rule_type_t;

typedef struct bootstrap_grammar_rule {
  int                           lhsi;
  char                         *descs;
  bootstrap_grammar_rule_type_t type;
  size_t                        nrhsl;
  int                           rhsip[10]; /* 10 is arbitrary - just to make C happy */
  int                           minimumi;
  int                           separatori;
  short                         properb;
} bootstrap_grammar_rule_t;

#include "marpaESLIF/internal/eslif/L0.h"
#include "marpaESLIF/internal/eslif/G1.h"

#endif /* MARPAESLIF_INTERNAL_ESLIF_H */
