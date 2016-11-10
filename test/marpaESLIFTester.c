#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <genericLogger.h>
#include <marpaESLIF.h>

const static char *metags = "# Copyright 2015 Jeffrey Kegler\n"
"# This file is part of Marpa::R2.  Marpa::R2 is free software: you can\n"
"# redistribute it and/or modify it under the terms of the GNU Lesser\n"
"# General Public License as published by the Free Software Foundation,\n"
"# either version 3 of the License, or (at your option) any later version.\n"
"#\n"
"# Marpa::R2 is distributed in the hope that it will be useful,\n"
"# but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n"
"# Lesser General Public License for more details.\n"
"#\n"
"# You should have received a copy of the GNU Lesser\n"
"# General Public License along with Marpa::R2.  If not, see\n"
"# http://www.gnu.org/licenses/.\n"
"\n"
":default :[0]:= action => default_meta_action\n"
":desc ::= 'Description String 1'\n"
":desc ::= \"Description String 2\"\n"
"lexeme default =\n"
"  action => default_lexeme_action\n"
"  forgiving => 1\n"
"\n"
":start ::= statements\n"
"statements ::= statement+\n"
"empty_rule ::= ;\n"
"statement ::= <start rule> | <empty rule>\n"
"  | <null statement> | <statement group>\n"
"  | <priority rule> | <quantified rule>\n"
"  | <discard rule> | <default rule>\n"
"  | <lexeme default statement>\n"
"  | <discard default statement>\n"
"  | <lexeme rule>\n"
"  | <completion event declaration>\n"
"  | <nulled event declaration>\n"
"  | <prediction event declaration>\n"
"  | <current lexer statement>\n"
"  | <inaccessible statement>\n"
"\n"
"<null statement> ::= ';'\n"
"<statement group> ::= '{' statements '}'\n"
"<start rule> ::= ':start' <op declare bnf> symbol\n"
"<start rule> ::= 'start' 'symbol' 'is' symbol\n"
"<default rule> ::= ':default' <op declare bnf> <adverb list>\n"
"<lexeme default statement> ::= 'lexeme' 'default' '=' <adverb list>\n"
"<discard default statement> ::= 'discard' 'default' '=' <adverb list>\n"
"<priority rule> ::= lhs <op declare> priorities\n"
"<empty rule> ::= lhs <op declare> <adverb list>\n"
"<quantified rule> ::= lhs <op declare> <single symbol> quantifier <adverb list>\n"
"<discard rule> ::= ':discard' <op declare match> <single symbol> <adverb list>\n"
"<lexeme rule> ::= ':lexeme' <op declare match> symbol <adverb list>\n"
"<completion event declaration> ::= 'event' <event initialization> '=' 'completed' <symbol name>\n"
"<nulled event declaration> ::= 'event' <event initialization> '=' 'nulled' <symbol name>\n"
"<prediction event declaration> ::= 'event' <event initialization> '=' 'predicted' <symbol name>\n"
"<current lexer statement> ::= 'current' 'lexer' 'is' <lexer name>\n"
"\n"
"<inaccessible statement> ::= 'inaccessible' 'is' <inaccessible treatment> 'by' 'default'\n"
"<inaccessible treatment> ::= 'warn' | 'ok' | 'fatal'\n"
"\n"
"<op declare> ::= <op declare bnf> | <op declare match>\n"
"priorities ::= alternatives+\n"
"    separator => <op loosen> proper => 1\n"
"alternatives ::= alternative+\n"
"    separator => <op equal priority> proper => 1\n"
"alternative ::= rhs <adverb list>\n"
"\n"
"<adverb list> ::= <adverb list items>\n"
"<adverb list items> ::= <adverb item>*\n"
"<adverb item> ::=\n"
"      action\n"
"    | <left association> | <right association> | <group association>\n"
"    | <separator specification> | <proper specification>\n"
"    | <rank specification> | <null ranking specification>\n"
"    | <priority specification> | <pause specification> | <event specification>\n"
"    | <latm specification> | naming | <null adverb>\n"
"\n"
"<null adverb> ::= ','\n"
"action ::= 'action' '=>' <action name>\n"
"<left association> ::= 'assoc' '=>' 'left'\n"
"<right association> ::= 'assoc' '=>' 'right'\n"
"<group association> ::= 'assoc' '=>' 'group'\n"
"<separator specification> ::= 'separator' '=>' <single symbol>\n"
"<proper specification> ::= 'proper' '=>' boolean\n"
"<rank specification> ::= 'rank' '=>' <signed integer>\n"
"<null ranking specification> ::= 'null-ranking' '=>' <null ranking constant>\n"
"<null ranking specification> ::= 'null' 'rank' '=>' <null ranking constant>\n"
"<null ranking constant> ::= 'low' | 'high'\n"
"<priority specification> ::= 'priority' '=>' <signed integer>\n"
"<pause specification> ::= 'pause' '=>' <before or after>\n"
"\n"
"<event specification> ::= 'event' '=>' <event initialization>\n"
"<event initialization> ::= <event name> <event initializer>\n"
"<event initializer> ::= '=' <on or off>\n"
"<on or off> ::= 'on' | 'off'\n"
"<event initializer> ::= # empty\n"
"\n"
"<latm specification> ::= 'forgiving' '=>' boolean\n"
"<latm specification> ::= 'latm' '=>' boolean\n"
"<naming> ::= 'name' '=>' <alternative name>\n"
"\n"
"<alternative name> ::= <standard name> | <single quoted name>\n"
"<lexer name> ::= <standard name> | <single quoted name>\n"
"\n"
"<event name> ::= <standard name>\n"
"    | <single quoted name>\n"
"    | <reserved event name>\n"
"<reserved event name> ~ ':symbol'\n"
"\n"
"lhs ::= <symbol name>\n"
"rhs ::= <rhs primary>+\n"
"<rhs primary> ::= <single symbol>\n"
"<rhs primary> ::= <single quoted string>\n"
"<rhs primary> ::= <parenthesized rhs primary list>\n"
"<parenthesized rhs primary list> ::= '(' <rhs primary list> ')'\n"
"<rhs primary list> ::= <rhs primary>+\n"
"<single symbol> ::=\n"
"    symbol\n"
"  | <character class>\n"
"symbol ::= <symbol name>\n"
"<symbol name> ::= <bare name>\n"
"<symbol name> ::= <bracketed name>\n"
"<action name> ::= <Perl name>\n"
"<action name> ::= <reserved action name>\n"
"\n"
":discard ~ whitespace\n"
"whitespace ~ [\\s]+\n"
"\n"
"# allow comments\n"
":discard ~ <hash comment>\n"
"<hash comment> ~ <terminated hash comment> | <unterminated\n"
"   final hash comment>\n"
"<terminated hash comment> ~ '#' <hash comment body> <vertical space char>\n"
"<unterminated final hash comment> ~ '#' <hash comment body>\n"
"<hash comment body> ~ <hash comment char>*\n"
"<vertical space char> ~ [\\x{A}\\x{B}\\x{C}\\x{D}\\x{2028}\\x{2029}]\n"
"<hash comment char> ~ [^\\x{A}\\x{B}\\x{C}\\x{D}\\x{2028}\\x{2029}]\n"
"\n"
"<op declare bnf> ~ '::='\n"
"<op declare match> ~ '~'\n"
"<op loosen> ~ '||'\n"
"<op equal priority> ~ '|'\n"
"quantifier ::= '*' | '+'\n"
"<before or after> ~ 'before' | 'after'\n"
"\n"
"<signed integer> ~ <integer> | <sign> <integer>\n"
"<sign> ~ [+-]\n"
"<integer> ~ [\\d]+\n"
"\n"
"boolean ~ [01]\n"
"\n"
"<reserved action name> ~ '::' <one or more word characters>\n"
"<one or more word characters> ~ [\\w]+\n"
"<zero or more word characters> ~ [\\w]*\n"
"\n"
"# Perl identifiers allow an initial digit, which makes them slightly more liberal than Perl bare names\n"
"# but equivalent to Perl names with sigils.\n"
"<Perl identifier> ~ [\\w]+\n"
"<double colon> ~ '::'\n"
"<Perl name> ~ <Perl identifier>+ separator => <double colon> proper => 1\n"
"\n"
"<bare name> ~ [\\w]+\n"
"<standard name> ~ [a-zA-Z] <zero or more word characters>\n"
"<bracketed name> ~ '<' <bracketed name string> '>'\n"
"<bracketed name string> ~ [\\s\\w]+\n"
"\n"
"# In single quoted strings and character classes\n"
"# no escaping or internal newlines, and disallow empty string\n"
"\n"
"<single quoted string> ~ ['] <string without single quote or vertical space> ['] <character class modifiers>\n"
"<single quoted name> ~ ['] <string without single quote or vertical space> [']\n"
"<string without single quote or vertical space> ~ [^'\\x{0A}\\x{0B}\\x{0C}\\x{0D}\\x{0085}\\x{2028}\\x{2029}]+\n"
"\n"
"<character class> ~ '[' <cc elements> ']' <character class modifiers>\n"
"<cc elements> ~ <cc element>+\n"
"<cc element> ~ <safe cc character>\n"
"# hex 5d is right square bracket\n"
"<safe cc character> ~ [^\\x{5d}\\x{0A}\\x{0B}\\x{0C}\\x{0D}\\x{0085}\\x{2028}\\x{2029}]\n"
"<cc element> ~ <escaped cc character>\n"
"<escaped cc character> ~ '\\\\' <horizontal character>\n"
"<cc element> ~ <posix char class>\n"
"<cc element> ~ <negated posix char class>\n"
"<character class modifiers> ~ <character class modifier>*\n"
"<character class modifier> ~ ':ic'\n"
"<character class modifier> ~ ':i'\n"
"\n"
"# [=xyz=] and [.xyz.] are parsed by Perl, but then currently cause an exception.\n"
"# Catching Perl exceptions is inconvenient for Marpa,\n"
"# so we reject them syntactically instead.\n"
"<posix char class> ~ '[:' <posix char class name> ':]'\n"
"<negated posix char class> ~ '[:^' <posix char class name> ':]'\n"
"<posix char class name> ~ [[:alnum:]]+\n"
"\n"
"# a horizontal character is any character that is not vertical space\n"
"<horizontal character> ~ [^\\x{A}\\x{B}\\x{C}\\x{D}\\x{2028}\\x{2029}]\n"
;

int main() {
  marpaESLIF_t             *marpaESLIFp        = NULL;
  marpaESLIFGrammar_t      *marpaESLIFGrammarp = NULL;
  char                     *helpers            = NULL;
  marpaESLIFOption_t        marpaESLIFOption;
  marpaESLIFGrammarOption_t marpaESLIFGrammarOption;
  int                       exiti;

  marpaESLIFOption.genericLoggerp = GENERICLOGGER_NEW(GENERICLOGGER_LOGLEVEL_DEBUG);
  marpaESLIFp = marpaESLIF_newp(&marpaESLIFOption);
  if (marpaESLIFp == NULL) {
    goto err;
  }

  helpers = marpaESLIF_generateHelper(marpaESLIFp, marpaESLIF_grammarp(marpaESLIFp));
  if (helpers == NULL) {
    goto err;
  }
  fprintf(stdout, "%s", helpers);
  goto done;

  marpaESLIFGrammarOption.grammars            = (char *) metags;
  marpaESLIFGrammarOption.grammarl            = strlen(metags);
  marpaESLIFGrammarOption.encodings           = NULL;
  marpaESLIFGrammarOption.encodingl           = 0;
  marpaESLIFGrammarOption.encodingOfEncodings = NULL;
  marpaESLIFGrammarp = marpaESLIFGrammar_newp(marpaESLIFp, &marpaESLIFGrammarOption);
  if (marpaESLIFGrammarp == NULL) {
    goto err;
  }

  exiti = 0;
  goto done;
  
 err:
  exiti = 1;

 done:
  if (helpers != NULL) {
    free(helpers);
  }
  marpaESLIFGrammar_freev(marpaESLIFGrammarp);
  marpaESLIF_freev(marpaESLIFp);

  GENERICLOGGER_FREE(marpaESLIFOption.genericLoggerp);
  return exiti;
}
