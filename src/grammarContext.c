
/*****************************************************************************/
static inline void _marpaESLIF_grammarContext_resetv(marpaESLIF_t *marpaESLIFp, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp)
/*****************************************************************************/
{
  int                   i;
  int                   usedi;
  genericStack_t       *outputStackp;
  genericStack_t       *itemTypeStackp;
  genericStack_t       *grammarStackp;
  marpaESLIF_grammar_t *grammarp;

  /* In the grammar context, outputStack contain items that are typed using itemTypeStackp */
  if (marpaESLIF_grammarContextp != NULL) {
    outputStackp   = marpaESLIF_grammarContextp->outputStackp;
    itemTypeStackp = marpaESLIF_grammarContextp->itemTypeStackp;
    grammarStackp  = marpaESLIF_grammarContextp->grammarStackp;

    /* If one of them is NULL, this cannot be done */
    if ((outputStackp != NULL) && (itemTypeStackp != NULL)) {
      usedi = (int) GENERICSTACK_USED(outputStackp);
      for (i = usedi - 1; i >= 0; i--) {
        _marpaESLIF_grammarContext_i_resetb(marpaESLIFp, outputStackp, itemTypeStackp, i);
      }
      /* We know there are "on the stack" */
      GENERICSTACK_RESET(outputStackp);
      GENERICSTACK_RESET(itemTypeStackp);
    }

    if (grammarStackp != NULL) {
      usedi = (int) GENERICSTACK_USED(grammarStackp);
      for (i = usedi - 1; i >= 0; i--) {
        if (! GENERICSTACK_IS_PTR(grammarStackp, i)) {
          continue;
        }
        grammarp = (marpaESLIF_grammar_t *) GENERICSTACK_GET_PTR(grammarStackp, i);
        _marpaESLIF_grammar_freev(grammarp);
      }
      /* We know it is on the "heap" */
      GENERICSTACK_FREE(grammarStackp);
    }
  }
}

/*****************************************************************************/
static inline short _marpaESLIF_grammarContext_i_resetb(marpaESLIF_t *marpaESLIFp, genericStack_t *outputStackp, genericStack_t *itemTypeStackp, int i)
/*****************************************************************************/
{
  static const char            *funcs = "_marpaESLIF_grammarContext_i_resetb";
  marpaESLIF_grammarItemType_t  itemType;
  char                         *asciis;
  genericStack_t               *alternativesStackp;
  genericStack_t               *alternativeStackp;
  int                           j;
  int                           k;
  short                         rcb;

  if ((outputStackp != NULL) && (itemTypeStackp != NULL)) {
    if (GENERICSTACK_IS_INT(itemTypeStackp, i)) {
      itemType = (marpaESLIF_grammarItemType_t) GENERICSTACK_GET_INT(itemTypeStackp, i);

      switch (itemType) {
      case MARPAESLIF_GRAMMARITEMTYPE_LEXEME:        /* ARRAY */
        if (GENERICSTACK_IS_ARRAY(outputStackp, i)) {
          GENERICSTACKITEMTYPE2TYPE_ARRAY array =  GENERICSTACK_GET_ARRAY(outputStackp, i);
          if (GENERICSTACK_ARRAY_PTR(array) != NULL) {
            free(GENERICSTACK_ARRAY_PTR(array));
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_OP_DECLARE:         /* INT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ACTION_NAME:        /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ACTION:             /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_ACTION: /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_AUTORANK: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LEFT: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RIGHT: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_GROUP: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_SEPARATOR: /* String */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          marpaESLIF_string_t *stringp = (marpaESLIF_string_t *) GENERICSTACK_GET_PTR(outputStackp, i);
          _marpaESLIF_string_freev(stringp);
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PROPER: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RANK: /* INT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL_RANKING: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PRIORITY: /* INT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PAUSE: /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LATM: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NAMING: /* String */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          marpaESLIF_string_t *stringp = (marpaESLIF_string_t *) GENERICSTACK_GET_PTR(outputStackp, i);
          _marpaESLIF_string_freev(stringp);
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL: /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_LIST_ITEMS:  /* Stack of marpaESLIF_adverbItem_t */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          _marpaESLIF_adverbItemStack_freev((genericStack_t *) GENERICSTACK_GET_PTR(outputStackp, i));
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_LIST:        /* Stack of marpaESLIF_adverbItem_t as well */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          _marpaESLIF_adverbItemStack_freev((genericStack_t *) GENERICSTACK_GET_PTR(outputStackp, i));
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_LATM:               /* SHORT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_SYMBOL_NAME:        /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_SYMBOL:             /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_LHS:                /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_SINGLE_SYMBOL:       /* ASCII string */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          asciis = (char *) GENERICSTACK_GET_PTR(outputStackp, i);
          if (asciis != NULL) {
            free(asciis);
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_QUANTIFIER:          /* INT */
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_PRIORITIES:        /* Stack of alternatives */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          alternativesStackp = (genericStack_t *) GENERICSTACK_GET_PTR(outputStackp, i);
          for (j = 0; j < GENERICSTACK_USED(alternativesStackp); j++) { /* Stack of alternatives -> Stack of alternative */
            if (GENERICSTACK_IS_PTR(alternativesStackp, j)) {
              alternativeStackp = (genericStack_t *) GENERICSTACK_GET_PTR(alternativesStackp, j);
              for (k = 0; k < GENERICSTACK_USED(alternativeStackp); k++) { /* Stack of alternatives -> Stack of alternative -> Stack of marpaESLIF_alternativeItem_t */
                if (GENERICSTACK_IS_PTR(alternativeStackp, k)) {
                  _marpaESLIF_alternativeItemStack_freev((genericStack_t *) GENERICSTACK_GET_PTR(alternativeStackp, k));
                }
              }
            }
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ALTERNATIVES:        /* Stack of alternative */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          alternativeStackp = (genericStack_t *) GENERICSTACK_GET_PTR(outputStackp, i);
          for (j = 0; j < GENERICSTACK_USED(alternativeStackp); j++) { /* Stack of alternative -> Stack of marpaESLIF_alternativeItem_t */
            if (GENERICSTACK_IS_PTR(alternativeStackp, j)) {
              _marpaESLIF_alternativeItemStack_freev((genericStack_t *) GENERICSTACK_GET_PTR(alternativeStackp, j));
            }
          }
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ALTERNATIVE:        /* marpaESLIF_alternativeItem_t* */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          _marpaESLIF_alternativeItem_freev((marpaESLIF_alternativeItem_t *) GENERICSTACK_GET_PTR(outputStackp, i));
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_RHS:        /* marpaESLIF_rhsItem_t* */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          _marpaESLIF_rhsItem_freev((marpaESLIF_rhsItem_t *) GENERICSTACK_GET_PTR(outputStackp, i));
        }
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_GRAMMAR_REFERENCE: /* marpaESLIF_grammarReference_t* */
        if (GENERICSTACK_IS_PTR(outputStackp, i)) {
          _marpaESLIF_grammarReference_freev((marpaESLIF_grammarReference_t *) GENERICSTACK_GET_PTR(outputStackp, i));
        }
        break;
      default:
        break;
      }
    }

    GENERICSTACK_SET_NA(itemTypeStackp, i);
    if (GENERICSTACK_ERROR(itemTypeStackp)) {
      MARPAESLIF_ERRORF(marpaESLIFp, "itemTypeStackp set failure, %s", strerror(errno));
      goto err;
    }
    GENERICSTACK_SET_NA(outputStackp, i);
    if (GENERICSTACK_ERROR(outputStackp)) {
      MARPAESLIF_ERRORF(marpaESLIFp, "outputStackp set failure, %s", strerror(errno));
      goto err;
    }
  }

  rcb = 1;
  goto done;

 err:
  rcb = 0;

 done:
  return rcb;
}

/*****************************************************************************/
static inline const char *_marpaESLIF_grammarContext_i_types(marpaESLIF_t *marpaESLIFp, genericStack_t *itemTypeStackp, int i)
/*****************************************************************************/
{
  static const char            *funcs = "_marpaESLIF_grammarContext_i_types";
  marpaESLIF_grammarItemType_t  itemType;
  const char                   *rcs = marpaESLIF_grammarContext_UNKNOWN_types;

  if (itemTypeStackp != NULL) {
    if (GENERICSTACK_IS_INT(itemTypeStackp, i)) {
      itemType = (marpaESLIF_grammarItemType_t) GENERICSTACK_GET_INT(itemTypeStackp, i);

      switch (itemType) {
      case MARPAESLIF_GRAMMARITEMTYPE_NA:        /* N/A */
        rcs = marpaESLIF_grammarContext_NA_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_LEXEME:        /* ARRAY */
        rcs = marpaESLIF_grammarContext_LEXEME_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_OP_DECLARE:         /* INT */
        rcs = marpaESLIF_grammarContext_OP_DECLARE_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ACTION_NAME:        /* ASCII string */
        rcs = marpaESLIF_grammarContext_ACTION_NAME_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ACTION:             /* ASCII string */
        rcs = marpaESLIF_grammarContext_ACTION_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_ACTION: /* ASCII string */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_ACTION_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_AUTORANK: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_AUTORANK_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LEFT: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_LEFT_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RIGHT: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_RIGHT_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_GROUP: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_GROUP_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_SEPARATOR: /* String */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_SEPARATOR_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PROPER: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_PROPER_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RANK: /* INT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_RANK_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL_RANKING: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_NULL_RANKING_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PRIORITY: /* INT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_PRIORITY_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PAUSE: /* ASCII string */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_PAUSE_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LATM: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_LATM_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NAMING: /* String */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_NAMING_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL: /* SHORT */
        rcs = marpaESLIF_grammarContext_ADVERB_ITEM_NULL_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_LIST_ITEMS:  /* Stack of marpaESLIF_adverbItem_t */
        rcs = marpaESLIF_grammarContext_ADVERB_LIST_ITEMS_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_LIST:        /* Alias to MARPAESLIF_GRAMMARITEMTYPE_ADVERB_LIST_ITEMS - the two are exclusives (they share the same indice in outputStackp) */
        rcs = marpaESLIF_grammarContext_ADVERB_LIST_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_LATM:               /* SHORT */
        rcs = marpaESLIF_grammarContext_LATM_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_SYMBOL_NAME:        /* ASCII string */
        rcs = marpaESLIF_grammarContext_SYMBOL_NAME_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_SYMBOL:             /* ASCII string */
        rcs = marpaESLIF_grammarContext_SYMBOL_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_LHS:                /* ASCII string */
        rcs = marpaESLIF_grammarContext_LHS_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_SINGLE_SYMBOL:       /* ASCII string */
        rcs = marpaESLIF_grammarContext_SINGLE_SYMBOL_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_QUANTIFIER:          /* INT */
        rcs = marpaESLIF_grammarContext_QUANTIFIER_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_PRIORITIES:          /* Stack of alternatives */
        rcs = marpaESLIF_grammarContext_PRIORITIES_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ALTERNATIVES:        /* Stack of alternative */
        rcs = marpaESLIF_grammarContext_ALTERNATIVES_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_ALTERNATIVE:        /* Stack of marpaESLIF_alternativeItem_t */
        rcs = marpaESLIF_grammarContext_ALTERNATIVE_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_RHS:        /* Stack of marpaESLIF_rhsItem_t */
        rcs = marpaESLIF_grammarContext_RHS_types;
        break;
      case MARPAESLIF_GRAMMARITEMTYPE_GRAMMAR_REFERENCE:        /* Pointer to marpaESLIF_grammarReferenceItem_t */
        rcs = marpaESLIF_grammarContext_GRAMMAR_REFERENCE_types;
        break;
      default:
        break;
      }
    }
  }

  return rcs;
}

/*****************************************************************************/
static inline short _marpaESLIF_grammarContext_get_typeb(marpaESLIF_t *marpaESLIFp, genericStack_t *itemTypeStackp, int i, marpaESLIF_grammarItemType_t *typep)
/*****************************************************************************/
{
  static const char            *funcs = "_marpaESLIF_grammarContext_get_typeb";
  marpaESLIF_grammarItemType_t  type;
  short                         rcb;

  if (GENERICSTACK_IS_INT(itemTypeStackp, i)) {
    type = (marpaESLIF_grammarItemType_t) GENERICSTACK_GET_INT(itemTypeStackp, i);
  } else {
    MARPAESLIF_ERRORF(marpaESLIFp, "Not an INT in itemTypeStackp at indice %d", i);
    goto err;
  }

  if (typep != NULL) {
    *typep = type;
  }
  rcb = 1;
  goto done;

 err:
  rcb = 0;

 done:
  return rcb;
}

/*****************************************************************************/
static inline short _marpaESLIF_grammarContext_set_typeb(marpaESLIF_t *marpaESLIFp, genericStack_t *itemTypeStackp, int i, marpaESLIF_grammarItemType_t type)
/*****************************************************************************/
{
  static const char *funcs = "_marpaESLIF_grammarContext_set_typeb";
  short              rcb;

  GENERICSTACK_SET_INT(itemTypeStackp, type, i);
  if (GENERICSTACK_ERROR(itemTypeStackp)) {
    MARPAESLIF_ERRORF(marpaESLIFp, "itemTypeStackp set failure at indice %d, %s", i, strerror(errno));
    goto err;
  }

  rcb = 1;
  goto done;

 err:
  rcb = 0;

 done:
  return rcb;
}

/*****************************************************************************/
static inline void _marpaESLIF_adverbItemStack_freev(genericStack_t *stackp)
/*****************************************************************************/
{
  marpaESLIF_adverbItem_t *adverbItemp;
  int                      i;

  if (stackp != NULL) {
    for (i = 0; i < GENERICSTACK_USED(stackp); i++) {
      if (GENERICSTACK_IS_PTR(stackp, i)) {
        adverbItemp = (marpaESLIF_adverbItem_t *) GENERICSTACK_GET_PTR(stackp, i);
        if (adverbItemp != NULL) {
          switch (adverbItemp->type) {
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_ACTION: /* ASCII string */
            if (adverbItemp->u.asciis != NULL) {
              free(adverbItemp->u.asciis);
            }
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_AUTORANK: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LEFT: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RIGHT: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_GROUP: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_SEPARATOR: /* String */
            _marpaESLIF_string_freev(adverbItemp->u.stringp);
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PROPER: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RANK: /* INT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL_RANKING: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PRIORITY: /* INT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PAUSE: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LATM: /* SHORT */
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NAMING: /* String */
            _marpaESLIF_string_freev(adverbItemp->u.stringp);
            break;
          case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL: /* NA */
            break;
          default:
            break;
          }
          free(adverbItemp);
        }
      }
    }
    GENERICSTACK_FREE(stackp);
  }
}

/*****************************************************************************/
static inline void _marpaESLIF_alternativeItem_freev(marpaESLIF_alternativeItem_t *alternativeItemp)
/*****************************************************************************/
{
  if (alternativeItemp != NULL) {
    _marpaESLIF_rhsItemStack_freev(alternativeItemp->rhsItemStackp);
    _marpaESLIF_adverbItemStack_freev(alternativeItemp->adverbItemStackp);
    free(alternativeItemp);
  }
}

/*****************************************************************************/
static inline void _marpaESLIF_alternativeItemStack_freev(genericStack_t *stackp)
/*****************************************************************************/
{
  int i;

  if (stackp != NULL) {
    for (i = 0; i < GENERICSTACK_USED(stackp); i++) {
      if (GENERICSTACK_IS_PTR(stackp, i)) {
        _marpaESLIF_alternativeItem_freev((marpaESLIF_alternativeItem_t *) GENERICSTACK_GET_PTR(stackp, i));
      }
    }
    GENERICSTACK_FREE(stackp);
  }
}

/*****************************************************************************/
static inline void _marpaESLIF_rhsItem_freev(marpaESLIF_rhsItem_t *rhsItemp)
/*****************************************************************************/
{
  if (rhsItemp != NULL) {
    if (rhsItemp->singleSymbols != NULL) {
      free(rhsItemp->singleSymbols);
    }
    _marpaESLIF_grammarReference_freev(rhsItemp->grammarReferencep);
    free(rhsItemp);
  }
}

/*****************************************************************************/
static inline void _marpaESLIF_rhsItemStack_freev(genericStack_t *stackp)
/*****************************************************************************/
{
  int i;

  if (stackp != NULL) {
    for (i = 0; i < GENERICSTACK_USED(stackp); i++) {
      if (GENERICSTACK_IS_PTR(stackp, i)) {
        _marpaESLIF_rhsItem_freev((marpaESLIF_rhsItem_t *) GENERICSTACK_GET_PTR(stackp, i));
      }
    }
    GENERICSTACK_FREE(stackp);
  }
}

/*****************************************************************************/
static inline void _marpaESLIF_grammarReference_freev(marpaESLIF_grammarReference_t *grammarReferencep)
/*****************************************************************************/
{
  if (grammarReferencep != NULL) {
    _marpaESLIF_string_freev(grammarReferencep->stringp);
    free(grammarReferencep);
  }
}

/*****************************************************************************/
static inline short _marpaESLIFValueRuleCallbackGrammar_grammarb(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, marpaESLIF_grammarContext_op_declare_t op_declare, marpaESLIF_string_t *descp, marpaESLIF_string_t *new_descp, short createb, marpaESLIF_grammar_t **out_grammarpp)
/*****************************************************************************/
{
  static const char           *funcs = "_marpaESLIFValueRuleCallbackGrammar_grammarb";
  marpaESLIF_t                *marpaESLIFp                = marpaESLIFValuep->marpaESLIFp;
  marpaESLIFRecognizer_t      *marpaESLIFRecognizerp      = marpaESLIFValuep->marpaESLIFRecognizerp;
  genericStack_t              *grammarStackp              = marpaESLIF_grammarContextp->grammarStackp;
  marpaESLIFGrammar_t          marpaESLIFGrammar;
  marpaESLIF_grammar_t        *out_grammarp               = NULL;
  short                        rcb;

  marpaESLIFRecognizerp->callstackCounteri++;
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "start");

  /* Make sure grammar at this level exist - the method _marpaESLIFGrammar_grammar_findp want a marpaESLIFGrammar_t in input -; */
  marpaESLIFGrammar.marpaESLIFp   = marpaESLIFp;
  marpaESLIFGrammar.grammarStackp = grammarStackp;
  marpaESLIFGrammar.grammarp      = NULL;
  
  out_grammarp = _marpaESLIFGrammar_grammar_findp(&marpaESLIFGrammar, op_declare, descp);
  if (out_grammarp == NULL) {
    if (! createb) {
      MARPAESLIF_ERROR(marpaESLIFp, "No such grammar");
      goto err;
    }
    out_grammarp = _marpaESLIF_grammar_newp(marpaESLIFp,
                                            NULL /* marpaWrapperGrammarOptionp */,
                                            op_declare,
                                            "UTF-8", (descp != NULL) ? descp->bytep : NULL, (descp != NULL) ? descp->bytel : 0,
                                            0 /* latmb */,
                                            NULL /* defaultSymbolActionp */,
                                            NULL /* defaultRuleActionp */);
    if (out_grammarp == NULL) {
      goto err;
    }
    GENERICSTACK_SET_PTR(grammarStackp, out_grammarp, op_declare);
    if (GENERICSTACK_ERROR(grammarStackp)) {
      MARPAESLIF_ERRORF(marpaESLIFValuep->marpaESLIFp, "grammarStackp set failure, %s", strerror(errno));
      goto err;
    }
    MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "Created grammar at level %d", op_declare);
  } else {
    MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "Grammar at level %d already exist", op_declare);
    out_grammarp = (marpaESLIF_grammar_t *) GENERICSTACK_GET_PTR(grammarStackp, op_declare);
  }

  /* Check/Update attributes */
  if (new_descp != NULL) {
    _marpaESLIF_string_freev(out_grammarp->descp);
    out_grammarp->descp = _marpaESLIF_string_clonep(marpaESLIFValuep->marpaESLIFp, new_descp);
    if (out_grammarp->descp == NULL) {
      goto err;
    }
  }
  
  if (out_grammarpp != NULL) {
    *out_grammarpp = out_grammarp;
  }
  
  rcb = 1;
  goto done;

 err:
  _marpaESLIF_grammar_freev(out_grammarp);
  out_grammarp = NULL;
  rcb = 0;

 done:
  MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "return %d", (int) rcb);
  marpaESLIFRecognizerp->callstackCounteri--;
  return rcb;
}

/*****************************************************************************/
static inline short _marpaESLIFValueRuleCallbackGrammar_metab(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, marpaESLIF_grammarContext_op_declare_t op_declare, char *asciis, marpaESLIF_string_t *descp, short startb, short discardb, marpaESLIF_symbol_t **out_symbolpp)
/*****************************************************************************/
/* startb   is considered set by the caller if it is >= 0 */
/* discardb is considered set by the caller if it is >= 0 */
{
  static const char           *funcs                 = "_marpaESLIFValueRuleCallbackGrammar_metab";
  marpaESLIF_t                *marpaESLIFp           = marpaESLIFValuep->marpaESLIFp;
  marpaESLIFRecognizer_t      *marpaESLIFRecognizerp = marpaESLIFValuep->marpaESLIFRecognizerp;
  marpaESLIF_meta_t           *out_metap             = NULL;
  marpaESLIF_symbol_t         *out_symbolp           = NULL;
  marpaESLIF_grammar_t        *out_grammarp;
  short                        rcb;

  marpaESLIFRecognizerp->callstackCounteri++;
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "start");

  if (asciis == NULL) {
    MARPAESLIF_ERROR(marpaESLIFp, "No symbol name given");
    goto err;
  }
  
  /* Make sure grammar at this level exist */
  if (! _marpaESLIFValueRuleCallbackGrammar_grammarb(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, NULL /* descp */, NULL /* new_descp */, 1 /* createb */, &out_grammarp)) {
    goto err;
  }

  /* Make sure this symbol at this level exist */
  out_symbolp = _marpaESLIF_symbol_findp(marpaESLIFp, out_grammarp, asciis, -1 /* symboli */);
  if (out_symbolp == NULL) {
    /* This is a symbol out of a meta symbol */
    out_metap = _marpaESLIF_meta_newp(marpaESLIFp, out_grammarp, MARPAWRAPPERGRAMMAR_EVENTTYPE_NONE, asciis, NULL /* descEncodings */, NULL /* descs */, 0 /* descl */);
    if (out_metap == NULL) {
      goto err;
    }
    out_symbolp = _marpaESLIF_symbol_newp(marpaESLIFp);
    if (out_symbolp == NULL) {
      goto err;
    }
    out_symbolp->type       = MARPAESLIF_SYMBOL_TYPE_META;
    out_symbolp->startb     = (startb >= 0) ? startb : 0;
    out_symbolp->discardb   = (discardb >= 0) ? discardb : 0;
    out_symbolp->u.metap    = out_metap;
    out_symbolp->idi        = out_metap->idi;
    out_symbolp->descp      = out_metap->descp;
    /* Meta is now in symbol */
    out_metap = NULL;
    /* Push symbol */
    GENERICSTACK_SET_PTR(out_grammarp->symbolStackp, out_symbolp, out_symbolp->u.metap->idi);
    if (GENERICSTACK_ERROR(out_grammarp->symbolStackp)) {
      MARPAESLIF_ERRORF(marpaESLIFp, "out_grammarp->symbolStackp set failure, %s", strerror(errno));
      goto err;
    }
    MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "Created symbol No %d (%s) at level %d", out_symbolp->idi, out_symbolp->descp->asciis, op_declare);
  } else {
    MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "Found symbol No %d (%s) at level %d", out_symbolp->idi, out_symbolp->descp->asciis, op_declare);
  }

  /* Check/Update attributes */
  if (startb >= 0) {
    if (out_symbolp->startb != startb) {
      MARPAESLIF_ERRORF(marpaESLIFp, "The :start meta symbol can appear only once for grammar at level %d (%s)", out_grammarp->leveli, out_grammarp->descp->asciis);
      goto err;
    }
  }
  if (discardb >= 0) {
    if (out_symbolp->discardb != discardb) {
      MARPAESLIF_ERRORF(marpaESLIFp, "The :discardb meta symbol can appear only once for grammar at level %d (%s)", out_grammarp->leveli, out_grammarp->descp->asciis);
      goto err;
    }
  }
  if (descp != NULL) {
    if (! _marpaESLIF_string_eqb(out_symbolp->descp, descp)) {
      _marpaESLIF_string_freev(out_symbolp->descp);
      out_symbolp->descp = _marpaESLIF_string_clonep(marpaESLIFp, descp);
      if (out_symbolp->descp == NULL) {
        goto err;
      }
    }
  }
  
  if (out_symbolpp != NULL) {
    *out_symbolpp = out_symbolp;
  }

  rcb = 1;
  goto done;

 err:
  _marpaESLIF_meta_freev(out_metap);
  if (out_symbolp != NULL) {
    /* First remove shallow reference - per def out_grammarp is not NULL if out_symbolp is not NULL */
    GENERICSTACK_SET_NA(out_grammarp->symbolStackp, out_symbolp->idi);
    if (GENERICSTACK_ERROR(out_grammarp->symbolStackp)) {
      MARPAESLIF_ERRORF(marpaESLIFp, "out_grammarp->symbolStackp set failure, %s", strerror(errno));
      /* Really - bad luck - let grammar cleaner handle the cleanup */
      /* goto err; */
    } else {
      _marpaESLIF_symbol_freev(out_symbolp);
    }
    out_symbolp = NULL;
  }
  rcb = 0;

 done:
  MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "return %d", (int) rcb);
  marpaESLIFRecognizerp->callstackCounteri--;
  return rcb;
}

/*****************************************************************************/
static inline short _marpaESLIF_grammarContext_adverbList_unstackb(marpaESLIF_t *marpaESLIFp, genericStack_t *adverbItemStackp, char **actionsp, short *autorankbp, short *leftbp, short *rightbp, short *groupbp, char **separatorsp, short *properbp, int *rankip, short *nullRanksHighbp, int *priorityip, char **pausesp, short *latmbp, marpaESLIF_string_t **namingpp)
/*****************************************************************************/
/* Semantics are special here: if a NULL pointer is given to an adverb, then we do NOT want this adverb to exist */
{
  marpaESLIF_adverbItem_t *adverbItemp;
  int                      i;
  short                    rcb;

  if (adverbItemStackp == NULL) {
    MARPAESLIF_ERROR(marpaESLIFp, "adverbItemStackp is NULL");
    goto err;
  }

  /* Put the default values */
  if (actionsp != NULL) {
    *actionsp = NULL;
  }
  if (autorankbp != NULL) {
    *autorankbp = 0;
  }
  if (leftbp != NULL) {
    *leftbp = 1; /* Default is always left associativity */
  }
  if (rightbp != NULL) {
    *rightbp = 0;
  }
  if (groupbp != NULL) {
    *groupbp = 0;
  }
  if (separatorsp != NULL) {
    *separatorsp = NULL;
  }
  if (properbp != NULL) {
    *properbp = 0;
  }
  if (rankip != NULL) {
    *rankip = 0;
  }
  if (nullRanksHighbp != NULL) {
    *nullRanksHighbp = 0;
  }
  if (priorityip != NULL) {
    *priorityip = 0;
  }
  if (pausesp != NULL) {
    *pausesp = NULL;
  }
  if (latmbp != NULL) {
    *latmbp = 0;
  }
  if (namingpp != NULL) {
    *namingpp = NULL;
  }

  for (i = 0; i < GENERICSTACK_USED(adverbItemStackp); i++) {
    if (! GENERICSTACK_IS_PTR(adverbItemStackp, i)) {
      MARPAESLIF_ERRORF(marpaESLIFp, "Item No %d of adverbItemStackp is NULL", i);
      goto err;
    }

    adverbItemp = (marpaESLIF_adverbItem_t *) GENERICSTACK_GET_PTR(adverbItemStackp, i);
    switch (adverbItemp->type) {
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_ACTION:
      if (actionsp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "action adverb is not allowed");
        goto err;
      }
      *actionsp = adverbItemp->u.asciis;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_AUTORANK:
      if (autorankbp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "autorank adverb is not allowed");
        goto err;
      }
      *autorankbp = adverbItemp->u.b;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LEFT:
      if (leftbp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "left adverb is not allowed");
        goto err;
      }
      *leftbp = adverbItemp->u.b;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RIGHT:
      if (rightbp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "right adverb is not allowed");
        goto err;
      }
      *rightbp = adverbItemp->u.b;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_GROUP:
      if (groupbp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "group adverb is not allowed");
        goto err;
      }
      *groupbp = adverbItemp->u.b;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_SEPARATOR:
      if (separatorsp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "separator adverb is not allowed");
        goto err;
      }
      *separatorsp = adverbItemp->u.asciis;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PROPER:
      if (properbp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "proper adverb is not allowed");
        goto err;
      }
      *properbp = adverbItemp->u.b;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_RANK:
      if (rankip == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "rank adverb is not allowed");
        goto err;
      }
      *rankip = adverbItemp->u.i;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL_RANKING:
      if (nullRanksHighbp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "null-ranking adverb is not allowed");
        goto err;
      }
      *nullRanksHighbp = adverbItemp->u.b;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PRIORITY:
      if (priorityip == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "priority adverb is not allowed");
        goto err;
      }
      *priorityip = adverbItemp->u.i;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_PAUSE:
      if (pausesp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "pause adverb is not allowed");
        goto err;
      }
      *pausesp = adverbItemp->u.asciis;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_LATM:
      if (latmbp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "latm or forgiving adverb is not allowed");
        goto err;
      }
      *latmbp = adverbItemp->u.b;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NAMING:
      if (namingpp == NULL) {
        MARPAESLIF_ERROR(marpaESLIFp, "name adverb is not allowed");
        goto err;
      }
      *namingpp = adverbItemp->u.stringp;
      break;
    case MARPAESLIF_GRAMMARITEMTYPE_ADVERB_ITEM_NULL:
      /* Ignored */
      break;
    default:
      MARPAESLIF_ERRORF(marpaESLIFp, "Unsupported type %s (enum value %d) in adverbItemStackp", _marpaESLIF_grammarContext_i_types(marpaESLIFp, adverbItemStackp, i), adverbItemp->type);
      goto err;
    }
  }

  rcb = 1;
  goto done;

 err:
  rcb = 0;

 done:
  return rcb;
}

/*****************************************************************************/
static inline short _marpaESLIFValueRuleCallbackGrammar_rhsItemb(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, marpaESLIF_grammarContext_op_declare_t op_declare, marpaESLIF_rhsItem_t *rhsItemp, marpaESLIF_symbol_t **out_symbolpp)
/*****************************************************************************/
{
  static const char             *funcs                 = "_marpaESLIFValueRuleCallbackGrammar_rhsItemb";
  marpaESLIF_t                  *marpaESLIFp           = marpaESLIFValuep->marpaESLIFp;
  marpaESLIFRecognizer_t        *marpaESLIFRecognizerp = marpaESLIFValuep->marpaESLIFRecognizerp;
  marpaESLIF_grammar_t          *out_grammarp;
  marpaESLIF_symbol_t           *out_symbolp;
  marpaESLIF_grammarReference_t *out_grammarReferencep;
  marpaESLIF_grammar_t          *out_referencegrammarp;
  short                          rcb;

  marpaESLIFRecognizerp->callstackCounteri++;
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "start");

  if  (rhsItemp == NULL) {
    MARPAESLIF_ERROR(marpaESLIFp, "rhsItemp is NULL");
    goto err;
  }

  /* Check grammar */
  if (! _marpaESLIFValueRuleCallbackGrammar_grammarb(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, NULL /* descp */, NULL /* new_descp */, 1 /* createb */, &out_grammarp)) {
    goto err;
  }
  
  out_grammarReferencep = rhsItemp->grammarReferencep;
  if  (out_grammarReferencep != NULL) {
    if (! _marpaESLIFValueRuleCallbackGrammar_grammarb(marpaESLIFValuep, marpaESLIF_grammarContextp, out_grammarReferencep->leveli, out_grammarReferencep->stringp, NULL /* new_descp */, 1 /* createb */, &out_referencegrammarp)) {
      goto err;
    }
  } else {
    /* No referenced grammar: look into current grammar */
    if (! _marpaESLIFValueRuleCallbackGrammar_grammarb(marpaESLIFValuep, marpaESLIF_grammarContextp, out_grammarp->leveli, NULL /* desc */, NULL /* new_descp */, 0 /* createb - already eventually created upper */, NULL /* out_grammarp */)) {
      goto err;
    }
    out_referencegrammarp = out_grammarp;
  }

  if (out_referencegrammarp != out_grammarp) {
    /* Check this symbol in lookup grammar */
    if (! _marpaESLIFValueRuleCallbackGrammar_metab(marpaESLIFValuep, marpaESLIF_grammarContextp, out_referencegrammarp->leveli, rhsItemp->singleSymbols, NULL /* descp */, -1 /* startb */, -1 /* discardb */, NULL /* out_symbolpp */)) {
      goto err;
    }
  }

  /* Check this symbol in current grammar */
  if (! _marpaESLIFValueRuleCallbackGrammar_metab(marpaESLIFValuep, marpaESLIF_grammarContextp, out_grammarp->leveli, rhsItemp->singleSymbols, NULL /* descp */, -1 /* startb */, -1 /* discardb */, &out_symbolp)) {
    goto err;
  }

  if (out_symbolpp != NULL) {
    *out_symbolpp = out_symbolp;
  }

  rcb = 1;
  goto done;

 err:
  rcb = 0;

 done:
  MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "return %d", (int) rcb);
  marpaESLIFRecognizerp->callstackCounteri--;
  return rcb;
}

/*****************************************************************************/
static inline short _marpaESLIFValueRuleCallbackGrammar_rhsItemStackb(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, marpaESLIF_grammarContext_op_declare_t op_declare, genericStack_t *rhsItemStackp, size_t *nrhslp, int **rhsipp)
/*****************************************************************************/
{
  static const char             *funcs                 = "_marpaESLIFValueRuleCallbackGrammar_rhsItemStackb";
  marpaESLIF_t                  *marpaESLIFp           = marpaESLIFValuep->marpaESLIFp;
  marpaESLIFRecognizer_t        *marpaESLIFRecognizerp = marpaESLIFValuep->marpaESLIFRecognizerp;
  size_t                         nrhsl                 = 0;
  int                           *rhsip                 = NULL;
  int                           *rhstmpip;
  marpaESLIF_rhsItem_t          *rhsItemp;
  marpaESLIF_symbol_t           *out_symbolp;
  int                            i;
  short                          rcb;

  marpaESLIFRecognizerp->callstackCounteri++;
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "start");

  if (rhsItemStackp != NULL) {
  
    /* Check every RHS */
    if (rhsItemStackp != NULL) {
      for (i = 0; i < GENERICSTACK_USED(rhsItemStackp); i++) {
        if (! GENERICSTACK_IS_PTR(rhsItemStackp, i)) {
          MARPAESLIF_ERRORF(marpaESLIFp, "rhsItemStackp->[%d] is not a PTR", i);
          goto err;
        }
        rhsItemp = (marpaESLIF_rhsItem_t *) GENERICSTACK_GET_PTR(rhsItemStackp, i);

        if (! _marpaESLIFValueRuleCallbackGrammar_rhsItemb(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, rhsItemp, &out_symbolp)) {
          goto err;
        }

        /* Create/expand rhsip */
        if (nrhsl <= 0) {
          rhsip = (int *) malloc(sizeof(int));
          if (rhsip == NULL) {
            MARPAESLIF_ERRORF(marpaESLIFp, "malloc failure, %s", strerror(errno));
            goto err;
          }
          nrhsl = 1;
          rhsip[0] = out_symbolp->idi;
        } else {
          rhstmpip = realloc(rhsip, (nrhsl + 1) * sizeof(int));
          if (rhstmpip == NULL) {
            MARPAESLIF_ERRORF(marpaESLIFp, "realloc failure, %s", strerror(errno));
            goto err;
          }
          rhsip = rhstmpip;
          rhsip[nrhsl++] = out_symbolp->idi;
        }
      }
    }

  }
      
  if (nrhslp != NULL) {
    *nrhslp = nrhsl;
  }
  if (rhsipp != NULL) {
    *rhsipp = rhsip;
  } else if (rhsip != NULL) {
    free(rhsip);
  }

  rcb = 1;
  goto done;

 err:
  if (rhsip != NULL) {
    free(rhsip);
  }
  rcb = 0;

 done:
  MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "return %d", (int) rcb);
  marpaESLIFRecognizerp->callstackCounteri--;
  return rcb;
}

/*****************************************************************************/
static inline short _marpaESLIFValueRuleCallbackGrammar_ruleb(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, marpaESLIF_grammarContext_op_declare_t op_declare, marpaESLIF_string_t *descp, char *lhsasciis, genericStack_t *rhsItemStackp, genericStack_t *rhsItemExceptionStackp, int ranki, short nullRanksHighb, short sequenceb, int minimumi, char *separators, short properb, char *actions, short passthroughb, marpaESLIF_rule_t **out_rulepp)
/*****************************************************************************/
{
  static const char             *funcs                 = "_marpaESLIFValueRuleCallbackGrammar_ruleb";
  marpaESLIF_t                  *marpaESLIFp           = marpaESLIFValuep->marpaESLIFp;
  marpaESLIFRecognizer_t        *marpaESLIFRecognizerp = marpaESLIFValuep->marpaESLIFRecognizerp;
  marpaESLIF_rule_t             *out_rulep             = NULL;
  size_t                         nrhsl                 = 0;
  int                           *rhsip                 = NULL;
  size_t                         nrhsExceptionl        = 0;
  int                           *rhsExceptionip        = NULL;
  int                            separatori            = -1;
  marpaESLIF_symbol_t           *out_symbolp;
  marpaESLIF_symbol_t           *out_symbolseparatorp;
  marpaESLIF_grammar_t          *out_grammarp;
  short                          rcb;

  marpaESLIFRecognizerp->callstackCounteri++;
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "start");

  /* Check grammar */
  if (! _marpaESLIFValueRuleCallbackGrammar_grammarb(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, NULL /* descp */, NULL /* new_descp */, 1 /* createb */, &out_grammarp)) {
    goto err;
  }
  
  /* Check LHS stack */
  if (! _marpaESLIFValueRuleCallbackGrammar_metab(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, lhsasciis, NULL /* descp */, -1 /* startb */, -1 /* discardb */, &out_symbolp)) {
    goto err;
  }

  /* Check RHS stack */
  if (! _marpaESLIFValueRuleCallbackGrammar_rhsItemStackb(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, rhsItemStackp, &nrhsl, &rhsip)) {
    goto err;
  }

  /* Check Exception stack */
  if (! _marpaESLIFValueRuleCallbackGrammar_rhsItemStackb(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, rhsItemExceptionStackp, &nrhsExceptionl, &rhsExceptionip)) {
    goto err;
  }

  /* Check separator */
  if (separators != NULL) {
    if (! _marpaESLIFValueRuleCallbackGrammar_metab(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, separators, NULL /* descp */, -1 /* startb */, -1 /* discardb */, &out_symbolseparatorp)) {
      goto err;
    }
    separatori = out_symbolseparatorp->idi;
  }

  out_rulep = _marpaESLIF_rule_newp(marpaESLIFp,
                                    out_grammarp,
                                    (descp != NULL) ? descp->encodingasciis : NULL,
                                    (descp != NULL) ? descp->bytep : NULL,
                                    (descp != NULL) ? descp->bytel : 0,
                                    out_symbolp->idi,
                                    nrhsl,
                                    rhsip,
                                    nrhsExceptionl,
                                    rhsExceptionip,
                                    ranki,
                                    nullRanksHighb,
                                    sequenceb,
                                    minimumi,
                                    separatori,
                                    properb,
                                    actions,
                                    passthroughb);
  if (out_rulep == NULL) {
    goto err;
  }

  GENERICSTACK_SET_PTR(out_grammarp->ruleStackp, out_rulep, out_rulep->idi);
  if (GENERICSTACK_ERROR(out_grammarp->ruleStackp)) {
    MARPAESLIF_ERRORF(marpaESLIFp, "ruleStackp set failure, %s", strerror(errno));
    goto err;
  }

  MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "Created rule No %d (%s) at level %d", out_rulep->idi, out_rulep->descp->asciis, out_grammarp->leveli);

  if (out_rulepp != NULL) {
    *out_rulepp = out_rulep;
  }
  rcb = 1;
  goto done;

 err:
  _marpaESLIF_rule_freev(out_rulep);
  rcb = 0;

 done:
  if (rhsip != NULL) {
    free(rhsip);
  }
  if (rhsExceptionip != NULL) {
    free(rhsExceptionip);
  }
  MARPAESLIFRECOGNIZER_TRACEF(marpaESLIFRecognizerp, funcs, "return %d", (int) rcb);
  marpaESLIFRecognizerp->callstackCounteri--;
  return rcb;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENTS(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statements ::= statement+
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENTS);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_01(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <start rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_01);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_02(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <desc rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_02);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_03(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <empty rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_03);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_04(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <null statement>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_04);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_05(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <statement group>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_05);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_06(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <priority rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_06);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_07(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <quantified rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_07);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_08(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <discard rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_08);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_09(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <default rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_09);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_10(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <lexeme default statement>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_10);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_11(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <discard default statement>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_11);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_12(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <lexeme rule>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_12);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_13(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <completion event declaration>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_13);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_14(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <nulled event declaration>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_14);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_15(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <prediction event declaration>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_15);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_16(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <inaccessible statement>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_16);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_17(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * statement ::= <exception statement>
   *
   * No-op
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_17);
  MARPAESLIFRECOGNIZER_TRACE(marpaESLIFRecognizerp, funcs, "No op");
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_START_RULE(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <start rule> ::= ':start' <op declare> symbol
   *
   * Stack types:
   * NA ::= LEXEME OP_DECLARE SYMBOL
   *
   * C types:
   * -- ::= genericStackItemTypeArray_t int void*
   *
   * Note: We push NA because parents rule are No-opts
   *       symbol is an ASCII NUL terminated string
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_START_RULE);
  {
    CALLBACKGRAMMAR_DECL_OP_DECLARE(op_declare);
    CALLBACKGRAMMAR_DECL_SYMBOL(symbol);
    marpaESLIF_symbol_t  *out_symbolp;
    char                 *asciis;

    CALLBACKGRAMMAR_GET_OP_DECLARE(arg0i+1, op_declare);
    CALLBACKGRAMMAR_GET_SYMBOL(arg0i+2, symbol);

    /* Make sure this symbol exists at that grammar level */
    asciis = (char *) symbol;
    if (! _marpaESLIFValueRuleCallbackGrammar_metab(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, asciis, NULL /* descp */, 1 /* startb */, -1 /* discardb */, &out_symbolp)) {
      goto err;
    }

    /* Say this is the start symbol */
    out_symbolp->startb = 1;

    /* Parents are no-op */
    CALLBACKGRAMMAR_SET_NA(resulti);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_DESC_RULE(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <desc rule> ::= ':desc' <op declare> <quoted string>
   *
   * Stack types:
   * NA ::= LEXEME OP_DECLARE LEXEME
   *
   * C types:
   * -- ::= genericStackItemTypeArray_t int genericStackItemTypeArray_t
   *
   * Note: We push NA because parents rule are No-opts
   *       symbol is an ASCII NUL terminated string
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_DESC_RULE);
  {
    CALLBACKGRAMMAR_DECL_OP_DECLARE(op_declare);
    CALLBACKGRAMMAR_DECL_LEXEME(quoted_string);
    marpaESLIF_string_t  *out_descp;

    CALLBACKGRAMMAR_GET_OP_DECLARE(arg0i+1, op_declare);
    CALLBACKGRAMMAR_GET_LEXEME(arg0i+2, quoted_string);

    out_descp = _marpaESLIF_string_newp(marpaESLIFp, "UTF-8"/* Our lexeme imposed character stream */, GENERICSTACK_ARRAY_PTR(quoted_string), GENERICSTACK_ARRAY_LENGTH(quoted_string), 1 /* asciib */);
    if (out_descp == NULL) {
      goto err;
    }

    /* Change grammar description - we cannot search on description since we are changing it... */
    if (! _marpaESLIFValueRuleCallbackGrammar_grammarb(marpaESLIFValuep, marpaESLIF_grammarContextp, op_declare, NULL /* descp */, out_descp /* new_descp */, 0 /* createb */, NULL /* out_grammarpp */)) {
      _marpaESLIF_string_freev(out_descp);
      goto err;
    }

    _marpaESLIF_string_freev(out_descp);

    /* Parents are no-op */
    CALLBACKGRAMMAR_SET_NA(resulti);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_EMPTY_RULE(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <empty rule> ::= lhs <op declare> <adverb list>
   *
   * Stack types:
   * NA ::= LHS OP_DECLARE ADVERB_LIST
   *
   * C types:
   * -- ::= void* int void*
   *
   * Note: We push NA because parents rule are No-opts
   *       lhs is an ASCII NUL terminated string
   *       <adverb list> is a genericStack_t*
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_EMPTY_RULE);
  {
    CALLBACKGRAMMAR_DECL_LHS(lhs);
    CALLBACKGRAMMAR_DECL_OP_DECLARE(op_declare);
    CALLBACKGRAMMAR_DECL_ADVERB_LIST(adverb_list);
    /* Allowed adbvers */
    char                   *actions;
    int                     ranki;
    short                   nullRanksHighb;
    marpaESLIF_string_t    *namingp;
    
    CALLBACKGRAMMAR_GET_LHS(arg0i, lhs);
    CALLBACKGRAMMAR_GET_OP_DECLARE(arg0i+1, op_declare);
    CALLBACKGRAMMAR_GET_ADVERB_LIST(arg0i+2, adverb_list);

    /* Get the adverb items that are allowed in our context */
    if (! _marpaESLIF_grammarContext_adverbList_unstackb(marpaESLIFp,
                                                         (genericStack_t *) adverb_list,
                                                         &actions,
                                                         NULL, /* autorankbp */
                                                         NULL, /* leftbp */
                                                         NULL, /* rightbp */
                                                         NULL, /* groupb */
                                                         NULL, /* separatorsp */
                                                         NULL, /* properbp */
                                                         &ranki,
                                                         &nullRanksHighb,
                                                         NULL, /* priorityip */
                                                         NULL, /* pausesp */
                                                         NULL, /* latmbp */
                                                         &namingp)) {
      goto err;
    }

    /* Create the rule */
    if (! _marpaESLIFValueRuleCallbackGrammar_ruleb(marpaESLIFValuep,
                                                    marpaESLIF_grammarContextp,
                                                    op_declare,
                                                    namingp,
                                                    (char *) lhs,
                                                    NULL, /* rhsItemStackp */
                                                    NULL, /* rhsItemExceptionStackp */
                                                    ranki,
                                                    nullRanksHighb,
                                                    0, /* sequenceb */
                                                    -1, /* minimumi */
                                                    NULL, /* separators */
                                                    -1, /* properb */
                                                    actions,
                                                    0, /* passthroughb */
                                                    NULL /* out_rulepp */)) {
      goto err;
    }

    /* Parents are no-op */
    CALLBACKGRAMMAR_SET_NA(resulti);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_NULL_STATEMENT(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <null statement> ::= ';'
   *
   * Stack types:
   * NA ::= LEXEME
   *
   * C types:
   * -- ::= genericStackItemTypeArray_t
   *
   * Note: We push NA because parents rule are No-opts
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_NULL_STATEMENT);
  {
    /* Parents are no-op */
    CALLBACKGRAMMAR_SET_NA(resulti);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_STATEMENT_GROUP(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <statement group>              ::= '{' statements '}'
   *
   * Stack types:
   * NA ::= NA
   *
   * C types:
   * -- ::= --
   *
   * Note: We push NA because parents rule are No-opts
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_STATEMENT_GROUP);
  {
    /* Parents are no-op */
    CALLBACKGRAMMAR_SET_NA(resulti);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_PRIORITY_RULE(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <priority rule> ::= lhs <op declare> priorities
   *
   * Stack types:
   * NA ::= LHS OP_DECLARE PRIORITIES
   *
   * C types:
   * -- ::= void* int void*
   *
   * Note: We push NA because parents rule are No-opts
   *       lhs is an ASCII NUL terminated string
   *       priorities is a stack of alternatives separated by the loosen operator
   *       priorities can never be NULL because it is defined as alternatives+
   *
   *       Alternatives is a stack of alternative, cannot be NULL because it is defined as alternative+
   *       Alternative is a stack of rhs, cannot be NULL because it is defined as rhs, itself being defined a <rhs primary>+
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_PRIORITY_RULE);
  {
    CALLBACKGRAMMAR_DECL_LHS(lhs);
    CALLBACKGRAMMAR_DECL_OP_DECLARE(op_declare);
    CALLBACKGRAMMAR_DECL_PRIORITIES(priorities);
    genericStack_t               *alternativesStackp;
    genericStack_t               *alternativeStackp;
    marpaESLIF_alternativeItem_t *alternativeItemp;
    int                           priorityCounti;
    int                           i;
    /* Adverb items */
    char                         *actions;
    char                         *separators;
    short                         properb;
    marpaESLIF_string_t          *namingp;
    short                         nullRanksHighb;
    int                           ranki;
    
    CALLBACKGRAMMAR_GET_LHS(arg0i, lhs);
    CALLBACKGRAMMAR_GET_OP_DECLARE(arg0i+1, op_declare);
    CALLBACKGRAMMAR_GET_PRIORITIES(arg0i+2, priorities);

    priorityCounti = GENERICSTACK_USED(alternativesStackp);  /* Number of times the loosen operator '||' appears */

    if (priorityCounti <= 1) {

      /* There is only one priority */
      if (! GENERICSTACK_IS_PTR(alternativesStackp, 0)) {
        MARPAESLIF_ERROR(marpaESLIFValuep->marpaESLIFp, "alternativesStackp->[0] is not a PTR");
        goto err;
      }
      alternativeStackp = (genericStack_t *) GENERICSTACK_IS_PTR(alternativesStackp, 0);
      /* These are normal alternatives, separated by '|' */
      for (i = 0; i < GENERICSTACK_USED(alternativeStackp); i++) {
        if (! GENERICSTACK_IS_PTR(alternativeStackp, i)) {
          MARPAESLIF_ERRORF(marpaESLIFValuep->marpaESLIFp, "alternativesStackp->[%d] is not a PTR", i);
          goto err;
        }
        alternativeItemp = (marpaESLIF_alternativeItem_t *) GENERICSTACK_GET_PTR(alternativeStackp, i);

        /* Get the adverb items that are allowed in our context */
        if (! _marpaESLIF_grammarContext_adverbList_unstackb(marpaESLIFp,
                                                             alternativeItemp->adverbItemStackp,
                                                             &actions,
                                                             NULL, /* autorankbp */
                                                             NULL, /* leftbp */
                                                             NULL, /* rightbp */
                                                             NULL, /* groupb */
                                                             &separators,
                                                             &properb,
                                                             &ranki,
                                                             NULL, /* nullRanksHighbp */
                                                             NULL, /* priorityip */
                                                             NULL, /* pausesp */
                                                             NULL, /* latmbp */
                                                             &namingp)) {
          goto err;
        }

        /* Create the rule */
        if (! _marpaESLIFValueRuleCallbackGrammar_ruleb(marpaESLIFValuep,
                                                        marpaESLIF_grammarContextp,
                                                        op_declare,
                                                        namingp,
                                                        (char *) lhs,
                                                        alternativeItemp->rhsItemStackp, /* rhsItemStackp */
                                                        NULL, /* rhsItemExceptionStackp */
                                                        ranki,
                                                        nullRanksHighb,
                                                        0, /* sequenceb */
                                                        -1, /* minimumi */
                                                        separators,
                                                        properb,
                                                        actions,
                                                        0, /* passthroughb */
                                                        NULL /* out_rulepp */)) {
          goto err;
        }

      }
    }

    /* Parents are no-op */
    CALLBACKGRAMMAR_SET_NA(resulti);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_OP_DECLARE_1(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <op declare> ::= <op declare top grammar>
   *
   * Stack types:
   * INT ::= LEXEME
   *
   * C types:
   * int ::= genericStackItemTypeArray_t
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_OP_DECLARE_1);
  {
    CALLBACKGRAMMAR_DECL_OP_DECLARE(op_declare);
    op_declare = 0; /* No need to fetch the lexeme, we know it is for level 0 */
    CALLBACKGRAMMAR_SET_OP_DECLARE(resulti, op_declare);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_OP_DECLARE_3(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /* ---------------------------------------------------------------------------
   * <op declare> ::= <op declare any grammar>
   *
   * Stack types:
   * INT ::= LEXEME
   *
   * C types:
   * int ::= genericStackItemTypeArray_t
   * ------------------------------------------------------------------------- */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_OP_DECLARE_3);
  {
    CALLBACKGRAMMAR_DECL_OP_DECLARE(op_declare);
    CALLBACKGRAMMAR_DECL_LEXEME    (op_declare_any_grammar);
    char *p;

    CALLBACKGRAMMAR_GET_LEXEME(arg0i, op_declare_any_grammar);

    /* Get the grammar level */
    /* By construction this cannot be < 0 - we made sure the string is ASCII (via the grammar) and NUL terminated (via the symbol callback) */
    p = GENERICSTACK_ARRAY_PTR(op_declare_any_grammar);
    p += 2;    /* Skip ":[" */
    op_declare = atoi(p);

    CALLBACKGRAMMAR_SET_OP_DECLARE(resulti, op_declare);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_ACTION_NAME(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /*
   * ---------------------------------------------------------------------------------------------
   * <action name>  ::= <ascii name>
   *
   * Stack types:
   * PTR ::= LEXEME
   *
   * C types:
   * void* ::= genericStackItemTypeArray_t
   *
   * Note: <ascii name>  inner pointer is an ASCII NUL terminated string: ASCII as per the grammar, NUL terminated as per charconv
   *       <action name> is an ASCII NUL terminated string
   * ---------------------------------------------------------------------------------------------
   */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_ACTION_NAME);
  {
    CALLBACKGRAMMAR_DECL_ACTION_NAME(action_name);
    CALLBACKGRAMMAR_DECL_LEXEME     (ascii_name);

    CALLBACKGRAMMAR_GET_LEXEME(arg0i, ascii_name);

    action_name = strdup(GENERICSTACK_ARRAY_PTR(ascii_name));
    if (action_name == NULL) {
      MARPAESLIF_ERRORF(marpaESLIFValuep->marpaESLIFp, "strdup failure, %s", strerror(errno));
      goto err;
    }

    CALLBACKGRAMMAR_SET_ACTION_NAME(resulti, action_name);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_ACTION(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /*
   * ---------------------------------------------------------------------------------------------
   * action ::= 'action' '=>' <action name>
   *
   * Stack types:
   * PTR ::= LEXEME LEXEME PTR
   *
   * C types:
   * void* ::= genericStackItemTypeArray_t genericStackItemTypeArray_t void*
   *
   * Note: <action name> is an ASCII NUL terminated string
   *       <action> is an ASCII NUL terminated string
   * ---------------------------------------------------------------------------------------------
   */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_ACTION);
  {
    CALLBACKGRAMMAR_DECL_ACTION     (action);
    CALLBACKGRAMMAR_DECL_ACTION_NAME(action_name);

    CALLBACKGRAMMAR_GET_ACTION_NAME(arg0i+2, action_name);

    action = strdup(action_name);
    if (action == NULL) {
      MARPAESLIF_ERRORF(marpaESLIFValuep->marpaESLIFp, "strdup failure, %s", strerror(errno));
      goto err;
    }

    CALLBACKGRAMMAR_SET_ACTION(resulti, action);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_ADVERB_ITEM_01(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /*
   * ---------------------------------------------------------------------------------------------
   * <adverb item> ::= action
   *
   * Stack types:
   * PTR ::= PTR
   *
   * C types:
   * void* ::= void*
   *
   * Note: <action>      is an ASCII NUL terminated string
   *       <adverb item> is an ASCII NUL terminated string
   * ---------------------------------------------------------------------------------------------
   */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_ADVERB_ITEM_01);
  {
    CALLBACKGRAMMAR_DECL_ADVERB_ITEM_ACTION(adverb_item_action);
    CALLBACKGRAMMAR_DECL_ACTION            (action);

    CALLBACKGRAMMAR_GET_ACTION(arg0i, action);

    adverb_item_action = strdup(action);
    if (adverb_item_action == NULL) {
      MARPAESLIF_ERRORF(marpaESLIFValuep->marpaESLIFp, "strdup failure, %s", strerror(errno));
      goto err;
    }

    CALLBACKGRAMMAR_SET_ADVERB_ITEM_ACTION(resulti, adverb_item_action);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_ADVERB_ITEM_12(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /*
   * ---------------------------------------------------------------------------------------------
   * <adverb item> ::= <latm specification>
   *
   * Stack types:
   * SHORT ::= SHORT
   *
   * C types:
   * short ::= short
   * ---------------------------------------------------------------------------------------------
   */
  CALLBACKGRAMMAR_COMMON_HEADER(_G1_RULE_ADVERB_ITEM_12);
  {
    CALLBACKGRAMMAR_DECL_ADVERB_ITEM_LATM(adverb_item_latm);
    CALLBACKGRAMMAR_DECL_LATM            (latm);

    CALLBACKGRAMMAR_GET_LATM(arg0i, latm);

    adverb_item_latm = latm;

    CALLBACKGRAMMAR_SET_ADVERB_ITEM_LATM(resulti, adverb_item_latm);
  }
  CALLBACKGRAMMAR_COMMON_TRAILER;
}

/*****************************************************************************/
static inline short _G1_RULE_ADVERB_LIST_ITEMS(marpaESLIFValue_t *marpaESLIFValuep, marpaESLIF_grammarContext_t *marpaESLIF_grammarContextp, int rulei, int arg0i, int argni, int resulti)
/*****************************************************************************/
{
  /*
   * ---------------------------------------------------------------------------------------------
   * <adverb list items> ::= <adverb item>*
   *
   * Stack types:
   * PTR ::= ~variable types see below~
   *
   * C types:
   * PTR ::= short
   *
   * Note: <adverb list items> is a genericStack pointer
   *       <adverb item> can be any of the supported adverb items
   * ---------------------------------------------------------------------------------------------
   */
}

