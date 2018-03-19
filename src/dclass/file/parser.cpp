/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 4 "parser.ypp" /* yacc.c:339  */

	#include "file/lexerDefs.h"
	#include "file/parserDefs.h"
	#include "file/parser.h"
	#include "file/write.h" // format_type(Type);

	#include "dc/File.h"
	#include "dc/DistributedType.h"
	#include "dc/NumericRange.h"
	#include "dc/NumericType.h"
	#include "dc/ArrayType.h"
	#include "dc/Struct.h"
	#include "dc/Class.h"
	#include "dc/Annotation.h"
	#include "dc/Field.h"
	#include "dc/Method.h"
	#include "dc/Parameter.h"
	#include "dc/MolecularField.h"

	#include "util/byteorder.h"

	#include <stdint.h> // Fixed width integer limits
	#include <math.h>   // Float INFINITY
	#include <stack>    // std::stack

	#define yyparse run_parser
	#define yylex run_lexer
	#define yyerror parser_error
	#define yywarning parser_warning
	#define yychar dcyychar
	#define yydebug dcyydebug
	#define yynerrs dcyynerrs

	// Because our token type contains objects of type string, which
	// require correct copy construction (and not simply memcpying), we
	// cannot use bison's built-in auto-stack-grow feature.  As an easy
	// solution, we ensure here that we have enough yacc stack to start
	// with, and that it doesn't ever try to grow.
	#define YYINITDEPTH 1000
	#define YYMAXDEPTH 1000

	using namespace std;
	namespace dclass   // open namespace dclass
	{


	// Parser output
	static File* parsed_file = nullptr;
	static string* parsed_value = nullptr;

	// Parser state
	static Class* current_class = nullptr;
	static Struct* current_struct = nullptr;


	// Stack of distributed types for parsing values
	struct TypeAndDepth
	{
		int depth;
		const DistributedType* type;
		TypeAndDepth(const DistributedType* t, int d) : depth(d), type(t) {}
	};
	static stack<TypeAndDepth> type_stack;
	static int current_depth;

	// These two types are really common types the parser doesn't need to make new
	//     duplicates of every time a string or blob is used.
	static ArrayType* basic_string = nullptr;
	static ArrayType* basic_blob = nullptr;

	/* Helper functions */
	static bool check_depth();
	static void depth_error(string what);
	static void depth_error(int depth, string what);
	static string number_value(Type type, double &number);
	static string number_value(Type type, int64_t &number);
	static string number_value(Type type, uint64_t &number);

////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

	void init_file_parser(istream& in, const string& filename, File& file)
	{
		parsed_file = &file;
		init_file_lexer(in, filename);
	}

	void init_value_parser(istream& in, const string& source,
	                       const DistributedType* type, string& output)
	{
		parsed_value = &output;
		current_depth = 0;
		type_stack.push(TypeAndDepth(type, 0));
		init_value_lexer(in, source);
	}

	void cleanup_parser()
	{
		current_depth = 0;
		type_stack = stack<TypeAndDepth>();
		parsed_file = nullptr;
		parsed_value = nullptr;
	}

	int parser_error_count()
	{
		return lexer_error_count();
	}
	int parser_warning_count()
	{
		return lexer_warning_count();
	}

	void parser_error(const string &msg)
	{
		lexer_error(msg);
	}
	void parser_warning(const string &msg)
	{
		lexer_warning(msg);
	}

#line 190 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    UNSIGNED_INTEGER = 258,
    REAL = 259,
    STRING = 260,
    HEX_STRING = 261,
    IDENTIFIER = 262,
    CHAR = 263,
    START_DC_FILE = 264,
    START_DC_VALUE = 265,
    KW_DCLASS = 266,
    KW_STRUCT = 267,
    KW_FROM = 268,
    KW_IMPORT = 269,
    KW_TYPEDEF = 270,
    KW_KEYWORD = 271,
    KW_ANN_CHECK_SIZE_LT = 272,
    KW_INT8 = 273,
    KW_INT16 = 274,
    KW_INT32 = 275,
    KW_INT64 = 276,
    KW_UINT8 = 277,
    KW_UINT16 = 278,
    KW_UINT32 = 279,
    KW_UINT64 = 280,
    KW_FLOAT32 = 281,
    KW_FLOAT64 = 282,
    KW_STRING = 283,
    KW_BLOB = 284,
    KW_CHAR = 285
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 267 "parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   268

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  173
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  273

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    44,     2,     2,
      42,    43,    33,    46,    34,    45,    32,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    31,
       2,    41,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   235,   235,   236,   241,   242,   243,   244,   245,   246,
     250,   254,   258,   263,   271,   276,   285,   286,   293,   294,
     301,   305,   313,   314,   321,   366,   370,   378,   388,   403,
     407,   408,   416,   415,   455,   456,   460,   467,   477,   508,
     509,   510,   511,   549,   565,   587,   595,   594,   634,   635,
     636,   670,   671,   675,   676,   677,   678,   682,   687,   686,
     701,   708,   713,   722,   721,   733,   732,   744,   743,   757,
     764,   765,   769,   787,   791,   795,   799,   803,   807,   814,
     840,   872,   894,   922,   945,   946,   947,   948,   952,   956,
     965,   974,   986,   998,  1005,  1015,  1019,  1026,  1036,  1049,
    1050,  1051,  1052,  1057,  1056,  1070,  1077,  1082,  1091,  1090,
    1102,  1101,  1115,  1116,  1117,  1121,  1122,  1123,  1127,  1139,
    1143,  1156,  1157,  1158,  1162,  1174,  1178,  1193,  1208,  1223,
    1251,  1288,  1322,  1323,  1328,  1327,  1369,  1370,  1378,  1377,
    1419,  1420,  1421,  1425,  1432,  1477,  1476,  1549,  1551,  1550,
    1571,  1576,  1598,  1620,  1642,  1698,  1758,  1759,  1763,  1764,
    1768,  1769,  1770,  1771,  1772,  1773,  1774,  1775,  1776,  1777,
    1778,  1782,  1786,  1799
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "UNSIGNED_INTEGER", "REAL", "STRING",
  "HEX_STRING", "IDENTIFIER", "CHAR", "START_DC_FILE", "START_DC_VALUE",
  "KW_DCLASS", "KW_STRUCT", "KW_FROM", "KW_IMPORT", "KW_TYPEDEF",
  "KW_KEYWORD", "KW_ANN_CHECK_SIZE_LT", "KW_INT8", "KW_INT16", "KW_INT32",
  "KW_INT64", "KW_UINT8", "KW_UINT16", "KW_UINT32", "KW_UINT64",
  "KW_FLOAT32", "KW_FLOAT64", "KW_STRING", "KW_BLOB", "KW_CHAR", "';'",
  "'.'", "'*'", "','", "'/'", "'['", "']'", "'{'", "'}'", "':'", "'='",
  "'('", "')'", "'%'", "'-'", "'+'", "$accept", "grammar", "file", "value",
  "import", "import_module", "import_symbols", "import_symbol_list",
  "import_alternatives", "typedef", "typedef_type",
  "nonmethod_type_with_name", "defined_type", "keyword_decl",
  "keyword_decl_list", "dclass", "$@1", "class_inheritance",
  "class_parents", "defined_class", "class_fields", "annotation_field",
  "class_field", "dstruct", "$@2", "struct_fields", "struct_field",
  "named_field", "unnamed_field", "$@3", "field_with_name",
  "field_with_name_as_array", "field_with_name_and_default", "$@4", "$@5",
  "$@6", "method_as_field", "nonmethod_type", "nonmethod_type_no_array",
  "type_with_array", "molecular", "defined_field", "builtin_array_type",
  "numeric_type", "numeric_token_only", "numeric_with_range",
  "numeric_with_modulus", "numeric_with_divisor", "method", "method_body",
  "parameter", "$@7", "param_with_name", "param_with_name_as_array",
  "param_with_name_and_default", "$@8", "$@9", "numeric_range",
  "array_range", "char_or_uint", "small_unsigned_integer", "number",
  "char_or_number", "type_value", "method_value", "$@10",
  "parameter_values", "struct_value", "$@11", "field_values",
  "array_value", "$@12", "element_values", "$@13", "array_expansion",
  "signed_integer", "array_type_token", "numeric_type_token",
  "keyword_list", "empty", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    59,    46,    42,    44,    47,    91,    93,   123,   125,
      58,    61,    40,    41,    37,    45,    43
};
# endif

#define YYPACT_NINF -203

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-203)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     107,  -203,    14,    24,    97,  -203,  -203,  -203,  -203,  -203,
    -203,    -3,  -203,  -203,    44,    63,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,    91,    95,   118,   118,   226,  -203,
    -203,  -203,  -203,    15,  -203,  -203,  -203,  -203,    38,    14,
      59,  -203,  -203,  -203,  -203,  -203,     7,    20,   100,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,    49,   122,  -203,   101,   102,   103,
     -12,  -203,    26,    98,    99,  -203,   126,  -203,    72,   109,
     110,   128,   129,  -203,    81,  -203,   130,  -203,  -203,    47,
    -203,    11,   119,   133,    46,   118,   157,    72,  -203,    72,
      72,    72,   162,    32,    54,   162,    32,    32,    72,  -203,
    -203,  -203,   131,   121,  -203,  -203,   162,   162,   162,   162,
    -203,  -203,   162,    14,  -203,    59,  -203,   160,   134,  -203,
    -203,  -203,  -203,   139,    20,    20,  -203,   138,   140,   141,
     142,  -203,  -203,  -203,  -203,   137,  -203,   136,  -203,  -203,
    -203,  -203,   158,   159,   161,  -203,    72,  -203,  -203,  -203,
    -203,    38,  -203,  -203,  -203,  -203,  -203,   148,  -203,   166,
     167,  -203,   118,  -203,  -203,  -203,  -203,  -203,    32,  -203,
    -203,  -203,  -203,  -203,   160,   173,   192,   169,  -203,   163,
    -203,  -203,  -203,   172,  -203,  -203,    52,    53,  -203,   183,
       8,    20,  -203,  -203,   174,    80,  -203,  -203,   177,  -203,
     191,  -203,   127,  -203,    48,  -203,    72,  -203,    72,  -203,
     184,  -203,   162,   220,  -203,   221,  -203,   220,  -203,   188,
     223,  -203,    60,    78,  -203,   226,  -203,   195,    59,   197,
      59,  -203,    59,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
      72,  -203,    72,  -203,  -203,  -203,  -203,  -203,  -203,    59,
    -203,   221,    59,   198,    59,   200,    59,  -203,  -203,  -203,
    -203,  -203,  -203
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   173,   173,     0,     2,     4,   127,   128,   130,   131,
     129,   145,   138,   134,     0,     0,     3,    12,    13,   133,
     132,   126,    11,     1,     0,     0,     0,     0,     0,   173,
       5,     8,     9,    24,    10,     6,     7,   144,     0,     0,
       0,   157,   156,    32,    46,    22,     0,    16,    14,    28,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     158,   159,   160,    25,    72,     0,    70,    71,    74,    73,
      84,    87,    85,    86,    82,    88,    29,    30,   173,   127,
     128,   130,   131,   150,     0,   147,   126,   140,   141,     0,
     136,     0,   173,     0,     0,     0,     0,   173,    27,   173,
     173,   173,     0,   173,     0,     0,   173,   173,   173,    31,
     120,   118,     0,   116,   119,   115,     0,     0,     0,     0,
     148,   146,     0,     0,   139,     0,   135,     0,     0,    34,
     173,    19,    15,    18,    20,    17,    23,     0,     0,     0,
       0,    93,   121,   123,   124,     0,   125,   113,   122,   112,
      92,    94,     0,     0,     0,    26,     0,   152,   153,   154,
     155,     0,   151,   142,   143,   137,    38,    35,    36,   173,
       0,    48,     0,    76,    78,    77,    75,    89,     0,    90,
      91,    83,   117,   149,     0,     0,     0,     0,    39,    28,
      49,    47,    60,     0,    51,    52,    53,    54,    55,    56,
      57,    21,   114,    37,     0,    28,    41,    33,     0,   173,
      45,    40,     0,    69,     0,    50,   173,    63,   173,    65,
       0,    58,     0,     0,    42,    44,   171,     0,    95,   102,
      70,    97,    99,   100,   101,     0,    96,     0,     0,     0,
       0,    67,     0,   173,    81,    79,   172,    80,   103,   105,
     173,   108,   173,   110,    98,    61,    64,    62,    66,     0,
      59,    43,     0,     0,     0,     0,     0,    68,   104,   106,
     109,   107,   111
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -203,  -203,  -203,  -203,  -203,   212,  -203,  -203,   -82,  -203,
    -203,   213,  -203,  -203,  -203,  -203,  -203,  -203,  -203,    58,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,    73,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -164,  -202,  -203,
    -203,    31,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
      28,  -203,  -203,  -203,  -203,  -203,  -203,    29,   -92,   105,
     -91,   164,    87,    -2,   -36,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,   106,   -34,  -203,  -203,    23,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    16,    31,    46,   132,   133,    47,    32,
      33,   192,    64,    34,    76,    35,    92,   128,   167,   168,
     186,   187,   208,    36,    93,   170,   193,   194,   195,   242,
     196,   197,   198,   238,   240,   259,   199,    65,    66,    67,
     210,   245,    68,    69,    70,    71,    72,    73,   213,   214,
     231,   262,   232,   233,   234,   264,   266,   145,   112,   113,
     114,   146,   147,    83,    18,    40,    91,    19,    39,    89,
      20,    38,    84,   161,    85,    21,    74,    75,   225,   115
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      17,     5,    22,    88,    86,   137,   200,   138,   139,   140,
     230,   141,   134,   135,   151,    98,   154,     6,     7,     8,
       9,    94,    10,   102,    23,   157,   158,   159,   160,    77,
     103,   162,   104,   230,    37,   142,   143,    87,    90,    95,
     144,    79,    80,    81,    82,   125,    10,    41,   229,   221,
      11,    78,    12,    45,   126,    96,    13,   142,   143,    14,
      15,   105,     6,     7,     8,     9,    42,    10,   106,   148,
     148,   229,   148,   148,    11,   110,    12,    14,    15,   131,
     111,   123,   235,    14,    15,    97,   124,   164,   216,   218,
     201,   236,   129,   217,   219,    11,   250,    12,    43,    14,
      15,   251,    44,   149,    14,    15,   149,   149,    24,    25,
      26,    27,    28,    29,   252,   120,     1,     2,   121,   253,
     223,   163,   212,   165,   237,    45,   239,    86,    30,    98,
     171,   243,    95,   109,    49,   152,   153,    99,   100,   101,
     107,   108,   116,   117,   148,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,   263,   127,
     265,   118,   119,   122,   136,   110,   156,   166,   155,   188,
     228,   130,   169,   172,   189,   173,   204,   174,   175,   176,
     177,   178,   184,   185,   241,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,   190,   205,
     211,   179,   180,   215,   181,   212,   191,   222,   224,   226,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   206,   220,   227,    13,   244,   246,   248,
     249,   207,   255,    49,   257,   269,   256,   271,   258,    48,
     260,    63,   203,   226,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,   267,   247,   209,
     268,   182,   270,   254,   272,   202,   261,   183,   150
};

static const yytype_uint16 yycheck[] =
{
       2,     1,     2,    39,    38,    97,   170,    99,   100,   101,
     212,   102,    94,    95,   105,     7,   108,     3,     4,     5,
       6,    14,     8,    35,     0,   116,   117,   118,   119,    29,
      42,   122,    44,   235,    37,     3,     4,    39,    40,    32,
       8,     3,     4,     5,     6,    34,     8,     3,   212,    41,
      36,    36,    38,     7,    43,    35,    42,     3,     4,    45,
      46,    35,     3,     4,     5,     6,     3,     8,    42,   103,
     104,   235,   106,   107,    36,     3,    38,    45,    46,    33,
       8,    34,    34,    45,    46,    36,    39,   123,    36,    36,
     172,    43,    92,    41,    41,    36,    36,    38,     7,    45,
      46,    41,     7,   103,    45,    46,   106,   107,    11,    12,
      13,    14,    15,    16,    36,    34,     9,    10,    37,    41,
      40,   123,    42,   125,   216,     7,   218,   161,    31,     7,
     130,   222,    32,     7,     7,   106,   107,    36,    36,    36,
      42,    42,    33,    33,   178,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,   250,    40,
     252,    33,    33,    33,     7,     3,    45,     7,    37,   169,
      43,    38,    38,    34,     7,    37,     3,    37,    37,    37,
      43,    45,    34,    17,   220,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     7,
      31,    43,    43,    31,    43,    42,    39,    33,    31,   209,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    41,    34,    42,     7,     7,    41,
       7,    39,    37,     7,    37,    37,   238,    37,   240,    27,
     242,    28,   184,   243,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,   259,   227,   186,
     262,   156,   264,   235,   266,   178,   243,   161,   104
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    48,    49,   126,     3,     4,     5,     6,
       8,    36,    38,    42,    45,    46,    50,   110,   111,   114,
     117,   122,   126,     0,    11,    12,    13,    14,    15,    16,
      31,    51,    56,    57,    60,    62,    70,    37,   118,   115,
     112,     3,     3,     7,     7,     7,    52,    55,    52,     7,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    58,    59,    84,    85,    86,    89,    90,
      91,    92,    93,    94,   123,   124,    61,   126,    36,     3,
       4,     5,     6,   110,   119,   121,   122,   110,   111,   116,
     110,   113,    63,    71,    14,    32,    35,    36,     7,    36,
      36,    36,    35,    42,    44,    35,    42,    42,    42,     7,
       3,     8,   105,   106,   107,   126,    33,    33,    33,    33,
      34,    37,    33,    34,    39,    34,    43,    40,    64,   126,
      38,    33,    53,    54,    55,    55,     7,   105,   105,   105,
     105,   107,     3,     4,     8,   104,   108,   109,   122,   126,
     108,   107,   104,   104,   105,    37,    45,   107,   107,   107,
     107,   120,   107,   110,   111,   110,     7,    65,    66,    38,
      72,   126,    34,    37,    37,    37,    37,    43,    45,    43,
      43,    43,   106,   121,    34,    17,    67,    68,   126,     7,
      31,    39,    58,    73,    74,    75,    77,    78,    79,    83,
      84,    55,   109,    66,     3,     7,    31,    39,    69,    74,
      87,    31,    42,    95,    96,    31,    36,    41,    36,    41,
      41,    41,    33,    40,    31,   125,   126,    34,    43,    84,
      85,    97,    99,   100,   101,    34,    43,   105,    80,   105,
      81,   111,    76,   107,     7,    88,     7,    88,    41,     7,
      36,    41,    36,    41,    97,    37,   110,    37,   110,    82,
     110,   125,    98,   105,   102,   105,   103,   110,   110,    37,
     110,    37,   110
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    49,    49,    49,    49,
      49,    50,    50,    50,    51,    51,    52,    52,    53,    53,
      54,    54,    55,    55,    56,    57,    57,    58,    59,    60,
      61,    61,    63,    62,    64,    64,    65,    65,    66,    67,
      67,    67,    67,    68,    69,    69,    71,    70,    72,    72,
      72,    73,    73,    74,    74,    74,    74,    75,    76,    75,
      77,    78,    78,    80,    79,    81,    79,    82,    79,    83,
      84,    84,    85,    85,    85,    86,    86,    86,    86,    87,
      87,    88,    89,    89,    90,    90,    90,    90,    91,    92,
      92,    92,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    97,    97,    98,    97,    99,   100,   100,   102,   101,
     103,   101,   104,   104,   104,   105,   105,   105,   106,   106,
     107,   108,   108,   108,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   112,   111,   113,   113,   115,   114,
     116,   116,   116,   116,   117,   118,   117,   119,   120,   119,
     121,   121,   121,   121,   121,   121,   122,   122,   123,   123,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   125,   125,   126
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     2,     4,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     2,     4,     2,     1,     2,
       1,     2,     0,     7,     1,     2,     1,     3,     1,     1,
       2,     2,     3,     5,     2,     1,     0,     6,     1,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     4,     4,     0,     4,     0,     4,     0,     5,     2,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     3,
       3,     1,     1,     4,     1,     1,     1,     1,     1,     4,
       4,     4,     3,     3,     3,     2,     2,     2,     3,     1,
       1,     1,     1,     0,     4,     2,     4,     4,     0,     4,
       0,     4,     1,     1,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     3,     0,     4,
       1,     1,     3,     3,     2,     0,     4,     1,     0,     4,
       1,     3,     3,     3,     3,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:
#line 247 "parser.ypp" /* yacc.c:1646  */
    {

	}
#line 1565 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 255 "parser.ypp" /* yacc.c:1646  */
    {
		parsed_value->clear();
	}
#line 1573 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 259 "parser.ypp" /* yacc.c:1646  */
    {
		parsed_value->assign((yyvsp[0].str));
		if(!type_stack.empty()) depth_error(0, "type");
	}
#line 1582 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 264 "parser.ypp" /* yacc.c:1646  */
    {
		parsed_value->assign((yyvsp[0].str));
		if(!type_stack.empty()) depth_error(0, "method");
	}
#line 1591 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 272 "parser.ypp" /* yacc.c:1646  */
    {
		Import* import = new Import((yyvsp[0].str));
		parsed_file->add_import(import);
	}
#line 1600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 277 "parser.ypp" /* yacc.c:1646  */
    {
		Import* import = new Import((yyvsp[-2].str));
		import->symbols.assign((yyvsp[0].strings).begin(), (yyvsp[0].strings).end());
		parsed_file->add_import(import);
	}
#line 1610 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 285 "parser.ypp" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 1616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 287 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[-2].str) + string(".") + (yyvsp[0].str);
	}
#line 1624 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 293 "parser.ypp" /* yacc.c:1646  */
    { (yyval.strings) = (yyvsp[0].strings); }
#line 1630 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 295 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.strings) = vector<string>();
	}
#line 1638 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 302 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.strings) = vector<string>(1, (yyvsp[0].str));
	}
#line 1646 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 306 "parser.ypp" /* yacc.c:1646  */
    {
		(yyvsp[-2].strings).push_back((yyvsp[0].str));
		(yyval.strings) = (yyvsp[-2].strings);
	}
#line 1655 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 313 "parser.ypp" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 1661 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 315 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[-2].str) + string("/") + (yyvsp[0].str);
	}
#line 1669 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 322 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].nametype).type == nullptr)
		{
			// Ignore this typedef, it should have already produced an error
			break;
		}

		// Set the type's typedef
		(yyvsp[0].nametype).type->set_alias((yyvsp[0].nametype).name);

		bool type_added	= parsed_file->add_typedef((yyvsp[0].nametype).name, (yyvsp[0].nametype).type);
		if(!type_added)
		{
			// Lets be really descriptive about why this failed
			DistributedType* dtype = parsed_file->get_type_by_name((yyvsp[0].nametype).name);
			if(dtype == nullptr)
			{
				parser_error("Unknown error adding typedef to file.");
				break;
			}

			Struct* dstruct = dtype->as_struct();
			if(dstruct == nullptr)
			{
				parser_error("Cannot add 'typedef " + (yyvsp[0].nametype).name
				             + "' to file because a typedef was already declared with that name.");
				break;
			}

			if(dstruct->as_class())
			{
				parser_error("Cannot add 'typedef " + (yyvsp[0].nametype).name
				             + "' to file because a class was already declared with that name.");
			}
			else
			{
				parser_error("Cannot add 'typedef " + (yyvsp[0].nametype).name
				             + "' to file because a struct was already declared with that name.");
			}
		}
	}
#line 1715 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 367 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.nametype) = (yyvsp[0].nametype);
	}
#line 1723 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 371 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.nametype) = (yyvsp[-3].nametype);
		(yyval.nametype).type = new ArrayType((yyvsp[-3].nametype).type, (yyvsp[-1].range));
	}
#line 1732 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 379 "parser.ypp" /* yacc.c:1646  */
    {
		TokenType::NameType nt;
		nt.type = (yyvsp[-1].u.dtype);
		nt.name = (yyvsp[0].str);
		(yyval.nametype) = nt;
	}
#line 1743 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 389 "parser.ypp" /* yacc.c:1646  */
    {
		DistributedType* dtype = parsed_file->get_type_by_name((yyvsp[0].str));
		if(dtype == nullptr)
		{
			parser_error("Type '" + string((yyvsp[0].str)) + "' has not been declared.");
			(yyval.u.dtype) = nullptr;
			break;
		}

		(yyval.u.dtype) = dtype;
	}
#line 1759 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 409 "parser.ypp" /* yacc.c:1646  */
    {
		parsed_file->add_keyword((yyvsp[0].str));
	}
#line 1767 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 416 "parser.ypp" /* yacc.c:1646  */
    {
		current_class = new Class(parsed_file, (yyvsp[0].str));
	}
#line 1775 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 420 "parser.ypp" /* yacc.c:1646  */
    {
		bool class_added = parsed_file->add_class(current_class);
		if(!class_added)
		{
			// Lets be really descriptive about why this failed
			DistributedType* dtype = parsed_file->get_type_by_name(current_class->get_name());
			if(dtype == nullptr)
			{
				parser_error("Unknown error adding class to file.");
				break;
			}

			Struct* dstruct = dtype->as_struct();
			if(dstruct == nullptr)
			{
				parser_error("Cannot add 'dclass " + current_class->get_name()
				             + "' to file because a typedef was already declared with that name.");
				break;
			}

			if(dstruct->as_class())
			{
				parser_error("Cannot add 'dclass " + current_class->get_name()
				             + "' to file because a class was already declared with that name.");
			}
			else
			{
				parser_error("Cannot add 'dclass " + current_class->get_name()
				             + "' to file because a struct was already declared with that name.");
			}
		}
	}
#line 1812 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 461 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].u.dclass) != nullptr)
		{
			current_class->add_parent((yyvsp[0].u.dclass));
		}
	}
#line 1823 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 468 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].u.dclass) != nullptr)
		{
			current_class->add_parent((yyvsp[0].u.dclass));
		}
	}
#line 1834 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 478 "parser.ypp" /* yacc.c:1646  */
    {
		DistributedType* dtype = parsed_file->get_type_by_name((yyvsp[0].str));
		if(dtype == nullptr)
		{
			parser_error("'dclass " + string((yyvsp[0].str)) + "' has not been declared.");
			(yyval.u.dclass) = nullptr;
			break;
		}

		Struct* dstruct = dtype->as_struct();
		if(dstruct == nullptr)
		{
			parser_error("class cannot inherit from non-class type '" + string((yyvsp[0].str)) + "'.");
			(yyval.u.dclass) = nullptr;
			break;
		}

		Class* dclass = dstruct->as_class();
		if(dclass == nullptr)
		{
			parser_error("class cannot inherit from struct type '" + string((yyvsp[0].str)) + "'.");
			(yyval.u.dclass) = nullptr;
			break;
		}

		(yyval.u.dclass) = dclass;
	}
#line 1866 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 512 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[-1].u.dfield) == nullptr)
		{
			// Ignore this field, it should have already generated a parser error
			break;
		}

		bool field_added = current_class->add_field((yyvsp[-1].u.dfield));
		if(!field_added)
		{
			// Lets be really descriptive about why this failed
			if(current_class->get_field_by_name((yyvsp[-1].u.dfield)->get_name()))
			{
				parser_error("Cannot add field '" + (yyvsp[-1].u.dfield)->get_name()
				             + "', a field with that name already exists in 'dclass "
				             + current_class->get_name() + "'.");
			}
			else if(current_class->get_name() == (yyvsp[-1].u.dfield)->get_name())
			{
				if((yyvsp[-1].u.dfield)->as_molecular())
				{
					parser_error("Cannot use a molecular field as a constructor.");
				}
				else
				{
					parser_error("The constructor must be the first field in the class.");
				}
			}
			else
			{
				parser_error("Unknown error adding field to class.");
			}
		}
	}
#line 1905 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 550 "parser.ypp" /* yacc.c:1646  */
    {
		auto *annotation = new Annotation();
		annotation->m_annotation_type = AnnotationType::CHECK_SIZE_LT;
		annotation->m_annotation_name = std::string{"check_size_lt"};
		annotation->m_dclass_name = current_class->get_name();
		annotation->check_max_bytes = (yyvsp[-3].u.uint64) * (yyvsp[-1].u.uint32);

		for(const auto& kw : (yyvsp[0].strings))
			annotation->add_keyword(kw);

		current_class->add_annotation(annotation);
	}
#line 1922 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 566 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[-1].u.dfield) == nullptr)
		{
			// Ignore this field, it should have already generated a parser error
			(yyval.u.dfield) = nullptr;
			break;
		}

		if((yyvsp[-1].u.dfield)->get_name().empty())
		{
			parser_error("An unnamed field can't be defined in a class.");
			(yyval.u.dfield) = nullptr;
			break;
		}

		// Add the keywords to the class
		for(const auto& kw : (yyvsp[0].strings))
			(yyvsp[-1].u.dfield)->add_keyword(kw);

		(yyval.u.dfield) = (yyvsp[-1].u.dfield);
	}
#line 1948 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 588 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dfield) = (Field*)(yyvsp[0].u.dmolecule);
	}
#line 1956 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 595 "parser.ypp" /* yacc.c:1646  */
    {
		current_struct = new Struct(parsed_file, (yyvsp[0].str));
	}
#line 1964 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 599 "parser.ypp" /* yacc.c:1646  */
    {
		bool struct_added = parsed_file->add_struct(current_struct);
		if(!struct_added)
		{
			// Lets be really descriptive about why this failed
			DistributedType* dtype = parsed_file->get_type_by_name(current_struct->get_name());
			if(dtype == nullptr)
			{
				parser_error("Unknown error adding struct to file.");
				break;
			}

			Struct* dstruct = dtype->as_struct();
			if(dstruct == nullptr)
			{
				parser_error("Cannot add 'struct " + current_struct->get_name()
				             + "' to file because a typedef was already declared with that name.");
				break;
			}

			if(dstruct->as_class())
			{
				parser_error("Cannot add 'struct " + current_struct->get_name()
				             + "' to file because a class was already declared with that name.");
			}
			else
			{
				parser_error("Cannot add 'struct " + current_struct->get_name()
				             + "' to file because a struct was already declared with that name.");
			}
		}
	}
#line 2001 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 637 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[-1].u.dfield) == nullptr || (yyvsp[-1].u.dfield)->get_type() == nullptr)
		{
			// Ignore this field, it should have already generated a parser error
			break;
		}

		if(!current_struct->add_field((yyvsp[-1].u.dfield)))
		{
			// Lets be really descriptive about why this failed
			if(current_struct->get_field_by_name((yyvsp[-1].u.dfield)->get_name()))
			{
				parser_error("Cannot add field '" + (yyvsp[-1].u.dfield)->get_name()
				             + "', a field with that name already exists in 'struct "
				             + current_struct->get_name() + "'.");
			}
			else if(current_struct->get_name() == (yyvsp[-1].u.dfield)->get_name())
			{
				parser_error("A constructor can't be defined in a struct.");
			}
			else if((yyvsp[-1].u.dfield)->get_type()->as_method())
			{
				parser_error("A method can't be defined in a struct.");
			}
			else
			{
				parser_error("Unknown error adding field to struct.");
			}
		}
	}
#line 2036 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 683 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dfield) = new Field((yyvsp[0].u.dtype));
	}
#line 2044 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 687 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[-1].u.dtype), 0));
	}
#line 2053 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 692 "parser.ypp" /* yacc.c:1646  */
    {
		Field* field = new Field((yyvsp[-3].u.dtype));
		if(!type_stack.empty()) depth_error(0, "unnamed field");
		field->set_default_value((yyvsp[0].str));
		(yyval.u.dfield) = field;
	}
#line 2064 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 702 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dfield) = new Field((yyvsp[0].nametype).type, (yyvsp[0].nametype).name);
	}
#line 2072 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 709 "parser.ypp" /* yacc.c:1646  */
    {
		(yyvsp[-3].u.dfield)->set_type(new ArrayType((yyvsp[-3].u.dfield)->get_type(), (yyvsp[-1].range)));
		(yyval.u.dfield) = (yyvsp[-3].u.dfield);
	}
#line 2081 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 714 "parser.ypp" /* yacc.c:1646  */
    {
		(yyvsp[-3].u.dfield)->set_type(new ArrayType((yyvsp[-3].u.dfield)->get_type(), (yyvsp[-1].range)));
		(yyval.u.dfield) = (yyvsp[-3].u.dfield);
	}
#line 2090 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 722 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[-1].u.dfield)->get_type(), 0));
	}
#line 2099 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 727 "parser.ypp" /* yacc.c:1646  */
    {
		if(!type_stack.empty()) depth_error(0, "field '" + (yyvsp[-3].u.dfield)->get_name() + "'");
		(yyvsp[-3].u.dfield)->set_default_value((yyvsp[0].str));
		(yyval.u.dfield) = (yyvsp[-3].u.dfield);
	}
#line 2109 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 733 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[-1].u.dfield)->get_type(), 0));
	}
#line 2118 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 738 "parser.ypp" /* yacc.c:1646  */
    {
		if(!type_stack.empty()) depth_error(0, "field '" + (yyvsp[-3].u.dfield)->get_name() + "'");
		(yyvsp[-3].u.dfield)->set_default_value((yyvsp[0].str));
		(yyval.u.dfield) = (yyvsp[-3].u.dfield);
	}
#line 2128 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 744 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[-2].u.dfield)->get_type(), 0));
	}
#line 2137 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 749 "parser.ypp" /* yacc.c:1646  */
    {
		if(!type_stack.empty()) depth_error(0, "method");
		(yyvsp[-4].u.dfield)->set_default_value((yyvsp[-2].str));
		(yyval.u.dfield) = (yyvsp[-4].u.dfield);
	}
#line 2147 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 758 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dfield) = new Field((yyvsp[0].u.dmethod), (yyvsp[-1].str));
	}
#line 2155 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 770 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].u.dtype) == nullptr)
		{
			// defined_type should have output an error, pass nullptr upstream
			(yyval.u.dtype) = nullptr;
			break;
		}

		if((yyvsp[0].u.dtype)->get_type() == T_METHOD)
		{
			parser_error("Cannot use a method type here.");
			(yyval.u.dtype) = nullptr;
			break;
		}

		(yyval.u.dtype) = (yyvsp[0].u.dtype);
	}
#line 2177 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 788 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dtype) = (DistributedType*)(yyvsp[0].u.dnumeric);
	}
#line 2185 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 796 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dtype) = new ArrayType((yyvsp[-3].u.dnumeric), (yyvsp[-1].range));
	}
#line 2193 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 800 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dtype) = new ArrayType((yyvsp[-3].u.dtype), (yyvsp[-1].range));
	}
#line 2201 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 804 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dtype) = new ArrayType((yyvsp[-3].u.dtype), (yyvsp[-1].range));
	}
#line 2209 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 808 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dtype) = new ArrayType((yyvsp[-3].u.dtype), (yyvsp[-1].range));
	}
#line 2217 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 815 "parser.ypp" /* yacc.c:1646  */
    {
		MolecularField* mol = new MolecularField(current_class, (yyvsp[-2].str));
		if((yyvsp[0].u.dfield) == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.u.dmolecule) = mol;
			break;
		}

		bool field_added = mol->add_field((yyvsp[0].u.dfield));
		if(!field_added)
		{
			if((yyvsp[0].u.dfield)->as_molecular())
			{
				parser_error("Cannot add molecular '" + (yyvsp[0].u.dfield)->get_name() + "' to a molecular field.");
			}
			else
			{
				parser_error("Unkown error adding field " + (yyvsp[0].u.dfield)->get_name() + " to molecular '"
				             + (yyvsp[-2].str) + "'.");
			}
		}

		(yyval.u.dmolecule) = mol;
	}
#line 2247 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 841 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].u.dfield) == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.u.dmolecule) = (yyvsp[-2].u.dmolecule);
			break;
		}

		bool field_added = (yyvsp[-2].u.dmolecule)->add_field((yyvsp[0].u.dfield));
		if(!field_added)
		{
			if((yyvsp[0].u.dfield)->as_molecular())
			{
				parser_error("Cannot add molecular '" + (yyvsp[0].u.dfield)->get_name() + "' to a molecular field.");
			}
			else if(!(yyvsp[-2].u.dmolecule)->has_matching_keywords(*(yyvsp[0].u.dfield)))
			{
				parser_error("Mismatched keywords in molecular between " +
					(yyvsp[-2].u.dmolecule)->get_field(0)->get_name() + " and " + (yyvsp[0].u.dfield)->get_name() + ".");
			}
			else
			{
				parser_error("Unkown error adding field " + (yyvsp[0].u.dfield)->get_name() + " to molecular '"
				             + (yyvsp[-2].u.dmolecule)->get_name() + "'.");
			}
		}

		(yyval.u.dmolecule) = (yyvsp[-2].u.dmolecule);
	}
#line 2281 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 873 "parser.ypp" /* yacc.c:1646  */
    {
		if(!current_class)
		{
			parser_error("Field '" + (yyvsp[0].str) + "' not defined in current class.");
			(yyval.u.dfield) = nullptr;
			break;
		}

		Field *field = current_class->get_field_by_name((yyvsp[0].str));
		if(field == nullptr)
		{
			parser_error("Field '" + (yyvsp[0].str) + "' not defined in current class.");
			(yyval.u.dfield) = nullptr;
			break;
		}

		(yyval.u.dfield) = field;
	}
#line 2304 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 895 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].u.type) == T_STRING)
		{
			if(basic_string == nullptr)
			{
				basic_string = new ArrayType(new NumericType(T_CHAR));
				basic_string->set_alias("string");
			}

			(yyval.u.dtype) = basic_string;
		}
		else if((yyvsp[0].u.type) == T_BLOB)
		{
			if(basic_blob == nullptr)
			{
				basic_blob = new ArrayType(new NumericType(T_UINT8));
				basic_blob->set_alias("blob");
			}

			(yyval.u.dtype) = basic_blob;
		}
		else
		{
			parser_error("Found builtin ArrayType not handled by parser.");
			(yyval.u.dtype) = nullptr;
		}
	}
#line 2336 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 923 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[-3].u.type) == T_STRING)
		{
			ArrayType* arr = new ArrayType(new NumericType(T_CHAR), (yyvsp[-1].range));
			arr->set_alias("string");
			(yyval.u.dtype) = arr;
		}
		else if((yyvsp[-3].u.type) == T_BLOB)
		{
			ArrayType* arr = new ArrayType(new NumericType(T_UINT8), (yyvsp[-1].range));
			arr->set_alias("blob");
			(yyval.u.dtype) = arr;
		}
		else
		{
			parser_error("Found builtin ArrayType not handled by parser.");
			(yyval.u.dtype) = nullptr;
		}
	}
#line 2360 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 952 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.dnumeric) = new NumericType((yyvsp[0].u.type)); }
#line 2366 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 957 "parser.ypp" /* yacc.c:1646  */
    {
		if(!(yyvsp[-3].u.dnumeric)->set_range((yyvsp[-1].range)))
		{
			parser_error("Invalid range for type.");
		}

		(yyval.u.dnumeric) = (yyvsp[-3].u.dnumeric);
	}
#line 2379 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 966 "parser.ypp" /* yacc.c:1646  */
    {
		if(!(yyvsp[-3].u.dnumeric)->set_range((yyvsp[-1].range)))
		{
			parser_error("Invalid range for type.");
		}

		(yyval.u.dnumeric) = (yyvsp[-3].u.dnumeric);
	}
#line 2392 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 975 "parser.ypp" /* yacc.c:1646  */
    {
		if(!(yyvsp[-3].u.dnumeric)->set_range((yyvsp[-1].range)))
		{
			parser_error("Invalid range for type.");
		}

		(yyval.u.dnumeric) = (yyvsp[-3].u.dnumeric);
	}
#line 2405 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 987 "parser.ypp" /* yacc.c:1646  */
    {
		if(!(yyvsp[-2].u.dnumeric)->set_modulus((yyvsp[0].u.real)))
		{
			parser_error("Invalid modulus for type.");
		}

		(yyval.u.dnumeric) = (yyvsp[-2].u.dnumeric);
	}
#line 2418 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 999 "parser.ypp" /* yacc.c:1646  */
    {
		if(!(yyvsp[-2].u.dnumeric)->set_divisor((yyvsp[0].u.uint32)))
		{
			parser_error("Invalid divisor for type.");
		}
	}
#line 2429 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 1006 "parser.ypp" /* yacc.c:1646  */
    {
		if(!(yyvsp[-2].u.dnumeric)->set_divisor((yyvsp[0].u.uint32)))
		{
			parser_error("Invalid divisor for type.");
		}
	}
#line 2440 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 1016 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dmethod) = new Method();
	}
#line 2448 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 1020 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dmethod) = (yyvsp[-1].u.dmethod);
	}
#line 2456 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 1027 "parser.ypp" /* yacc.c:1646  */
    {
		Method* fn = new Method();
		bool param_added = fn->add_parameter((yyvsp[0].u.dparam));
		if(!param_added)
		{
			parser_error("Unknown error adding parameter to method.");
		}
		(yyval.u.dmethod) = fn;
	}
#line 2470 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 1037 "parser.ypp" /* yacc.c:1646  */
    {
		bool param_added = (yyvsp[-2].u.dmethod)->add_parameter((yyvsp[0].u.dparam));
		if(!param_added)
		{
			parser_error("Cannot add parameter '" + (yyvsp[0].u.dparam)->get_name()
			             + "', a parameter with that name is already used in this method.");
		}
		(yyval.u.dmethod) = (yyvsp[-2].u.dmethod);
	}
#line 2484 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 1053 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dparam) = new Parameter((yyvsp[0].u.dtype));
	}
#line 2492 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 1057 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[-1].u.dtype),0));
	}
#line 2501 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 1062 "parser.ypp" /* yacc.c:1646  */
    {
		Parameter* param = new Parameter((yyvsp[-3].u.dtype));
		if(!type_stack.empty()) depth_error(0, "type");
		param->set_default_value((yyvsp[0].str));
		(yyval.u.dparam) = param;
	}
#line 2512 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 1071 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.u.dparam) = new Parameter((yyvsp[-1].u.dtype), (yyvsp[0].str));
	}
#line 2520 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 1078 "parser.ypp" /* yacc.c:1646  */
    {
		(yyvsp[-3].u.dparam)->set_type(new ArrayType((yyvsp[-3].u.dparam)->get_type(), (yyvsp[-1].range)));
		(yyval.u.dparam) = (yyvsp[-3].u.dparam);
	}
#line 2529 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 1083 "parser.ypp" /* yacc.c:1646  */
    {
		(yyvsp[-3].u.dparam)->set_type(new ArrayType((yyvsp[-3].u.dparam)->get_type(), (yyvsp[-1].range)));
		(yyval.u.dparam) = (yyvsp[-3].u.dparam);
	}
#line 2538 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 1091 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[-1].u.dparam)->get_type(), 0));
	}
#line 2547 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 1096 "parser.ypp" /* yacc.c:1646  */
    {
		if(!type_stack.empty()) depth_error(0, "parameter '" + (yyvsp[-3].u.dparam)->get_name() + "'");
		(yyvsp[-3].u.dparam)->set_default_value((yyvsp[0].str));
		(yyval.u.dparam) = (yyvsp[-3].u.dparam);
	}
#line 2557 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 1102 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[-1].u.dparam)->get_type(), 0));
	}
#line 2566 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 1107 "parser.ypp" /* yacc.c:1646  */
    {
		if(!type_stack.empty()) depth_error(0, "parameter '" + (yyvsp[-3].u.dparam)->get_name() + "'");
		(yyvsp[-3].u.dparam)->set_default_value((yyvsp[0].str));
		(yyval.u.dparam) = (yyvsp[-3].u.dparam);
	}
#line 2576 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 1115 "parser.ypp" /* yacc.c:1646  */
    { (yyval.range) = NumericRange(); }
#line 2582 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 1116 "parser.ypp" /* yacc.c:1646  */
    { (yyval.range) = NumericRange((yyvsp[0].u.real), (yyvsp[0].u.real)); }
#line 2588 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 1117 "parser.ypp" /* yacc.c:1646  */
    { (yyval.range) = NumericRange((yyvsp[-2].u.real), (yyvsp[0].u.real)); }
#line 2594 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 1121 "parser.ypp" /* yacc.c:1646  */
    { (yyval.range) = NumericRange(); }
#line 2600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 1122 "parser.ypp" /* yacc.c:1646  */
    { (yyval.range) = NumericRange((yyvsp[0].u.uint32), (yyvsp[0].u.uint32)); }
#line 2606 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 1123 "parser.ypp" /* yacc.c:1646  */
    { (yyval.range) = NumericRange((yyvsp[-2].u.uint32), (yyvsp[0].u.uint32)); }
#line 2612 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1128 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].str).length() != 1)
		{
			parser_error("Single character required.");
			(yyval.u.uint32) = 0;
		}
		else
		{
			(yyval.u.uint32) = (unsigned char)(yyvsp[0].str)[0];
		}
	}
#line 2628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1144 "parser.ypp" /* yacc.c:1646  */
    {
		unsigned int num = (unsigned int)(yyvsp[0].u.uint64);
		if(num != (yyvsp[0].u.uint64))
		{
			parser_error("Number out of range.");
			(yyval.u.uint32) = 1;
		}
		(yyval.u.uint32) = num;
	}
#line 2642 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1156 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.real) = (double)(yyvsp[0].u.uint64); }
#line 2648 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1157 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.real) = (double)(yyvsp[0].u.int64); }
#line 2654 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1163 "parser.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[0].str).length() != 1)
		{
			parser_error("Single character required.");
			(yyval.u.real) = 0;
		}
		else
		{
			(yyval.u.real) = (double)(unsigned char)(yyvsp[0].str)[0];
		}
	}
#line 2670 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1179 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("signed integer");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Remove numeric type from stack

		(yyval.str) = number_value(dtype->get_type(), (yyvsp[0].u.int64));
	}
#line 2689 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 1194 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("unsigned integer");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Remove numeric type from stack

		(yyval.str) = number_value(dtype->get_type(), (yyvsp[0].u.uint64));
	}
#line 2708 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 1209 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("floating point");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Remove numeric type from stack

		(yyval.str) = number_value(dtype->get_type(), (yyvsp[0].u.real));
	}
#line 2727 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 1224 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("char");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Remove type from stack

		if(dtype->get_type() != T_CHAR) {
			parser_error("Cannot use char value for non-char type '"
			             + format_type(dtype->get_type()) + "'.");
		}

		if((yyvsp[0].str).length() != 1)
		{
			parser_error("Single character required.");
			(yyval.str) = "";
		}
		else
		{
			(yyval.str) = (yyvsp[0].str);
		}
	}
#line 2759 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1252 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("string");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Remove string type from stack

		if(dtype->get_type() == T_STRING || dtype->get_type() == T_BLOB)
		{
			if((yyvsp[0].str).length() != dtype->get_size())
			{
				parser_error("Value for fixed-length string has incorrect length.");
			}

			(yyval.str) = (yyvsp[0].str);
		}
		else if(dtype->get_type() == T_VARSTRING || dtype->get_type() == T_VARBLOB)
		{
			// TODO: Check for range limits
			// Prepend length tag
			sizetag_t length = (yyvsp[0].str).length();
			length = swap_le(length);
			(yyval.str) = string((char*)&length, sizeof(sizetag_t)) + (yyvsp[0].str);
		}
		else
		{
			parser_error("Cannot use string value for non-string type '"
			             + format_type(dtype->get_type()) + "'.");
			(yyval.str) = (yyvsp[0].str);
		}
	}
#line 2800 "parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1289 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("hex-string");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Remove type from stack

		if(dtype->get_type() == T_BLOB)
		{
			if((yyvsp[0].str).length() != dtype->get_size())
			{
				parser_error("Value for fixed-length blob has incorrect length.");
			}

			(yyval.str) = (yyvsp[0].str);
		}
		else if(dtype->get_type() == T_VARBLOB)
		{
			// TODO: Check for range limits
			(yyval.str) = (yyvsp[0].str);
		}
		else
		{
			parser_error("Cannot use hex value for non-blob type '"
			             + format_type(dtype->get_type()) + "'.");
			(yyval.str) = (yyvsp[0].str);
		}
	}
#line 2838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1328 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("method");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			break;
		}
		if(dtype->as_method())
		{
			current_depth++;
			const Method* method = dtype->as_method();

			size_t num_params = method->get_num_parameters();
			for(unsigned int i = 1; i <= num_params; ++i)
			{
				// Reverse iteration
				const Parameter* param = method->get_parameter(num_params-i);
				// Add parameter types to stack such that the first is on top
				type_stack.push(TypeAndDepth(param->get_type(), current_depth));
			}
		}
		else
		{
			parser_error("Cannot use method-value for non-method type '"
			             + format_type(dtype->get_type()) + "'.");
		}
	}
#line 2872 "parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1358 "parser.ypp" /* yacc.c:1646  */
    {
		if(type_stack.top().type->as_method())
		{
			current_depth--;
		}
		type_stack.pop(); // Remove method type from the stack
		(yyval.str) = (yyvsp[-1].str);
	}
#line 2885 "parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1371 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[-2].str) + (yyvsp[0].str);
	}
#line 2893 "parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1378 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("struct");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			break;
		}
		if(dtype->as_struct())
		{
			current_depth++;
			const Struct* dstruct = dtype->as_struct();

			size_t num_fields = dstruct->get_num_fields();
			for(unsigned int i = 1; i <= num_fields; ++i)
			{
				// Reverse iteration
				const Field* field = dstruct->get_field(num_fields-i);
				// Add field types to stack such that the first is on top
				type_stack.push(TypeAndDepth(field->get_type(), current_depth));
			}
		}
		else
		{
			parser_error("Cannot use struct-composition for non-struct type '"
			             + format_type(dtype->get_type()) + "'.");
		}
	}
#line 2927 "parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1408 "parser.ypp" /* yacc.c:1646  */
    {
		if(type_stack.top().type->as_struct())
		{
			current_depth--;
		}
		type_stack.pop(); // Remove method type from the stack
		(yyval.str) = (yyvsp[-1].str);
	}
#line 2940 "parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1422 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[-2].str) + (yyvsp[0].str);
	}
#line 2948 "parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1426 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[-2].str) + (yyvsp[0].str);
	}
#line 2956 "parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1433 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("array");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop();
		if(!dtype->as_array())
		{
			parser_error("Cannot use array-composition for non-array type '"
			             + format_type(dtype->get_type()) + "'.");
			(yyval.str) = "";
			break;
		}
		const ArrayType* array = dtype->as_array();

		string val;

		if(array->get_array_size() > 0)
		{
			// For fixed size arrays, an empty array is an error
			parser_error("Fixed-sized array of size "
			             + to_string((unsigned long long)array->get_array_size())
			             + " can't have 0 elements.");
		}
		else if(array->has_range())
		{
			// If we have a range, 0 elements must be valid in the range
			if(0 < array->get_range().min.uinteger)
			{
				parser_error("Too few elements in array value, minimum "
				             + to_string(array->get_range().min.uinteger) + ".");
			}
		}

		// Since a fixed-size array can't have zero elements, this always
		// the default value for a varsize array, which is the length-tag 0.
		(yyval.str) = string(sizeof(sizetag_t), '\0');
	}
#line 3004 "parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1477 "parser.ypp" /* yacc.c:1646  */
    {
		if(!check_depth()) depth_error("array");

		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			break;
		}
		if(dtype->as_array())
		{
			const ArrayType* array = dtype->as_array();

			// For arrays we're going to do something pretty hacky:
			//    For every element we had we are going to increment the depth,
			//    and after we finish the element_values production we will compare
			//    the current_depth to the depth of our original symbol to check
			//    if the array size is proper.
			type_stack.push(TypeAndDepth(array->get_element_type(), current_depth));
		}
		else
		{
			parser_error("Cannot use array-composition for non-array type '"
			             + format_type(dtype->get_type()) + "'.");
		}
	}
#line 3035 "parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1504 "parser.ypp" /* yacc.c:1646  */
    {
		if(type_stack.top().type->as_array())
		{
			uint64_t actual_size = current_depth - type_stack.top().depth;

			const DistributedType* dtype = type_stack.top().type;
			if(dtype == nullptr)
			{
				// Ignore this field, it should have already generated an error
				(yyval.str) = "";
				break;
			}

			const ArrayType* array = dtype->as_array();
			if(array->has_range())
			{
				if(actual_size > array->get_range().max.uinteger)
				{
					parser_error("Too many elements in array value, maximum "
					             + to_string(array->get_range().max.uinteger) + ".");
				}
				else if(actual_size < array->get_range().min.uinteger)
				{
					parser_error("Too few elements in array value, minimum "
					             + to_string(array->get_range().min.uinteger) + ".");
				}
			}

			if(array->get_array_size() == 0)
			{
				sizetag_t length = (yyvsp[-1].str).length();
				(yyval.str) = string((char*)&length, sizeof(sizetag_t)) + (yyvsp[-1].str);
			}
			else
			{
				(yyval.str) = (yyvsp[-1].str);
			}
			current_depth = type_stack.top().depth;
		}

		type_stack.pop(); // Remove array type from the stack
	}
#line 3082 "parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1551 "parser.ypp" /* yacc.c:1646  */
    {
		// We popped off the only element we added, so we're back to the array
		// Don't increment the depth; the array_expansion will add to
		// the current_depth depending on the number of elements it adds.
		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			break;
		}
		const ArrayType* array = dtype->as_array();
		type_stack.push(TypeAndDepth(array->get_element_type(), current_depth));
	}
#line 3100 "parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1565 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[-3].str) + (yyvsp[0].str);
	}
#line 3108 "parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1572 "parser.ypp" /* yacc.c:1646  */
    {
		current_depth++;
		(yyval.str) = (yyvsp[0].str);
	}
#line 3117 "parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1577 "parser.ypp" /* yacc.c:1646  */
    {
		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Pop that array element type
		current_depth += (yyvsp[0].u.uint32); // For arrays, we add 1 to the depth per element

		string base = number_value(dtype->get_type(), (yyvsp[-2].u.int64));

		string val;
		val.reserve(base.length() * (yyvsp[0].u.uint32));
		for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
		{
			val += base;
		}
		(yyval.str) = val;
	}
#line 3143 "parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1599 "parser.ypp" /* yacc.c:1646  */
    {
		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Pop that array element type
		current_depth += (yyvsp[0].u.uint32); // For arrays, we add 1 to the depth per element

		string base = number_value(dtype->get_type(), (yyvsp[-2].u.uint64));

		string val;
		val.reserve(base.length() * (yyvsp[0].u.uint32));
		for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
		{
			val += base;
		}
		(yyval.str) = val;
	}
#line 3169 "parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1621 "parser.ypp" /* yacc.c:1646  */
    {
		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Pop that array element type
		current_depth += (yyvsp[0].u.uint32); // For arrays, we add 1 to the depth per element

		string base = number_value(dtype->get_type(), (yyvsp[-2].u.real));

		string val;
		val.reserve(base.length() * (yyvsp[0].u.uint32));
		for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
		{
			val += base;
		}
		(yyval.str) = val;
	}
#line 3195 "parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1643 "parser.ypp" /* yacc.c:1646  */
    {
		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Pop that array element type
		current_depth += (yyvsp[0].u.uint32); // For arrays, we add 1 to the depth per element

		if(dtype->get_type() == T_STRING)
		{
			if((yyvsp[-2].str).length() != dtype->get_size())
			{
				parser_error("Value for fixed-length string has incorrect length.");
			}

			string val;
			val.reserve((yyvsp[-2].str).length() * (yyvsp[0].u.uint32));
			for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
			{
				val += (yyvsp[-2].str);
			}
			(yyval.str) = val;
		}
		else if(dtype->get_type() == T_VARSTRING)
		{
			// TODO: Check for range limits
			// Prepend length tag
			sizetag_t length = (yyvsp[-2].str).length();
			string base = string((char*)&length, sizeof(sizetag_t)) + (yyvsp[-2].str);

			string val;
			val.reserve(base.length() * (yyvsp[0].u.uint32));
			for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
			{
				val += base;
			}
			(yyval.str) = val;
		}
		else
		{
			parser_error("Cannot use string value for non-string type '"
			             + format_type(dtype->get_type()) + "'.");

			string val;
			val.reserve((yyvsp[-2].str).length() * (yyvsp[0].u.uint32));
			for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
			{
				val += (yyvsp[-2].str);
			}
			(yyval.str) = val;
		}
	}
#line 3255 "parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1699 "parser.ypp" /* yacc.c:1646  */
    {
		const DistributedType* dtype = type_stack.top().type;
		if(dtype == nullptr)
		{
			// Ignore this field, it should have already generated an error
			(yyval.str) = "";
			break;
		}
		type_stack.pop(); // Pop that array element type
		current_depth += (yyvsp[0].u.uint32); // For arrays, we add 1 to the depth per element

		if(dtype->get_type() == T_BLOB)
		{
			if((yyvsp[-2].str).length() != dtype->get_size())
			{
				parser_error("Value for fixed-length blob has incorrect length.");
			}

			string val;
			val.reserve((yyvsp[-2].str).length() * (yyvsp[0].u.uint32));
			for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
			{
				val += (yyvsp[-2].str);
			}
			(yyval.str) = val;
		}
		else if(dtype->get_type() == T_VARBLOB)
		{
			// TODO: Check for range limits
			// Prepend length tag
			sizetag_t length = (yyvsp[-2].str).length();
			string base = string((char*)&length, sizeof(sizetag_t)) + (yyvsp[-2].str);

			string val;
			val.reserve(base.length() * (yyvsp[0].u.uint32));
			for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
			{
				val += base;
			}
			(yyval.str) = val;

		}
		else
		{
			parser_error("Cannot use hex value for non-blob type '"
			             + format_type(dtype->get_type()) + "'.");

			string val;
			val.reserve((yyvsp[-2].str).length() * (yyvsp[0].u.uint32));
			for(unsigned int i = 0; i < (yyvsp[0].u.uint32); ++i)
			{
				val += (yyvsp[-2].str);
			}
			(yyval.str) = val;
		}
	}
#line 3316 "parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1758 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.int64) = int64_t((yyvsp[0].u.uint64)); }
#line 3322 "parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1759 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.int64) = -int64_t((yyvsp[0].u.uint64)); }
#line 3328 "parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1763 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_STRING; }
#line 3334 "parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1764 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_BLOB; }
#line 3340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1768 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_CHAR; }
#line 3346 "parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1769 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_INT8; }
#line 3352 "parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1770 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_INT16; }
#line 3358 "parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1771 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_INT32; }
#line 3364 "parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1772 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_INT64; }
#line 3370 "parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1773 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_UINT8; }
#line 3376 "parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1774 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_UINT16; }
#line 3382 "parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1775 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_UINT32; }
#line 3388 "parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 1776 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_UINT64; }
#line 3394 "parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 1777 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_FLOAT32; }
#line 3400 "parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 1778 "parser.ypp" /* yacc.c:1646  */
    { (yyval.u.type) = T_FLOAT64; }
#line 3406 "parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 1783 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval.strings) = vector<string>();
	}
#line 3414 "parser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 1787 "parser.ypp" /* yacc.c:1646  */
    {
		if(!parsed_file->has_keyword((yyvsp[0].str)))
		{
			parser_error("Keyword '" + (yyvsp[0].str) + "' has not been declared.");
			break;
		}

		(yyvsp[-1].strings).push_back((yyvsp[0].str));
		(yyval.strings) = (yyvsp[-1].strings);
	}
#line 3429 "parser.cpp" /* yacc.c:1646  */
    break;


#line 3433 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1803 "parser.ypp" /* yacc.c:1906  */
 /* Start helper function section */


bool check_depth()
{
	return (!type_stack.empty() && current_depth == type_stack.top().depth);
}

void depth_error(string what)
{
	if(type_stack.empty() || current_depth < type_stack.top().depth)
	{
		parser_error("Too many nested values while parsing value for " + what + ".");
	}
	else
	{
		parser_error("Too few nested values while parsing value for " + what + ".");
	}
}

void depth_error(int depth, string what)
{
	if(current_depth > depth)
	{
		parser_error("Too few nested values before this " + what + " value.");
	}
	else
	{
		parser_error("Too many nested values before this " + what + " value.");
	}
}

string number_value(Type type, double &number)
{
	switch(type)
	{
		case T_FLOAT32:
		{
			float v = number;
			if(v == std::numeric_limits<float>::infinity() ||
			   v == -std::numeric_limits<float>::infinity())
			{
				parser_error("Value is out of range for type 'float32'.");
			}

			v = swap_le(v);
			return string((char*)&v, sizeof(float));
		}
		case T_FLOAT64:
		{
			double v = number;
			v = swap_le(v);
			return string((char*)&v, sizeof(double));
		}
		case T_INT8:
		case T_INT16:
		case T_INT32:
		case T_INT64:
		case T_CHAR:
		case T_UINT8:
		case T_UINT16:
		case T_UINT32:
		case T_UINT64:
		{
			parser_error("Cannot use floating-point value for integer datatype.");
			return string();
		}
		default:
		{
			parser_error("Cannot use floating-point value for non-numeric datatype.");
			return string();
		}
	}
}

string number_value(Type type, int64_t &number)
{
	switch(type)
	{
		case T_INT8:
		{
			if(INT8_MIN > number || number > INT8_MAX)
			{
				parser_error("Signed integer out of range for type 'int8'.");
			}

			int8_t v = number;
			return string((char*)&v, sizeof(int8_t));
		}
		case T_INT16:
		{
			if(INT16_MIN > number || number > INT16_MAX)
			{
				parser_error("Signed integer out of range for type 'int16'.");
			}

			uint16_t v = number;
			v = swap_le(v);
			return string((char*)&v, sizeof(int16_t));
		}
		case T_INT32:
		{
			if(INT32_MIN > number || number > INT32_MAX)
			{
				parser_error("Signed integer out of range for type 'int32'.");
			}

			int32_t v = number;
			v = swap_le(v);
			return string((char*)&v, sizeof(int32_t));
		}
		case T_INT64:
		{
			int64_t v = number;
			v = swap_le(v);
			return string((char*)&v, sizeof(int64_t));
		}
		case T_CHAR:
		case T_UINT8:
		case T_UINT16:
		case T_UINT32:
		case T_UINT64:
		{
			if(number < 0)
			{
				parser_error("Can't use negative value for unsigned integer datatype.");
			}
			uint64_t v = number;
			return number_value(type, v);
		}
		case T_FLOAT32:
		case T_FLOAT64:
		{
			// Note: Expecting number to be converted to a double by value (ie. -1 becomes -1.0)
			double v = number;
			return number_value(type, v);
		}
		default:
		{
			parser_error("Cannot use signed integer value for non-numeric datatype.");
			return string();
		}
	}
}

string number_value(Type type, uint64_t &number)
{
	switch(type)
	{
		case T_CHAR:
		case T_UINT8:
		{
			if(number > UINT8_MAX)
			{
				parser_error("Unsigned integer out of range for type 'uint8'.");
			}

			uint8_t v = number;
			return string((char*)&v, sizeof(uint8_t));
		}
		case T_UINT16:
		{
			if(number > UINT16_MAX)
			{
				parser_error("Unsigned integer out of range for type 'uint16'.");
			}

			uint16_t v = number;
			v = swap_le(v);
			return string((char*)&v, sizeof(uint16_t));
		}
		case T_UINT32:
		{
			if(number > UINT32_MAX)
			{
				parser_error("Unsigned integer out of range for type 'uint32'.");
			}

			uint32_t v = number;
			v = swap_le(v);
			return string((char*)&v, sizeof(uint32_t));
		}
		case T_UINT64:
		{
			uint64_t v = number;
			v = swap_le(v);
			return string((char*)&number, sizeof(uint64_t));
		}
		case T_INT8:
		case T_INT16:
		case T_INT32:
		case T_INT64:
		{
			if(number > INT64_MAX)
			{
				parser_error("Unsigned integer out of range for signed integer datatype.");
			}
			int64_t v = number;
			return number_value(type, v);
		}
		case T_FLOAT32:
		case T_FLOAT64:
		{
			// Note: Expecting number to be converted to a double by value (ie. 3 becomes 3.0)
			double v = number;
			return number_value(type, v);
		}
		default:
		{
			parser_error("Cannot use unsigned integer value for non-numeric datatype.");
			return string();
		}
	}
}


} // close namespace dclass
