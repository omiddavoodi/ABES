
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 6 "a.y"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

struct var_block {
    std::string name;
    int stack_number;
    int block_number;
};

std::stack<std::string> whileStack;
std::stack<std::string> ifStack;
std::vector<std::string> vars;
std::vector<var_block> var_blocks;
std::vector<std::string> funcs;
std::vector<std::string> procs;

int stack_top = -1;
int block_num = 0;

int currentparamcount = 0;

std::string result = "";
std::string subendlabel = "";
std::string substartlabel = "";


int tmpNum = 0;
int labelNum = 0;

std::string newLabel()
{
	char * g = new char[15];
	itoa (++labelNum, g, 10);
	return  std::string("?L") + std::string(g);
}

void removeTemp()
{
	--tmpNum;
}

std::string newTemp()
{
	char * g = new char[15];
	itoa (++tmpNum, g, 10);
	return  std::string("#T") + std::string(g);
}

bool isTemp(std::string s)
{
	if (s[0] == '#')
		return true;
	return false;
}

bool isVar(std::string s)
{
    return (s[0] < '0' || s[0] > '9');
}

void yyerror(char *);
int yylex(void);



std::string findInStack(std::string s)
{
    if (!isVar(s))
    {
        return s;
    }
    
    for (int i = var_blocks.size() - 1; i >= 0; --i)
    {
        if (var_blocks[i].name == s)
        {
            char * g = new char[15];
            itoa (stack_top - var_blocks[i].stack_number, g, 10);
            return std::string("[") + g + "]";
        }
    }
    yyerror((char *)(std::string("Unrecognized variable name ") + s).data());
    return "-1";
}

void add_var_to_stack(std::string s)
{
    var_block newvarblock;
    newvarblock.name = s;
    ++stack_top;
    newvarblock.stack_number = stack_top;
    newvarblock.block_number = block_num;
    var_blocks.push_back(newvarblock);
}

void remove_all_stack_with_block_num(int n)
{
    int num = 0;
    
    while(var_blocks[var_blocks.size()-1].block_number == n)
    {
        ++num;
        --stack_top;
        var_blocks.pop_back();
    }
    char * g = new char[15];
    itoa (num, g, 10);
	result += std::string("pop ") + g + "\n";
    
}


extern FILE * yyin;
extern FILE *fopen(const char *filename, const char *mode);



/* Line 189 of yacc.c  */
#line 197 "a.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF_T = 258,
     ELSE_T = 259,
     WHILE_T = 260,
     VAR_T = 261,
     INPUT_T = 262,
     PRINT_T = 263,
     VARNAME = 264,
     NUMBER = 265,
     PBAZZ = 266,
     PBASTE = 267,
     AND_T = 268,
     GTE_T = 269,
     LTE_T = 270,
     EQ_T = 271,
     NEQ_T = 272,
     GT_T = 273,
     LT_T = 274,
     BREAK_T = 275,
     CONTINUE_T = 276,
     FUNC_T = 277,
     PROC_T = 278,
     RETURN_T = 279
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 263 "a.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNRULES -- Number of states.  */
#define YYNSTATES  233

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,    36,     2,     2,
       2,     2,    34,    32,    28,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
       2,    31,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,    25,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    27,    29,    32,    34,    36,    38,    40,
      42,    44,    47,    49,    51,    53,    56,    58,    60,    62,
      64,    66,    68,    70,    72,    75,    77,    79,    81,    84,
      86,    88,    90,    92,    94,    96,    98,   101,   103,   106,
     108,   110,   112,   114,   116,   118,   120,   123,   124,   130,
     134,   136,   137,   141,   143,   145,   146,   147,   158,   159,
     160,   171,   175,   177,   178,   182,   184,   186,   189,   193,
     196,   199,   203,   207,   208,   209,   210,   222,   223,   224,
     225,   238,   240,   241,   242,   248,   249,   250,   251,   263,
     264,   265,   266,   279,   281,   282,   283,   289,   290,   291,
     292,   303,   308,   312,   318,   322,   326,   330,   332,   336,
     340,   344,   348,   352,   356,   358,   362,   366,   368,   372,
     376,   380,   382,   385,   387,   389,   391,   393
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    40,    39,    -1,    89,    -1,
      69,    -1,    94,    -1,    93,    -1,    67,    -1,    68,    -1,
      54,    -1,    57,    -1,    49,    27,    -1,    42,    -1,    42,
      41,    -1,    89,    -1,    69,    -1,    94,    -1,    93,    -1,
      67,    -1,    68,    -1,    49,    27,    -1,    64,    -1,    63,
      -1,    44,    -1,    44,    43,    -1,    89,    -1,    79,    -1,
      94,    -1,    93,    -1,    67,    -1,    68,    -1,    65,    -1,
      66,    -1,    49,    27,    -1,    64,    -1,    63,    -1,    46,
      -1,    46,    45,    -1,    89,    -1,    69,    -1,    94,    -1,
      93,    -1,    67,    -1,    68,    -1,    63,    -1,    49,    27,
      -1,    48,    -1,    48,    47,    -1,    89,    -1,    69,    -1,
      94,    -1,    93,    -1,    67,    -1,    68,    -1,    64,    -1,
      49,    27,    -1,    -1,     9,    50,    11,    51,    12,    -1,
      52,    28,    53,    -1,    53,    -1,    -1,    52,    28,    53,
      -1,    53,    -1,    95,    -1,    -1,    -1,    22,     9,    11,
      61,    12,    55,    29,    56,    47,    30,    -1,    -1,    -1,
      23,     9,    11,    60,    12,    58,    29,    59,    45,    30,
      -1,    61,    28,    62,    -1,    62,    -1,    -1,    61,    28,
      62,    -1,    62,    -1,     9,    -1,    24,    27,    -1,    24,
      95,    27,    -1,    20,    27,    -1,    21,    27,    -1,     8,
       9,    27,    -1,     7,     9,    27,    -1,    -1,    -1,    -1,
       3,    11,    95,    12,    70,    29,    71,    41,    30,    72,
      73,    -1,    -1,    -1,    -1,     4,     3,    11,    95,    12,
      74,    29,    75,    41,    30,    76,    73,    -1,    77,    -1,
      -1,    -1,     4,    29,    78,    41,    30,    -1,    -1,    -1,
      -1,     3,    11,    95,    12,    80,    29,    81,    43,    30,
      82,    83,    -1,    -1,    -1,    -1,     4,     3,    11,    95,
      12,    84,    29,    85,    43,    30,    86,    83,    -1,    87,
      -1,    -1,    -1,     4,    29,    88,    43,    30,    -1,    -1,
      -1,    -1,     5,    90,    11,    95,    12,    91,    29,    92,
      43,    30,    -1,     9,    31,    95,    27,    -1,     6,     9,
      27,    -1,     6,     9,    31,    95,    27,    -1,    95,    13,
      95,    -1,    95,    25,    95,    -1,    95,    26,    95,    -1,
      96,    -1,    96,    18,    97,    -1,    96,    19,    97,    -1,
      96,    15,    97,    -1,    96,    14,    97,    -1,    96,    16,
      97,    -1,    96,    17,    97,    -1,    97,    -1,    97,    32,
      98,    -1,    97,    33,    98,    -1,    98,    -1,    98,    34,
      99,    -1,    98,    35,    99,    -1,    98,    36,    99,    -1,
      99,    -1,    37,    99,    -1,    49,    -1,   100,    -1,     9,
      -1,    10,    -1,    11,    95,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   130,   130,   130,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   132,   132,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   136,   136,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138,   139,
     139,   139,   139,   139,   139,   139,   139,   142,   141,   202,
     202,   202,   204,   204,   206,   231,   239,   228,   269,   278,
     265,   299,   299,   299,   301,   301,   303,   308,   322,   352,
     359,   368,   373,   375,   393,   403,   375,   413,   429,   439,
     413,   449,   450,   457,   455,   480,   498,   508,   480,   518,
     534,   544,   518,   554,   555,   562,   560,   582,   589,   609,
     582,   630,   648,   655,   680,   718,   754,   790,   792,   828,
     864,   900,   936,   972,  1008,  1010,  1046,  1082,  1084,  1120,
    1156,  1192,  1193,  1214,  1221,  1222,  1223,  1224
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF_T", "ELSE_T", "WHILE_T", "VAR_T",
  "INPUT_T", "PRINT_T", "VARNAME", "NUMBER", "PBAZZ", "PBASTE", "AND_T",
  "GTE_T", "LTE_T", "EQ_T", "NEQ_T", "GT_T", "LT_T", "BREAK_T",
  "CONTINUE_T", "FUNC_T", "PROC_T", "RETURN_T", "'|'", "'^'", "';'", "','",
  "'{'", "'}'", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "$accept",
  "p", "s", "pi", "si", "wp", "ws", "procp", "procs", "funcp", "funcs",
  "CALL_S", "$@1", "PARAMS_S", "PARAMS", "PARAM", "FUNC_S", "$@2", "$@3",
  "PROC_S", "$@4", "$@5", "ARGS_S", "ARGS", "ARG", "RETURN_S",
  "FUNC_RETURN_S", "BREAK_S", "CONTINUE_S", "PRINT_S", "INPUT_S", "IF_S",
  "$@6", "$@7", "$@8", "ELSEIF_ST", "$@9", "$@10", "$@11", "ELSE_ST",
  "$@12", "IF_W_S", "$@13", "$@14", "$@15", "ELSEIF_W_ST", "$@16", "$@17",
  "$@18", "ELSE_W_ST", "$@19", "WHILE_S", "$@20", "$@21", "$@22", "ASS_S",
  "VAR_S", "EXP", "EXP1", "EXP2", "EXP3", "EXP4", "EXP5", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   124,    94,    59,    44,   123,
     125,    61,    43,    45,    42,    47,    37,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    43,    43,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    46,
      46,    46,    46,    46,    46,    46,    46,    47,    47,    48,
      48,    48,    48,    48,    48,    48,    48,    50,    49,    51,
      51,    51,    52,    52,    53,    55,    56,    54,    58,    59,
      57,    60,    60,    60,    61,    61,    62,    63,    64,    65,
      66,    67,    68,    70,    71,    72,    69,    74,    75,    76,
      73,    73,    73,    78,    77,    80,    81,    82,    79,    84,
      85,    86,    83,    83,    83,    88,    87,    90,    91,    92,
      89,    93,    94,    94,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    97,    98,    98,
      98,    98,    98,    99,    99,   100,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     5,     3,
       1,     0,     3,     1,     1,     0,     0,    10,     0,     0,
      10,     3,     1,     0,     3,     1,     1,     2,     3,     2,
       2,     3,     3,     0,     0,     0,    11,     0,     0,     0,
      12,     1,     0,     0,     5,     0,     0,     0,    11,     0,
       0,     0,    12,     1,     0,     0,     5,     0,     0,     0,
      10,     4,     3,     5,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     2,     1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   107,     0,     0,     0,    57,     0,     0,     0,
       2,     0,    10,    11,     8,     9,     5,     4,     7,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       3,    12,   135,   136,     0,     0,   133,     0,   117,   124,
     127,   131,   134,     0,   112,     0,    82,    81,     0,    61,
       0,    73,     0,   132,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   111,     0,     0,    60,    64,    76,     0,    75,     0,
       0,    72,   137,     0,   114,   115,   116,   121,   120,   122,
     123,   118,   119,   125,   126,   128,   129,   130,   108,   113,
      58,     0,    65,     0,    68,     0,    84,     0,    59,     0,
      74,     0,    71,     0,   109,    66,    69,     0,     0,    13,
       0,    23,    22,    19,    20,    16,    15,    18,    17,     0,
       0,     0,    77,     0,    85,    14,    21,     0,     0,     0,
       0,    24,     0,    36,    35,    32,    33,    30,    31,    27,
      26,    29,    28,     0,     0,    47,     0,    55,    53,    54,
      50,    49,    52,    51,     0,     0,    37,     0,    45,    43,
      44,    40,    39,    42,    41,    78,    92,     0,    79,    80,
     110,    25,    34,    67,    48,    56,    70,    38,    46,     0,
      86,    91,     0,     0,    93,    95,     0,     0,     0,     0,
       0,    96,    87,    94,     0,     0,     0,    88,    97,     0,
     104,     0,     0,    98,   103,    89,     0,   105,    92,     0,
       0,    90,     0,     0,    99,   106,     0,   100,     0,     0,
     101,   104,   102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,   118,   119,   140,   141,   165,   166,   154,
     155,    36,    26,    72,    73,    74,    12,   109,   130,    13,
     111,   131,    79,    77,    78,   143,   144,   145,   146,   147,
     148,   125,    83,   113,   176,   190,   205,   209,   218,   191,
     197,   149,   198,   204,   210,   213,   226,   228,   231,   214,
     220,   150,    21,   107,   129,   151,   152,    75,    38,    39,
      40,    41,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -134
static const yytype_int16 yypact[] =
{
     240,    11,  -134,    22,    35,    45,   -11,    47,    51,    62,
     240,    36,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
      27,    55,   -10,    42,    56,    27,    61,    63,    75,  -134,
    -134,  -134,    77,  -134,    27,    18,  -134,    86,   265,    -8,
     102,  -134,  -134,    27,  -134,    27,  -134,  -134,   154,    27,
      83,    83,   212,  -134,  -134,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    18,    18,    18,   241,
     190,  -134,    81,    72,    74,   101,  -134,    37,  -134,    92,
      82,    88,  -134,    89,  -134,  -134,  -134,    -8,    -8,    -8,
      -8,    -8,    -8,   102,   102,  -134,  -134,  -134,  -134,  -134,
    -134,    27,  -134,    83,  -134,    83,  -134,    91,    97,   115,
    -134,   119,   122,   100,  -134,  -134,  -134,    24,   123,   100,
     125,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,    70,
     183,   227,  -134,   243,  -134,  -134,  -134,   143,   129,   131,
     135,    70,   142,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,    27,   144,   183,   145,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,   146,   147,   227,   149,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,   179,    27,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,    10,
    -134,  -134,   246,   173,  -134,  -134,    27,   100,   164,   248,
     165,  -134,  -134,  -134,    70,   171,   175,  -134,  -134,   100,
     204,   180,    38,  -134,  -134,  -134,   201,  -134,   179,    27,
      70,  -134,   252,   184,  -134,  -134,   193,  -134,    70,   189,
    -134,   204,  -134
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,   213,  -134,  -113,  -134,  -133,  -134,    28,  -134,    71,
    -134,     0,  -134,  -134,  -134,   130,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,   191,   -48,  -108,  -112,  -134,  -134,     2,
       4,    16,  -134,  -134,  -134,    34,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,    19,  -134,  -134,  -134,  -134,
    -134,     9,  -134,  -134,  -134,    30,    32,    25,  -134,   228,
     -12,   -20,  -134
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -76
static const yytype_int16 yytable[] =
{
      11,   122,    14,    81,    15,   121,   135,   122,   181,    17,
      11,   121,    14,   193,    15,    53,    16,    44,   157,    17,
      25,    45,    20,   168,    64,    65,    16,    32,    33,    34,
      18,    22,    19,    32,    33,    34,    32,    33,    34,   194,
      18,   216,    19,   157,    23,    37,    95,    96,    97,   102,
      48,   132,    93,    94,    24,   110,    27,   112,   168,    52,
      28,    35,    29,    31,    35,   103,    43,   217,    69,    46,
      70,   206,    49,   137,    50,     2,     3,     4,     5,     6,
      84,    85,    86,    47,   200,   122,    51,   223,   -57,   121,
     138,   139,    76,   100,   117,   229,   211,   122,    54,    55,
     101,   121,   -63,     1,   104,     2,     3,     4,     5,     6,
     105,    56,    57,   120,    55,   123,   -75,   124,   106,   120,
     114,   123,   126,   124,   117,   -62,    56,    57,   126,   142,
     156,   167,   158,   169,   159,   170,    66,    67,    68,   161,
     172,   142,   133,   127,   115,   128,   160,   171,   116,   127,
     -74,   128,   136,   134,   177,   156,   178,   158,   179,   159,
     162,   173,   163,   174,   161,   180,   167,    55,   169,   182,
     170,   160,   185,   132,   183,   172,   188,   186,   133,    56,
      57,    71,   171,   189,   196,   162,     1,   163,     2,     3,
       4,     5,     6,   201,   187,   203,   173,   120,   174,   123,
     207,   124,   192,    55,   142,   208,   126,   153,   212,   120,
     215,   123,   219,   124,   225,    56,    57,    99,   126,   230,
     142,   199,   227,    30,    82,    55,   184,   127,   142,   128,
       1,   108,     2,     3,     4,     5,     6,    56,    57,   127,
       0,   128,    80,     1,   222,     2,     3,     4,     5,     6,
     232,   164,   221,    98,    55,     0,    55,     0,   195,    55,
     202,    55,     7,     8,   224,    55,    56,    57,    56,    57,
     175,    56,    57,    56,    57,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,     0,    87,    88,    89,    90,
      91,    92
};

static const yytype_int16 yycheck[] =
{
       0,   113,     0,    51,     0,   113,   119,   119,   141,     0,
      10,   119,    10,     3,    10,    35,     0,    27,   130,    10,
      31,    31,    11,   131,    32,    33,    10,     9,    10,    11,
       0,     9,     0,     9,    10,    11,     9,    10,    11,    29,
      10,     3,    10,   155,     9,    20,    66,    67,    68,    12,
      25,    27,    64,    65,     9,   103,     9,   105,   166,    34,
       9,    37,     0,    27,    37,    28,    11,    29,    43,    27,
      45,   204,    11,     3,    11,     5,     6,     7,     8,     9,
      55,    56,    57,    27,   197,   197,    11,   220,    11,   197,
      20,    21,     9,    12,    24,   228,   209,   209,    12,    13,
      28,   209,    28,     3,    12,     5,     6,     7,     8,     9,
      28,    25,    26,   113,    13,   113,    28,   113,    29,   119,
      29,   119,   113,   119,    24,    28,    25,    26,   119,   129,
     130,   131,   130,   131,   130,   131,    34,    35,    36,   130,
     131,   141,   117,   113,    29,   113,   130,   131,    29,   119,
      28,   119,    27,    30,    11,   155,    27,   155,    27,   155,
     130,   131,   130,   131,   155,    30,   166,    13,   166,    27,
     166,   155,    27,    27,    30,   166,    27,    30,   153,    25,
      26,    27,   166,     4,    11,   155,     3,   155,     5,     6,
       7,     8,     9,    29,   166,    30,   166,   197,   166,   197,
      29,   197,   177,    13,   204,    30,   197,    24,     4,   209,
      30,   209,    11,   209,    30,    25,    26,    27,   209,    30,
     220,   196,    29,    10,    12,    13,   155,   197,   228,   197,
       3,   101,     5,     6,     7,     8,     9,    25,    26,   209,
      -1,   209,    51,     3,   219,     5,     6,     7,     8,     9,
     231,    24,   218,    12,    13,    -1,    13,    -1,    12,    13,
      12,    13,    22,    23,    12,    13,    25,    26,    25,    26,
      27,    25,    26,    25,    26,    -1,    -1,    25,    26,    14,
      15,    16,    17,    18,    19,    -1,    58,    59,    60,    61,
      62,    63
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    22,    23,    39,
      40,    49,    54,    57,    67,    68,    69,    89,    93,    94,
      11,    90,     9,     9,     9,    31,    50,     9,     9,     0,
      39,    27,     9,    10,    11,    37,    49,    95,    96,    97,
      98,    99,   100,    11,    27,    31,    27,    27,    95,    11,
      11,    11,    95,    99,    12,    13,    25,    26,    14,    15,
      16,    17,    18,    19,    32,    33,    34,    35,    36,    95,
      95,    27,    51,    52,    53,    95,     9,    61,    62,    60,
      61,    62,    12,    70,    95,    95,    95,    97,    97,    97,
      97,    97,    97,    98,    98,    99,    99,    99,    12,    27,
      12,    28,    12,    28,    12,    28,    29,    91,    53,    55,
      62,    58,    62,    71,    29,    29,    29,    24,    41,    42,
      49,    63,    64,    67,    68,    69,    89,    93,    94,    92,
      56,    59,    27,    95,    30,    41,    27,     3,    20,    21,
      43,    44,    49,    63,    64,    65,    66,    67,    68,    79,
      89,    93,    94,    24,    47,    48,    49,    64,    67,    68,
      69,    89,    93,    94,    24,    45,    46,    49,    63,    67,
      68,    69,    89,    93,    94,    27,    72,    11,    27,    27,
      30,    43,    27,    30,    47,    27,    30,    45,    27,     4,
      73,    77,    95,     3,    29,    12,    11,    78,    80,    95,
      41,    29,    12,    30,    81,    74,    43,    29,    30,    75,
      82,    41,     4,    83,    87,    30,     3,    29,    76,    11,
      88,    73,    95,    43,    12,    30,    84,    29,    85,    43,
      30,    86,    83
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 57:

/* Line 1455 of yacc.c  */
#line 142 "a.y"
    {
    bool isFunc = false;
    
    for (int kk = 0; kk < funcs.size(); ++kk)
    {
        if (funcs[kk] == vars[(yyvsp[(1) - (1)])])
        {
            isFunc = true;
            break;
        }
    }
    
    if (isFunc)
    {
        result += "push 0\n";
        
        ++stack_top;
        //std::cout << $$;
    }
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 163 "a.y"
    {

    bool isFunc = false;
    
    for (int kk = 0; kk < funcs.size(); ++kk)
    {
        if (funcs[kk] == vars[(yyvsp[(1) - (5)])])
        {
            isFunc = true;
            break;
        }
    }
    
    if (isFunc)
    {
        result += "push 0\n";
    }
    
    result += std::string("call ") + "?LS" + vars[(yyvsp[(1) - (5)])] + "\n";
    
    
    //std::cout << $$ << " " << $1 << " " << $2 << " " << $3 << " " << $4 << " " << $5 << " ";
    
    
    if (isFunc)
    {
        //std::cout << $$;
        char * g = new char[15];
        itoa ((yyvsp[(4) - (5)])+1, g, 10);
        result += std::string("[") + g + "]=[0]\n";
        result += "pop 1\n";
    }
    --stack_top;
    char * g = new char[15];
    itoa ((yyvsp[(4) - (5)]), g, 10);
	result += std::string("pop ") + g + "\n";
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 202 "a.y"
    { (yyval) = (yyvsp[(1) - (3)]) + 1; ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 202 "a.y"
    { (yyval) = 1; ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 202 "a.y"
    { (yyval) = 0; ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 204 "a.y"
    { (yyval) = (yyvsp[(1) - (3)]) + 1; ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 204 "a.y"
    { (yyval) = 1; ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 206 "a.y"
    {
	if (isVar(vars[(yyvsp[(1) - (1)])]))
    {
        result += "push " + findInStack(vars[(yyvsp[(1) - (1)])]) + "\n";
        if (isTemp(vars[(yyvsp[(1) - (1)])]))
        {
            removeTemp();
            result += "pop 1\n";
            --stack_top;
            var_blocks.pop_back();
        }
    }
    else
    {
        result += "push " + vars[(yyvsp[(1) - (1)])] + "\n";
    }
    
    
;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 231 "a.y"
    {
    substartlabel = std::string("?LS") + vars[(yyvsp[(2) - (5)])];
    subendlabel = std::string("?LE") + vars[(yyvsp[(2) - (5)])];
    funcs.push_back(vars[(yyvsp[(2) - (5)])]);
	result += "goto " + subendlabel + "\n";
	result += substartlabel + ":\n";
;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 239 "a.y"
    {
    add_var_to_stack(std::string("return"));
    ++block_num;
    ++stack_top;
;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 248 "a.y"
    {
    
    remove_all_stack_with_block_num(block_num);
    --block_num;
    --stack_top;
    --stack_top;
    var_blocks.pop_back();
	result += "return\n";
	result += subendlabel + ":\n";
    for (int i = 0; i < currentparamcount; ++i)
    {
        --stack_top;
        var_blocks.pop_back();
    }
    currentparamcount = 0;
;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 269 "a.y"
    {
    substartlabel = std::string("?LS") + vars[(yyvsp[(2) - (5)])];
    subendlabel = std::string("?LE") + vars[(yyvsp[(2) - (5)])];
    procs.push_back(vars[(yyvsp[(2) - (5)])]);
    
	result += "goto " + subendlabel + "\n";
	result += substartlabel + ":\n";
;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 278 "a.y"
    {
    ++block_num;
    ++stack_top;
;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 285 "a.y"
    {
    remove_all_stack_with_block_num(block_num);
    --block_num;
    --stack_top;
	result += "return\n";
	result += subendlabel + ":\n";
    for (int i = 0; i < currentparamcount; ++i)
    {
        --stack_top;
        var_blocks.pop_back();
    }
    currentparamcount = 0;
;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 303 "a.y"
    {
    add_var_to_stack(vars[(yyvsp[(1) - (1)])]);
    ++currentparamcount;
;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 308 "a.y"
    {
    int num = 0;
    
    for (int jji = var_blocks.size()-1; var_blocks[jji].block_number == block_num; --jji)
    {
        ++num;
    }
    char * g = new char[15];
    itoa (num, g, 10);
	result += std::string("pop ") + g + "\n";
    
	result += "return\n";
;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 322 "a.y"
    {
    if (isVar(vars[(yyvsp[(2) - (3)])]))
    {
        result += findInStack("return") + "=" + findInStack(vars[(yyvsp[(2) - (3)])]) + "\n";
        if (isTemp(vars[(yyvsp[(2) - (3)])]))
        {
            removeTemp();
            result += "pop 1\n";
            --stack_top;
            var_blocks.pop_back();
        }
    }
    else
    {
        result += findInStack("return") + "=" + vars[(yyvsp[(2) - (3)])] + "\n";
    }
    int num = 0;
    
    for (int jji = var_blocks.size()-1; var_blocks[jji].block_number == block_num; --jji)
    {
        ++num;
    }
    char * g = new char[15];
    itoa (num, g, 10);
	result += std::string("pop ") + g + "\n";
    
	result += "return\n";
    
;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 352 "a.y"
    {
	std::string w_end = whileStack.top();

	result += "goto " + w_end + "_POPS\n";
;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 359 "a.y"
    {
	std::string w_end = whileStack.top();
	whileStack.pop();
	std::string w_beginning = whileStack.top();
	whileStack.push(w_end);
	result += "goto " + w_beginning + "\n";
;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 368 "a.y"
    { 

result += "print " + findInStack(vars[(yyvsp[(2) - (3)])]) + "\n";

;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 373 "a.y"
    { result += "input " + findInStack(vars[(yyvsp[(2) - (3)])]) + "\n";;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 375 "a.y"
    {
	std::string w_globalend = newLabel();
	ifStack.push(w_globalend);
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[(yyvsp[(3) - (4)])]))
	{
        result += "if not " + findInStack(vars[(yyvsp[(3) - (4)])]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[(yyvsp[(3) - (4)])]) + " goto " + w_end + "\n";
    }
;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 393 "a.y"
    {
    ++block_num;
;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 403 "a.y"
    {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 413 "a.y"
    {
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[(yyvsp[(4) - (5)])]))
	{
        result += "if not " + findInStack(vars[(yyvsp[(4) - (5)])]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[(yyvsp[(4) - (5)])]) + " goto " + w_end + "\n";
    }
;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 429 "a.y"
    {
    ++block_num;
;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 439 "a.y"
    {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
    
    
;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 450 "a.y"
    {
	std::string w_gend = ifStack.top();
	ifStack.pop();
	result += w_gend + ":\n";
;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 457 "a.y"
    {
    ++block_num;
;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 467 "a.y"
    {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += w_end + ":\n";
;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 480 "a.y"
    {
	std::string w_globalend = newLabel();
	ifStack.push(w_globalend);
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[(yyvsp[(3) - (4)])]))
	{
        result += "if not " + findInStack(vars[(yyvsp[(3) - (4)])]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[(yyvsp[(3) - (4)])]) + " goto " + w_end + "\n";
    }
;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 498 "a.y"
    {
    ++block_num;
;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 508 "a.y"
    {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
    
    
;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 518 "a.y"
    {
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[(yyvsp[(4) - (5)])]))
	{
        result += "if not " + findInStack(vars[(yyvsp[(4) - (5)])]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[(yyvsp[(4) - (5)])]) + " goto " + w_end + "\n";
    }
;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 534 "a.y"
    {
    ++block_num;
;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 544 "a.y"
    {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
    
    
;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 555 "a.y"
    {
	std::string w_gend = ifStack.top();
	ifStack.pop();
	result += w_gend + ":\n";
;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 562 "a.y"
    {
    ++block_num;
;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 572 "a.y"
    {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += w_end + ":\n";
;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 582 "a.y"
    {
	std::string w_start = newLabel();
	std::string w_end = newLabel();
	whileStack.push(w_start);
	whileStack.push(w_end);
	result += w_start + ":\n";
;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 589 "a.y"
    {
    //std::cout << vars[$1] << " " << vars[$2] << " " << vars[$3] << " " << vars[$4] ;
	std::string w_end = whileStack.top();
	whileStack.pop();
	std::string w_start = whileStack.top();
	whileStack.push(w_end);
	
	if (isTemp(vars[(yyvsp[(4) - (5)])]))
	{
        result += "if not " + findInStack(vars[(yyvsp[(4) - (5)])]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[(yyvsp[(4) - (5)])]) + " goto " + w_end + "\n";
    }
;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 609 "a.y"
    {
    ++block_num;
;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 618 "a.y"
    {
	std::string w_end = whileStack.top();
	whileStack.pop();
	std::string w_start = whileStack.top();
	result += "goto " + w_start + "\n";
    result += w_end + "_POPS:";
	remove_all_stack_with_block_num(block_num);
    --block_num;
	result += w_end + ":\n";
	whileStack.pop();
;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 630 "a.y"
    {
    if (isVar(vars[(yyvsp[(3) - (4)])]))
    {
        result += findInStack(vars[(yyvsp[(1) - (4)])]) + "=" + findInStack(vars[(yyvsp[(3) - (4)])]) + "\n";
        if (isTemp(vars[(yyvsp[(3) - (4)])]))
        {
            removeTemp();
            result += "pop 1\n";
            --stack_top;
            var_blocks.pop_back();
        }
    }
    else
    {
        result += findInStack(vars[(yyvsp[(1) - (4)])]) + "=" + vars[(yyvsp[(3) - (4)])] + "\n";
    }
;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 649 "a.y"
    {
    result += "push 0\n";
    add_var_to_stack(vars[(yyvsp[(2) - (3)])]);
    
;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 655 "a.y"
    {
    
	if (isTemp(vars[(yyvsp[(4) - (5)])]))
    {
		removeTemp();
        var_blocks[var_blocks.size()-1].name = vars[(yyvsp[(2) - (5)])];
    }
    else if (isVar(vars[(yyvsp[(4) - (5)])]))
    {
        result += "push 0\n";
        add_var_to_stack(vars[(yyvsp[(2) - (5)])]);
        result += findInStack(vars[(yyvsp[(2) - (5)])]) + "=" + findInStack(vars[(yyvsp[(4) - (5)])]) + "\n";
        ++stack_top;
	}
    else
    {
        result += "push 0\n";
        add_var_to_stack(vars[(yyvsp[(2) - (5)])]);
        
        result += findInStack(vars[(yyvsp[(2) - (5)])]) + "=" + vars[(yyvsp[(4) - (5)])] + "\n";
    }
    
;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 680 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "&" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "&" + findInStack(q) + "\n";
        }
        
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "&" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "&" + findInStack(q) + "\n";
	}
	
	//std::cout << "AND:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 718 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "|" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "|" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "|" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "|" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 754 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "^" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "^" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "^" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "^" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 790 "a.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 792 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 828 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 864 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<=" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<=" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<=" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "<=" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 900 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">=" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">=" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">=" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + ">=" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 936 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "==" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "==" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "==" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "==" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 972 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "!=" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "!=" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "!=" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "!=" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1008 "a.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1010 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "+" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "+" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "+" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "+" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1046 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "-" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "-" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "-" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "-" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1082 "a.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1084 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "*" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "*" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "*" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "*" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1120 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "/" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "/" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "/" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "/" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1156 "a.y"
    {
	std::string q = vars[(yyvsp[(3) - (3)])];
	if (isTemp(vars[(yyvsp[(1) - (3)])]))
	{
		(yyval) = (yyvsp[(1) - (3)]);
		if (isTemp(vars[(yyvsp[(3) - (3)])]))
		{
			vars.erase(vars.begin() + (yyvsp[(3) - (3)]));
			removeTemp();
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "%" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "%" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[(yyvsp[(3) - (3)])]))
	{
		(yyval) = (yyvsp[(3) - (3)]);
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "%" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(1) - (3)])]) + "%" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1192 "a.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1193 "a.y"
    {
	if (isTemp(vars[(yyvsp[(2) - (2)])]))
	{
		(yyval) = (yyvsp[(2) - (2)]);
        result += std::string("~") + findInStack(vars[(yyval)]) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		(yyval) = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
		result += findInStack(vars[(yyval)]) + "=" + findInStack(vars[(yyvsp[(2) - (2)])]) + "\n";
        
        result += std::string("~") + findInStack(vars[(yyval)]) + "\n";
	}
	
	//std::cout << "NOT:" << vars[$1] << std::endl;
;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1214 "a.y"
    { 

std::string nt = newTemp();
(yyval) = vars.size();
vars.push_back(nt);
add_var_to_stack(nt);

;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1221 "a.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1222 "a.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1223 "a.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1224 "a.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3074 "a.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1229 "a.y"

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}
int main(int argc, char *argv[])
{
//	yylex();
	if (argc > 2)
	{
		yyin = fopen(argv[1], "r");
		std::ofstream myfile;
		myfile.open(argv[2]);
		yyparse();
		myfile << result;
		myfile.close();
		fclose(yyin);
	}
    else if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
        yyparse();
        std::cout << result;
    }
	else
	{
		yyparse();
		std::cout << result;
	}
	
	return 0;
}
