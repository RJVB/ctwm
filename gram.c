/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LB = 258,
     RB = 259,
     LP = 260,
     RP = 261,
     MENUS = 262,
     MENU = 263,
     BUTTON = 264,
     DEFAULT_FUNCTION = 265,
     PLUS = 266,
     MINUS = 267,
     ALL = 268,
     OR = 269,
     CURSORS = 270,
     PIXMAPS = 271,
     ICONS = 272,
     COLOR = 273,
     SAVECOLOR = 274,
     MONOCHROME = 275,
     FUNCTION = 276,
     ICONMGR_SHOW = 277,
     ICONMGR = 278,
     ALTER = 279,
     WINDOW_FUNCTION = 280,
     ZOOM = 281,
     ICONMGRS = 282,
     ICONMGR_GEOMETRY = 283,
     ICONMGR_NOSHOW = 284,
     MAKE_TITLE = 285,
     ICONIFY_BY_UNMAPPING = 286,
     DONT_ICONIFY_BY_UNMAPPING = 287,
     NO_BORDER = 288,
     NO_ICON_TITLE = 289,
     NO_TITLE = 290,
     AUTO_RAISE = 291,
     NO_HILITE = 292,
     ICON_REGION = 293,
     WINDOW_REGION = 294,
     META = 295,
     SHIFT = 296,
     LOCK = 297,
     CONTROL = 298,
     WINDOW = 299,
     TITLE = 300,
     ICON = 301,
     ROOT = 302,
     FRAME = 303,
     COLON = 304,
     EQUALS = 305,
     SQUEEZE_TITLE = 306,
     DONT_SQUEEZE_TITLE = 307,
     START_ICONIFIED = 308,
     NO_TITLE_HILITE = 309,
     TITLE_HILITE = 310,
     MOVE = 311,
     RESIZE = 312,
     WAITC = 313,
     SELECT = 314,
     KILL = 315,
     LEFT_TITLEBUTTON = 316,
     RIGHT_TITLEBUTTON = 317,
     NUMBER = 318,
     KEYWORD = 319,
     NKEYWORD = 320,
     CKEYWORD = 321,
     CLKEYWORD = 322,
     FKEYWORD = 323,
     FSKEYWORD = 324,
     SKEYWORD = 325,
     DKEYWORD = 326,
     JKEYWORD = 327,
     WINDOW_RING = 328,
     WARP_CURSOR = 329,
     ERRORTOKEN = 330,
     NO_STACKMODE = 331,
     ALWAYS_ON_TOP = 332,
     WORKSPACE = 333,
     WORKSPACES = 334,
     WORKSPCMGR_GEOMETRY = 335,
     OCCUPYALL = 336,
     OCCUPYLIST = 337,
     MAPWINDOWCURRENTWORKSPACE = 338,
     MAPWINDOWDEFAULTWORKSPACE = 339,
     UNMAPBYMOVINGFARAWAY = 340,
     OPAQUEMOVE = 341,
     NOOPAQUEMOVE = 342,
     OPAQUERESIZE = 343,
     NOOPAQUERESIZE = 344,
     DONTSETINACTIVE = 345,
     CHANGE_WORKSPACE_FUNCTION = 346,
     DEICONIFY_FUNCTION = 347,
     ICONIFY_FUNCTION = 348,
     AUTOSQUEEZE = 349,
     STARTSQUEEZED = 350,
     STRING = 351
   };
#endif
/* Tokens.  */
#define LB 258
#define RB 259
#define LP 260
#define RP 261
#define MENUS 262
#define MENU 263
#define BUTTON 264
#define DEFAULT_FUNCTION 265
#define PLUS 266
#define MINUS 267
#define ALL 268
#define OR 269
#define CURSORS 270
#define PIXMAPS 271
#define ICONS 272
#define COLOR 273
#define SAVECOLOR 274
#define MONOCHROME 275
#define FUNCTION 276
#define ICONMGR_SHOW 277
#define ICONMGR 278
#define ALTER 279
#define WINDOW_FUNCTION 280
#define ZOOM 281
#define ICONMGRS 282
#define ICONMGR_GEOMETRY 283
#define ICONMGR_NOSHOW 284
#define MAKE_TITLE 285
#define ICONIFY_BY_UNMAPPING 286
#define DONT_ICONIFY_BY_UNMAPPING 287
#define NO_BORDER 288
#define NO_ICON_TITLE 289
#define NO_TITLE 290
#define AUTO_RAISE 291
#define NO_HILITE 292
#define ICON_REGION 293
#define WINDOW_REGION 294
#define META 295
#define SHIFT 296
#define LOCK 297
#define CONTROL 298
#define WINDOW 299
#define TITLE 300
#define ICON 301
#define ROOT 302
#define FRAME 303
#define COLON 304
#define EQUALS 305
#define SQUEEZE_TITLE 306
#define DONT_SQUEEZE_TITLE 307
#define START_ICONIFIED 308
#define NO_TITLE_HILITE 309
#define TITLE_HILITE 310
#define MOVE 311
#define RESIZE 312
#define WAITC 313
#define SELECT 314
#define KILL 315
#define LEFT_TITLEBUTTON 316
#define RIGHT_TITLEBUTTON 317
#define NUMBER 318
#define KEYWORD 319
#define NKEYWORD 320
#define CKEYWORD 321
#define CLKEYWORD 322
#define FKEYWORD 323
#define FSKEYWORD 324
#define SKEYWORD 325
#define DKEYWORD 326
#define JKEYWORD 327
#define WINDOW_RING 328
#define WARP_CURSOR 329
#define ERRORTOKEN 330
#define NO_STACKMODE 331
#define ALWAYS_ON_TOP 332
#define WORKSPACE 333
#define WORKSPACES 334
#define WORKSPCMGR_GEOMETRY 335
#define OCCUPYALL 336
#define OCCUPYLIST 337
#define MAPWINDOWCURRENTWORKSPACE 338
#define MAPWINDOWDEFAULTWORKSPACE 339
#define UNMAPBYMOVINGFARAWAY 340
#define OPAQUEMOVE 341
#define NOOPAQUEMOVE 342
#define OPAQUERESIZE 343
#define NOOPAQUERESIZE 344
#define DONTSETINACTIVE 345
#define CHANGE_WORKSPACE_FUNCTION 346
#define DEICONIFY_FUNCTION 347
#define ICONIFY_FUNCTION 348
#define AUTOSQUEEZE 349
#define STARTSQUEEZED 350
#define STRING 351




/* Copy the first part of user declarations.  */
#line 67 "gram.y"

#include <stdio.h>
#include <ctype.h>
#include "twm.h"
#include "menus.h"
#include "icons.h"
#include "add_window.h"
#include "list.h"
#include "util.h"
#include "screen.h"
#include "parse.h"
#include "cursor.h"
#ifdef VMS
#  include <decw$include/Xos.h>
#  include <X11Xmu/CharSet.h>
#else
#  include <X11/Xos.h>
#  include <X11/Xmu/CharSet.h>
#endif

static char *Action = "";
static char *Name = "";
static char *defstring = "default";
static MenuRoot	*root, *pull = NULL;
static char *curWorkSpc;
static char *client, *workspace;
static MenuItem *lastmenuitem = (MenuItem*) 0;

extern yyerror();
extern RemoveDQuote();

static MenuRoot *GetRoot();

static Bool CheckWarpScreenArg(), CheckWarpRingArg();
static Bool CheckColormapArg();
static void GotButton(), GotKey(), GotTitleButton();
static char *ptr;
static name_list **list;
static int cont = 0;
static int color;
int mods = 0;
unsigned int mods_used = (ShiftMask | ControlMask | Mod1Mask);

extern twmrc_error_prefix();

extern int do_single_keyword(), do_string_keyword(), do_number_keyword();
extern name_list **do_colorlist_keyword();
extern int do_color_keyword(), do_string_savecolor();
extern int do_var_savecolor(), do_squeeze_entry();
extern int yylineno;
extern yylex();


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 121 "gram.y"
{
    int num;
    unsigned char *ptr;
}
/* Line 193 of yacc.c.  */
#line 346 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 359 "y.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   506

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  123
/* YYNRULES -- Number of rules.  */
#define YYNRULES  300
/* YYNRULES -- Number of states.  */
#define YYNSTATES  431

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   351

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    13,    15,    17,
      19,    26,    34,    43,    53,    54,    63,    64,    74,    75,
      86,    87,    99,   100,   107,   111,   114,   118,   121,   122,
     126,   127,   131,   134,   136,   139,   142,   143,   147,   149,
     150,   154,   156,   157,   161,   163,   164,   168,   170,   171,
     175,   177,   182,   187,   188,   193,   194,   199,   202,   205,
     208,   211,   212,   216,   217,   221,   222,   226,   227,   231,
     232,   236,   237,   241,   242,   246,   247,   251,   252,   256,
     258,   259,   263,   264,   268,   269,   273,   275,   276,   280,
     282,   283,   287,   288,   292,   294,   295,   299,   300,   304,
     306,   307,   311,   313,   314,   318,   319,   323,   324,   328,
     330,   331,   341,   342,   347,   348,   353,   354,   358,   359,
     363,   364,   368,   369,   373,   376,   379,   382,   385,   388,
     389,   393,   395,   396,   400,   402,   404,   407,   409,   412,
     419,   426,   427,   430,   432,   434,   436,   438,   441,   444,
     446,   447,   450,   452,   454,   456,   458,   460,   462,   464,
     466,   468,   470,   471,   474,   476,   478,   480,   482,   484,
     486,   488,   490,   492,   494,   496,   500,   501,   504,   508,
     512,   513,   516,   519,   523,   524,   527,   531,   534,   538,
     541,   545,   548,   552,   555,   559,   562,   566,   569,   573,
     576,   580,   583,   587,   590,   594,   597,   601,   604,   608,
     609,   612,   615,   616,   621,   624,   628,   629,   632,   634,
     636,   640,   641,   644,   647,   649,   650,   656,   658,   659,
     663,   664,   670,   674,   675,   678,   682,   687,   691,   692,
     695,   697,   698,   702,   706,   707,   710,   712,   715,   719,
     724,   730,   734,   739,   745,   752,   756,   761,   767,   774,
     778,   779,   782,   784,   788,   789,   792,   793,   797,   798,
     803,   804,   809,   813,   814,   817,   819,   823,   824,   827,
     829,   833,   834,   837,   840,   844,   845,   848,   850,   854,
     855,   858,   861,   869,   871,   874,   876,   879,   882,   885,
     887
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      98,     0,    -1,    99,    -1,    -1,    99,   100,    -1,     1,
      -1,   145,    -1,   146,    -1,   147,    -1,   175,    -1,    38,
     218,    71,    71,   219,   219,    -1,    38,   218,    71,    71,
     219,   219,   218,    -1,    38,   218,    71,    71,   219,   219,
     218,   218,    -1,    38,   218,    71,    71,   219,   219,   218,
     218,   218,    -1,    -1,    38,   218,    71,    71,   219,   219,
     101,   191,    -1,    -1,    38,   218,    71,    71,   219,   219,
     218,   102,   191,    -1,    -1,    38,   218,    71,    71,   219,
     219,   218,   218,   103,   191,    -1,    -1,    38,   218,    71,
      71,   219,   219,   218,   218,   218,   104,   191,    -1,    -1,
      39,   218,    71,    71,   105,   191,    -1,    28,   218,   219,
      -1,    28,   218,    -1,    80,   218,   219,    -1,    80,   218,
      -1,    -1,    83,   106,   189,    -1,    -1,    84,   107,   190,
      -1,    26,   219,    -1,    26,    -1,    16,   159,    -1,    15,
     162,    -1,    -1,    31,   108,   191,    -1,    31,    -1,    -1,
      86,   109,   191,    -1,    86,    -1,    -1,    87,   110,   191,
      -1,    87,    -1,    -1,    88,   111,   191,    -1,    88,    -1,
      -1,    89,   112,   191,    -1,    89,    -1,    61,   218,    50,
     215,    -1,    62,   218,    50,   215,    -1,    -1,    61,   218,
     113,   156,    -1,    -1,    62,   218,   114,   156,    -1,   217,
     218,    -1,   217,   215,    -1,   218,   149,    -1,   217,   148,
      -1,    -1,    32,   115,   191,    -1,    -1,    79,   116,   182,
      -1,    -1,    81,   117,   191,    -1,    -1,    82,   118,   194,
      -1,    -1,    85,   119,   191,    -1,    -1,    94,   120,   191,
      -1,    -1,    95,   121,   191,    -1,    -1,    90,   122,   191,
      -1,    -1,    29,   123,   191,    -1,    29,    -1,    -1,    27,
     124,   179,    -1,    -1,    22,   125,   191,    -1,    -1,    54,
     126,   191,    -1,    54,    -1,    -1,    37,   127,   191,    -1,
      37,    -1,    -1,    77,   128,   191,    -1,    -1,    76,   129,
     191,    -1,    76,    -1,    -1,    33,   130,   191,    -1,    -1,
      34,   131,   191,    -1,    34,    -1,    -1,    35,   132,   191,
      -1,    35,    -1,    -1,    30,   133,   191,    -1,    -1,    53,
     134,   191,    -1,    -1,    36,   135,   191,    -1,    36,    -1,
      -1,     8,   218,     5,   218,    49,   218,     6,   136,   212,
      -1,    -1,     8,   218,   137,   212,    -1,    -1,    21,   218,
     138,   209,    -1,    -1,    17,   139,   206,    -1,    -1,    18,
     140,   165,    -1,    -1,    19,   141,   169,    -1,    -1,    20,
     142,   165,    -1,    10,   215,    -1,    25,   215,    -1,    91,
     215,    -1,    92,   215,    -1,    93,   215,    -1,    -1,    74,
     143,   191,    -1,    74,    -1,    -1,    73,   144,   191,    -1,
      73,    -1,    64,    -1,    70,   218,    -1,    70,    -1,    65,
     219,    -1,    50,   150,    49,   152,    49,   215,    -1,    50,
     150,    49,   154,    49,   215,    -1,    -1,   150,   151,    -1,
      40,    -1,    41,    -1,    42,    -1,    43,    -1,    24,   219,
      -1,    40,   219,    -1,    14,    -1,    -1,   152,   153,    -1,
      44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,
      23,    -1,    40,    -1,    24,    -1,    13,    -1,    14,    -1,
      -1,   154,   155,    -1,    44,    -1,    45,    -1,    46,    -1,
      47,    -1,    48,    -1,    23,    -1,    40,    -1,    13,    -1,
      24,    -1,    14,    -1,   218,    -1,     3,   157,     4,    -1,
      -1,   157,   158,    -1,   217,    49,   215,    -1,     3,   160,
       4,    -1,    -1,   160,   161,    -1,    55,   218,    -1,     3,
     163,     4,    -1,    -1,   163,   164,    -1,    48,   218,   218,
      -1,    48,   218,    -1,    45,   218,   218,    -1,    45,   218,
      -1,    46,   218,   218,    -1,    46,   218,    -1,    23,   218,
     218,    -1,    23,   218,    -1,     9,   218,   218,    -1,     9,
     218,    -1,    56,   218,   218,    -1,    56,   218,    -1,    57,
     218,   218,    -1,    57,   218,    -1,    58,   218,   218,    -1,
      58,   218,    -1,     8,   218,   218,    -1,     8,   218,    -1,
      59,   218,   218,    -1,    59,   218,    -1,    60,   218,   218,
      -1,    60,   218,    -1,     3,   166,     4,    -1,    -1,   166,
     167,    -1,    67,   218,    -1,    -1,    67,   218,   168,   172,
      -1,    66,   218,    -1,     3,   170,     4,    -1,    -1,   170,
     171,    -1,   218,    -1,    67,    -1,     3,   173,     4,    -1,
      -1,   173,   174,    -1,   218,   218,    -1,    51,    -1,    -1,
      51,   176,     3,   178,     4,    -1,    52,    -1,    -1,    52,
     177,   191,    -1,    -1,   178,   218,    72,   216,   219,    -1,
       3,   180,     4,    -1,    -1,   180,   181,    -1,   218,   218,
     219,    -1,   218,   218,   218,   219,    -1,     3,   183,     4,
      -1,    -1,   183,   184,    -1,   218,    -1,    -1,   218,   185,
     186,    -1,     3,   187,     4,    -1,    -1,   187,   188,    -1,
     218,    -1,   218,   218,    -1,   218,   218,   218,    -1,   218,
     218,   218,   218,    -1,   218,   218,   218,   218,   218,    -1,
       3,   218,     4,    -1,     3,   218,   218,     4,    -1,     3,
     218,   218,   218,     4,    -1,     3,   218,   218,   218,   218,
       4,    -1,     3,   218,     4,    -1,     3,   218,   218,     4,
      -1,     3,   218,   218,   218,     4,    -1,     3,   218,   218,
     218,   218,     4,    -1,     3,   192,     4,    -1,    -1,   192,
     193,    -1,   218,    -1,     3,   195,     4,    -1,    -1,   195,
     196,    -1,    -1,   218,   197,   200,    -1,    -1,    44,   218,
     198,   200,    -1,    -1,    78,   218,   199,   203,    -1,     3,
     201,     4,    -1,    -1,   201,   202,    -1,   218,    -1,     3,
     204,     4,    -1,    -1,   204,   205,    -1,   218,    -1,     3,
     207,     4,    -1,    -1,   207,   208,    -1,   218,   218,    -1,
       3,   210,     4,    -1,    -1,   210,   211,    -1,   215,    -1,
       3,   213,     4,    -1,    -1,   213,   214,    -1,   218,   215,
      -1,   218,     5,   218,    49,   218,     6,   215,    -1,    68,
      -1,    69,   218,    -1,   219,    -1,    11,   219,    -1,    12,
     219,    -1,     9,   219,    -1,    96,    -1,    63,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   152,   152,   155,   156,   159,   160,   161,   162,   163,
     164,   167,   170,   173,   176,   176,   180,   180,   184,   184,
     188,   188,   193,   193,   198,   204,   207,   213,   216,   216,
     219,   219,   222,   228,   230,   231,   232,   232,   234,   237,
     237,   239,   240,   240,   242,   243,   243,   245,   246,   246,
     248,   250,   253,   256,   256,   258,   258,   260,   264,   280,
     281,   283,   283,   285,   285,   287,   287,   289,   289,   291,
     291,   293,   293,   295,   295,   297,   297,   299,   299,   301,
     302,   302,   304,   304,   306,   306,   308,   310,   310,   312,
     314,   314,   316,   316,   318,   320,   320,   322,   322,   324,
     326,   326,   328,   330,   330,   332,   332,   334,   334,   336,
     337,   337,   340,   340,   342,   342,   344,   344,   346,   346,
     348,   348,   350,   350,   352,   368,   376,   384,   392,   400,
     400,   402,   404,   404,   406,   409,   419,   427,   437,   449,
     452,   455,   456,   459,   460,   461,   462,   463,   473,   483,
     486,   487,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   502,   503,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   515,   516,   520,   523,   524,   527,   531,
     534,   535,   538,   542,   545,   546,   549,   551,   553,   555,
     557,   559,   561,   563,   565,   567,   569,   571,   573,   575,
     577,   579,   581,   583,   585,   587,   589,   591,   595,   599,
     600,   603,   612,   612,   623,   634,   637,   638,   641,   642,
     645,   648,   649,   652,   657,   660,   660,   665,   666,   666,
     670,   671,   679,   682,   683,   686,   691,   699,   702,   703,
     706,   709,   709,   715,   718,   719,   722,   725,   728,   731,
     734,   739,   742,   745,   748,   753,   756,   759,   762,   767,
     770,   771,   774,   779,   782,   783,   786,   786,   788,   788,
     790,   790,   794,   797,   798,   801,   805,   808,   809,   812,
     816,   819,   820,   823,   826,   829,   830,   833,   839,   842,
     843,   846,   856,   868,   869,   910,   911,   912,   915,   927,
     932
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LB", "RB", "LP", "RP", "MENUS", "MENU",
  "BUTTON", "DEFAULT_FUNCTION", "PLUS", "MINUS", "ALL", "OR", "CURSORS",
  "PIXMAPS", "ICONS", "COLOR", "SAVECOLOR", "MONOCHROME", "FUNCTION",
  "ICONMGR_SHOW", "ICONMGR", "ALTER", "WINDOW_FUNCTION", "ZOOM",
  "ICONMGRS", "ICONMGR_GEOMETRY", "ICONMGR_NOSHOW", "MAKE_TITLE",
  "ICONIFY_BY_UNMAPPING", "DONT_ICONIFY_BY_UNMAPPING", "NO_BORDER",
  "NO_ICON_TITLE", "NO_TITLE", "AUTO_RAISE", "NO_HILITE", "ICON_REGION",
  "WINDOW_REGION", "META", "SHIFT", "LOCK", "CONTROL", "WINDOW", "TITLE",
  "ICON", "ROOT", "FRAME", "COLON", "EQUALS", "SQUEEZE_TITLE",
  "DONT_SQUEEZE_TITLE", "START_ICONIFIED", "NO_TITLE_HILITE",
  "TITLE_HILITE", "MOVE", "RESIZE", "WAITC", "SELECT", "KILL",
  "LEFT_TITLEBUTTON", "RIGHT_TITLEBUTTON", "NUMBER", "KEYWORD", "NKEYWORD",
  "CKEYWORD", "CLKEYWORD", "FKEYWORD", "FSKEYWORD", "SKEYWORD", "DKEYWORD",
  "JKEYWORD", "WINDOW_RING", "WARP_CURSOR", "ERRORTOKEN", "NO_STACKMODE",
  "ALWAYS_ON_TOP", "WORKSPACE", "WORKSPACES", "WORKSPCMGR_GEOMETRY",
  "OCCUPYALL", "OCCUPYLIST", "MAPWINDOWCURRENTWORKSPACE",
  "MAPWINDOWDEFAULTWORKSPACE", "UNMAPBYMOVINGFARAWAY", "OPAQUEMOVE",
  "NOOPAQUEMOVE", "OPAQUERESIZE", "NOOPAQUERESIZE", "DONTSETINACTIVE",
  "CHANGE_WORKSPACE_FUNCTION", "DEICONIFY_FUNCTION", "ICONIFY_FUNCTION",
  "AUTOSQUEEZE", "STARTSQUEEZED", "STRING", "$accept", "twmrc", "stmts",
  "stmt", "@1", "@2", "@3", "@4", "@5", "@6", "@7", "@8", "@9", "@10",
  "@11", "@12", "@13", "@14", "@15", "@16", "@17", "@18", "@19", "@20",
  "@21", "@22", "@23", "@24", "@25", "@26", "@27", "@28", "@29", "@30",
  "@31", "@32", "@33", "@34", "@35", "@36", "@37", "@38", "@39", "@40",
  "@41", "@42", "@43", "@44", "noarg", "sarg", "narg", "full", "fullkey",
  "keys", "key", "contexts", "context", "contextkeys", "contextkey",
  "binding_list", "binding_entries", "binding_entry", "pixmap_list",
  "pixmap_entries", "pixmap_entry", "cursor_list", "cursor_entries",
  "cursor_entry", "color_list", "color_entries", "color_entry", "@45",
  "save_color_list", "s_color_entries", "s_color_entry", "win_color_list",
  "win_color_entries", "win_color_entry", "squeeze", "@46", "@47",
  "win_sqz_entries", "iconm_list", "iconm_entries", "iconm_entry",
  "workspc_list", "workspc_entries", "workspc_entry", "@48",
  "workapp_list", "workapp_entries", "workapp_entry", "curwork", "defwork",
  "win_list", "win_entries", "win_entry", "occupy_list", "occupy_entries",
  "occupy_entry", "@49", "@50", "@51", "occupy_workspc_list",
  "occupy_workspc_entries", "occupy_workspc_entry", "occupy_window_list",
  "occupy_window_entries", "occupy_window_entry", "icon_list",
  "icon_entries", "icon_entry", "function", "function_entries",
  "function_entry", "menu", "menu_entries", "menu_entry", "action",
  "signed_number", "button", "string", "number", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    99,    99,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   101,   100,   102,   100,   103,   100,
     104,   100,   105,   100,   100,   100,   100,   100,   106,   100,
     107,   100,   100,   100,   100,   100,   108,   100,   100,   109,
     100,   100,   110,   100,   100,   111,   100,   100,   112,   100,
     100,   100,   100,   113,   100,   114,   100,   100,   100,   100,
     100,   115,   100,   116,   100,   117,   100,   118,   100,   119,
     100,   120,   100,   121,   100,   122,   100,   123,   100,   100,
     124,   100,   125,   100,   126,   100,   100,   127,   100,   100,
     128,   100,   129,   100,   100,   130,   100,   131,   100,   100,
     132,   100,   100,   133,   100,   134,   100,   135,   100,   100,
     136,   100,   137,   100,   138,   100,   139,   100,   140,   100,
     141,   100,   142,   100,   100,   100,   100,   100,   100,   143,
     100,   100,   144,   100,   100,   145,   146,   146,   147,   148,
     149,   150,   150,   151,   151,   151,   151,   151,   151,   151,
     152,   152,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   154,   154,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   156,   157,   157,   158,   159,
     160,   160,   161,   162,   163,   163,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   165,   166,
     166,   167,   168,   167,   167,   169,   170,   170,   171,   171,
     172,   173,   173,   174,   175,   176,   175,   175,   177,   175,
     178,   178,   179,   180,   180,   181,   181,   182,   183,   183,
     184,   185,   184,   186,   187,   187,   188,   188,   188,   188,
     188,   189,   189,   189,   189,   190,   190,   190,   190,   191,
     192,   192,   193,   194,   195,   195,   197,   196,   198,   196,
     199,   196,   200,   201,   201,   202,   203,   204,   204,   205,
     206,   207,   207,   208,   209,   210,   210,   211,   212,   213,
     213,   214,   214,   215,   215,   216,   216,   216,   217,   218,
     219
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       6,     7,     8,     9,     0,     8,     0,     9,     0,    10,
       0,    11,     0,     6,     3,     2,     3,     2,     0,     3,
       0,     3,     2,     1,     2,     2,     0,     3,     1,     0,
       3,     1,     0,     3,     1,     0,     3,     1,     0,     3,
       1,     4,     4,     0,     4,     0,     4,     2,     2,     2,
       2,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     1,
       0,     3,     0,     3,     0,     3,     1,     0,     3,     1,
       0,     3,     0,     3,     1,     0,     3,     0,     3,     1,
       0,     3,     1,     0,     3,     0,     3,     0,     3,     1,
       0,     9,     0,     4,     0,     4,     0,     3,     0,     3,
       0,     3,     0,     3,     2,     2,     2,     2,     2,     0,
       3,     1,     0,     3,     1,     1,     2,     1,     2,     6,
       6,     0,     2,     1,     1,     1,     1,     2,     2,     1,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     2,     3,     3,
       0,     2,     2,     3,     0,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     3,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     3,     2,     3,     2,     3,     0,
       2,     2,     0,     4,     2,     3,     0,     2,     1,     1,
       3,     0,     2,     2,     1,     0,     5,     1,     0,     3,
       0,     5,     3,     0,     2,     3,     4,     3,     0,     2,
       1,     0,     3,     3,     0,     2,     1,     2,     3,     4,
       5,     3,     4,     5,     6,     3,     4,     5,     6,     3,
       0,     2,     1,     3,     0,     2,     0,     3,     0,     4,
       0,     4,     3,     0,     2,     1,     3,     0,     2,     1,
       3,     0,     2,     2,     3,     0,     2,     1,     3,     0,
       2,     2,     7,     1,     2,     1,     2,     2,     2,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     0,     1,     5,     0,     0,     0,     0,     0,
     116,   118,   120,   122,     0,    82,     0,    33,    80,     0,
      79,   103,    38,    61,    95,    99,   102,   109,    89,     0,
       0,   224,   227,   105,    86,     0,     0,   135,     0,   137,
     134,   131,    94,    90,    63,     0,    65,    67,    28,    30,
      69,    41,    44,    47,    50,    75,     0,     0,     0,    71,
      73,   299,     4,     6,     7,     8,     9,     0,     0,   112,
     300,   298,   293,     0,   124,   184,    35,   180,    34,     0,
       0,     0,     0,   114,     0,   125,    32,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    53,    55,   138,   136,     0,     0,
       0,     0,     0,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   126,   127,   128,     0,     0,   141,
      60,    58,    57,   141,    59,     0,     0,   294,     0,     0,
     281,   117,   209,   119,   216,   121,   123,     0,   260,    83,
     233,    81,    24,    78,   104,    37,    62,    96,    98,   101,
     108,    88,     0,     0,   230,   229,   106,    85,     0,     0,
       0,     0,   133,   130,    93,    91,   238,    64,    26,    66,
     264,    68,     0,    29,     0,    31,    70,    40,    43,    46,
      49,    76,    72,    74,     0,     0,     0,   289,   113,   183,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   185,   179,     0,   181,     0,     0,     0,   285,   115,
       0,     0,     0,    22,     0,    51,   176,    54,    52,    56,
       0,     0,     0,     0,   149,     0,   143,   144,   145,   146,
     150,   142,   162,     0,     0,   203,   195,   193,   189,   191,
     187,   197,   199,   201,   205,   207,   182,   280,   282,     0,
     208,     0,     0,   210,   215,   219,   217,   218,     0,   259,
     261,   262,   232,   234,     0,     0,     0,   226,     0,     0,
     237,   239,   240,   263,     0,     0,   265,   266,   251,     0,
     255,     0,   147,   148,     0,     0,     0,   288,   290,     0,
     202,   194,   192,   188,   190,   186,   196,   198,   200,   204,
     206,   283,   214,   211,   284,   286,   287,     0,    10,    23,
       0,   175,   177,     0,     0,   268,   270,     0,   252,     0,
     256,     0,   160,   161,   157,   159,   158,   152,   153,   154,
     155,   156,     0,   151,   171,   173,   169,   172,   170,   164,
     165,   166,   167,   168,     0,   163,   174,   110,     0,   291,
       0,     0,   235,     0,    11,     0,     0,     0,   295,     0,
     244,   242,     0,     0,   273,   267,   253,     0,   257,     0,
     139,   140,     0,     0,   221,   213,   236,    15,     0,    12,
     296,   297,   231,   178,     0,   269,   277,   271,     0,   254,
     258,   111,     0,     0,    17,     0,    13,   243,   245,   246,
       0,   272,   274,   275,     0,   220,   222,     0,    19,     0,
     247,   276,   278,   279,     0,   223,    21,   248,   292,   249,
     250
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    62,   363,   388,   405,   419,   276,   116,
     117,    91,   119,   120,   121,   122,   169,   171,    92,   112,
     114,   115,   118,   127,   128,   123,    89,    87,    84,   103,
      97,   111,   110,    93,    94,    95,    90,   102,    96,   382,
     136,   147,    79,    80,    81,    82,   109,   108,    63,    64,
      65,   130,   134,   194,   241,   294,   343,   295,   355,   227,
     279,   322,    78,   139,   214,    76,   138,   211,   143,   216,
     263,   360,   145,   217,   266,   385,   403,   416,    66,   100,
     101,   224,   151,   221,   273,   177,   230,   281,   324,   371,
     394,   408,   183,   185,   149,   220,   270,   181,   231,   286,
     327,   372,   373,   375,   398,   412,   397,   410,   422,   141,
     215,   258,   219,   268,   315,   198,   244,   298,    74,   367,
      67,    68,    71
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -165
static const yytype_int16 yypact[] =
{
    -165,    20,   410,  -165,  -165,   -93,   -57,   -51,    41,    42,
    -165,  -165,  -165,  -165,   -93,  -165,   -51,   -57,  -165,   -93,
      50,  -165,    51,  -165,  -165,    52,    54,    55,    61,   -93,
     -93,    64,    66,  -165,    67,   -93,   -93,  -165,   -57,   -93,
      77,    83,    85,  -165,  -165,   -93,  -165,  -165,  -165,  -165,
    -165,    86,    92,   103,   105,  -165,   -51,   -51,   -51,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,    82,   -12,   121,
    -165,  -165,  -165,   -93,  -165,  -165,  -165,  -165,  -165,   126,
     133,   136,   133,  -165,   137,  -165,  -165,   138,   -57,   137,
     137,   137,   137,   137,   137,   137,   137,   137,    71,    72,
     141,   137,   137,   137,    95,    96,  -165,  -165,   137,   137,
     137,   137,   146,   -57,   137,   149,   150,   151,   137,   137,
     137,   137,   137,   137,  -165,  -165,  -165,   137,   137,  -165,
    -165,  -165,  -165,  -165,  -165,   -93,   154,  -165,   284,     6,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,   155,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,    88,    90,  -165,  -165,  -165,  -165,   -51,   160,
     -51,   160,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,   -93,  -165,   -93,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   254,   259,   118,  -165,  -165,  -165,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,  -165,  -165,   -93,  -165,    11,    56,    15,  -165,  -165,
      17,    18,   -57,  -165,    19,  -165,  -165,  -165,  -165,  -165,
      22,     3,    23,    24,  -165,   -57,   -57,  -165,  -165,  -165,
    -165,  -165,  -165,   -93,    25,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,  -165,  -165,  -165,   -93,
    -165,   -93,   -93,  -165,  -165,  -165,  -165,  -165,    48,  -165,
    -165,  -165,  -165,  -165,   -93,   -57,   137,  -165,   102,    47,
    -165,  -165,   172,  -165,   -93,   -93,  -165,  -165,  -165,    28,
    -165,    29,  -165,  -165,   142,   124,   170,  -165,  -165,    -3,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,   177,  -165,  -165,  -165,   -50,    -2,  -165,
       0,  -165,  -165,   132,   180,  -165,  -165,   181,  -165,    31,
    -165,    32,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,   -51,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   -51,  -165,  -165,  -165,   -93,  -165,
     182,   -57,  -165,   137,     1,   -57,   -57,   -57,  -165,   -51,
    -165,  -165,   181,   189,  -165,  -165,  -165,   190,  -165,   202,
    -165,  -165,   154,   144,  -165,  -165,  -165,  -165,   137,     2,
    -165,  -165,  -165,  -165,    35,  -165,  -165,  -165,    37,  -165,
    -165,  -165,   -93,    38,  -165,   137,   204,  -165,  -165,   -93,
      39,  -165,  -165,  -165,   203,  -165,  -165,   -93,  -165,   137,
     -93,  -165,  -165,  -165,   -51,  -165,  -165,   -93,  -165,   -93,
    -165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,    78,  -165,  -165,  -165,  -165,  -165,    43,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   131,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   -18,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -155,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -164,  -165,  -165,    -8,  -165,
     -56,    -5,    -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -242
static const yytype_int16 yytable[] =
{
      69,   -14,   358,    61,   -16,   -18,    70,   283,    85,    83,
     212,   365,   366,    70,    88,   257,    86,    72,    73,   264,
       3,   269,   272,   277,    98,    99,   280,   288,   290,   297,
     104,   105,   328,   330,   107,   376,   378,   106,   133,   407,
     113,   411,   415,   421,    75,    77,    61,   284,   124,   125,
     126,   321,   314,   -77,   -36,   -97,     6,  -100,  -107,   131,
     260,   213,   132,    70,   -87,    72,    73,  -225,   137,  -228,
     -84,   153,   154,   155,   156,   157,   158,   159,   160,   161,
    -132,   285,   265,   165,   166,   167,  -129,   152,   -92,   -39,
     172,   173,   174,   175,    61,   -42,   179,    61,    61,    61,
     186,   187,   188,   189,   190,   191,   -45,    61,   -48,   192,
     193,    61,   178,    61,    61,    61,    72,    73,    61,    61,
      61,    61,   261,   262,    61,    61,   135,    61,    61,   140,
     196,    61,   129,    61,    61,    61,   142,   344,   345,   144,
     148,   150,   162,   163,   164,   168,   170,   346,   347,   176,
      72,    73,   180,   182,   184,   332,   333,   197,   218,   222,
     225,   223,   228,   226,   348,   334,   335,   243,   349,   350,
     351,   352,   353,   354,   320,  -241,   357,   232,    61,   233,
    -212,   369,   336,   370,   374,   384,   337,   338,   339,   340,
     341,   342,   396,   402,   399,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   400,   -20,   256,   424,
     259,   195,   267,   146,   229,   271,   274,   395,   401,   278,
      61,   275,     0,   323,     0,   282,   287,   289,   291,     0,
       0,     0,     0,     0,   292,   293,     0,     0,   296,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,     0,     0,     0,   311,     0,   312,   313,   319,     0,
     316,     0,     0,     0,     0,     0,     0,     0,   234,   317,
       0,     0,     0,   234,   318,     0,     0,     0,   235,   325,
     326,     0,     0,   235,   329,     0,   331,     0,   199,     0,
     356,   359,   200,   201,   236,   237,   238,   239,     0,   236,
     237,   238,   239,   240,     0,     0,     0,   202,   242,     0,
       0,     0,   361,   364,     0,     0,   362,     0,     0,   368,
       0,     0,     0,     0,   377,     0,   379,     0,     0,   203,
     204,     0,   205,     0,   380,     0,     0,     0,     0,     0,
     206,   207,   208,   209,   210,   387,   381,     0,     0,     0,
       0,     0,     0,   383,     0,     0,     0,     0,     0,   389,
     386,   393,     0,     0,   390,   391,   392,     0,     0,     0,
     404,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   406,     0,     0,   418,     0,   409,
       0,     0,     0,   413,     0,     0,     0,   414,   417,     0,
       0,   426,     0,     0,   420,   423,     0,     0,     0,     0,
      -2,     4,   425,     0,     0,   427,   428,     0,     5,     6,
       7,     0,   429,     0,   430,     8,     9,    10,    11,    12,
      13,    14,    15,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,    33,    34,     0,     0,     0,     0,     0,
       0,    35,    36,     0,    37,    38,     0,     0,     0,     0,
      39,     0,     0,    40,    41,     0,    42,    43,     0,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

static const yytype_int16 yycheck[] =
{
       5,     3,     5,    96,     3,     3,    63,     4,    16,    14,
       4,    11,    12,    63,    19,     4,    17,    68,    69,     4,
       0,     4,     4,     4,    29,    30,     4,     4,     4,     4,
      35,    36,     4,     4,    39,     4,     4,    38,    50,     4,
      45,     4,     4,     4,     3,     3,    96,    44,    56,    57,
      58,     4,     4,     3,     3,     3,     9,     3,     3,    67,
       4,    55,    67,    63,     3,    68,    69,     3,    73,     3,
       3,    89,    90,    91,    92,    93,    94,    95,    96,    97,
       3,    78,    67,   101,   102,   103,     3,    88,     3,     3,
     108,   109,   110,   111,    96,     3,   114,    96,    96,    96,
     118,   119,   120,   121,   122,   123,     3,    96,     3,   127,
     128,    96,   113,    96,    96,    96,    68,    69,    96,    96,
      96,    96,    66,    67,    96,    96,     5,    96,    96,     3,
     135,    96,    50,    96,    96,    96,     3,    13,    14,     3,
       3,     3,    71,    71,     3,    50,    50,    23,    24,     3,
      68,    69,     3,     3,     3,    13,    14,     3,     3,    71,
     168,    71,   170,     3,    40,    23,    24,    49,    44,    45,
      46,    47,    48,    49,    72,     3,     6,   182,    96,   184,
       3,    49,    40,     3,     3,     3,    44,    45,    46,    47,
      48,    49,     3,    49,     4,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     4,     3,   213,     6,
     215,   133,   217,    82,   171,   220,   221,   372,   382,   224,
      96,   222,    -1,   279,    -1,   230,   231,   232,   233,    -1,
      -1,    -1,    -1,    -1,   235,   236,    -1,    -1,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,    -1,    -1,    -1,   259,    -1,   261,   262,   276,    -1,
     268,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,   274,
      -1,    -1,    -1,    14,   275,    -1,    -1,    -1,    24,   284,
     285,    -1,    -1,    24,   289,    -1,   291,    -1,     4,    -1,
     295,   299,     8,     9,    40,    41,    42,    43,    -1,    40,
      41,    42,    43,    49,    -1,    -1,    -1,    23,    49,    -1,
      -1,    -1,   317,   318,    -1,    -1,   317,    -1,    -1,   320,
      -1,    -1,    -1,    -1,   329,    -1,   331,    -1,    -1,    45,
      46,    -1,    48,    -1,   342,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,   363,   354,    -1,    -1,    -1,
      -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,   364,
     361,   369,    -1,    -1,   365,   366,   367,    -1,    -1,    -1,
     388,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   389,    -1,    -1,   405,    -1,   394,
      -1,    -1,    -1,   398,    -1,    -1,    -1,   402,   403,    -1,
      -1,   419,    -1,    -1,   409,   410,    -1,    -1,    -1,    -1,
       0,     1,   417,    -1,    -1,   420,   424,    -1,     8,     9,
      10,    -1,   427,    -1,   429,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    -1,    64,    65,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    73,    74,    -1,    76,    77,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    98,    99,     0,     1,     8,     9,    10,    15,    16,
      17,    18,    19,    20,    21,    22,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    51,    52,    53,    54,    61,    62,    64,    65,    70,
      73,    74,    76,    77,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   100,   145,   146,   147,   175,   217,   218,   218,
      63,   219,    68,    69,   215,     3,   162,     3,   159,   139,
     140,   141,   142,   218,   125,   215,   219,   124,   218,   123,
     133,   108,   115,   130,   131,   132,   135,   127,   218,   218,
     176,   177,   134,   126,   218,   218,   219,   218,   144,   143,
     129,   128,   116,   218,   117,   118,   106,   107,   119,   109,
     110,   111,   112,   122,   215,   215,   215,   120,   121,    50,
     148,   215,   218,    50,   149,     5,   137,   218,   163,   160,
       3,   206,     3,   165,     3,   169,   165,   138,     3,   191,
       3,   179,   219,   191,   191,   191,   191,   191,   191,   191,
     191,   191,    71,    71,     3,   191,   191,   191,    50,   113,
      50,   114,   191,   191,   191,   191,     3,   182,   219,   191,
       3,   194,     3,   189,     3,   190,   191,   191,   191,   191,
     191,   191,   191,   191,   150,   150,   218,     3,   212,     4,
       8,     9,    23,    45,    46,    48,    56,    57,    58,    59,
      60,   164,     4,    55,   161,   207,   166,   170,     3,   209,
     192,   180,    71,    71,   178,   215,     3,   156,   215,   156,
     183,   195,   218,   218,    14,    24,    40,    41,    42,    43,
      49,   151,    49,    49,   213,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,     4,   208,   218,
       4,    66,    67,   167,     4,    67,   171,   218,   210,     4,
     193,   218,     4,   181,   218,   219,   105,     4,   218,   157,
       4,   184,   218,     4,    44,    78,   196,   218,     4,   218,
       4,   218,   219,   219,   152,   154,   218,     4,   214,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,     4,   211,   215,   218,   219,   191,
      72,     4,   158,   217,   185,   218,   218,   197,     4,   218,
       4,   218,    13,    14,    23,    24,    40,    44,    45,    46,
      47,    48,    49,   153,    13,    14,    23,    24,    40,    44,
      45,    46,    47,    48,    49,   155,   218,     6,     5,   215,
     168,   218,   219,   101,   218,    11,    12,   216,   219,    49,
       3,   186,   198,   199,     3,   200,     4,   218,     4,   218,
     215,   215,   136,   218,     3,   172,   219,   191,   102,   218,
     219,   219,   219,   215,   187,   200,     3,   203,   201,     4,
       4,   212,    49,   173,   191,   103,   218,     4,   188,   218,
     204,     4,   202,   218,   218,     4,   174,   218,   191,   104,
     218,     4,   205,   218,     6,   218,   191,   218,   215,   218,
     218
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 10:
#line 164 "gram.y"
    {
		      (void) AddIconRegion((yyvsp[(2) - (6)].ptr), (yyvsp[(3) - (6)].num), (yyvsp[(4) - (6)].num), (yyvsp[(5) - (6)].num), (yyvsp[(6) - (6)].num), "undef", "undef", "undef");
		  }
    break;

  case 11:
#line 167 "gram.y"
    {
		      (void) AddIconRegion((yyvsp[(2) - (7)].ptr), (yyvsp[(3) - (7)].num), (yyvsp[(4) - (7)].num), (yyvsp[(5) - (7)].num), (yyvsp[(6) - (7)].num), (yyvsp[(7) - (7)].ptr), "undef", "undef");
		  }
    break;

  case 12:
#line 170 "gram.y"
    {
		      (void) AddIconRegion((yyvsp[(2) - (8)].ptr), (yyvsp[(3) - (8)].num), (yyvsp[(4) - (8)].num), (yyvsp[(5) - (8)].num), (yyvsp[(6) - (8)].num), (yyvsp[(7) - (8)].ptr), (yyvsp[(8) - (8)].ptr), "undef");
		  }
    break;

  case 13:
#line 173 "gram.y"
    {
		      (void) AddIconRegion((yyvsp[(2) - (9)].ptr), (yyvsp[(3) - (9)].num), (yyvsp[(4) - (9)].num), (yyvsp[(5) - (9)].num), (yyvsp[(6) - (9)].num), (yyvsp[(7) - (9)].ptr), (yyvsp[(8) - (9)].ptr), (yyvsp[(9) - (9)].ptr));
		  }
    break;

  case 14:
#line 176 "gram.y"
    {
		      list = AddIconRegion((yyvsp[(2) - (6)].ptr), (yyvsp[(3) - (6)].num), (yyvsp[(4) - (6)].num), (yyvsp[(5) - (6)].num), (yyvsp[(6) - (6)].num), "undef", "undef", "undef");
		  }
    break;

  case 16:
#line 180 "gram.y"
    {
		      list = AddIconRegion((yyvsp[(2) - (7)].ptr), (yyvsp[(3) - (7)].num), (yyvsp[(4) - (7)].num), (yyvsp[(5) - (7)].num), (yyvsp[(6) - (7)].num), (yyvsp[(7) - (7)].ptr), "undef", "undef");
		  }
    break;

  case 18:
#line 184 "gram.y"
    {
		      list = AddIconRegion((yyvsp[(2) - (8)].ptr), (yyvsp[(3) - (8)].num), (yyvsp[(4) - (8)].num), (yyvsp[(5) - (8)].num), (yyvsp[(6) - (8)].num), (yyvsp[(7) - (8)].ptr), (yyvsp[(8) - (8)].ptr), "undef");
		  }
    break;

  case 20:
#line 188 "gram.y"
    {
		      list = AddIconRegion((yyvsp[(2) - (9)].ptr), (yyvsp[(3) - (9)].num), (yyvsp[(4) - (9)].num), (yyvsp[(5) - (9)].num), (yyvsp[(6) - (9)].num), (yyvsp[(7) - (9)].ptr), (yyvsp[(8) - (9)].ptr), (yyvsp[(9) - (9)].ptr));
		  }
    break;

  case 22:
#line 193 "gram.y"
    {
		      list = AddWindowRegion ((yyvsp[(2) - (4)].ptr), (yyvsp[(3) - (4)].num), (yyvsp[(4) - (4)].num));
		  }
    break;

  case 24:
#line 198 "gram.y"
    { if (Scr->FirstTime)
						  {
						    Scr->iconmgr->geometry= (char*)(yyvsp[(2) - (3)].ptr);
						    Scr->iconmgr->columns=(yyvsp[(3) - (3)].num);
						  }
						}
    break;

  case 25:
#line 204 "gram.y"
    { if (Scr->FirstTime)
						    Scr->iconmgr->geometry = (char*)(yyvsp[(2) - (2)].ptr);
						}
    break;

  case 26:
#line 207 "gram.y"
    { if (Scr->FirstTime)
				{
				    Scr->workSpaceMgr.workspaceWindow.geometry= (char*)(yyvsp[(2) - (3)].ptr);
				    Scr->workSpaceMgr.workspaceWindow.columns=(yyvsp[(3) - (3)].num);
				}
						}
    break;

  case 27:
#line 213 "gram.y"
    { if (Scr->FirstTime)
				    Scr->workSpaceMgr.workspaceWindow.geometry = (char*)(yyvsp[(2) - (2)].ptr);
						}
    break;

  case 28:
#line 216 "gram.y"
    {}
    break;

  case 30:
#line 219 "gram.y"
    {}
    break;

  case 32:
#line 222 "gram.y"
    { if (Scr->FirstTime)
					  {
						Scr->DoZoom = TRUE;
						Scr->ZoomCount = (yyvsp[(2) - (2)].num);
					  }
					}
    break;

  case 33:
#line 228 "gram.y"
    { if (Scr->FirstTime) 
						Scr->DoZoom = TRUE; }
    break;

  case 34:
#line 230 "gram.y"
    {}
    break;

  case 35:
#line 231 "gram.y"
    {}
    break;

  case 36:
#line 232 "gram.y"
    { list = &Scr->IconifyByUn; }
    break;

  case 38:
#line 234 "gram.y"
    { if (Scr->FirstTime) 
		    Scr->IconifyByUnmapping = TRUE; }
    break;

  case 39:
#line 237 "gram.y"
    { list = &Scr->OpaqueMoveList; }
    break;

  case 41:
#line 239 "gram.y"
    { if (Scr->FirstTime) Scr->DoOpaqueMove = TRUE; }
    break;

  case 42:
#line 240 "gram.y"
    { list = &Scr->NoOpaqueMoveList; }
    break;

  case 44:
#line 242 "gram.y"
    { if (Scr->FirstTime) Scr->DoOpaqueMove = FALSE; }
    break;

  case 45:
#line 243 "gram.y"
    { list = &Scr->OpaqueMoveList; }
    break;

  case 47:
#line 245 "gram.y"
    { if (Scr->FirstTime) Scr->DoOpaqueResize = TRUE; }
    break;

  case 48:
#line 246 "gram.y"
    { list = &Scr->NoOpaqueResizeList; }
    break;

  case 50:
#line 248 "gram.y"
    { if (Scr->FirstTime) Scr->DoOpaqueResize = FALSE; }
    break;

  case 51:
#line 250 "gram.y"
    { 
					  GotTitleButton ((yyvsp[(2) - (4)].ptr), (yyvsp[(4) - (4)].num), False);
					}
    break;

  case 52:
#line 253 "gram.y"
    { 
					  GotTitleButton ((yyvsp[(2) - (4)].ptr), (yyvsp[(4) - (4)].num), True);
					}
    break;

  case 53:
#line 256 "gram.y"
    { CreateTitleButton((yyvsp[(2) - (2)].ptr), 0, NULL, NULL, FALSE, TRUE); }
    break;

  case 55:
#line 258 "gram.y"
    { CreateTitleButton((yyvsp[(2) - (2)].ptr), 0, NULL, NULL, TRUE, TRUE); }
    break;

  case 57:
#line 260 "gram.y"
    {
		    root = GetRoot((yyvsp[(2) - (2)].ptr), NULLSTR, NULLSTR);
		    AddFuncButton ((yyvsp[(1) - (2)].num), C_ROOT, 0, F_MENU, root, (MenuItem*) 0);
		}
    break;

  case 58:
#line 264 "gram.y"
    {
			if ((yyvsp[(2) - (2)].num) == F_MENU) {
			    pull->prev = NULL;
			    AddFuncButton ((yyvsp[(1) - (2)].num), C_ROOT, 0, (yyvsp[(2) - (2)].num), pull, (MenuItem*) 0);
			}
			else {
			    MenuItem *item;

			    root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
			    item = AddToMenu (root, "x", Action,
					NULLSTR, (yyvsp[(2) - (2)].num), NULLSTR, NULLSTR);
			    AddFuncButton ((yyvsp[(1) - (2)].num), C_ROOT, 0, (yyvsp[(2) - (2)].num), (MenuRoot*) 0, item);
			}
			Action = "";
			pull = NULL;
		}
    break;

  case 59:
#line 280 "gram.y"
    { GotKey((yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].num)); }
    break;

  case 60:
#line 281 "gram.y"
    { GotButton((yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].num)); }
    break;

  case 61:
#line 283 "gram.y"
    { list = &Scr->DontIconify; }
    break;

  case 63:
#line 285 "gram.y"
    {}
    break;

  case 65:
#line 287 "gram.y"
    { list = &Scr->OccupyAll; }
    break;

  case 67:
#line 289 "gram.y"
    {}
    break;

  case 69:
#line 291 "gram.y"
    { list = &Scr->UnmapByMovingFarAway; }
    break;

  case 71:
#line 293 "gram.y"
    { list = &Scr->AutoSqueeze; }
    break;

  case 73:
#line 295 "gram.y"
    { list = &Scr->StartSqueezed; }
    break;

  case 75:
#line 297 "gram.y"
    { list = &Scr->DontSetInactive; }
    break;

  case 77:
#line 299 "gram.y"
    { list = &Scr->IconMgrNoShow; }
    break;

  case 79:
#line 301 "gram.y"
    { Scr->IconManagerDontShow = TRUE; }
    break;

  case 80:
#line 302 "gram.y"
    { list = &Scr->IconMgrs; }
    break;

  case 82:
#line 304 "gram.y"
    { list = &Scr->IconMgrShow; }
    break;

  case 84:
#line 306 "gram.y"
    { list = &Scr->NoTitleHighlight; }
    break;

  case 86:
#line 308 "gram.y"
    { if (Scr->FirstTime)
						Scr->TitleHighlight = FALSE; }
    break;

  case 87:
#line 310 "gram.y"
    { list = &Scr->NoHighlight; }
    break;

  case 89:
#line 312 "gram.y"
    { if (Scr->FirstTime)
						Scr->Highlight = FALSE; }
    break;

  case 90:
#line 314 "gram.y"
    { list = &Scr->AlwaysOnTopL; }
    break;

  case 92:
#line 316 "gram.y"
    { list = &Scr->NoStackModeL; }
    break;

  case 94:
#line 318 "gram.y"
    { if (Scr->FirstTime)
						Scr->StackMode = FALSE; }
    break;

  case 95:
#line 320 "gram.y"
    { list = &Scr->NoBorder; }
    break;

  case 97:
#line 322 "gram.y"
    { list = &Scr->NoIconTitle; }
    break;

  case 99:
#line 324 "gram.y"
    { if (Scr->FirstTime)
						Scr->NoIconTitlebar = TRUE; }
    break;

  case 100:
#line 326 "gram.y"
    { list = &Scr->NoTitle; }
    break;

  case 102:
#line 328 "gram.y"
    { if (Scr->FirstTime)
						Scr->NoTitlebar = TRUE; }
    break;

  case 103:
#line 330 "gram.y"
    { list = &Scr->MakeTitle; }
    break;

  case 105:
#line 332 "gram.y"
    { list = &Scr->StartIconified; }
    break;

  case 107:
#line 334 "gram.y"
    { list = &Scr->AutoRaise; }
    break;

  case 109:
#line 336 "gram.y"
    { Scr->AutoRaiseDefault = TRUE; }
    break;

  case 110:
#line 337 "gram.y"
    {
					root = GetRoot((yyvsp[(2) - (7)].ptr), (yyvsp[(4) - (7)].ptr), (yyvsp[(6) - (7)].ptr)); }
    break;

  case 111:
#line 339 "gram.y"
    { root->real_menu = TRUE;}
    break;

  case 112:
#line 340 "gram.y"
    { root = GetRoot((yyvsp[(2) - (2)].ptr), NULLSTR, NULLSTR); }
    break;

  case 113:
#line 341 "gram.y"
    { root->real_menu = TRUE; }
    break;

  case 114:
#line 342 "gram.y"
    { root = GetRoot((yyvsp[(2) - (2)].ptr), NULLSTR, NULLSTR); }
    break;

  case 116:
#line 344 "gram.y"
    { list = &Scr->IconNames; }
    break;

  case 118:
#line 346 "gram.y"
    { color = COLOR; }
    break;

  case 120:
#line 348 "gram.y"
    {}
    break;

  case 122:
#line 350 "gram.y"
    { color = MONOCHROME; }
    break;

  case 124:
#line 352 "gram.y"
    { Scr->DefaultFunction.func = (yyvsp[(2) - (2)].num);
					  if ((yyvsp[(2) - (2)].num) == F_MENU)
					  {
					    pull->prev = NULL;
					    Scr->DefaultFunction.menu = pull;
					  }
					  else
					  {
					    root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
					    Scr->DefaultFunction.item = 
						AddToMenu(root,"x",Action,
							  NULLSTR,(yyvsp[(2) - (2)].num), NULLSTR, NULLSTR);
					  }
					  Action = "";
					  pull = NULL;
					}
    break;

  case 125:
#line 368 "gram.y"
    { Scr->WindowFunction.func = (yyvsp[(2) - (2)].num);
					   root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
					   Scr->WindowFunction.item = 
						AddToMenu(root,"x",Action,
							  NULLSTR,(yyvsp[(2) - (2)].num), NULLSTR, NULLSTR);
					   Action = "";
					   pull = NULL;
					}
    break;

  case 126:
#line 376 "gram.y"
    { Scr->ChangeWorkspaceFunction.func = (yyvsp[(2) - (2)].num);
					   root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
					   Scr->ChangeWorkspaceFunction.item = 
						AddToMenu(root,"x",Action,
							  NULLSTR,(yyvsp[(2) - (2)].num), NULLSTR, NULLSTR);
					   Action = "";
					   pull = NULL;
					}
    break;

  case 127:
#line 384 "gram.y"
    { Scr->DeIconifyFunction.func = (yyvsp[(2) - (2)].num);
					   root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
					   Scr->DeIconifyFunction.item = 
						AddToMenu(root,"x",Action,
							  NULLSTR,(yyvsp[(2) - (2)].num), NULLSTR, NULLSTR);
					   Action = "";
					   pull = NULL;
					}
    break;

  case 128:
#line 392 "gram.y"
    { Scr->IconifyFunction.func = (yyvsp[(2) - (2)].num);
					   root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
					   Scr->IconifyFunction.item = 
						AddToMenu(root,"x",Action,
							  NULLSTR,(yyvsp[(2) - (2)].num), NULLSTR, NULLSTR);
					   Action = "";
					   pull = NULL;
					}
    break;

  case 129:
#line 400 "gram.y"
    { list = &Scr->WarpCursorL; }
    break;

  case 131:
#line 402 "gram.y"
    { if (Scr->FirstTime) 
					    Scr->WarpCursor = TRUE; }
    break;

  case 132:
#line 404 "gram.y"
    { list = &Scr->WindowRingL; }
    break;

  case 134:
#line 406 "gram.y"
    { Scr->WindowRingAll = TRUE; }
    break;

  case 135:
#line 409 "gram.y"
    { if (!do_single_keyword ((yyvsp[(1) - (1)].num))) {
					    twmrc_error_prefix();
					    fprintf (stderr,
					"unknown singleton keyword %d\n",
						     (yyvsp[(1) - (1)].num));
					    ParseError = 1;
					  }
					}
    break;

  case 136:
#line 419 "gram.y"
    { if (!do_string_keyword ((yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].ptr))) {
					    twmrc_error_prefix();
					    fprintf (stderr,
				"unknown string keyword %d (value \"%s\")\n",
						     (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].ptr));
					    ParseError = 1;
					  }
					}
    break;

  case 137:
#line 427 "gram.y"
    { if (!do_string_keyword ((yyvsp[(1) - (1)].num), defstring)) {
 					    twmrc_error_prefix();
 					    fprintf (stderr,
 				"unknown string keyword %d (no value)\n",
 						     (yyvsp[(1) - (1)].num));
 					    ParseError = 1;
 					  }
 					}
    break;

  case 138:
#line 437 "gram.y"
    { if (!do_number_keyword ((yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].num))) {
					    twmrc_error_prefix();
					    fprintf (stderr,
				"unknown numeric keyword %d (value %d)\n",
						     (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].num));
					    ParseError = 1;
					  }
					}
    break;

  case 139:
#line 449 "gram.y"
    { (yyval.num) = (yyvsp[(6) - (6)].num); }
    break;

  case 140:
#line 452 "gram.y"
    { (yyval.num) = (yyvsp[(6) - (6)].num); }
    break;

  case 143:
#line 459 "gram.y"
    { mods |= Mod1Mask; }
    break;

  case 144:
#line 460 "gram.y"
    { mods |= ShiftMask; }
    break;

  case 145:
#line 461 "gram.y"
    { mods |= LockMask; }
    break;

  case 146:
#line 462 "gram.y"
    { mods |= ControlMask; }
    break;

  case 147:
#line 463 "gram.y"
    { if ((yyvsp[(2) - (2)].num) < 1 || (yyvsp[(2) - (2)].num) > 5) {
					     twmrc_error_prefix();
					     fprintf (stderr, 
				"bad modifier number (%d), must be 1-5\n",
						      (yyvsp[(2) - (2)].num));
					     ParseError = 1;
					  } else {
					     mods |= (Alt1Mask << ((yyvsp[(2) - (2)].num) - 1));
					  }
					}
    break;

  case 148:
#line 473 "gram.y"
    { if ((yyvsp[(2) - (2)].num) < 1 || (yyvsp[(2) - (2)].num) > 5) {
					     twmrc_error_prefix();
					     fprintf (stderr, 
				"bad modifier number (%d), must be 1-5\n",
						      (yyvsp[(2) - (2)].num));
					     ParseError = 1;
					  } else {
					     mods |= (Mod1Mask << ((yyvsp[(2) - (2)].num) - 1));
					  }
					}
    break;

  case 149:
#line 483 "gram.y"
    { }
    break;

  case 152:
#line 490 "gram.y"
    { cont |= C_WINDOW_BIT; }
    break;

  case 153:
#line 491 "gram.y"
    { cont |= C_TITLE_BIT; }
    break;

  case 154:
#line 492 "gram.y"
    { cont |= C_ICON_BIT; }
    break;

  case 155:
#line 493 "gram.y"
    { cont |= C_ROOT_BIT; }
    break;

  case 156:
#line 494 "gram.y"
    { cont |= C_FRAME_BIT; }
    break;

  case 157:
#line 495 "gram.y"
    { cont |= C_ICONMGR_BIT; }
    break;

  case 158:
#line 496 "gram.y"
    { cont |= C_ICONMGR_BIT; }
    break;

  case 159:
#line 497 "gram.y"
    { cont |= C_ALTER_BIT; }
    break;

  case 160:
#line 498 "gram.y"
    { cont |= C_ALL_BITS; }
    break;

  case 161:
#line 499 "gram.y"
    {  }
    break;

  case 164:
#line 506 "gram.y"
    { cont |= C_WINDOW_BIT; }
    break;

  case 165:
#line 507 "gram.y"
    { cont |= C_TITLE_BIT; }
    break;

  case 166:
#line 508 "gram.y"
    { cont |= C_ICON_BIT; }
    break;

  case 167:
#line 509 "gram.y"
    { cont |= C_ROOT_BIT; }
    break;

  case 168:
#line 510 "gram.y"
    { cont |= C_FRAME_BIT; }
    break;

  case 169:
#line 511 "gram.y"
    { cont |= C_ICONMGR_BIT; }
    break;

  case 170:
#line 512 "gram.y"
    { cont |= C_ICONMGR_BIT; }
    break;

  case 171:
#line 513 "gram.y"
    { cont |= C_ALL_BITS; }
    break;

  case 172:
#line 514 "gram.y"
    { cont |= C_ALTER_BIT; }
    break;

  case 173:
#line 515 "gram.y"
    { }
    break;

  case 174:
#line 516 "gram.y"
    { Name = (char*)(yyvsp[(1) - (1)].ptr); cont |= C_NAME_BIT; }
    break;

  case 175:
#line 520 "gram.y"
    {}
    break;

  case 178:
#line 527 "gram.y"
    { ModifyCurrentTB((yyvsp[(1) - (3)].num), (yyvsp[(3) - (3)].num), Action, pull);}
    break;

  case 179:
#line 531 "gram.y"
    {}
    break;

  case 182:
#line 538 "gram.y"
    { SetHighlightPixmap ((yyvsp[(2) - (2)].ptr)); }
    break;

  case 183:
#line 542 "gram.y"
    {}
    break;

  case 186:
#line 549 "gram.y"
    {
			NewBitmapCursor(&Scr->FrameCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 187:
#line 551 "gram.y"
    {
			NewFontCursor(&Scr->FrameCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 188:
#line 553 "gram.y"
    {
			NewBitmapCursor(&Scr->TitleCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 189:
#line 555 "gram.y"
    {
			NewFontCursor(&Scr->TitleCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 190:
#line 557 "gram.y"
    {
			NewBitmapCursor(&Scr->IconCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 191:
#line 559 "gram.y"
    {
			NewFontCursor(&Scr->IconCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 192:
#line 561 "gram.y"
    {
			NewBitmapCursor(&Scr->IconMgrCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 193:
#line 563 "gram.y"
    {
			NewFontCursor(&Scr->IconMgrCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 194:
#line 565 "gram.y"
    {
			NewBitmapCursor(&Scr->ButtonCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 195:
#line 567 "gram.y"
    {
			NewFontCursor(&Scr->ButtonCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 196:
#line 569 "gram.y"
    {
			NewBitmapCursor(&Scr->MoveCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 197:
#line 571 "gram.y"
    {
			NewFontCursor(&Scr->MoveCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 198:
#line 573 "gram.y"
    {
			NewBitmapCursor(&Scr->ResizeCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 199:
#line 575 "gram.y"
    {
			NewFontCursor(&Scr->ResizeCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 200:
#line 577 "gram.y"
    {
			NewBitmapCursor(&Scr->WaitCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 201:
#line 579 "gram.y"
    {
			NewFontCursor(&Scr->WaitCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 202:
#line 581 "gram.y"
    {
			NewBitmapCursor(&Scr->MenuCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 203:
#line 583 "gram.y"
    {
			NewFontCursor(&Scr->MenuCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 204:
#line 585 "gram.y"
    {
			NewBitmapCursor(&Scr->SelectCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 205:
#line 587 "gram.y"
    {
			NewFontCursor(&Scr->SelectCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 206:
#line 589 "gram.y"
    {
			NewBitmapCursor(&Scr->DestroyCursor, (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); }
    break;

  case 207:
#line 591 "gram.y"
    {
			NewFontCursor(&Scr->DestroyCursor, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 208:
#line 595 "gram.y"
    {}
    break;

  case 211:
#line 603 "gram.y"
    { if (!do_colorlist_keyword ((yyvsp[(1) - (2)].num), color,
								     (yyvsp[(2) - (2)].ptr))) {
					    twmrc_error_prefix();
					    fprintf (stderr,
			"unhandled list color keyword %d (string \"%s\")\n",
						     (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].ptr));
					    ParseError = 1;
					  }
					}
    break;

  case 212:
#line 612 "gram.y"
    { list = do_colorlist_keyword((yyvsp[(1) - (2)].num),color,
								      (yyvsp[(2) - (2)].ptr));
					  if (!list) {
					    twmrc_error_prefix();
					    fprintf (stderr,
			"unhandled color list keyword %d (string \"%s\")\n",
						     (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].ptr));
					    ParseError = 1;
					  }
					}
    break;

  case 214:
#line 623 "gram.y"
    { if (!do_color_keyword ((yyvsp[(1) - (2)].num), color,
								 (yyvsp[(2) - (2)].ptr))) {
					    twmrc_error_prefix();
					    fprintf (stderr,
			"unhandled color keyword %d (string \"%s\")\n",
						     (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].ptr));
					    ParseError = 1;
					  }
					}
    break;

  case 215:
#line 634 "gram.y"
    {}
    break;

  case 218:
#line 641 "gram.y"
    { do_string_savecolor(color, (yyvsp[(1) - (1)].ptr)); }
    break;

  case 219:
#line 642 "gram.y"
    { do_var_savecolor((yyvsp[(1) - (1)].num)); }
    break;

  case 220:
#line 645 "gram.y"
    {}
    break;

  case 223:
#line 652 "gram.y"
    { if (Scr->FirstTime &&
					      color == Scr->Monochrome)
					    AddToList(list, (yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr)); }
    break;

  case 224:
#line 657 "gram.y"
    { 
				    if (HasShape) Scr->SqueezeTitle = TRUE;
				}
    break;

  case 225:
#line 660 "gram.y"
    { list = &Scr->SqueezeTitleL; 
				  if (HasShape && Scr->SqueezeTitle == -1)
				    Scr->SqueezeTitle = TRUE;
				}
    break;

  case 227:
#line 665 "gram.y"
    { Scr->SqueezeTitle = FALSE; }
    break;

  case 228:
#line 666 "gram.y"
    { list = &Scr->DontSqueezeTitleL; }
    break;

  case 231:
#line 671 "gram.y"
    {
				if (Scr->FirstTime) {
				   do_squeeze_entry (list, (yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].num), (yyvsp[(4) - (5)].num), (yyvsp[(5) - (5)].num));
				}
			}
    break;

  case 232:
#line 679 "gram.y"
    {}
    break;

  case 235:
#line 686 "gram.y"
    { if (Scr->FirstTime)
					    AddToList(list, (yyvsp[(1) - (3)].ptr), (char *)
						AllocateIconManager((yyvsp[(1) - (3)].ptr), NULLSTR,
							(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].num)));
					}
    break;

  case 236:
#line 692 "gram.y"
    { if (Scr->FirstTime)
					    AddToList(list, (yyvsp[(1) - (4)].ptr), (char *)
						AllocateIconManager((yyvsp[(1) - (4)].ptr),(yyvsp[(2) - (4)].ptr),
						(yyvsp[(3) - (4)].ptr), (yyvsp[(4) - (4)].num)));
					}
    break;

  case 237:
#line 699 "gram.y"
    {}
    break;

  case 240:
#line 706 "gram.y"
    {
			AddWorkSpace ((yyvsp[(1) - (1)].ptr), NULLSTR, NULLSTR, NULLSTR, NULLSTR, NULLSTR);
		}
    break;

  case 241:
#line 709 "gram.y"
    {
			curWorkSpc = (char*)(yyvsp[(1) - (1)].ptr);
		}
    break;

  case 243:
#line 715 "gram.y"
    {}
    break;

  case 246:
#line 722 "gram.y"
    {
			AddWorkSpace (curWorkSpc, (yyvsp[(1) - (1)].ptr), NULLSTR, NULLSTR, NULLSTR, NULLSTR);
		}
    break;

  case 247:
#line 725 "gram.y"
    {
			AddWorkSpace (curWorkSpc, (yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr), NULLSTR, NULLSTR, NULLSTR);
		}
    break;

  case 248:
#line 728 "gram.y"
    {
			AddWorkSpace (curWorkSpc, (yyvsp[(1) - (3)].ptr), (yyvsp[(2) - (3)].ptr), (yyvsp[(3) - (3)].ptr), NULLSTR, NULLSTR);
		}
    break;

  case 249:
#line 731 "gram.y"
    {
			AddWorkSpace (curWorkSpc, (yyvsp[(1) - (4)].ptr), (yyvsp[(2) - (4)].ptr), (yyvsp[(3) - (4)].ptr), (yyvsp[(4) - (4)].ptr), NULLSTR);
		}
    break;

  case 250:
#line 734 "gram.y"
    {
			AddWorkSpace (curWorkSpc, (yyvsp[(1) - (5)].ptr), (yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].ptr), (yyvsp[(4) - (5)].ptr), (yyvsp[(5) - (5)].ptr));
		}
    break;

  case 251:
#line 739 "gram.y"
    {
		    WMapCreateCurrentBackGround ((yyvsp[(2) - (3)].ptr), NULL, NULL, NULL);
		}
    break;

  case 252:
#line 742 "gram.y"
    {
		    WMapCreateCurrentBackGround ((yyvsp[(2) - (4)].ptr), (yyvsp[(3) - (4)].ptr), NULL, NULL);
		}
    break;

  case 253:
#line 745 "gram.y"
    {
		    WMapCreateCurrentBackGround ((yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].ptr), (yyvsp[(4) - (5)].ptr), NULL);
		}
    break;

  case 254:
#line 748 "gram.y"
    {
		    WMapCreateCurrentBackGround ((yyvsp[(2) - (6)].ptr), (yyvsp[(3) - (6)].ptr), (yyvsp[(4) - (6)].ptr), (yyvsp[(5) - (6)].ptr));
		}
    break;

  case 255:
#line 753 "gram.y"
    {
		    WMapCreateDefaultBackGround ((yyvsp[(2) - (3)].ptr), NULL, NULL, NULL);
		}
    break;

  case 256:
#line 756 "gram.y"
    {
		    WMapCreateDefaultBackGround ((yyvsp[(2) - (4)].ptr), (yyvsp[(3) - (4)].ptr), NULL, NULL);
		}
    break;

  case 257:
#line 759 "gram.y"
    {
		    WMapCreateDefaultBackGround ((yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].ptr), (yyvsp[(4) - (5)].ptr), NULL);
		}
    break;

  case 258:
#line 762 "gram.y"
    {
		    WMapCreateDefaultBackGround ((yyvsp[(2) - (6)].ptr), (yyvsp[(3) - (6)].ptr), (yyvsp[(4) - (6)].ptr), (yyvsp[(5) - (6)].ptr));
		}
    break;

  case 259:
#line 767 "gram.y"
    {}
    break;

  case 262:
#line 774 "gram.y"
    { if (Scr->FirstTime)
					    AddToList(list, (yyvsp[(1) - (1)].ptr), 0);
					}
    break;

  case 263:
#line 779 "gram.y"
    {}
    break;

  case 266:
#line 786 "gram.y"
    {client = (char*)(yyvsp[(1) - (1)].ptr);}
    break;

  case 268:
#line 788 "gram.y"
    {client = (char*)(yyvsp[(2) - (2)].ptr);}
    break;

  case 270:
#line 790 "gram.y"
    {workspace = (char*)(yyvsp[(2) - (2)].ptr);}
    break;

  case 272:
#line 794 "gram.y"
    {}
    break;

  case 275:
#line 801 "gram.y"
    {
				AddToClientsList ((yyvsp[(1) - (1)].ptr), client);
			  }
    break;

  case 276:
#line 805 "gram.y"
    {}
    break;

  case 279:
#line 812 "gram.y"
    {
				AddToClientsList (workspace, (yyvsp[(1) - (1)].ptr));
			  }
    break;

  case 280:
#line 816 "gram.y"
    {}
    break;

  case 283:
#line 823 "gram.y"
    { if (Scr->FirstTime) AddToList(list, (yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr)); }
    break;

  case 284:
#line 826 "gram.y"
    {}
    break;

  case 287:
#line 833 "gram.y"
    { AddToMenu(root, "", Action, NULLSTR, (yyvsp[(1) - (1)].num),
						NULLSTR, NULLSTR);
					  Action = "";
					}
    break;

  case 288:
#line 839 "gram.y"
    {lastmenuitem = (MenuItem*) 0;}
    break;

  case 291:
#line 846 "gram.y"
    {
			if ((yyvsp[(2) - (2)].num) == F_SEPARATOR) {
			    if (lastmenuitem) lastmenuitem->separated = 1;
			}
			else {
			    lastmenuitem = AddToMenu(root, (yyvsp[(1) - (2)].ptr), Action, pull, (yyvsp[(2) - (2)].num), NULLSTR, NULLSTR);
			    Action = "";
			    pull = NULL;
			}
		}
    break;

  case 292:
#line 856 "gram.y"
    {
			if ((yyvsp[(7) - (7)].num) == F_SEPARATOR) {
			    if (lastmenuitem) lastmenuitem->separated = 1;
			}
			else {
			    lastmenuitem = AddToMenu(root, (yyvsp[(1) - (7)].ptr), Action, pull, (yyvsp[(7) - (7)].num), (yyvsp[(3) - (7)].ptr), (yyvsp[(5) - (7)].ptr));
			    Action = "";
			    pull = NULL;
			}
		}
    break;

  case 293:
#line 868 "gram.y"
    { (yyval.num) = (yyvsp[(1) - (1)].num); }
    break;

  case 294:
#line 869 "gram.y"
    {
				(yyval.num) = (yyvsp[(1) - (2)].num);
				Action = (char*)(yyvsp[(2) - (2)].ptr);
				switch ((yyvsp[(1) - (2)].num)) {
				  case F_MENU:
				    pull = GetRoot ((yyvsp[(2) - (2)].ptr), NULLSTR,NULLSTR);
				    pull->prev = root;
				    break;
				  case F_WARPRING:
				    if (!CheckWarpRingArg (Action)) {
					twmrc_error_prefix();
					fprintf (stderr,
			"ignoring invalid f.warptoring argument \"%s\"\n",
						 Action);
					(yyval.num) = F_NOP;
				    }
				  case F_WARPTOSCREEN:
				    if (!CheckWarpScreenArg (Action)) {
					twmrc_error_prefix();
					fprintf (stderr, 
			"ignoring invalid f.warptoscreen argument \"%s\"\n", 
					         Action);
					(yyval.num) = F_NOP;
				    }
				    break;
				  case F_COLORMAP:
				    if (CheckColormapArg (Action)) {
					(yyval.num) = F_COLORMAP;
				    } else {
					twmrc_error_prefix();
					fprintf (stderr,
			"ignoring invalid f.colormap argument \"%s\"\n", 
						 Action);
					(yyval.num) = F_NOP;
				    }
				    break;
				} /* end switch */
				   }
    break;

  case 295:
#line 910 "gram.y"
    { (yyval.num) = (yyvsp[(1) - (1)].num); }
    break;

  case 296:
#line 911 "gram.y"
    { (yyval.num) = (yyvsp[(2) - (2)].num); }
    break;

  case 297:
#line 912 "gram.y"
    { (yyval.num) = -((yyvsp[(2) - (2)].num)); }
    break;

  case 298:
#line 915 "gram.y"
    { (yyval.num) = (yyvsp[(2) - (2)].num);
					  if ((yyvsp[(2) - (2)].num) == 0)
						yyerror("bad button 0");

					  if ((yyvsp[(2) - (2)].num) > MAX_BUTTONS)
					  {
						(yyval.num) = 0;
						yyerror("button number too large");
					  }
					}
    break;

  case 299:
#line 927 "gram.y"
    { ptr = (char *)malloc(strlen((char*)(yyvsp[(1) - (1)].ptr))+1);
					  strcpy((char*)ptr, (char*)(yyvsp[(1) - (1)].ptr));
					  RemoveDQuote(ptr);
					  (yyval.ptr) = (unsigned char*)ptr;
					}
    break;

  case 300:
#line 932 "gram.y"
    { (yyval.num) = (yyvsp[(1) - (1)].num); }
    break;


/* Line 1267 of yacc.c.  */
#line 3402 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 935 "gram.y"

yyerror(s) char *s;
{
    twmrc_error_prefix();
    fprintf (stderr, "error in input file:  %s\n", s ? s : "");
    ParseError = 1;
}
RemoveDQuote(str)
char *str;
{
    register char *i, *o;
    register n;
    register count;

    for (i=str+1, o=str; *i && *i != '\"'; o++)
    {
	if (*i == '\\')
	{
	    switch (*++i)
	    {
	    case 'n':
		*o = '\n';
		i++;
		break;
	    case 'b':
		*o = '\b';
		i++;
		break;
	    case 'r':
		*o = '\r';
		i++;
		break;
	    case 't':
		*o = '\t';
		i++;
		break;
	    case 'f':
		*o = '\f';
		i++;
		break;
	    case '0':
		if (*++i == 'x')
		    goto hex;
		else
		    --i;
	    case '1': case '2': case '3':
	    case '4': case '5': case '6': case '7':
		n = 0;
		count = 0;
		while (*i >= '0' && *i <= '7' && count < 3)
		{
		    n = (n<<3) + (*i++ - '0');
		    count++;
		}
		*o = n;
		break;
	    hex:
	    case 'x':
		n = 0;
		count = 0;
		while (i++, count++ < 2)
		{
		    if (*i >= '0' && *i <= '9')
			n = (n<<4) + (*i - '0');
		    else if (*i >= 'a' && *i <= 'f')
			n = (n<<4) + (*i - 'a') + 10;
		    else if (*i >= 'A' && *i <= 'F')
			n = (n<<4) + (*i - 'A') + 10;
		    else
			break;
		}
		*o = n;
		break;
	    case '\n':
		i++;	/* punt */
		o--;	/* to account for o++ at end of loop */
		break;
	    case '\"':
	    case '\'':
	    case '\\':
	    default:
		*o = *i++;
		break;
	    }
	}
	else
	    *o = *i++;
    }
    *o = '\0';
}

static MenuRoot *GetRoot(name, fore, back)
char *name;
char *fore, *back;
{
    MenuRoot *tmp;

    tmp = FindMenuRoot(name);
    if (tmp == NULL)
	tmp = NewMenuRoot(name);

    if (fore)
    {
	int save;

	save = Scr->FirstTime;
	Scr->FirstTime = TRUE;
	GetColor(COLOR, &tmp->highlight.fore, fore);
	GetColor(COLOR, &tmp->highlight.back, back);
	Scr->FirstTime = save;
    }

    return tmp;
}

static void GotButton (butt, func)
int butt, func;
{
    int i;
    MenuItem *item;

    for (i = 0; i < NUM_CONTEXTS; i++) {
	if ((cont & (1 << i)) == 0) continue;

	if (func == F_MENU) {
	    pull->prev = NULL;
	    AddFuncButton (butt, i, mods, func, pull, (MenuItem*) 0);
	}
	else {
	    root = GetRoot (TWM_ROOT, NULLSTR, NULLSTR);
	    item = AddToMenu (root, "x", Action, NULLSTR, func, NULLSTR, NULLSTR);
	    AddFuncButton (butt, i, mods, func, (MenuRoot*) 0, item);
	}
    }

    Action = "";
    pull = NULL;
    cont = 0;
    mods_used |= mods;
    mods = 0;
}

static void GotKey(key, func)
char *key;
int func;
{
    int i;

    for (i = 0; i < NUM_CONTEXTS; i++)
    {
	if ((cont & (1 << i)) == 0) 
	  continue;

	if (func == F_MENU) {
	    pull->prev = NULL;
	    if (!AddFuncKey (key, i, mods, func, pull, Name, Action)) break;
	}
	else
	if (!AddFuncKey(key, i, mods, func, (MenuRoot*) 0, Name, Action)) 
	  break;
    }

    Action = "";
    pull = NULL;
    cont = 0;
    mods_used |= mods;
    mods = 0;
}


static void GotTitleButton (bitmapname, func, rightside)
    char *bitmapname;
    int func;
    Bool rightside;
{
    if (!CreateTitleButton (bitmapname, func, Action, pull, rightside, True)) {
	twmrc_error_prefix();
	fprintf (stderr, 
		 "unable to create %s titlebutton \"%s\"\n",
		 rightside ? "right" : "left", bitmapname);
    }
    Action = "";
    pull = NULL;
}

static Bool CheckWarpScreenArg (s)
    register char *s;
{
    XmuCopyISOLatin1Lowered (s, s);

    if (strcmp (s,  WARPSCREEN_NEXT) == 0 ||
	strcmp (s,  WARPSCREEN_PREV) == 0 ||
	strcmp (s,  WARPSCREEN_BACK) == 0)
      return True;

    for (; *s && isascii(*s) && isdigit(*s); s++) ; /* SUPPRESS 530 */
    return (*s ? False : True);
}


static Bool CheckWarpRingArg (s)
    register char *s;
{
    XmuCopyISOLatin1Lowered (s, s);

    if (strcmp (s,  WARPSCREEN_NEXT) == 0 ||
	strcmp (s,  WARPSCREEN_PREV) == 0)
      return True;

    return False;
}


static Bool CheckColormapArg (s)
    register char *s;
{
    XmuCopyISOLatin1Lowered (s, s);

    if (strcmp (s, COLORMAP_NEXT) == 0 ||
	strcmp (s, COLORMAP_PREV) == 0 ||
	strcmp (s, COLORMAP_DEFAULT) == 0)
      return True;

    return False;
}


twmrc_error_prefix ()
{
    fprintf (stderr, "%s:  line %d:  ", ProgramName, yylineno);
}

