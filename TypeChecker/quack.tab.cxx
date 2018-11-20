// A Bison parser, made by GNU Bison 3.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "quack.tab.cxx" // lalr1.cc:407

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "quack.tab.hxx"

// User implementation prologue.

#line 51 "quack.tab.cxx" // lalr1.cc:415
// Unqualified %code blocks.
#line 28 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:416

    #include "lex.yy.h"
    #undef yylex
    #define yylex lexer.yylex  /* Within bison's parse() we should invoke lexer.yylex(), not the global yylex() */
    void dump(AST::ASTNode* n);


#line 61 "quack.tab.cxx" // lalr1.cc:416


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 156 "quack.tab.cxx" // lalr1.cc:491

  /// Build a parser object.
  parser::parser (yy::Lexer& lexer_yyarg, AST::ASTNode** root_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      root (root_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value (other.value)
    , location (other.location)
  {
  }

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    value = that.value;
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.value, that.location)
  {
    // that is emptied.
    that.type = empty_symbol;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  parser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 83 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {*root = (yystack_[0].value.classes);}
#line 580 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 3:
#line 86 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.classes) = new AST::Classes();(yylhs.value.classes) ->append((yystack_[0].value.clazz));}
#line 586 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 4:
#line 87 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yystack_[1].value.classes)->append((yystack_[0].value.clazz)); (yylhs.value.classes) = (yystack_[1].value.classes);}
#line 592 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 5:
#line 88 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yystack_[1].value.classes)->append((yystack_[0].value.statement)); (yylhs.value.classes) = (yystack_[1].value.classes);}
#line 598 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 6:
#line 89 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.classes) = new AST::Classes();}
#line 604 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 7:
#line 92 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { 
                                                  AST::Ident* class_name = new AST::Ident((yystack_[7].value.str));
                                                  (yylhs.value.clazz) = new AST::Class(*class_name,*(yystack_[5].value.actuals),*(yystack_[3].value.ident),*(yystack_[1].value.block));
                                                  }
#line 613 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 8:
#line 97 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.ident) = new AST::Ident((yystack_[0].value.str));}
#line 619 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 9:
#line 98 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.ident) = new AST::Ident("Nothing");}
#line 625 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 10:
#line 103 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.actuals) = new AST::Actuals(); 
                              AST::Ident* id1 = new AST::Ident((yystack_[2].value.str)); 
                              AST::Ident* id2 = new AST::Ident((yystack_[0].value.str)); 
                              (yylhs.value.actuals)->append(new AST::Argus(*id1,*id2));
                            }
#line 635 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 11:
#line 108 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yystack_[4].value.actuals)->append(new AST::Argus(*new AST::Ident((yystack_[2].value.str)),*new AST::Ident((yystack_[0].value.str)))); (yylhs.value.actuals) = (yystack_[4].value.actuals);}
#line 641 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 12:
#line 109 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.actuals) = new AST::Actuals();}
#line 647 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 13:
#line 112 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yystack_[1].value.block)->append((yystack_[0].value.statement)); (yylhs.value.block) = (yystack_[1].value.block);}
#line 653 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 14:
#line 113 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.block) = new AST::Block(); (yylhs.value.block)->append((yystack_[0].value.statement));}
#line 659 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 15:
#line 114 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block();}
#line 665 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 16:
#line 117 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { AST::Ident* method_name = new AST::Ident((yystack_[7].value.str));
                                                                          (yylhs.value.method) = new AST::Method(*method_name,*(yystack_[5].value.actuals),*(yystack_[3].value.ident),*(yystack_[1].value.block));
                                                                  }
#line 673 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 17:
#line 121 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.ident) = new AST::Ident((yystack_[0].value.str));}
#line 679 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 18:
#line 122 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.ident) = new AST::Ident("Nothing");}
#line 685 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 19:
#line 125 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yystack_[1].value.block)->append((yystack_[0].value.statement)); (yylhs.value.block) = (yystack_[1].value.block);}
#line 691 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 20:
#line 126 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block(); (yylhs.value.block)->append((yystack_[0].value.statement));}
#line 697 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 21:
#line 127 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block();}
#line 703 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 22:
#line 130 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { }
#line 709 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 23:
#line 131 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.statement) = new AST::Statement(*new AST::Assign(*new AST::TypeExtend(*(yystack_[5].value.l_expr),*new AST::Ident((yystack_[3].value.str))), *(yystack_[1].value.node)));}
#line 715 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 24:
#line 132 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.statement) = new AST::Statement(*new AST::Assign(*(yystack_[3].value.l_expr), *(yystack_[1].value.node)));}
#line 721 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 25:
#line 133 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.statement) = new AST::Statement(*(yystack_[1].value.node));}
#line 727 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 26:
#line 134 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.statement) = new AST::Statement(*new AST::Return_opt(*(yystack_[1].value.node)));}
#line 733 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 27:
#line 135 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.statement) = new AST::Statement(*new AST::Return_opt(*new AST::Ident("Nothing")));}
#line 739 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 28:
#line 136 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.statement) = new AST::Statement(*(yystack_[0].value.node));}
#line 745 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 29:
#line 137 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.statement) = new AST::Statement(*(yystack_[0].value.node));}
#line 751 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 30:
#line 138 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.statement) = new AST::Statement(*new AST::While(*(yystack_[4].value.node),*(yystack_[1].value.block)));}
#line 757 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 31:
#line 139 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.statement) = new AST::Statement(*(yystack_[0].value.method));}
#line 763 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 32:
#line 142 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.l_expr) = new AST::Ident(std::string((yystack_[0].value.str))); dump((yylhs.value.l_expr)); }
#line 769 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 33:
#line 143 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.l_expr) = new AST::Dot(*(yystack_[2].value.node),*new AST::Ident((yystack_[0].value.str)));}
#line 775 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 34:
#line 146 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::TypeCase(*(yystack_[3].value.node),*(yystack_[1].value.block));}
#line 781 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 35:
#line 148 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block(); (yylhs.value.block)-> append(new AST::Type_Alternatives(*new AST::Ident((yystack_[5].value.str)),*new AST::Ident((yystack_[3].value.str)),*(yystack_[1].value.block)));}
#line 787 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 36:
#line 149 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yystack_[6].value.block)-> append(new AST::Type_Alternatives(*new AST::Ident((yystack_[5].value.str)),*new AST::Ident((yystack_[3].value.str)),*(yystack_[1].value.block))); (yylhs.value.block) = (yystack_[6].value.block);}
#line 793 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 37:
#line 150 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block();}
#line 799 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 38:
#line 153 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::If(*(yystack_[8].value.node), *(yystack_[6].value.block), *(yystack_[4].value.block), *(yystack_[1].value.block));}
#line 805 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 39:
#line 154 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::If(*(yystack_[4].value.node), *(yystack_[2].value.block), *(yystack_[0].value.block), *new AST::Block());}
#line 811 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 40:
#line 157 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block(); AST::ASTNode *if_stm = new AST::If(*(yystack_[4].value.node), *(yystack_[2].value.block), *(yystack_[0].value.block), *new AST::Block()); (yylhs.value.block)->append(if_stm);}
#line 817 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 41:
#line 158 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block();}
#line 823 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 42:
#line 162 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block(); (yylhs.value.block) ->append((yystack_[0].value.node));}
#line 829 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 43:
#line 163 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.block) = new AST::Block();}
#line 835 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 44:
#line 164 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yystack_[2].value.block)->append((yystack_[0].value.node)); (yylhs.value.block) = (yystack_[2].value.block);}
#line 841 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 45:
#line 167 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.l_expr);}
#line 847 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 46:
#line 168 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.node) = new AST::Plus( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 853 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 47:
#line 169 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.node) = new AST::Minus( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 859 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 48:
#line 170 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.node) = new AST::Times( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 865 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 49:
#line 171 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.node) = new AST::Div( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 871 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 50:
#line 172 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Large( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 877 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 51:
#line 173 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Less( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 883 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 52:
#line 174 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Atleast( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 889 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 53:
#line 175 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Atmost( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 895 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 54:
#line 176 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Equals( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 901 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 55:
#line 177 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::And( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 907 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 56:
#line 178 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Or( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 913 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 57:
#line 179 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Not( *(yystack_[2].value.node), *(yystack_[0].value.node) ); dump((yylhs.value.node));}
#line 919 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 58:
#line 180 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {}
#line 925 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 59:
#line 181 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Method_call(*new AST::Ident((yystack_[3].value.str)),*(yystack_[1].value.block));}
#line 931 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 60:
#line 182 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::Dot(*(yystack_[5].value.node),*new AST::Method_call(*new AST::Ident((yystack_[3].value.str)),*(yystack_[1].value.block)));}
#line 937 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 61:
#line 183 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[1].value.node); }
#line 943 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 62:
#line 184 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::IntConst((yystack_[0].value.num)); dump((yylhs.value.node));}
#line 949 "quack.tab.cxx" // lalr1.cc:870
    break;

  case 63:
#line 185 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:870
    {(yylhs.value.node) = new AST::StringConst((yystack_[0].value.str)); dump((yylhs.value.node));}
#line 955 "quack.tab.cxx" // lalr1.cc:870
    break;


#line 959 "quack.tab.cxx" // lalr1.cc:870
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -79;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -10,     0,    20,    81,   -79,    -1,   -79,   -79,     3,   -79,
      53,     4,    24,    53,    44,    53,    53,   -79,   -79,   -79,
      -4,   -79,   -79,   253,    32,    53,   -79,   275,    53,    14,
     297,   -79,   319,   438,   341,    40,    53,    53,    53,    53,
      53,    53,    53,   -79,    49,    53,    53,    53,    53,    53,
      53,    28,   -14,   -13,   438,   473,   363,    32,    55,   -79,
     -79,    31,   372,   438,   438,   438,   438,   438,   438,    38,
     438,   438,   438,   438,   438,   438,    58,    50,    60,   -79,
      53,   137,   -79,    43,   -12,    42,    -2,    53,   -79,    53,
     -79,    61,    45,    52,   438,    64,   -79,   473,    54,    68,
      62,   -79,   394,   -11,   -79,   473,    73,    53,    80,   152,
      86,    72,    74,    94,   -79,   -79,   167,   -79,   -79,   416,
      76,   -79,   -79,   473,   473,    83,   -79,   -79,   473,   473,
     182,   197,   473,   212,   227,   -79,   -79,   242,    64,   -79,
     -79,   -79
  };

  const unsigned char
  parser::yydefact_[] =
  {
       6,     0,     0,     2,     3,     0,     1,    63,    32,    62,
       0,     0,     0,     0,     0,     0,     0,     4,    31,     5,
      45,    29,    28,     0,    12,    43,    45,     0,     0,     0,
       0,    27,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    21,     0,    12,    37,    26,
      61,     0,     0,    52,    53,    54,    55,    56,    57,    33,
      46,    47,    48,    49,    50,    51,     0,     9,     0,    59,
       0,     0,    20,     0,     0,     0,     0,     0,    24,    43,
      10,     0,     0,     0,    44,    41,    19,    21,    18,     0,
       0,    34,     0,     0,     8,    15,     0,     0,    39,     0,
       0,     0,     0,     0,    23,    60,     0,    14,    11,     0,
       0,    30,    17,    21,    21,     0,     7,    13,    21,    21,
       0,     0,    21,     0,     0,    16,    35,     0,    41,    38,
      36,    40
  };

  const signed char
  parser::yypgoto_[] =
  {
     -79,   -79,   -79,   102,   -79,    57,   -79,   -79,   -79,   -78,
       2,    -3,   -79,   -79,   -79,   -29,    21,    -7
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,    92,    52,   116,    18,   111,    81,
      82,    26,    21,    86,    22,   108,    53,    23
  };

  const unsigned char
  parser::yytable_[] =
  {
      20,     1,   100,    27,     5,    19,    30,    32,    33,    34,
      77,    79,    98,   115,    78,    80,    78,    80,    54,   109,
       6,    56,    24,    35,   101,    36,    25,    28,    29,    62,
      63,    64,    65,    66,    67,    68,    51,    57,    70,    71,
      72,    73,    74,    75,    61,   130,   131,     7,     8,     9,
     133,   134,    20,    69,   137,    76,     7,     8,     9,    85,
      87,    89,    90,    91,    93,   104,    15,    16,    97,    99,
     105,   107,   112,    94,    31,    15,    16,   118,    20,   106,
     102,   110,    54,    96,     7,     8,     9,    10,   120,   113,
     122,    11,     1,    12,    20,    13,    14,   123,   125,   124,
     119,   129,    20,    15,    16,    17,    20,   117,   132,   141,
     103,    96,     0,    20,    84,     0,     0,     0,   127,     0,
      20,    20,     0,     0,     0,    20,    20,    20,    20,    20,
      20,    20,    96,    96,    20,    96,    96,     0,     0,    96,
       7,     8,     9,    10,     0,     0,     0,    11,     0,    12,
       0,    13,    14,     0,     0,     7,     8,     9,    10,    15,
      16,     0,    11,    95,    12,     0,    13,    14,     0,     0,
       7,     8,     9,    10,    15,    16,     0,    11,   121,    12,
       0,    13,    14,     0,     0,     7,     8,     9,    10,    15,
      16,     0,    11,   126,    12,     0,    13,    14,     0,     0,
       7,     8,     9,    10,    15,    16,     0,    11,   135,    12,
       0,    13,    14,     0,     0,     7,     8,     9,    10,    15,
      16,     0,    11,   136,    12,     0,    13,    14,     0,     0,
       7,     8,     9,    10,    15,    16,     0,    11,   138,    12,
       0,    13,    14,     0,     0,     7,     8,     9,    10,    15,
      16,     0,    11,   139,    12,     0,    13,    14,     0,     0,
       0,     0,     0,     0,    15,    16,     0,     0,   140,    37,
      38,    39,    40,    41,    42,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,    49,
      50,    37,    38,    39,    40,    41,    42,     0,     0,     0,
      55,     0,     0,     0,     0,     0,    44,    45,    46,    47,
      48,    49,    50,    37,    38,    39,    40,    41,    42,     0,
       0,     0,    58,     0,     0,     0,     0,     0,    44,    45,
      46,    47,    48,    49,    50,    37,    38,    39,    40,    41,
      42,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      44,    45,    46,    47,    48,    49,    50,    37,    38,    39,
      40,    41,    42,     0,     0,    60,     0,     0,     0,     0,
       0,     0,    44,    45,    46,    47,    48,    49,    50,    37,
      38,    39,    40,    41,    42,     0,     0,    83,    37,    38,
      39,    40,    41,    42,    44,    45,    46,    47,    48,    49,
      50,     0,    88,    44,    45,    46,    47,    48,    49,    50,
      37,    38,    39,    40,    41,    42,     0,     0,     0,     0,
       0,     0,     0,     0,   114,    44,    45,    46,    47,    48,
      49,    50,    37,    38,    39,    40,    41,    42,     0,     0,
       0,   128,     0,     0,     0,     0,     0,    44,    45,    46,
      47,    48,    49,    50,    37,    38,    39,    40,    41,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    46,    47,    48,    49,    50,     7,     8,     9,    10,
       0,     0,     0,    11,     0,    12,     0,    13,    14,     0,
       0,     0,     0,     0,     0,    15,    16
  };

  const short
  parser::yycheck_[] =
  {
       3,    11,     4,    10,     4,     3,    13,    14,    15,    16,
      24,    24,    24,    24,    28,    28,    28,    28,    25,    97,
       0,    28,    23,    27,    26,    29,    23,    23,     4,    36,
      37,    38,    39,    40,    41,    42,     4,    23,    45,    46,
      47,    48,    49,    50,     4,   123,   124,     3,     4,     5,
     128,   129,    55,     4,   132,    27,     3,     4,     5,     4,
      29,    23,     4,    13,     4,     4,    22,    23,    25,    27,
      25,     7,     4,    80,    30,    22,    23,     4,    81,    27,
      87,    27,    89,    81,     3,     4,     5,     6,     8,    27,
       4,    10,    11,    12,    97,    14,    15,    25,     4,    25,
     107,    25,   105,    22,    23,     3,   109,   105,    25,   138,
      89,   109,    -1,   116,    57,    -1,    -1,    -1,   116,    -1,
     123,   124,    -1,    -1,    -1,   128,   129,   130,   131,   132,
     133,   134,   130,   131,   137,   133,   134,    -1,    -1,   137,
       3,     4,     5,     6,    -1,    -1,    -1,    10,    -1,    12,
      -1,    14,    15,    -1,    -1,     3,     4,     5,     6,    22,
      23,    -1,    10,    26,    12,    -1,    14,    15,    -1,    -1,
       3,     4,     5,     6,    22,    23,    -1,    10,    26,    12,
      -1,    14,    15,    -1,    -1,     3,     4,     5,     6,    22,
      23,    -1,    10,    26,    12,    -1,    14,    15,    -1,    -1,
       3,     4,     5,     6,    22,    23,    -1,    10,    26,    12,
      -1,    14,    15,    -1,    -1,     3,     4,     5,     6,    22,
      23,    -1,    10,    26,    12,    -1,    14,    15,    -1,    -1,
       3,     4,     5,     6,    22,    23,    -1,    10,    26,    12,
      -1,    14,    15,    -1,    -1,     3,     4,     5,     6,    22,
      23,    -1,    10,    26,    12,    -1,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    26,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    37,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    16,    17,    18,
      19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    16,
      17,    18,    19,    20,    21,    -1,    -1,    24,    16,    17,
      18,    19,    20,    21,    31,    32,    33,    34,    35,    36,
      37,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,     3,     4,     5,     6,
      -1,    -1,    -1,    10,    -1,    12,    -1,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    39,    40,    41,     4,     0,     3,     4,     5,
       6,    10,    12,    14,    15,    22,    23,    41,    45,    48,
      49,    50,    52,    55,    23,    23,    49,    55,    23,     4,
      55,    30,    55,    55,    55,    27,    29,    16,    17,    18,
      19,    20,    21,    30,    31,    32,    33,    34,    35,    36,
      37,     4,    43,    54,    55,    25,    55,    23,    25,    30,
      24,     4,    55,    55,    55,    55,    55,    55,    55,     4,
      55,    55,    55,    55,    55,    55,    27,    24,    28,    24,
      28,    47,    48,    24,    43,     4,    51,    29,    30,    23,
       4,    13,    42,     4,    55,    26,    48,    25,    24,    27,
       4,    26,    55,    54,     4,    25,    27,     7,    53,    47,
      27,    46,     4,    27,    30,    24,    44,    48,     4,    55,
       8,    26,     4,    25,    25,     4,    26,    48,    25,    25,
      47,    47,    25,    47,    47,    26,    26,    47,    26,    26,
      26,    53
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    38,    39,    40,    40,    40,    40,    41,    42,    42,
      43,    43,    43,    44,    44,    44,    45,    46,    46,    47,
      47,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    49,    49,    50,    51,    51,    51,    52,    52,
      53,    53,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     0,     9,     2,     0,
       3,     5,     0,     2,     1,     0,     9,     2,     0,     2,
       1,     0,     0,     6,     4,     2,     3,     2,     1,     1,
       7,     1,     1,     3,     5,     6,     7,     0,    10,     6,
       6,     0,     1,     0,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     4,
       6,     3,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "STRING_LIT", "IDENT", "INT_LIT", "IF",
  "ELIF", "ELSE", "FI", "WHILE", "CLASS", "DEF", "EXTENDS", "TYPECASE",
  "RETURN", "ATLEAST", "ATMOST", "EQUALS", "AND", "OR", "NOT", "NEG",
  "'('", "')'", "'{'", "'}'", "':'", "','", "'='", "';'", "'.'", "'+'",
  "'-'", "'*'", "'/'", "'>'", "'<'", "$accept", "program", "classes",
  "class", "classExtends", "class_args", "block", "method", "method_type",
  "stmt_block", "stmt", "l_expr", "type_case", "type_alternative",
  "if_stmt", "elif_stmt", "actual_args", "r_expr", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    83,    83,    86,    87,    88,    89,    92,    97,    98,
     103,   108,   109,   112,   113,   114,   117,   121,   122,   125,
     126,   127,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   142,   143,   146,   148,   149,   150,   153,   154,
     157,   158,   162,   163,   164,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      23,    24,    34,    32,    28,    33,    31,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,    30,
      37,    29,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22
    };
    const unsigned user_token_number_max_ = 277;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1448 "quack.tab.cxx" // lalr1.cc:1181
#line 193 "/Users/xunliu/Desktop/CIS561 git/TypeChecker/quack.yxx" // lalr1.cc:1182

#include "Messages.h"

void yy::parser::error(const location_type& loc, const std::string& msg)
 { 
  report::error_at(loc, msg);
 }

void dump(AST::ASTNode* n) {
    // std::cout << "*** Building: " << n->str() << std::endl;
}
