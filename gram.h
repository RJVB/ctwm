/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 121 "gram.y"
{
    int num;
    unsigned char *ptr;
}
/* Line 1529 of yacc.c.  */
#line 246 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

