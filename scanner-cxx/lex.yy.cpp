// lex.yy.cpp generated by reflex 1.0.9 from quack.lxx

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_YYLTYPE             yy::location
#define REFLEX_OPTION_YYSTYPE             yy::parser::semantic_type
#define REFLEX_OPTION_bison_cc            true
#define REFLEX_OPTION_bison_cc_namespace  yy
#define REFLEX_OPTION_bison_cc_parser     parser
#define REFLEX_OPTION_bison_locations     true
#define REFLEX_OPTION_header_file         lex.yy.h
#define REFLEX_OPTION_lex                 yylex
#define REFLEX_OPTION_lexer               Lexer
#define REFLEX_OPTION_namespace           yy
#define REFLEX_OPTION_noyywrap            true
#define REFLEX_OPTION_outfile             lex.yy.cpp

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top{ user code %}                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "quack.lxx"

 /* Quack scanner
 *
 * 2018 Fall version for RE/flex,
 * skeleton.
 *
 */

#include "quack.tab.hxx"  /* Generated by bison. */
#include "Messages.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  ABSTRACT LEXER CLASS                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/abslexer.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  LEXER CLASS                                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

namespace yy {

class Lexer : public reflex::AbstractLexer<reflex::Matcher> {
 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  Lexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
  }
  static const int INITIAL = 0;
  static const int comment = 1;
  static const int s_comment = 2;
  static const int d_quote_str = 3;
  static const int s_quote_str = 4;
  static const int quote_str = 5;
  virtual int yylex(yy::parser::semantic_type *yylval, yy::location *yylloc)
  {
    yylloc->step();
    int ret = yylex(*yylval);
    yylloc->end.line = matcher().lineno();
    yylloc->end.column = matcher().columno();
    return ret;
  }
  virtual int yylex(yy::parser::semantic_type& yylval);
};

} // namespace yy

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 15 "quack.lxx"

/* Externally visible file name --
* for error messages.
* FIXME: Need to extract this from structures that reflex passes
* or else find another way to dig it out.
*/
std::string yyfilename = "What file is this, anyway?";

/* Some strings can't be matched in one gulp.  We need
 * a buffer in which to assemble them from parts.
 */
std::string string_buf = "";

void yyerror (const std::string &msg, yy::position* where) {
     std::cout << where << ": " << msg;
}

/* Some long messages that don't fit well in the code below */

std::string BAD_ESC_MSG =
  "Illegal escape code; only \\\\, \\0, \\t, \\n, \\r, \\n are permitted";
std::string BAD_NL_STR =
  "Unclosed string?  Encountered newline in quoted string.";


#line 45 "quack.lxx"
/* You'll probably want scanner states for both multi-line
   * comments and for triple-quote strings.  Do comments first,
   * because they're easier (you just throw away the text).  Then
   * do triple-quote strings.  You might consider doing the same for
   * normal strings with a single pair of double quotes, to avoid
   * writing a really ugly regex.  'comment' here is an example of
   * how to declare an exclusive scanner state.
   */
#line 63 "quack.lxx"
/*word (\w|\h\w)+*/


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  BISON C++                                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 2: rules                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int yy::Lexer::yylex(yy::parser::semantic_type& yylval)
{
  static const reflex::Pattern PATTERN_INITIAL("(?m)(==)|([<]=)|([>]=)|([*+\\x2d/])|([<>])|([\\x2e])|([=])|([\\x7b\\x7d])|([;])|([()])|([,])|(class)|(def)|(extends)|(if)|(elif)|(else)|(while)|(return)|(typecase)|([0-9]+)|([\\x09\\x0a\\x20]*)|([/][\\x2a])|([/][/])|([\"])|(['])|((?:[A-Z_a-z]+_*[0-9A-Z_a-z]*))|([:][\\x09\\x20\\x2a](?:[A-Z_a-z]+_*[0-9A-Z_a-z]*))|(.)");
  static const reflex::Pattern PATTERN_comment("(?m)([^\\x2a]*)|([\\x2a][^/])|([\\x2a][/])");
  static const reflex::Pattern PATTERN_s_comment("(?m)([\\x0a])|([^/])");
  static const reflex::Pattern PATTERN_d_quote_str("(?m)((?:[\"](?:\\w|\\h\\w)+[\"]))|([\"](?:[\"](?:\\w|\\h\\w)+[\"])[\"])|([\\x0a])|([\"])|([^/])");
  static const reflex::Pattern PATTERN_s_quote_str("(?m)([\\x0a])|(['])|([^/])");
  static const reflex::Pattern PATTERN_quote_str("(?m)");
  if (!has_matcher())
  {
    matcher(new Matcher(PATTERN_INITIAL, stdinit(), this));
  }
  switch (start())
  {
    case INITIAL:
#line 72 "quack.lxx"
/* We start with some tokens that are not value-bearing,
   * i.e., the parser needs to know only which token was matched.
   */

  /* Multi-character punctuation with names */
    break;
  }
  while (true)
  {
    switch (start())
    {
      case INITIAL:
        matcher().pattern(PATTERN_INITIAL);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
#line 175 "quack.lxx"
{ return EOF; }

            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 72: ==
#line 72 "quack.lxx"
{ return parser::token::EQUALS; }
            break;
          case 2: // rule at line 73: [<]=
#line 73 "quack.lxx"
{ return parser::token::ATMOST; }
            break;
          case 3: // rule at line 74: [>]=
#line 74 "quack.lxx"
{ return parser::token::ATLEAST; }


   /* Single character punctuation.  Because a character
    * in C or C++ can be treated as an integer, Bison lets
    * us return a character as a token.
    * JFlex/Cup do not let you do this in Java.
    * Here are a few ... there are more.
    */
            break;
          case 4: // rule at line 83: [*+\x2d/]
#line 83 "quack.lxx"
{ return text()[0];}
            break;
          case 5: // rule at line 84: [<>]
#line 84 "quack.lxx"
{ return text()[0];}
            break;
          case 6: // rule at line 85: [\x2e]
#line 85 "quack.lxx"
{return text()[0];}
            break;
          case 7: // rule at line 86: [=]
#line 86 "quack.lxx"
{return text()[0];}
            break;
          case 8: // rule at line 87: [\x7b\x7d]
#line 87 "quack.lxx"
{return text()[0];}
            break;
          case 9: // rule at line 88: [;]
#line 88 "quack.lxx"
{return text()[0];}
            break;
          case 10: // rule at line 89: [()]
#line 89 "quack.lxx"
{return text()[0];}
            break;
          case 11: // rule at line 90: [,]
#line 90 "quack.lxx"
{return text()[0];}


  /* Keywords are essentially another kind of punctuation,
   * but since they also match the identifier pattern, we
   * need to be sure we give their patterns *before* the
   * identifier pattern.  Most scanner generators work this
   * way, but WARNING for Python PLY users:  PLY prioritizes
   * by length of the regular expression!
   * Here are a couple of examples.
   */

            break;
          case 12: // rule at line 102: class
#line 102 "quack.lxx"
{ return parser::token::CLASS;}
            break;
          case 13: // rule at line 103: def
#line 103 "quack.lxx"
{ return parser::token::DEF;}
            break;
          case 14: // rule at line 104: extends
#line 104 "quack.lxx"
{ return parser::token::EXTENDS;}
            break;
          case 15: // rule at line 105: if
#line 105 "quack.lxx"
{ return parser::token::IF;}
            break;
          case 16: // rule at line 106: elif
#line 106 "quack.lxx"
{ return parser::token::ELIF;}
            break;
          case 17: // rule at line 107: else
#line 107 "quack.lxx"
{ return parser::token::ELSE;}
            break;
          case 18: // rule at line 108: while
#line 108 "quack.lxx"
{return parser::token::WHILE;}
            break;
          case 19: // rule at line 109: return
#line 109 "quack.lxx"
{ return parser::token::RETURN;}
            break;
          case 20: // rule at line 110: typecase
#line 110 "quack.lxx"
{ return parser::token::TYPECASE;}


   /* The following tokens are value-bearing:
    * We pass a value back to the parser by copying
    * it into the yylval parameter.  The parser
    * expects string values for identifiers and
    * string literals in yylval.str.  It expects integer
    * values for integer literals in yylval.num.
    * I'll give pattern for integer literals.
    * You'll need another for identifiers.  Remember to
    * 'strdup' the value returned by 'text()', or else it will
    * be clobbered by subsequent calls.
    */

            break;
          case 21: // rule at line 125: [0-9]+
#line 125 "quack.lxx"
{ yylval.num = atoi(text()); cout<<yylval.num<<"           ";return parser::token::INT_LIT; }

  /* You *can* write a one-line regular expression for matching a quoted string,
   * but you probably can't read it.  (I can't read mine.)  Scanner states and
   * simpler patterns are probably a better idea.
   * You almost certainly scanner states for triple quotes.
   * The tricky bit is catching errors, such as disallowed escape sequences
   * and unclosed quotes.
   */

  /* Ignore whitespace */
            break;
          case 22: // rule at line 136: [\x09\x0a\x20]*
#line 136 "quack.lxx"
{ ; }

   /* Multi-line comments */
            break;
          case 23: // rule at line 139: [/][\x2a]
#line 139 "quack.lxx"
{ start(comment); }
            break;
          case 24: // rule at line 145: [/][/]
#line 145 "quack.lxx"
{start(s_comment);}
            break;
          case 25: // rule at line 150: ["]
#line 150 "quack.lxx"
{ start(d_quote_str); }
            break;
          case 26: // rule at line 158: [']
#line 158 "quack.lxx"
{ start(s_quote_str); }
            break;
          case 27: // rule at line 164: (?:[A-Z_a-z]+_*[0-9A-Z_a-z]*)
#line 164 "quack.lxx"
{yylval.str = strdup(text());cout<<yylval.str<<"           ";return parser::token::IDENT;}
   /*single word as type*/
            break;
          case 28: // rule at line 166: [:][\x09\x20\x2a](?:[A-Z_a-z]+_*[0-9A-Z_a-z]*)
#line 166 "quack.lxx"
{string s= text(); s.erase(0,1);yylval.str = strdup(s.c_str());cout<<yylval.str<<"           ";return parser::token::TYPECASE; }


 /*otherwise, it must be an ERROR*/
            break;
          case 29: // rule at line 170: .
#line 170 "quack.lxx"
{   report::error("Unexpected character '" + std::string(text()) + "'" +
       " at line " + std::to_string(lineno()) +
       ", column " + std::to_string(columno()));
   }

            break;
        }
        break;
      case comment:
        matcher().pattern(PATTERN_comment);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
#line 175 "quack.lxx"
{ return EOF; }

            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 140: [^\x2a]*
#line 140 "quack.lxx"
{ ; }
            break;
          case 2: // rule at line 141: [\x2a][^/]
#line 141 "quack.lxx"
{ ; }
            break;
          case 3: // rule at line 142: [\x2a][/]
#line 142 "quack.lxx"
{ start(INITIAL); }

   /*single-line comments*/
            break;
        }
        break;
      case s_comment:
        matcher().pattern(PATTERN_s_comment);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
#line 175 "quack.lxx"
{ return EOF; }

            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 146: [\x0a]
#line 146 "quack.lxx"
{ start(INITIAL); }
            break;
          case 2: // rule at line 147: [^/]
#line 147 "quack.lxx"
{;}

   /* double_quote strings */
            break;
        }
        break;
      case d_quote_str:
        matcher().pattern(PATTERN_d_quote_str);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
#line 175 "quack.lxx"
{ return EOF; }

            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 151: (?:["](?:\w|\h\w)+["])
#line 151 "quack.lxx"
{;}
            break;
          case 2: // rule at line 152: ["](?:["](?:\w|\h\w)+["])["]
#line 152 "quack.lxx"
{;}
            break;
          case 3: // rule at line 153: [\x0a]
#line 153 "quack.lxx"
{ report::error("DOUBLE QUOTATION ERROR at line: " + std::to_string(lineno()) + ", column: " + std::to_string(columno()));  start(INITIAL);}
            break;
          case 4: // rule at line 154: ["]
#line 154 "quack.lxx"
{ string s= text(); s.erase(0,1);yylval.str = strdup(s.c_str());cout<<yylval.str<<"           ";start(INITIAL);return parser::token::STRING_LIT; }
            break;
          case 5: // rule at line 155: [^/]
#line 155 "quack.lxx"
{;}

   /* single_quote strings */
            break;
        }
        break;
      case s_quote_str:
        matcher().pattern(PATTERN_s_quote_str);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
#line 175 "quack.lxx"
{ return EOF; }

            }
            else
            {
              out().put(matcher().input());
            }
            break;
          case 1: // rule at line 159: [\x0a]
#line 159 "quack.lxx"
{ report::error("SINGLE QUOTATION ERROR at line: " + std::to_string(lineno()) + ", column: " + std::to_string(columno()));  start(INITIAL);}
            break;
          case 2: // rule at line 160: [']
#line 160 "quack.lxx"
{ string s= text(); s.erase(0,1);yylval.str = strdup(s.c_str());cout<<yylval.str<<"           ";start(INITIAL);return parser::token::STRING_LIT; }
            break;
          case 3: // rule at line 161: [^/]
#line 161 "quack.lxx"
{;}

   /*single word as indentifier*/
            break;
        }
        break;
      case quote_str:
        matcher().pattern(PATTERN_quote_str);
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
#line 175 "quack.lxx"
{ return EOF; }

            }
            else
            {
              out().put(matcher().input());
            }
            break;
        }
        break;
      default:
        return 0;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 3: user code                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 178 "quack.lxx"

 /* No main program here */

