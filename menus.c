/*****************************************************************************/
/**       Copyright 1988 by Evans & Sutherland Computer Corporation,        **/
/**                          Salt Lake City, Utah                           **/
/**  Portions Copyright 1989 by the Massachusetts Institute of Technology   **/
/**                        Cambridge, Massachusetts                         **/
/**                                                                         **/
/**                           All Rights Reserved                           **/
/**                                                                         **/
/**    Permission to use, copy, modify, and distribute this software and    **/
/**    its documentation  for  any  purpose  and  without  fee is hereby    **/
/**    granted, provided that the above copyright notice appear  in  all    **/
/**    copies and that both  that  copyright  notice  and  this  permis-    **/
/**    sion  notice appear in supporting  documentation,  and  that  the    **/
/**    names of Evans & Sutherland and M.I.T. not be used in advertising    **/
/**    in publicity pertaining to distribution of the  software  without    **/
/**    specific, written prior permission.                                  **/
/**                                                                         **/
/**    EVANS & SUTHERLAND AND M.I.T. DISCLAIM ALL WARRANTIES WITH REGARD    **/
/**    TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES  OF  MERCHANT-    **/
/**    ABILITY  AND  FITNESS,  IN  NO  EVENT SHALL EVANS & SUTHERLAND OR    **/
/**    M.I.T. BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL  DAM-    **/
/**    AGES OR  ANY DAMAGES WHATSOEVER  RESULTING FROM LOSS OF USE, DATA    **/
/**    OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER    **/
/**    TORTIOUS ACTION, ARISING OUT OF OR IN  CONNECTION  WITH  THE  USE    **/
/**    OR PERFORMANCE OF THIS SOFTWARE.                                     **/
/*****************************************************************************/
/* 
 *  [ ctwm ]
 *
 *  Copyright 1992 Claude Lecommandeur.
 *            
 * Permission to use, copy, modify  and distribute this software  [ctwm] and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above  copyright notice appear  in all copies and that both that
 * copyright notice and this permission notice appear in supporting documen-
 * tation, and that the name of  Claude Lecommandeur not be used in adverti-
 * sing or  publicity  pertaining to  distribution of  the software  without
 * specific, written prior permission. Claude Lecommandeur make no represen-
 * tations  about the suitability  of this software  for any purpose.  It is
 * provided "as is" without express or implied warranty.
 *
 * Claude Lecommandeur DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL  IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS.  IN NO
 * EVENT SHALL  Claude Lecommandeur  BE LIABLE FOR ANY SPECIAL,  INDIRECT OR
 * CONSEQUENTIAL  DAMAGES OR ANY  DAMAGES WHATSOEVER  RESULTING FROM LOSS OF
 * USE, DATA  OR PROFITS,  WHETHER IN AN ACTION  OF CONTRACT,  NEGLIGENCE OR
 * OTHER  TORTIOUS ACTION,  ARISING OUT OF OR IN  CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Claude Lecommandeur [ lecom@sic.epfl.ch ][ April 1992 ]
 */


/***********************************************************************
 *
 * $XConsortium: menus.c,v 1.186 91/07/17 13:58:00 dave Exp $
 *
 * twm menu code
 *
 * 17-Nov-87 Thomas E. LaStrange		File created
 *
 * Do the necessary modification to be integrated in ctwm.
 * Can no longer be used for the standard twm.
 *
 * 22-April-92 Claude Lecommandeur.
 *
 *
 ***********************************************************************/

#if defined(USE_SIGNALS) && defined(__sgi)
#  define _BSD_SIGNALS
#endif

#include <stdio.h>
#include <signal.h>

#ifdef VMS
#include <stdlib.h>
#include <string.h>
#include <unixio.h>
#include <file.h>
#include <decw$include/Xos.h>
#include <decw$include/Xatom.h>
#else
#include <X11/Xos.h>
#include <X11/Xatom.h>
#endif
#include "twm.h"
#include "gc.h"
#include "menus.h"
#include "resize.h"
#include "events.h"
#include "util.h"
#include "parse.h"
#include "gram.h"
#include "screen.h"
#include "icons.h"
#include "add_window.h"
#include "workmgr.h"
#include "cursor.h"
#ifdef VMS
#include <X11Xmu/CharSet.h>
#include <decw$bitmaps/menu12.xbm>
#include "vms_cmd_services.h"
#include <lib$routines.h>
#else
#include <X11/Xmu/CharSet.h>
#endif
#include "version.h"

#ifdef X11R6
#include <X11/SM/SMlib.h>
#endif

#if defined(MACH) || defined(sony_news) || defined(NeXT)
#define lrand48 random
#endif
#ifdef VMS
#define lrand48 rand
#endif

#ifndef VMS
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif
#define ABS(x) ((x)<0?-(x):(x))

#ifdef SOUNDS
extern int toggle_sound();
extern int reread_sounds();
#endif

extern XEvent Event;

int RootFunction = 0;
MenuRoot *ActiveMenu = NULL;		/* the active menu */
MenuItem *ActiveItem = NULL;		/* the active menu item */
int MoveFunction;			/* either F_MOVE or F_FORCEMOVE */
int WindowMoved = FALSE;
int menuFromFrameOrWindowOrTitlebar = FALSE;
char *CurrentSelectedWorkspace;
int AlternateKeymap;
Bool AlternateContext;

extern int captive;
extern char *captivename;

int ConstMove = FALSE;		/* constrained move variables */
int ConstMoveDir;
int ConstMoveX;
int ConstMoveY;
int ConstMoveXL;
int ConstMoveXR;
int ConstMoveYT;
int ConstMoveYB;
 
/* Globals used to keep track of whether the mouse has moved during
   a resize function. */
int ResizeOrigX;
int ResizeOrigY;

int MenuDepth = 0;		/* number of menus up */
static struct {
    int x;
    int y;
} MenuOrigins[MAXMENUDEPTH];
static Cursor LastCursor;
static Bool addingdefaults = False;

void WarpAlongRing(), WarpToWindow();
void DisplayPosition ();
void packwindow(), fillwindow();
int FindConstraint ();
int CreateFonts();		/* in ctwm.c */
int match ();			/* in list.c */

extern char *Action;
extern int Context;
extern TwmWindow *ButtonWindow, *Tmp_win;
extern XEvent Event, ButtonEvent;
extern char *InitFile;
static void LockScreen(), Identify();

#define SHADOWWIDTH 5			/* in pixels */



/***********************************************************************
 *
 *  Procedure:
 *	InitMenus - initialize menu roots
 *
 ***********************************************************************
 */

void
InitMenus()
{
    Scr->DefaultFunction.func = 0;
    Scr->WindowFunction.func  = 0;
    Scr->ChangeWorkspaceFunction.func  = 0;
    Scr->DeIconifyFunction.func  = 0;
    Scr->IconifyFunction.func  = 0;

    Scr->FuncKeyRoot.next = NULL;
    Scr->FuncButtonRoot.next = NULL;
}



/***********************************************************************
 *
 *  Procedure:
 *	AddFuncKey - add a function key to the list
 *
 *  Inputs:
 *	name	- the name of the key
 *	cont	- the context to look for the key press in
 *	mods	- modifier keys that need to be pressed
 *	func	- the function to perform
 *	win_name- the window name (if any)
 *	action	- the action string associated with the function (if any)
 *
 ***********************************************************************
 */

Bool AddFuncKey (name, cont, mods, func, menu, win_name, action)
    char *name;
    int cont, mods, func;
    MenuRoot *menu;
    char *win_name;
    char *action;
{
    FuncKey *tmp;
    KeySym keysym;
    KeyCode keycode;

    /*
     * Don't let a 0 keycode go through, since that means AnyKey to the
     * XGrabKey call in GrabKeys().
     */
    if ((keysym = XStringToKeysym(name)) == NoSymbol ||
	(keycode = XKeysymToKeycode(dpy, keysym)) == 0)
    {
	return False;
    }

    /* see if there already is a key defined for this context */
    for (tmp = Scr->FuncKeyRoot.next; tmp != NULL; tmp = tmp->next)
    {
	if (tmp->keysym == keysym &&
	    tmp->cont == cont &&
	    tmp->mods == mods)
	    break;
    }
    if (tmp && addingdefaults) return (True);

    if (tmp == NULL)
    {
	tmp = (FuncKey *) malloc(sizeof(FuncKey));
	tmp->next = Scr->FuncKeyRoot.next;
	Scr->FuncKeyRoot.next = tmp;
    }

    tmp->name = name;
    tmp->keysym = keysym;
    tmp->keycode = keycode;
    tmp->cont = cont;
    tmp->mods = mods;
    tmp->func = func;
    tmp->menu = menu;
    tmp->win_name = win_name;
    tmp->action = action;

    return True;
}

/***********************************************************************
 *
 *  Procedure:
 *	AddFuncButton - add a function button to the list
 *
 *  Inputs:
 *	num	- the num of the button
 *	cont	- the context to look for the key press in
 *	mods	- modifier keys that need to be pressed
 *	func	- the function to perform
 *	menu    - the menu (if any)
 *	item	- the menu item (if any)
 *
 ***********************************************************************
 */

Bool AddFuncButton (num, cont, mods, func, menu, item)
    int  num, cont, mods, func;
    MenuRoot *menu;
    MenuItem *item;
{
    FuncButton *tmp;

    /* see if there already is a key defined for this context */
    for (tmp = Scr->FuncButtonRoot.next; tmp != NULL; tmp = tmp->next) {
	if ((tmp->num == num) && (tmp->cont == cont) && (tmp->mods == mods))
	    break;
    }
    if (tmp && addingdefaults) return (True);

    if (tmp == NULL) {
	tmp = (FuncButton*) malloc (sizeof (FuncButton));
	tmp->next = Scr->FuncButtonRoot.next;
	Scr->FuncButtonRoot.next = tmp;
    }

    tmp->num  = num;
    tmp->cont = cont;
    tmp->mods = mods;
    tmp->func = func;
    tmp->menu = menu;
    tmp->item = item;

    return True;
}



static TitleButton *cur_tb = NULL;

void ModifyCurrentTB(button, func, action, menuroot)
    int button;
    int func;
    char *action;
    MenuRoot *menuroot;
{
    if (!cur_tb) {
        fprintf (stderr, "%s: can't find titlebutton\n", ProgramName);
      return;
    }
    cur_tb->funs[button - 1].func = func;
    cur_tb->funs[button - 1].action = action;
    cur_tb->funs[button - 1].menuroot = menuroot;
}

int CreateTitleButton (name, func, action, menuroot, rightside, append)
    char *name;
    int func;
    char *action;
    MenuRoot *menuroot;
    Bool rightside;
    Bool append;
{
    int button;
    cur_tb = (TitleButton *) malloc (sizeof(TitleButton));

    if (!cur_tb) {
	fprintf (stderr,
		 "%s:  unable to allocate %d bytes for title button\n",
		 ProgramName, sizeof(TitleButton));
	return 0;
    }

    cur_tb->next = NULL;
    cur_tb->name = name;                      /* note that we are not copying */
    cur_tb->image = None;                     /* WARNING, values not set yet */
    cur_tb->width = 0;                        /* see InitTitlebarButtons */
    cur_tb->height = 0;                       /* ditto */
    cur_tb->rightside = rightside;
    if (rightside) {
	Scr->TBInfo.nright++;
    } else {
	Scr->TBInfo.nleft++;
    }

    for(button = 0; button < MAX_BUTTONS; button++){
	cur_tb->funs[button].func = func;
	cur_tb->funs[button].action = action;
	cur_tb->funs[button].menuroot = menuroot;
    }

    /*
     * Cases for list:
     * 
     *     1.  empty list, prepend left       put at head of list
     *     2.  append left, prepend right     put in between left and right
     *     3.  append right                   put at tail of list
     *
     * Do not refer to widths and heights yet since buttons not created
     * (since fonts not loaded and heights not known).
     */
    if ((!Scr->TBInfo.head) || ((!append) && (!rightside))) {	/* 1 */
	cur_tb->next = Scr->TBInfo.head;
	Scr->TBInfo.head = cur_tb;
    } else if (append && rightside) {	/* 3 */
	register TitleButton *t;
	for /* SUPPRESS 530 */
	  (t = Scr->TBInfo.head; t->next; t = t->next);
	t->next = cur_tb;
	cur_tb->next = NULL;
    } else {				/* 2 */
	register TitleButton *t, *prev = NULL;
	for (t = Scr->TBInfo.head; t && !t->rightside; t = t->next) {
	    prev = t;
	}
	if (prev) {
	    cur_tb->next = prev->next;
	    prev->next = cur_tb;
	} else {
	    cur_tb->next = Scr->TBInfo.head;
	    Scr->TBInfo.head = cur_tb;
	}
    }

    return 1;
}



/*
 * InitTitlebarButtons - Do all the necessary stuff to load in a titlebar
 * button.  If we can't find the button, then put in a question; if we can't
 * find the question mark, something is wrong and we are probably going to be
 * in trouble later on.
 */
void InitTitlebarButtons ()
{
    TitleButton *tb;
    int h;

    /*
     * initialize dimensions
     */
    Scr->TBInfo.width = (Scr->TitleHeight -
			 2 * (Scr->FramePadding + Scr->ButtonIndent));
    if (Scr->use3Dtitles) 
	Scr->TBInfo.pad = ((Scr->TitlePadding > 1)
		       ? ((Scr->TitlePadding + 1) / 2) : 0);
    else
	Scr->TBInfo.pad = ((Scr->TitlePadding > 1)
		       ? ((Scr->TitlePadding + 1) / 2) : 1);
    h = Scr->TBInfo.width - 2 * Scr->TBInfo.border;

    /*
     * add in some useful buttons and bindings so that novices can still
     * use the system.
     */
    if (!Scr->NoDefaults) {
	/* insert extra buttons */
	if (Scr->use3Dtitles) {
	    if (!CreateTitleButton (TBPM_3DDOT, F_ICONIFY, "", (MenuRoot *) NULL,
				False, False)) {
	        fprintf (stderr, "%s:  unable to add iconify button\n", ProgramName);
	    }
	    if (!CreateTitleButton (TBPM_3DRESIZE, F_RESIZE, "", (MenuRoot *) NULL,
				True, True)) {
	        fprintf (stderr, "%s:  unable to add resize button\n", ProgramName);
	    }
	}
	else {
	    if (!CreateTitleButton (TBPM_ICONIFY, F_ICONIFY, "", (MenuRoot *) NULL,
				False, False)) {
	        fprintf (stderr, "%s:  unable to add iconify button\n", ProgramName);
	    }
	    if (!CreateTitleButton (TBPM_RESIZE, F_RESIZE, "", (MenuRoot *) NULL,
				True, True)) {
	        fprintf (stderr, "%s:  unable to add resize button\n", ProgramName);
	    }
	}
	addingdefaults = True;
	AddDefaultBindings ();
	addingdefaults = False;
    }
    ComputeCommonTitleOffsets ();

    /*
     * load in images and do appropriate centering
     */

    for (tb = Scr->TBInfo.head; tb; tb = tb->next) {
	tb->image = GetImage (tb->name, Scr->TitleC);
	if (!tb->image) {
	    tb->image = GetImage (TBPM_QUESTION, Scr->TitleC);
	    if (!tb->image) {		/* cannot happen (see util.c) */
		fprintf (stderr, "%s:  unable to add titlebar button \"%s\"\n",
			 ProgramName, tb->name);
	    }
	}
	tb->width  = tb->image->width;
	tb->height = tb->image->height;
	tb->dstx = (h - tb->width + 1) / 2;
	if (tb->dstx < 0) {		/* clip to minimize copying */
	    tb->srcx = -(tb->dstx);
	    tb->width = h;
	    tb->dstx = 0;
	} else {
	    tb->srcx = 0;
	}
	tb->dsty = (h - tb->height + 1) / 2;
	if (tb->dsty < 0) {
	    tb->srcy = -(tb->dsty);
	    tb->height = h;
	    tb->dsty = 0;
	} else {
	    tb->srcy = 0;
	}
    }
}


PaintEntry(mr, mi, exposure)
MenuRoot *mr;
MenuItem *mi;
int exposure;
{
    if (Scr->use3Dmenus)
	Paint3DEntry (mr, mi, exposure);
    else 
	PaintNormalEntry (mr, mi, exposure);
    if (mi->state) mr->lastactive = mi;
}

Paint3DEntry(mr, mi, exposure)
MenuRoot *mr;
MenuItem *mi;
int exposure;
{
    int y_offset;
    int text_y;
    GC gc;

    y_offset = mi->item_num * Scr->EntryHeight + Scr->MenuShadowDepth;
    text_y = y_offset + Scr->MenuFont.y + 2;

    if (mi->func != F_TITLE) {
	int x, y;

	if (mi->state) {
	    Draw3DBorder (mr->w, Scr->MenuShadowDepth, y_offset,
			mr->width - 2 * Scr->MenuShadowDepth, Scr->EntryHeight, 1, 
			mi->highlight, off, True, False);
#ifdef I18N
	    FB(mi->highlight.fore, mi->highlight.back);
	    XmbDrawImageString(dpy, mr->w, Scr->MenuFont.font_set,
			       Scr->NormalGC,
			       mi->x + Scr->MenuShadowDepth,
			       text_y, mi->item, mi->strlen);
#else	    
	    FBF(mi->highlight.fore, mi->highlight.back, Scr->MenuFont.font->fid);
	    XDrawImageString(dpy, mr->w, Scr->NormalGC,
		mi->x + Scr->MenuShadowDepth, text_y, mi->item, mi->strlen);
#endif	    
	    gc = Scr->NormalGC;
	}
	else {
	    if (mi->user_colors || !exposure) {
		XSetForeground (dpy, Scr->NormalGC, mi->normal.back);
		XFillRectangle (dpy, mr->w, Scr->NormalGC,
			Scr->MenuShadowDepth, y_offset,
			mr->width - 2 * Scr->MenuShadowDepth, Scr->EntryHeight);
#ifdef I18N
		FB (mi->normal.fore, mi->normal.back);
#else		
		FBF (mi->normal.fore, mi->normal.back, Scr->MenuFont.font->fid);
#endif		
		gc = Scr->NormalGC;
	    }
	    else {
		gc = Scr->MenuGC;
	    }
#ifdef I18N
	    XmbDrawImageString (dpy, mr->w, Scr->MenuFont.font_set, gc,
				mi->x + Scr->MenuShadowDepth, text_y,
				mi->item, mi->strlen);
#else	    
	    XDrawImageString (dpy, mr->w, gc,
			      mi->x + Scr->MenuShadowDepth, text_y,
			      mi->item, mi->strlen);
#endif	    
	    if (mi->separated) {
		FB (Scr->MenuC.shadd, Scr->MenuC.shadc);
		XDrawLine (dpy, mr->w, Scr->NormalGC,
				Scr->MenuShadowDepth,
				y_offset + Scr->EntryHeight - 2,
				mr->width - Scr->MenuShadowDepth,
				y_offset + Scr->EntryHeight - 2);
		FB (Scr->MenuC.shadc, Scr->MenuC.shadd);
		XDrawLine (dpy, mr->w, Scr->NormalGC,
				Scr->MenuShadowDepth,
				y_offset + Scr->EntryHeight - 1,
				mr->width - Scr->MenuShadowDepth,
				y_offset + Scr->EntryHeight - 1);
	    }
	}

	if (mi->func == F_MENU) {
	    /* create the pull right pixmap if needed */
	    if (Scr->pullPm == None)
	    {
		Scr->pullPm = Create3DMenuIcon (Scr->MenuFont.height, &Scr->pullW,
				&Scr->pullH, Scr->MenuC);
	    }
	    x = mr->width - Scr->pullW - Scr->MenuShadowDepth - 2;
	    y = y_offset + ((Scr->MenuFont.height - Scr->pullH) / 2) + 2;
	    XCopyArea (dpy, Scr->pullPm, mr->w, gc, 0, 0, Scr->pullW, Scr->pullH, x, y);
	}
    }
    else
    {
	Draw3DBorder (mr->w, Scr->MenuShadowDepth, y_offset,
			mr->width - 2 * Scr->MenuShadowDepth, Scr->EntryHeight, 1, 
			mi->normal, off, True, False);
#ifdef I18N
	FB (mi->normal.fore, mi->normal.back);
	XmbDrawImageString(dpy, mr->w, Scr->MenuFont.font_set, Scr->NormalGC,
			   mi->x + 2, text_y, mi->item, mi->strlen);
#else	
	FBF (mi->normal.fore, mi->normal.back, Scr->MenuFont.font->fid);
	XDrawImageString (dpy, mr->w, Scr->NormalGC, mi->x + 2, text_y, mi->item, mi->strlen);
#endif	
    }
}
    


PaintNormalEntry(mr, mi, exposure)
MenuRoot *mr;
MenuItem *mi;
int exposure;
{
    int y_offset;
    int text_y;
    GC gc;

    y_offset = mi->item_num * Scr->EntryHeight;
    text_y = y_offset + Scr->MenuFont.y;

    if (mi->func != F_TITLE)
    {
	int x, y;

	if (mi->state)
	{
	    XSetForeground(dpy, Scr->NormalGC, mi->highlight.back);

	    XFillRectangle(dpy, mr->w, Scr->NormalGC, 0, y_offset,
		mr->width, Scr->EntryHeight);
#ifdef I18N
	    FB(mi->highlight.fore, mi->highlight.back);
	    XmbDrawString(dpy, mr->w, Scr->MenuFont.font_set, Scr->NormalGC,
			  mi->x, text_y, mi->item, mi->strlen);
#else	    
	    FBF(mi->highlight.fore, mi->highlight.back, Scr->MenuFont.font->fid);

	    XDrawString(dpy, mr->w, Scr->NormalGC, mi->x,
		text_y, mi->item, mi->strlen);
#endif	    

	    gc = Scr->NormalGC;
	}
	else
	{
	    if (mi->user_colors || !exposure)
	    {
		XSetForeground(dpy, Scr->NormalGC, mi->normal.back);

		XFillRectangle(dpy, mr->w, Scr->NormalGC, 0, y_offset,
		    mr->width, Scr->EntryHeight);

#ifdef I18N
		FB(mi->normal.fore, mi->normal.back);
#else
		FBF(mi->normal.fore, mi->normal.back, Scr->MenuFont.font->fid);
#endif
		gc = Scr->NormalGC;
	    }
	    else {
		gc = Scr->MenuGC;
	    }
#ifdef I18N
	    XmbDrawString(dpy, mr->w, Scr->MenuFont.font_set, gc, mi->x,
			  text_y, mi->item, mi->strlen);
#else	    
	    XDrawString(dpy, mr->w, gc, mi->x,
			text_y, mi->item, mi->strlen);
#endif	    
	    if (mi->separated)
		XDrawLine (dpy, mr->w, gc, 0, y_offset + Scr->EntryHeight - 1,
				mr->width, y_offset + Scr->EntryHeight - 1);
	}

	if (mi->func == F_MENU)
	{
	    /* create the pull right pixmap if needed */
	    if (Scr->pullPm == None)
	    {
		Scr->pullPm = CreateMenuIcon (Scr->MenuFont.height,
					     &Scr->pullW, &Scr->pullH);
	    }
	    x = mr->width - Scr->pullW - 5;
	    y = y_offset + ((Scr->MenuFont.height - Scr->pullH) / 2);
	    XCopyPlane(dpy, Scr->pullPm, mr->w, gc, 0, 0,
		Scr->pullW, Scr->pullH, x, y, 1);
	}
    }
    else
    {
	int y;

	XSetForeground(dpy, Scr->NormalGC, mi->normal.back);

	/* fill the rectangle with the title background color */
	XFillRectangle(dpy, mr->w, Scr->NormalGC, 0, y_offset,
	    mr->width, Scr->EntryHeight);

	{
	    XSetForeground(dpy, Scr->NormalGC, mi->normal.fore);
	    /* now draw the dividing lines */
	    if (y_offset)
	      XDrawLine (dpy, mr->w, Scr->NormalGC, 0, y_offset,
			 mr->width, y_offset);
	    y = ((mi->item_num+1) * Scr->EntryHeight)-1;
	    XDrawLine(dpy, mr->w, Scr->NormalGC, 0, y, mr->width, y);
	}

#ifdef I18N
	FB(mi->normal.fore, mi->normal.back);
	/* finally render the title */
	XmbDrawString(dpy, mr->w, Scr->MenuFont.font_set, Scr->NormalGC, mi->x,
		      text_y, mi->item, mi->strlen);
#else	
	FBF(mi->normal.fore, mi->normal.back, Scr->MenuFont.font->fid);
	/* finally render the title */
	XDrawString(dpy, mr->w, Scr->NormalGC, mi->x,
	    text_y, mi->item, mi->strlen);
#endif	
    }
}
    
PaintMenu(mr, e)
MenuRoot *mr;
XEvent *e;
{
    MenuItem *mi;

    if (Scr->use3Dmenus) {
	Draw3DBorder (mr->w, 0, 0, mr->width, mr->height,
		Scr->MenuShadowDepth, Scr->MenuC, off, False, False);
    }
    for (mi = mr->first; mi != NULL; mi = mi->next)
    {
	int y_offset = mi->item_num * Scr->EntryHeight;

	/* be smart about handling the expose, redraw only the entries
	 * that we need to
	 */
	if (e->xexpose.y <= (y_offset + Scr->EntryHeight) &&
	    (e->xexpose.y + e->xexpose.height) >= y_offset)
	{
	    PaintEntry(mr, mi, True);
	}
    }
    XSync(dpy, 0);
}



void MakeWorkspacesMenu () {
    static char **actions = NULL;
    WorkSpaceList *wlist;
    char **act;

    if (! Scr->Workspaces) return;
    AddToMenu (Scr->Workspaces, "TWM Workspaces", NULLSTR, NULL, F_TITLE, NULLSTR, NULLSTR);
    if (! actions) {
	int count = 0;

        for (wlist = Scr->workSpaceMgr.workSpaceList; wlist != NULL; wlist = wlist->next) {
            count++;
        }
	count++;
	actions = (char**) malloc (count * sizeof (char*));
	act = actions;
        for (wlist = Scr->workSpaceMgr.workSpaceList; wlist != NULL; wlist = wlist->next) {
	    *act = (char*) malloc (strlen ("WGOTO : ") + strlen (wlist->name) + 1);
	    sprintf (*act, "WGOTO : %s", wlist->name);
	    act++;
	}
	*act = NULL;
    }
    act = actions;
    for (wlist = Scr->workSpaceMgr.workSpaceList; wlist != NULL; wlist = wlist->next) {
        AddToMenu (Scr->Workspaces, wlist->name, *act, Scr->Windows, F_MENU, NULL, NULL);
	act++;
    }
    Scr->Workspaces->pinned = False;
    MakeMenu (Scr->Workspaces);
}

static Bool fromMenu;

UpdateMenu()
{
    MenuItem *mi;
    int i, x, y, x_root, y_root, entry;
    int done;
    MenuItem *badItem = NULL;

    fromMenu = TRUE;

    while (TRUE)
    {
	/* block until there is an event */
        if (!menuFromFrameOrWindowOrTitlebar) {
	  XMaskEvent(dpy,
		     ButtonPressMask | ButtonReleaseMask |
		     KeyPressMask | KeyReleaseMask |
		     EnterWindowMask | ExposureMask |
		     VisibilityChangeMask | LeaveWindowMask |
		     ButtonMotionMask, &Event);
	}
	if (Event.type == MotionNotify) {
	    /* discard any extra motion events before a release */
	    while(XCheckMaskEvent(dpy,
		ButtonMotionMask | ButtonReleaseMask, &Event))
		if (Event.type == ButtonRelease)
		    break;
	}

	if (!DispatchEvent ())
	    continue;

	if ((! ActiveMenu) || Cancel) {
	  menuFromFrameOrWindowOrTitlebar = FALSE;
	  fromMenu = FALSE;
	  return (0);
	}

	if (Event.type != MotionNotify)
	    continue;

	done = FALSE;
	XQueryPointer( dpy, ActiveMenu->w, &JunkRoot, &JunkChild,
	    &x_root, &y_root, &x, &y, &JunkMask);

	/* if we haven't recieved the enter notify yet, wait */
	if (ActiveMenu && !ActiveMenu->entered)
	    continue;

	XFindContext(dpy, ActiveMenu->w, ScreenContext, (XPointer *)&Scr);

	if (x < 0 || y < 0 ||
	    x >= ActiveMenu->width || y >= ActiveMenu->height)
	{
	    if (ActiveItem && ActiveItem->func != F_TITLE)
	    {
		ActiveItem->state = 0;
		PaintEntry(ActiveMenu, ActiveItem, False);
	    }
	    ActiveItem = NULL;
	    continue;
	}

	/* look for the entry that the mouse is in */
	entry = y / Scr->EntryHeight;
	for (i = 0, mi = ActiveMenu->first; mi != NULL; i++, mi=mi->next)
	{
	    if (i == entry)
		break;
	}

	/* if there is an active item, we might have to turn it off */
	if (ActiveItem)
	{
	    /* is the active item the one we are on ? */
	    if (ActiveItem->item_num == entry && ActiveItem->state)
		done = TRUE;

	    /* if we weren't on the active entry, let's turn the old
	     * active one off 
	     */
	    if (!done && ActiveItem->func != F_TITLE)
	    {
		ActiveItem->state = 0;
		PaintEntry(ActiveMenu, ActiveItem, False);
	    }
	}

	/* if we weren't on the active item, change the active item and turn
	 * it on 
	 */
	if (!done)
	{
	    ActiveItem = mi;
	    if (ActiveItem && ActiveItem->func != F_TITLE && !ActiveItem->state)
	    {
		ActiveItem->state = 1;
		PaintEntry(ActiveMenu, ActiveItem, False);
	    }
	}

	/* now check to see if we were over the arrow of a pull right entry */
	if (ActiveItem && ActiveItem->func == F_MENU && 
	   ((ActiveMenu->width - x) < (ActiveMenu->width / 3)))
	{
	    MenuRoot *save = ActiveMenu;
	    int savex = MenuOrigins[MenuDepth - 1].x; 
	    int savey = MenuOrigins[MenuDepth - 1].y;

	    if (MenuDepth < MAXMENUDEPTH) {
		if (ActiveMenu == Scr->Workspaces)
		    CurrentSelectedWorkspace = ActiveItem->item;
		PopUpMenu (ActiveItem->sub, 
			   (savex + (((2 * ActiveMenu->width) / 3) - 1)), 
			   (savey + ActiveItem->item_num * Scr->EntryHeight)
			   /*(savey + ActiveItem->item_num * Scr->EntryHeight +
			    (Scr->EntryHeight >> 1))*/, False);
		CurrentSelectedWorkspace = NULL;
	    } else if (!badItem) {
		XBell (dpy, 0);
		badItem = ActiveItem;
	    }

	    /* if the menu did get popped up, unhighlight the active item */
	    if (save != ActiveMenu && ActiveItem->state)
	    {
		ActiveItem->state = 0;
		PaintEntry(save, ActiveItem, False);
		ActiveItem = NULL;
	    }
	}
	if (badItem != ActiveItem) badItem = NULL;
	XFlush(dpy);
    }
}



/***********************************************************************
 *
 *  Procedure:
 *	NewMenuRoot - create a new menu root
 *
 *  Returned Value:
 *	(MenuRoot *)
 *
 *  Inputs:
 *	name	- the name of the menu root
 *
 ***********************************************************************
 */

MenuRoot *
NewMenuRoot(name)
    char *name;
{
    MenuRoot *tmp;

#define UNUSED_PIXEL ((unsigned long) (~0))	/* more than 24 bits */

    tmp = (MenuRoot *) malloc(sizeof(MenuRoot));
    tmp->highlight.fore = UNUSED_PIXEL;
    tmp->highlight.back = UNUSED_PIXEL;
    tmp->name = name;
    tmp->prev = NULL;
    tmp->first = NULL;
    tmp->last = NULL;
    tmp->defaultitem = NULL;
    tmp->items = 0;
    tmp->width = 0;
    tmp->mapped = NEVER_MAPPED;
    tmp->pull = FALSE;
    tmp->w = None;
    tmp->shadow = None;
    tmp->real_menu = FALSE;

    if (Scr->MenuList == NULL)
    {
	Scr->MenuList = tmp;
	Scr->MenuList->next = NULL;
    }

    if (Scr->LastMenu == NULL)
    {
	Scr->LastMenu = tmp;
	Scr->LastMenu->next = NULL;
    }
    else
    {
	Scr->LastMenu->next = tmp;
	Scr->LastMenu = tmp;
	Scr->LastMenu->next = NULL;
    }

    if (strcmp(name, TWM_WINDOWS) == 0)
	Scr->Windows = tmp;

    if (strcmp(name, TWM_WORKSPACES) == 0) {
	Scr->Workspaces = tmp;
	if (!Scr->Windows) NewMenuRoot (TWM_WINDOWS);
    }
    if (strcmp(name, TWM_ALLWINDOWS) == 0)
	Scr->AllWindows = tmp;

    return (tmp);
}



/***********************************************************************
 *
 *  Procedure:
 *	AddToMenu - add an item to a root menu
 *
 *  Returned Value:
 *	(MenuItem *)
 *
 *  Inputs:
 *	menu	- pointer to the root menu to add the item
 *	item	- the text to appear in the menu
 *	action	- the string to possibly execute
 *	sub	- the menu root if it is a pull-right entry
 *	func	- the numeric function
 *	fore	- foreground color string
 *	back	- background color string
 *
 ***********************************************************************
 */

MenuItem *
AddToMenu(menu, item, action, sub, func, fore, back)
    MenuRoot *menu;
    char *item, *action;
    MenuRoot *sub;
    int func;
    char *fore, *back;
{
    MenuItem *tmp;
    int width;
    char *itemname;
#ifdef I18N
    XRectangle ink_rect;
    XRectangle logical_rect;
#endif    

#ifdef DEBUG_MENUS
    fprintf(stderr, "adding menu item=\"%s\", action=%s, sub=%d, f=%d\n",
	item, action, sub, func);
#endif

    tmp = (MenuItem *) malloc(sizeof(MenuItem));
    tmp->root = menu;

    if (menu->first == NULL)
    {
	menu->first = tmp;
	tmp->prev = NULL;
    }
    else
    {
	menu->last->next = tmp;
	tmp->prev = menu->last;
    }
    menu->last = tmp;

    if (*item == '*') {
	itemname = item + 1;
	menu->defaultitem = tmp;
    }
    else {
	itemname = item;
    }
    tmp->item = itemname;	
    tmp->strlen = strlen(itemname);
    tmp->action = action;
    tmp->next = NULL;
    tmp->sub = NULL;
    tmp->state = 0;
    tmp->func = func;
    tmp->separated = 0;

    if (!Scr->HaveFonts) CreateFonts();
#ifdef I18N
    XmbTextExtents(Scr->MenuFont.font_set,
		   itemname, tmp->strlen,
		   &ink_rect, &logical_rect);
    width = logical_rect.width;
#else    
    width = XTextWidth(Scr->MenuFont.font, itemname, tmp->strlen);
#endif    
    if (width <= 0)
	width = 1;
    if (width > menu->width)
	menu->width = width;

    tmp->user_colors = FALSE;
    if (Scr->Monochrome == COLOR && fore != NULL)
    {
	int save;

	save = Scr->FirstTime;
	Scr->FirstTime = TRUE;
	GetColor(COLOR, &tmp->normal.fore, fore);
	GetColor(COLOR, &tmp->normal.back, back);
	if (Scr->use3Dmenus && !Scr->BeNiceToColormap) GetShadeColors (&tmp->normal);
	Scr->FirstTime = save;
	tmp->user_colors = TRUE;
    }
    if (sub != NULL)
    {
	tmp->sub = sub;
	menu->pull = TRUE;
    }
    tmp->item_num = menu->items++;

    return (tmp);
}



MakeMenus()
{
    MenuRoot *mr;

    for (mr = Scr->MenuList; mr != NULL; mr = mr->next)
    {
	if (mr->real_menu == FALSE)
	    continue;

	mr->pinned = False;
	MakeMenu(mr);
    }
}



MakeMenu(mr)
MenuRoot *mr;
{
    MenuItem *start, *end, *cur, *tmp;
    XColor f1, f2, f3;
    XColor b1, b2, b3;
    XColor save_fore, save_back;
    int num, i;
    int fred, fgreen, fblue;
    int bred, bgreen, bblue;
    int width, borderwidth;
    unsigned long valuemask;
    XSetWindowAttributes attributes;
    Colormap cmap = Scr->TwmRoot.cmaps.cwins[0]->colormap->c;
#ifdef I18N
    XRectangle ink_rect;
    XRectangle logical_rect;
#endif    

    Scr->EntryHeight = Scr->MenuFont.height + 4;

    /* lets first size the window accordingly */
    if (mr->mapped == NEVER_MAPPED)
    {
	if (mr->pull == TRUE) {
	    mr->width += 16 + 10;
	}
	width = mr->width + 10;
	for (cur = mr->first; cur != NULL; cur = cur->next) {
	    if (cur->func != F_TITLE)
		cur->x = 5;
	    else {
#ifdef I18N
		XmbTextExtents(Scr->MenuFont.font_set, cur->item, cur->strlen,
			       &ink_rect, &logical_rect);
		cur->x = width - logical_rect.width;
#else		
		cur->x = width - XTextWidth(Scr->MenuFont.font, cur->item,
				cur->strlen);
#endif		
		cur->x /= 2;
	    }
	}
	mr->height = mr->items * Scr->EntryHeight;
	mr->width += 10;
	if (Scr->use3Dmenus) {
	    mr->width  += 2 * Scr->MenuShadowDepth;
	    mr->height += 2 * Scr->MenuShadowDepth;
	}
	if (Scr->Shadow && ! mr->pinned)
	{
	    /*
	     * Make sure that you don't draw into the shadow window or else
	     * the background bits there will get saved
	     */
	    valuemask = (CWBackPixel | CWBorderPixel);
	    attributes.background_pixel = Scr->MenuShadowColor;
	    attributes.border_pixel = Scr->MenuShadowColor;
	    if (Scr->SaveUnder) {
		valuemask |= CWSaveUnder;
		attributes.save_under = True;
	    }
	    mr->shadow = XCreateWindow (dpy, Scr->Root, 0, 0,
					(unsigned int) mr->width, 
					(unsigned int) mr->height,
					(unsigned int)0,
					CopyFromParent, 
					(unsigned int) CopyFromParent,
					(Visual *) CopyFromParent,
					valuemask, &attributes);
	}

	valuemask = (CWBackPixel | CWBorderPixel | CWEventMask);
	attributes.background_pixel = Scr->MenuC.back;
	attributes.border_pixel = Scr->MenuC.fore;
	if (mr->pinned) {
	    attributes.event_mask = (ExposureMask | EnterWindowMask
				| LeaveWindowMask | ButtonPressMask
				| ButtonReleaseMask | PointerMotionMask
				| ButtonMotionMask
				);
	    attributes.cursor = Scr->MenuCursor;
	    valuemask |= CWCursor;
	}
	else
	    attributes.event_mask = (ExposureMask | EnterWindowMask);

	if (Scr->SaveUnder && ! mr->pinned) {
	    valuemask |= CWSaveUnder;
	    attributes.save_under = True;
	}
	if (Scr->BackingStore) {
	    valuemask |= CWBackingStore;
	    attributes.backing_store = Always;
	}
	borderwidth = Scr->use3Dmenus ? 0 : 1;
	mr->w = XCreateWindow (dpy, Scr->Root, 0, 0, (unsigned int) mr->width,
			       (unsigned int) mr->height, (unsigned int) borderwidth,
			       CopyFromParent, (unsigned int) CopyFromParent,
			       (Visual *) CopyFromParent,
			       valuemask, &attributes);


	XSaveContext(dpy, mr->w, MenuContext, (XPointer)mr);
	XSaveContext(dpy, mr->w, ScreenContext, (XPointer)Scr);

	mr->mapped = UNMAPPED;
    }

    if (Scr->use3Dmenus && (Scr->Monochrome == COLOR) &&  (mr->highlight.back == UNUSED_PIXEL)) {
	XColor xcol;
	char colname [32];
	short save;

	xcol.pixel = Scr->MenuC.back;
	XQueryColor (dpy, cmap, &xcol);
	sprintf (colname, "#%04x%04x%04x", 
		5 * ((int)xcol.red   / 6),
		5 * ((int)xcol.green / 6),
		5 * ((int)xcol.blue  / 6));
	save = Scr->FirstTime;
	Scr->FirstTime = True;
	GetColor (Scr->Monochrome, &mr->highlight.back, colname);
	Scr->FirstTime = save;
    }

    if (Scr->use3Dmenus && (Scr->Monochrome == COLOR) && (mr->highlight.fore == UNUSED_PIXEL)) {
	XColor xcol;
	char colname [32];
	short save;

	xcol.pixel = Scr->MenuC.fore;
	XQueryColor (dpy, cmap, &xcol);
	sprintf (colname, "#%04x%04x%04x",
		5 * ((int)xcol.red   / 6),
		5 * ((int)xcol.green / 6),
		5 * ((int)xcol.blue  / 6));
	save = Scr->FirstTime;
	Scr->FirstTime = True;
	GetColor (Scr->Monochrome, &mr->highlight.fore, colname);
	Scr->FirstTime = save;
    }
    if (Scr->use3Dmenus && !Scr->BeNiceToColormap) GetShadeColors (&mr->highlight);

    /* get the default colors into the menus */
    for (tmp = mr->first; tmp != NULL; tmp = tmp->next)
    {
	if (!tmp->user_colors) {
	    if (tmp->func != F_TITLE) {
		tmp->normal.fore = Scr->MenuC.fore;
		tmp->normal.back = Scr->MenuC.back;
	    } else {
		tmp->normal.fore = Scr->MenuTitleC.fore;
		tmp->normal.back = Scr->MenuTitleC.back;
	    }
	}

	if (mr->highlight.fore != UNUSED_PIXEL)
	{
	    tmp->highlight.fore = mr->highlight.fore;
	    tmp->highlight.back = mr->highlight.back;
	}
	else
	{
	    tmp->highlight.fore = tmp->normal.back;
	    tmp->highlight.back = tmp->normal.fore;
	}
	if (Scr->use3Dmenus && !Scr->BeNiceToColormap) {
	    if (tmp->func != F_TITLE)
		GetShadeColors (&tmp->highlight);
	    else
		GetShadeColors (&tmp->normal);
	}
    }
    mr->pmenu = NULL;

    if (Scr->Monochrome == MONOCHROME || !Scr->InterpolateMenuColors)
	return 0;

    start = mr->first;
    while (TRUE)
    {
	for (; start != NULL; start = start->next)
	{
	    if (start->user_colors)
		break;
	}
	if (start == NULL)
	    break;

	for (end = start->next; end != NULL; end = end->next)
	{
	    if (end->user_colors)
		break;
	}
	if (end == NULL)
	    break;

	/* we have a start and end to interpolate between */
	num = end->item_num - start->item_num;

	f1.pixel = start->normal.fore;
	XQueryColor(dpy, cmap, &f1);
	f2.pixel = end->normal.fore;
	XQueryColor(dpy, cmap, &f2);

	b1.pixel = start->normal.back;
	XQueryColor(dpy, cmap, &b1);
	b2.pixel = end->normal.back;
	XQueryColor(dpy, cmap, &b2);

	fred = ((int)f2.red - (int)f1.red) / num;
	fgreen = ((int)f2.green - (int)f1.green) / num;
	fblue = ((int)f2.blue - (int)f1.blue) / num;

	bred = ((int)b2.red - (int)b1.red) / num;
	bgreen = ((int)b2.green - (int)b1.green) / num;
	bblue = ((int)b2.blue - (int)b1.blue) / num;

	f3 = f1;
	f3.flags = DoRed | DoGreen | DoBlue;

	b3 = b1;
	b3.flags = DoRed | DoGreen | DoBlue;

	start->highlight.back = start->normal.fore;
	start->highlight.fore = start->normal.back;
	num -= 1;
	for (i = 0, cur = start->next; i < num; i++, cur = cur->next)
	{
	    f3.red += fred;
	    f3.green += fgreen;
	    f3.blue += fblue;
	    save_fore = f3;

	    b3.red += bred;
	    b3.green += bgreen;
	    b3.blue += bblue;
	    save_back = b3;

	    XAllocColor(dpy, cmap, &f3);
	    XAllocColor(dpy, cmap, &b3);
	    cur->highlight.back = cur->normal.fore = f3.pixel;
	    cur->highlight.fore = cur->normal.back = b3.pixel;
	    cur->user_colors = True;

	    f3 = save_fore;
	    b3 = save_back;
	}
	start = end;
	start->highlight.back = start->normal.fore;
	start->highlight.fore = start->normal.back;
    }
}



/***********************************************************************
 *
 *  Procedure:
 *	PopUpMenu - pop up a pull down menu
 *
 *  Inputs:
 *	menu	- the root pointer of the menu to pop up
 *	x, y	- location of upper left of menu
 *      center	- whether or not to center horizontally over position
 *
 ***********************************************************************
 */

Bool PopUpMenu (menu, x, y, center)
    MenuRoot *menu;
    int x, y;
    Bool center;
{
    int WindowNameOffset, WindowNameCount;
    TwmWindow **WindowNames;
    TwmWindow *tmp_win2,*tmp_win3;
    int i;
    int xl, yt;
    int (*compar)() = (Scr->CaseSensitive ? strcmp : XmuCompareISOLatin1);
    Bool clipped;

    if (!menu) return False;

    InstallRootColormap();

    if ((menu == Scr->Windows) || (menu == Scr->AllWindows))
    {
	TwmWindow *tmp_win;
	WorkSpaceList *wlist;
	Boolean all;
	int func;

	/* this is the twm windows menu,  let's go ahead and build it */

	all = (menu == Scr->AllWindows);
	DestroyMenu (menu);

	menu->first = NULL;
	menu->last = NULL;
	menu->items = 0;
	menu->width = 0;
	menu->mapped = NEVER_MAPPED;
	menu->highlight.fore = UNUSED_PIXEL;
	menu->highlight.back = UNUSED_PIXEL;
	if (menu == Scr->Windows) 
  	    AddToMenu(menu, "TWM Windows", NULLSTR, NULL, F_TITLE,NULLSTR,NULLSTR);
	else
  	    AddToMenu(menu, "TWM All Windows", NULLSTR, NULL, F_TITLE,NULLSTR,NULLSTR);
  
	wlist = NULL;
	if (! all && CurrentSelectedWorkspace) {
	    for (wlist = Scr->workSpaceMgr.workSpaceList; wlist != NULL; wlist = wlist->next) {
        	if (strcmp (wlist->name, CurrentSelectedWorkspace) == 0) break;
	    }
	}
	if (! wlist) wlist = Scr->workSpaceMgr.activeWSPC;

        WindowNameOffset=(char *)Scr->TwmRoot.next->name -
                               (char *)Scr->TwmRoot.next;
        for(tmp_win = Scr->TwmRoot.next , WindowNameCount=0;
            tmp_win != NULL;
            tmp_win = tmp_win->next) {
	  if (tmp_win == Scr->workSpaceMgr.occupyWindow.twm_win) continue;
	  if (Scr->ShortAllWindowsMenus &&
		tmp_win == Scr->workSpaceMgr.workspaceWindow.twm_win) continue;
	  if (Scr->ShortAllWindowsMenus && tmp_win->iconmgr) continue;

	  if (all || OCCUPY (tmp_win, wlist)) WindowNameCount++;
	}
        WindowNames = (TwmWindow **)malloc(sizeof(TwmWindow *)*WindowNameCount);
	WindowNameCount = 0;
        for(tmp_win = Scr->TwmRoot.next;
            tmp_win != NULL;
            tmp_win = tmp_win->next)
        {
	    if (tmp_win == Scr->workSpaceMgr.occupyWindow.twm_win) continue;
	    if (Scr->ShortAllWindowsMenus &&
		tmp_win == Scr->workSpaceMgr.workspaceWindow.twm_win) continue;
	    if (Scr->ShortAllWindowsMenus && tmp_win->iconmgr) continue;

	    if (!all && ! OCCUPY (tmp_win, wlist)) continue;
            tmp_win2 = tmp_win;
            for (i=0;i<WindowNameCount;i++)
            {
                if ((*compar)(tmp_win2->name,WindowNames[i]->name) < 0)
                {
                    tmp_win3 = tmp_win2;
                    tmp_win2 = WindowNames[i];
                    WindowNames[i] = tmp_win3;
                }
            }
            WindowNames[WindowNameCount] = tmp_win2;
	    WindowNameCount++;
        }
	func = (all || CurrentSelectedWorkspace) ? F_WINWARP : F_POPUP;
        for (i=0; i<WindowNameCount; i++)
        {
            AddToMenu(menu, WindowNames[i]->name, (char *)WindowNames[i],
                      NULL, func,NULL,NULL);
        }
        free(WindowNames);

	menu->pinned = False;
	MakeMenu(menu);
    }

    if (menu->w == None || menu->items == 0) return False;

    /* Prevent recursively bringing up menus. */
    if ((!menu->pinned) && (menu->mapped == MAPPED)) return False;

    /*
     * Dynamically set the parent;  this allows pull-ups to also be main
     * menus, or to be brought up from more than one place.
     */
    menu->prev = ActiveMenu;

    if (menu->pinned) {
	ActiveMenu    = menu;
	menu->mapped  = MAPPED;
	menu->entered = TRUE;
	MenuOrigins [MenuDepth].x = menu->x;
	MenuOrigins [MenuDepth].y = menu->y;
	MenuDepth++;

	XRaiseWindow (dpy, menu->w);
	return (True);
    }

    XGrabPointer(dpy, Scr->Root, True,
	ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
	ButtonMotionMask | PointerMotionHintMask,
	GrabModeAsync, GrabModeAsync,
	Scr->Root,
	Scr->MenuCursor, CurrentTime);

    XGrabKeyboard (dpy, Scr->Root, True, GrabModeAsync, GrabModeAsync, CurrentTime);

    ActiveMenu = menu;
    menu->mapped = MAPPED;
    menu->entered = FALSE;

    if (center) {
	x -= (menu->width / 2);
	y -= (Scr->EntryHeight / 2);	/* sticky menus would be nice here */
    }

    /*
    * clip to screen
    */
    clipped = FALSE;
    if (x + menu->width > Scr->MyDisplayWidth) {
	x = Scr->MyDisplayWidth - menu->width;
	clipped = TRUE;
    }
    if (x < 0) {
	x = 0;
	clipped = TRUE;
    }
    if (y + menu->height > Scr->MyDisplayHeight) {
	y = Scr->MyDisplayHeight - menu->height;
	clipped = TRUE;
    }
    if (y < 0) {
	y = 0;
	clipped = TRUE;
    }
    MenuOrigins[MenuDepth].x = x;
    MenuOrigins[MenuDepth].y = y;
    MenuDepth++;

    XMoveWindow(dpy, menu->w, x, y);
    if (Scr->Shadow) {
	XMoveWindow  (dpy, menu->shadow, x + SHADOWWIDTH, y + SHADOWWIDTH);
	XRaiseWindow (dpy, menu->shadow);
    }
    XMapRaised(dpy, menu->w);
    if (clipped && center) {
	xl = x + (menu->width      / 2);
	yt = y + (Scr->EntryHeight / 2);
	XWarpPointer (dpy, Scr->Root, Scr->Root, x, y, menu->width, menu->height, xl, yt);
    }
    if (Scr->Shadow) XMapWindow (dpy, menu->shadow);
    XSync(dpy, 0);
    return True;
}



/***********************************************************************
 *
 *  Procedure:
 *	PopDownMenu - unhighlight the current menu selection and
 *		take down the menus
 *
 ***********************************************************************
 */

PopDownMenu()
{
    MenuRoot *tmp;

    if (ActiveMenu == NULL)
	return (1);

    if (ActiveItem)
    {
	ActiveItem->state = 0;
	PaintEntry(ActiveMenu, ActiveItem, False);
    }

    for (tmp = ActiveMenu; tmp != NULL; tmp = tmp->prev)
    {
	if (! tmp->pinned) HideMenu (tmp);
	UninstallRootColormap();
    }

    XFlush(dpy);
    ActiveMenu = NULL;
    ActiveItem = NULL;
    MenuDepth = 0;
    XUngrabKeyboard (dpy, CurrentTime);
    if (Context == C_WINDOW || Context == C_FRAME || Context == C_TITLE || Context == C_ICON)
      menuFromFrameOrWindowOrTitlebar = TRUE;
}



HideMenu (menu)
MenuRoot *menu;
{
    if (!menu) return False;

    if (Scr->Shadow) {
	XUnmapWindow (dpy, menu->shadow);
    }
    XUnmapWindow (dpy, menu->w);
    menu->mapped = UNMAPPED;
}

/***********************************************************************
 *
 *  Procedure:
 *	FindMenuRoot - look for a menu root
 *
 *  Returned Value:
 *	(MenuRoot *)  - a pointer to the menu root structure 
 *
 *  Inputs:
 *	name	- the name of the menu root 
 *
 ***********************************************************************
 */

MenuRoot *
FindMenuRoot(name)
    char *name;
{
    MenuRoot *tmp;

    for (tmp = Scr->MenuList; tmp != NULL; tmp = tmp->next)
    {
	if (strcmp(name, tmp->name) == 0)
	    return (tmp);
    }
    return NULL;
}



static Bool belongs_to_twm_window (t, w)
    register TwmWindow *t;
    register Window w;
{
    if (!t) return False;

    if (w == t->frame || w == t->title_w || w == t->hilite_wl || w == t->hilite_wr ||
	(t->icon && (w == t->icon->w || w == t->icon->bm_w))) return True;
    
    if (t && t->titlebuttons) {
	register TBWindow *tbw;
	register int nb = Scr->TBInfo.nleft + Scr->TBInfo.nright;
	for (tbw = t->titlebuttons; nb > 0; tbw++, nb--) {
	    if (tbw->window == w) return True;
	}
    }
    return False;
}




/***********************************************************************
 *
 *  Procedure:
 *	resizeFromCenter -
 *
 ***********************************************************************
 */


extern int AddingX;
extern int AddingY;
extern int AddingW;
extern int AddingH;

void resizeFromCenter(w, tmp_win)
     Window w;
     TwmWindow *tmp_win;
{
  int lastx, lasty, width, height, bw2;
  int namelen;
#ifdef I18N
  XRectangle inc_rect;
  XRectangle logical_rect;
#endif  

  namelen = strlen (tmp_win->name);
  bw2 = tmp_win->frame_bw * 2;
  AddingW = tmp_win->attr.width + bw2 + 2 * tmp_win->frame_bw3D;
  AddingH = tmp_win->attr.height + tmp_win->title_height + bw2 + 2 * tmp_win->frame_bw3D;

#ifdef I18N
  XmbTextExtents(Scr->SizeFont.font_set, tmp_win->name, namelen,
		 &inc_rect, &logical_rect);
  width = (SIZE_HINDENT + logical_rect.width);
#else  
  width = (SIZE_HINDENT + XTextWidth (Scr->SizeFont.font,
				      tmp_win->name, namelen));
#endif
  
  height = Scr->SizeFont.height + SIZE_VINDENT * 2;
  XGetGeometry(dpy, w, &JunkRoot, &origDragX, &origDragY,
	       (unsigned int *)&DragWidth, (unsigned int *)&DragHeight, 
	       &JunkBW, &JunkDepth);

  XWarpPointer(dpy, None, w,
	       0, 0, 0, 0, DragWidth/2, DragHeight/2);   
  XQueryPointer (dpy, Scr->Root, &JunkRoot, 
		 &JunkChild, &JunkX, &JunkY,
		 &AddingX, &AddingY, &JunkMask);
/*****
  Scr->SizeStringOffset = width +
    XTextWidth(Scr->SizeFont.font, ": ", 2);
  XResizeWindow (dpy, Scr->SizeWindow, Scr->SizeStringOffset +
		 Scr->SizeStringWidth, height);
  XDrawImageString (dpy, Scr->SizeWindow, Scr->NormalGC, width,
		    SIZE_VINDENT + Scr->SizeFont.font->ascent,
		    ": ", 2);
*****/
  lastx = -10000;
  lasty = -10000;
/*****
  MoveOutline(Scr->Root,
	      origDragX - JunkBW, origDragY - JunkBW,
	      DragWidth * JunkBW, DragHeight * JunkBW,
	      tmp_win->frame_bw,
	      tmp_win->title_height + tmp_win->frame_bw3D);
*****/
  MenuStartResize(tmp_win, origDragX, origDragY, DragWidth, DragHeight);
  while (TRUE)
    {
      XMaskEvent(dpy,
		 ButtonPressMask | PointerMotionMask | ExposureMask, &Event);
      
      if (Event.type == MotionNotify) {
	/* discard any extra motion events before a release */
	while(XCheckMaskEvent(dpy,
			      ButtonMotionMask | ButtonPressMask, &Event))
	  if (Event.type == ButtonPress)
	    break;
      }
      
      if (Event.type == ButtonPress)
	{
	  MenuEndResize(tmp_win);
	  XMoveResizeWindow(dpy, w, AddingX, AddingY, AddingW, AddingH);
	  break;
	}
      
      if (Event.type != MotionNotify) {
	DispatchEvent2 ();
	continue;
      }
      
      /*
       * XXX - if we are going to do a loop, we ought to consider
       * using multiple GXxor lines so that we don't need to 
       * grab the server.
       */
      XQueryPointer(dpy, Scr->Root, &JunkRoot, &JunkChild,
		    &JunkX, &JunkY, &AddingX, &AddingY, &JunkMask);
      
      if (lastx != AddingX || lasty != AddingY)
	{
	  MenuDoResize(AddingX, AddingY, tmp_win);
	  
	  lastx = AddingX;
	  lasty = AddingY;
	}
      
    }
} 



/***********************************************************************
 *
 *  Procedure:
 *	ExecuteFunction - execute a twm root function
 *
 *  Inputs:
 *	func	- the function to execute
 *	action	- the menu action to execute 
 *	w	- the window to execute this function on
 *	tmp_win	- the twm window structure
 *	event	- the event that caused the function
 *	context - the context in which the button was pressed
 *	pulldown- flag indicating execution from pull down menu
 *
 *  Returns:
 *	TRUE if should continue with remaining actions else FALSE to abort
 *
 ***********************************************************************
 */

int
ExecuteFunction(func, action, w, tmp_win, eventp, context, pulldown)
    int func;
    char *action;
    Window w;
    TwmWindow *tmp_win;
    XEvent *eventp;
    int context;
    int pulldown;
{
    static Time last_time = 0;
    char tmp[200];
    char *ptr;
    char buff[MAX_FILE_SIZE];
    int count, fd;
    Window rootw;
    int origX, origY;
    int do_next_action = TRUE;
    int moving_icon = FALSE;
    Bool fromtitlebar = False;
    Bool from3dborder = False;
    extern int ConstrainedMoveTime;
    TwmWindow *t;

    RootFunction = 0;
    if (Cancel)
	return TRUE;			/* XXX should this be FALSE? */

    switch (func)
    {
    case F_UPICONMGR:
    case F_LEFTICONMGR:
    case F_RIGHTICONMGR:
    case F_DOWNICONMGR:
    case F_FORWICONMGR:
    case F_BACKICONMGR:
    case F_NEXTICONMGR:
    case F_PREVICONMGR:
    case F_NOP:
    case F_TITLE:
    case F_DELTASTOP:
    case F_RAISELOWER:
    case F_WARPTOSCREEN:
    case F_WARPTO:
    case F_WARPRING:
    case F_WARPTOICONMGR:
    case F_COLORMAP:
    case F_ALTKEYMAP:
    case F_ALTCONTEXT:
	break;

    default:
        XGrabPointer(dpy, Scr->Root, True,
            ButtonPressMask | ButtonReleaseMask,
            GrabModeAsync, GrabModeAsync,
            Scr->Root, Scr->WaitCursor, CurrentTime);
	break;
    }

    switch (func)
    {
#ifdef SOUNDS
    case F_TOGGLESOUND:
	toggle_sound();
	break;
    case F_REREADSOUNDS:
	reread_sounds();
	break;
#endif
    case F_NOP:
    case F_TITLE:
	break;

    case F_DELTASTOP:
	if (WindowMoved) do_next_action = FALSE;
	break;

    case F_RESTART: {
#ifdef X11R6
	extern SmcConn smcConn;
#endif
	StopAnimation ();
	XSync (dpy, 0);
	Reborder (eventp->xbutton.time);
	XSync (dpy, 0);
#ifdef VMS
	exit (1);		/* Trust CTWM.COM  /Richard Levitte */
	fprintf (stderr, "%s:  restart capabilities not yet supported\n",
		 ProgramName);
#else
#ifdef X11R6
	if (smcConn) SmcCloseConnection (smcConn, 0, NULL);
#endif /* X11R6 */
	execvp(*Argv, Argv);
#endif /* VMS */
	fprintf (stderr, "%s:  unable to restart:  %s\n", ProgramName, *Argv);
	break;
    }
    case F_UPICONMGR:
    case F_DOWNICONMGR:
    case F_LEFTICONMGR:
    case F_RIGHTICONMGR:
    case F_FORWICONMGR:
    case F_BACKICONMGR:
	MoveIconManager(func);
        break;

    case F_FORWMAPICONMGR:
    case F_BACKMAPICONMGR:
	MoveMappedIconManager(func);
	break;

    case F_NEXTICONMGR:
    case F_PREVICONMGR:
	JumpIconManager(func);
        break;

    case F_SHOWLIST:
	if (Scr->NoIconManagers) break;
	ShowIconManager ();
	break;

    case F_STARTANIMATION :
	StartAnimation ();
	break;

    case F_STOPANIMATION :
	StopAnimation ();
	break;

    case F_SPEEDUPANIMATION :
	ModifyAnimationSpeed (1);
	break;

    case F_SLOWDOWNANIMATION :
	ModifyAnimationSpeed (-1);
	break;

    case F_HIDELIST:
	if (Scr->NoIconManagers) break;
	HideIconManager ();
	break;

    case F_SHOWWORKMGR:
	if (! Scr->workSpaceManagerActive) break;
	DeIconify (Scr->workSpaceMgr.workspaceWindow.twm_win);
	RaiseWindow(Scr->workSpaceMgr.workspaceWindow.twm_win);
	break;

    case F_HIDEWORKMGR:
	if (! Scr->workSpaceManagerActive) break;
	Iconify (Scr->workSpaceMgr.workspaceWindow.twm_win, eventp->xbutton.x_root - 5,
		     eventp->xbutton.y_root - 5);
	break;

    case F_TOGGLEWORKMGR:
	if (! Scr->workSpaceManagerActive) break;
	if (Scr->workSpaceMgr.workspaceWindow.twm_win->mapped)
	    Iconify (Scr->workSpaceMgr.workspaceWindow.twm_win, eventp->xbutton.x_root - 5,
		     eventp->xbutton.y_root - 5);
	else {
	    DeIconify (Scr->workSpaceMgr.workspaceWindow.twm_win);
	    RaiseWindow(Scr->workSpaceMgr.workspaceWindow.twm_win);
	}
	break;

    case F_TOGGLESTATE :
	WMapToggleState ();
	break;

    case F_SETBUTTONSTATE :
	WMapSetButtonsState ();
	break;

    case F_SETMAPSTATE :
	WMapSetMapState ();
	break;

    case F_PIN :
	if (! ActiveMenu) break;
	if (ActiveMenu->pinned) {
	    XUnmapWindow (dpy, ActiveMenu->w);
	    ActiveMenu->mapped = UNMAPPED;
	}
	else {
	    XWindowAttributes attr;
	    MenuRoot *menu;

	    if (ActiveMenu->pmenu == NULL) {
		menu  = (MenuRoot*) malloc (sizeof (struct MenuRoot));
		*menu = *ActiveMenu;
		menu->pinned = True;
		menu->mapped = NEVER_MAPPED;
		menu->width -= 10;
		if (menu->pull) menu->width -= 16 + 10;
		MakeMenu (menu);
		ActiveMenu->pmenu = menu;
	    }
	    else menu = ActiveMenu->pmenu;
	    if (menu->mapped == MAPPED) break;
	    XGetWindowAttributes (dpy, ActiveMenu->w, &attr);
	    menu->x = attr.x;
	    menu->y = attr.y;
	    XMoveWindow (dpy, menu->w, menu->x, menu->y);
	    XMapRaised  (dpy, menu->w);
	    menu->mapped = MAPPED;
	}
	PopDownMenu();
	break;

    case F_MOVEMENU:
	break;

    case F_VANISH:
	if (DeferExecution (context, func, Scr->SelectCursor)) return TRUE;

	WMgrRemoveFromCurrentWosksace (tmp_win);
	break;

    case F_WARPHERE:
	WMgrAddToCurrentWosksaceAndWarp (action);
	break;

    case F_ADDTOWORKSPACE:
	if (DeferExecution (context, func, Scr->SelectCursor)) return TRUE;
	AddToWorkSpace (action, tmp_win);
	break;

    case F_REMOVEFROMWORKSPACE:
	if (DeferExecution (context, func, Scr->SelectCursor)) return TRUE;
	RemoveFromWorkSpace (action, tmp_win);
	break;

    case F_TOGGLEOCCUPATION:
	if (DeferExecution (context, func, Scr->SelectCursor)) return TRUE;
	ToggleOccupation (action, tmp_win);
	break;

    case F_SORTICONMGR:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	{
	    int save_sort;

	    save_sort = Scr->SortIconMgr;
	    Scr->SortIconMgr = TRUE;

	    if (context == C_ICONMGR)
		SortIconManager((IconMgr *) NULL);
	    else if (tmp_win->iconmgr)
		SortIconManager(tmp_win->iconmgrp);
	    else
		XBell(dpy, 0);

	    Scr->SortIconMgr = save_sort;
	}
	break;

    case F_ALTKEYMAP: {
	int alt, stat;

	if (! action) return TRUE;
	stat = sscanf (action, "%d", &alt);
	if (stat != 1) return TRUE;
	if ((alt < 1) || (alt > 5)) return TRUE;
	AlternateKeymap = Alt1Mask << (alt - 1);
	XGrabPointer (dpy, Scr->Root, True, ButtonPressMask | ButtonReleaseMask,
			GrabModeAsync, GrabModeAsync,
			Scr->Root, Scr->AlterCursor, CurrentTime);
	XGrabKeyboard (dpy, Scr->Root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
	return TRUE;
    }

    case F_ALTCONTEXT: {
	AlternateContext = True;
	XGrabPointer (dpy, Scr->Root, False, ButtonPressMask | ButtonReleaseMask,
			GrabModeAsync, GrabModeAsync,
			Scr->Root, Scr->AlterCursor, CurrentTime);
	XGrabKeyboard (dpy, Scr->Root, False, GrabModeAsync, GrabModeAsync, CurrentTime);
	return TRUE;
    }

    case F_LOCKSCREEN:
	LockScreen();
	break;

    case F_IDENTIFY:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	Identify(tmp_win);
	break;

    case F_VERSION:
	Identify ((TwmWindow *) NULL);
	break;

    case F_AUTORAISE:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	tmp_win->auto_raise = !tmp_win->auto_raise;
	if (tmp_win->auto_raise) ++(Scr->NumAutoRaises);
	else --(Scr->NumAutoRaises);
	break;

    case F_BEEP:
	XBell(dpy, 0);
	break;

    case F_POPUP:
	tmp_win = (TwmWindow *)action;
	if (Scr->WindowFunction.func != 0)
	{
	   ExecuteFunction(Scr->WindowFunction.func,
			   Scr->WindowFunction.item->action,
			   w, tmp_win, eventp, C_FRAME, FALSE);
	}
	else
	{
	    DeIconify(tmp_win);
	    RaiseWindow (tmp_win);
	}
	break;

    case F_WINWARP:
	tmp_win = (TwmWindow *)action;

	if (! tmp_win) break;
	if (Scr->WarpUnmapped || tmp_win->mapped) {
	    if (!tmp_win->mapped) DeIconify (tmp_win);
	    if (!Scr->NoRaiseWarp) RaiseWindow (tmp_win);
	    WarpToWindow (tmp_win);
	}
	break;

    case F_RESIZE:
	EventHandler[EnterNotify] = HandleUnknown;
	EventHandler[LeaveNotify] = HandleUnknown;
	if (DeferExecution(context, func, Scr->MoveCursor))
	    return TRUE;

	PopDownMenu();
	if (tmp_win->squeezed) {
	    XBell (dpy, 0);
	    break;
	}
	if (tmp_win->OpaqueResize) {
	    int sw, ss;

	    sw = tmp_win->frame_width * tmp_win->frame_height;
	    ss = Scr->MyDisplayWidth  * Scr->MyDisplayHeight;
	    if (sw > ((ss * Scr->OpaqueResizeThreshold) / 100))
		Scr->OpaqueResize = FALSE;
	    else
		Scr->OpaqueResize = TRUE;
	}
	else
	    Scr->OpaqueResize = FALSE;

	if (pulldown)
	    XWarpPointer(dpy, None, Scr->Root, 
		0, 0, 0, 0, eventp->xbutton.x_root, eventp->xbutton.y_root);

	if (!tmp_win->icon || (w != tmp_win->icon->w)) {	/* can't resize icons */

/*	  fromMenu = False;  ????? */
	  if ((Context == C_FRAME || Context == C_WINDOW || Context == C_TITLE)
	      && fromMenu)
	    resizeFromCenter(w, tmp_win);
	  else {
	    /*
	     * see if this is being done from the titlebar
	     */
	    fromtitlebar = 
	      belongs_to_twm_window (tmp_win, eventp->xbutton.window);
	    from3dborder = (eventp->xbutton.window == tmp_win->frame) ? True : False;
	    
	    /* Save pointer position so we can tell if it was moved or
	       not during the resize. */
	    ResizeOrigX = eventp->xbutton.x_root;
	    ResizeOrigY = eventp->xbutton.y_root;
	    
	    StartResize (eventp, tmp_win, fromtitlebar, from3dborder);
	    
	    do {
	      XMaskEvent(dpy,
			   ButtonPressMask | ButtonReleaseMask |
			   EnterWindowMask | LeaveWindowMask |
			   ButtonMotionMask | VisibilityChangeMask | ExposureMask, &Event);
		
		if (fromtitlebar && Event.type == ButtonPress) {
		  fromtitlebar = False;
		    continue;
		  }
		
	    	if (Event.type == MotionNotify) {
		  /* discard any extra motion events before a release */
		  while
		    (XCheckMaskEvent
		     (dpy, ButtonMotionMask | ButtonReleaseMask, &Event))
		      if (Event.type == ButtonRelease)
			break;
		}
	      
	      if (!DispatchEvent2 ()) continue;
	      
	    } while (!(Event.type == ButtonRelease || Cancel));
	    return TRUE;
	  }
	} 
	break;


    case F_ZOOM:
    case F_HORIZOOM:
    case F_FULLZOOM:
    case F_LEFTZOOM:
    case F_RIGHTZOOM:
    case F_TOPZOOM:
    case F_BOTTOMZOOM:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;
	if (tmp_win->squeezed) {
	    XBell(dpy, 0);
	    break;
	}
	fullzoom(tmp_win, func);
	break;

    case F_PACK:
	if (DeferExecution(context, func, Scr->SelectCursor)) return TRUE;
	if (tmp_win->squeezed) { XBell(dpy, 0); break; }
	packwindow (tmp_win, action);
	break;

    case F_FILL:
	if (DeferExecution(context, func, Scr->SelectCursor)) return TRUE;
	if (tmp_win->squeezed) { XBell(dpy, 0); break; }
	fillwindow (tmp_win, action);
	break;

    case F_SAVEGEOMETRY:
	if (DeferExecution(context, func, Scr->SelectCursor)) return TRUE;
	savegeometry (tmp_win);
	break;

    case F_RESTOREGEOMETRY:
	if (DeferExecution(context, func, Scr->SelectCursor)) return TRUE;
	restoregeometry (tmp_win);
	break;

    case F_HYPERMOVE: {
	Bool	cont = True;
	Window	root = RootWindow (dpy, Scr->screen);
	Window	croot;
	Cursor	cursor;
	CaptiveCTWM cctwm0, cctwm;

	cctwm0 = GetCaptiveCTWMUnderPointer ();
	cursor = MakeStringCursor (cctwm0.name);
	free (cctwm0.name);
	if (DeferExecution (context, func, Scr->MoveCursor)) return TRUE;

	XGrabPointer (dpy, root, True,
		ButtonPressMask | ButtonMotionMask | ButtonReleaseMask,
		GrabModeAsync, GrabModeAsync, root, cursor, CurrentTime);
	while (cont) {
	    Window child;

	    XMaskEvent (dpy, ButtonPressMask | ButtonMotionMask |
				ButtonReleaseMask, &Event);
	    switch (Event.xany.type) {
		case ButtonPress :
		    cont = False;
		    break;

		case ButtonRelease :
		    cont = False;
		    cctwm = GetCaptiveCTWMUnderPointer ();
		    free (cctwm.name);
		    if (cctwm.root == Scr->Root) break;
		    SetNoRedirect (tmp_win->w);
		    XUngrabButton (dpy, AnyButton, AnyModifier, tmp_win->w);
		    XReparentWindow (dpy, tmp_win->w, cctwm.root, 0, 0);
		    XMapWindow (dpy, tmp_win->w);
		    break;
	
		case MotionNotify :
		    cctwm = GetCaptiveCTWMUnderPointer ();
		    if (cctwm.root != cctwm0.root) {
			XFreeCursor (dpy, cursor);
			cursor = MakeStringCursor (cctwm.name);
			cctwm0 = cctwm;
			XChangeActivePointerGrab (dpy,
				ButtonPressMask | ButtonMotionMask | ButtonReleaseMask,
				cursor, CurrentTime);
		    }
		    free (cctwm.name);
		    break;
	    }
	}
	ButtonPressed = -1;
	XUngrabPointer (dpy, CurrentTime);
	XFreeCursor (dpy, cursor);
	break;
    }
    case F_MOVE:
    case F_FORCEMOVE:
    case F_MOVEPACK:
    case F_MOVEPUSH:
	if (DeferExecution(context, func, Scr->MoveCursor))
	    return TRUE;

	PopDownMenu();
	if (tmp_win->OpaqueMove) {
	    int sw, ss;
	    float sf;

	    sw = tmp_win->frame_width * tmp_win->frame_height;
	    ss = Scr->MyDisplayWidth  * Scr->MyDisplayHeight;
	    sf = Scr->OpaqueMoveThreshold / 100.0;
	    if (sw > (ss * sf))
		Scr->OpaqueMove = FALSE;
	    else
		Scr->OpaqueMove = TRUE;
	}
	else
	    Scr->OpaqueMove = FALSE;

	rootw = eventp->xbutton.root;
	MoveFunction = func;

	if (pulldown)
	    XWarpPointer(dpy, None, Scr->Root, 
		0, 0, 0, 0, eventp->xbutton.x_root, eventp->xbutton.y_root);

	EventHandler[EnterNotify] = HandleUnknown;
	EventHandler[LeaveNotify] = HandleUnknown;

	if (!Scr->NoGrabServer || !Scr->OpaqueMove) {
	    XGrabServer(dpy);
	}

	Scr->SizeStringOffset = SIZE_HINDENT;
	XResizeWindow (dpy, Scr->SizeWindow,
		   Scr->SizeStringWidth + SIZE_HINDENT * 2, 
		   Scr->SizeFont.height + SIZE_VINDENT * 2);
	XMapRaised (dpy, Scr->SizeWindow);

	XGrabPointer(dpy, eventp->xbutton.root, True,
	    ButtonPressMask | ButtonReleaseMask |
	    ButtonMotionMask | PointerMotionMask, /* PointerMotionHintMask */
	    GrabModeAsync, GrabModeAsync,
	    Scr->Root, Scr->MoveCursor, CurrentTime);

	if (context == C_ICON && tmp_win->icon && tmp_win->icon->w)
	{
	    w = tmp_win->icon->w;
	    DragX = eventp->xbutton.x;
	    DragY = eventp->xbutton.y;
	    moving_icon = TRUE;
	    if (tmp_win->OpaqueMove) Scr->OpaqueMove = TRUE;
	}

	else if (! tmp_win->icon || w != tmp_win->icon->w)
	{
	    XTranslateCoordinates(dpy, w, tmp_win->frame,
		eventp->xbutton.x, 
		eventp->xbutton.y, 
		&DragX, &DragY, &JunkChild);

	    w = tmp_win->frame;
	}

	DragWindow = None;

	XGetGeometry(dpy, w, &JunkRoot, &origDragX, &origDragY,
	    (unsigned int *)&DragWidth, (unsigned int *)&DragHeight, &DragBW,
	    &JunkDepth);

	JunkBW = DragBW;
	origX = eventp->xbutton.x_root;
	origY = eventp->xbutton.y_root;
	CurrentDragX = origDragX;
	CurrentDragY = origDragY;

	/*
	 * only do the constrained move if timer is set; need to check it
	 * in case of stupid or wicked fast servers
	 */
	if (ConstrainedMoveTime && 
	    (eventp->xbutton.time - last_time) < ConstrainedMoveTime)
	{
	    int width, height;

	    ConstMove = TRUE;
	    ConstMoveDir = MOVE_NONE;
	    ConstMoveX = eventp->xbutton.x_root - DragX - JunkBW;
	    ConstMoveY = eventp->xbutton.y_root - DragY - JunkBW;
	    width = DragWidth + 2 * JunkBW;
	    height = DragHeight + 2 * JunkBW;
	    ConstMoveXL = ConstMoveX + width/3;
	    ConstMoveXR = ConstMoveX + 2*(width/3);
	    ConstMoveYT = ConstMoveY + height/3;
	    ConstMoveYB = ConstMoveY + 2*(height/3);

	    XWarpPointer(dpy, None, w,
		0, 0, 0, 0, DragWidth/2, DragHeight/2);

	    XQueryPointer(dpy, w, &JunkRoot, &JunkChild,
		&JunkX, &JunkY, &DragX, &DragY, &JunkMask);
	}
	last_time = eventp->xbutton.time;

	if (!Scr->OpaqueMove)
	{
	    InstallRootColormap();
	    if (!Scr->MoveDelta)
	    {
		/*
		 * Draw initial outline.  This was previously done the
		 * first time though the outer loop by dropping out of
		 * the XCheckMaskEvent inner loop down to one of the
		 * MoveOutline's below.
		 */
		MoveOutline(rootw,
		    origDragX - JunkBW, origDragY - JunkBW,
		    DragWidth + 2 * JunkBW, DragHeight + 2 * JunkBW,
		    tmp_win->frame_bw,
		    moving_icon ? 0 : tmp_win->title_height + tmp_win->frame_bw3D);
		/*
		 * This next line causes HandleReleaseNotify to call
		 * XRaiseWindow().  This is solely to preserve the
		 * previous behaviour that raises a window being moved
		 * on button release even if you never actually moved
		 * any distance (unless you move less than MoveDelta or
		 * NoRaiseMove is set or OpaqueMove is set).
		 */
		DragWindow = w;
	    }
	}

	/*
	 * see if this is being done from the titlebar
	 */
	fromtitlebar = belongs_to_twm_window (tmp_win, eventp->xbutton.window);

	if (menuFromFrameOrWindowOrTitlebar) {
	  /* warp the pointer to the middle of the window */
	  XWarpPointer(dpy, None, Scr->Root, 0, 0, 0, 0, 
		       origDragX + DragWidth / 2, 
		       origDragY + DragHeight / 2);
	  XFlush(dpy);
	}
	
	DisplayPosition (tmp_win, CurrentDragX, CurrentDragY);
	while (TRUE)
	{
	    long releaseEvent = menuFromFrameOrWindowOrTitlebar ? 
	                          ButtonPress : ButtonRelease;
	    long movementMask = menuFromFrameOrWindowOrTitlebar ?
	                          PointerMotionMask : ButtonMotionMask;

	    /* block until there is an interesting event */
	    XMaskEvent(dpy, ButtonPressMask | ButtonReleaseMask |
				    EnterWindowMask | LeaveWindowMask |
				    ExposureMask | movementMask |
				    VisibilityChangeMask, &Event);

	    /* throw away enter and leave events until release */
	    if (Event.xany.type == EnterNotify ||
		Event.xany.type == LeaveNotify) continue; 

	    if (Event.type == MotionNotify) {
		/* discard any extra motion events before a logical release */
		while(XCheckMaskEvent(dpy,
		    movementMask | releaseEvent, &Event))
		    if (Event.type == releaseEvent)
			break;
	    }

	    /* test to see if we have a second button press to abort move */
	    if (!menuFromFrameOrWindowOrTitlebar)
	      if (Event.type == ButtonPress && DragWindow != None) {
		Cursor cur;
		if (Scr->OpaqueMove)
		  XMoveWindow (dpy, DragWindow, origDragX, origDragY);
		else
		  MoveOutline(Scr->Root, 0, 0, 0, 0, 0, 0);
		DragWindow = None;

		XUnmapWindow (dpy, Scr->SizeWindow);
		cur = LeftButt;
		if (Event.xbutton.button == Button2)
		    cur = MiddleButt;
		else if (Event.xbutton.button >= Button3)
		    cur = RightButt;

		XGrabPointer (dpy, Scr->Root, True,
		    ButtonReleaseMask | ButtonPressMask,
		    GrabModeAsync, GrabModeAsync,
		    Scr->Root, cur, CurrentTime);
		return TRUE;
	      }

	    if (fromtitlebar && Event.type == ButtonPress) {
		fromtitlebar = False;
		CurrentDragX = origX = Event.xbutton.x_root;
		CurrentDragY = origY = Event.xbutton.y_root;
		XTranslateCoordinates (dpy, rootw, tmp_win->frame,
				       origX, origY,
				       &DragX, &DragY, &JunkChild);
		continue;
	    }

	    if (!DispatchEvent2 ()) continue;

	    if (Cancel)
	    {
		WindowMoved = FALSE;
		if (!Scr->OpaqueMove)
		    UninstallRootColormap();
		    return TRUE;	/* XXX should this be FALSE? */
	    }
	    if (Event.type == releaseEvent)
	    {
		MoveOutline(rootw, 0, 0, 0, 0, 0, 0);
		if (moving_icon &&
		    ((CurrentDragX != origDragX ||
		      CurrentDragY != origDragY)))
		    tmp_win->icon_moved = TRUE;
		if (!Scr->OpaqueMove && menuFromFrameOrWindowOrTitlebar) {
		    int xl = Event.xbutton.x_root - (DragWidth  / 2),
		        yt = Event.xbutton.y_root - (DragHeight / 2);
		    if (!moving_icon &&
		       (MoveFunction == F_MOVEPACK || MoveFunction == F_MOVEPUSH))
			TryToPack (tmp_win, &xl, &yt);
			XMoveWindow(dpy, DragWindow, xl, yt);
		}
		if (menuFromFrameOrWindowOrTitlebar) DragWindow = None;
		break;
	    }

	    /* something left to do only if the pointer moved */
	    if (Event.type != MotionNotify)
		continue;

	    XQueryPointer(dpy, rootw, &(eventp->xmotion.root), &JunkChild,
		&(eventp->xmotion.x_root), &(eventp->xmotion.y_root),
		&JunkX, &JunkY, &JunkMask);

	    if (captive) FixRootEvent (eventp);

	    if (DragWindow == None &&
		abs(eventp->xmotion.x_root - origX) < Scr->MoveDelta &&
	        abs(eventp->xmotion.y_root - origY) < Scr->MoveDelta)
		continue;

	    DragWindow = w;

	    if (!Scr->NoRaiseMove && Scr->OpaqueMove && !WindowMoved)
	      RaiseFrame(DragWindow);

	    WindowMoved = TRUE;

	    if (ConstMove)
	    {
		switch (ConstMoveDir)
		{
		    case MOVE_NONE:
			if (eventp->xmotion.x_root < ConstMoveXL ||
			    eventp->xmotion.x_root > ConstMoveXR)
			    ConstMoveDir = MOVE_HORIZ;

			if (eventp->xmotion.y_root < ConstMoveYT ||
			    eventp->xmotion.y_root > ConstMoveYB)
			    ConstMoveDir = MOVE_VERT;

			XQueryPointer(dpy, DragWindow, &JunkRoot, &JunkChild,
			    &JunkX, &JunkY, &DragX, &DragY, &JunkMask);
			break;

		    case MOVE_VERT:
			ConstMoveY = eventp->xmotion.y_root - DragY - JunkBW;
			break;

		    case MOVE_HORIZ:
			ConstMoveX= eventp->xmotion.x_root - DragX - JunkBW;
			break;
		}

		if (ConstMoveDir != MOVE_NONE)
		{
		    int xl, yt, xr, yb, w, h;

		    xl = ConstMoveX;
		    yt = ConstMoveY;
		    w = DragWidth + 2 * JunkBW;
		    h = DragHeight + 2 * JunkBW;

		    if (Scr->DontMoveOff && MoveFunction != F_FORCEMOVE)
		        TryToGrid (tmp_win, &xl, &yt);
		    if (!moving_icon && MoveFunction == F_MOVEPUSH && Scr->OpaqueMove)
			TryToPush (tmp_win, xl, yt, 0);

		    if (!moving_icon &&
			(MoveFunction == F_MOVEPACK || MoveFunction == F_MOVEPUSH))
			TryToPack (tmp_win, &xl, &yt);

		    if (Scr->DontMoveOff && MoveFunction != F_FORCEMOVE)
		    {
			xr = xl + w;
			yb = yt + h;

			if ((xl < 0) && ((Scr->MoveOffResistance < 0) 
					 || (xl > -Scr->MoveOffResistance)))
			    xl = 0;
			if ((xr > Scr->MyDisplayWidth) 
			    && ((Scr->MoveOffResistance < 0) 
				|| (xr < Scr->MyDisplayWidth + Scr->MoveOffResistance)))
			    xl = Scr->MyDisplayWidth - w;

			if ((yt < 0) && ((Scr->MoveOffResistance < 0) 
					 || (yt > -Scr->MoveOffResistance)))
			    yt = 0;
			if ((yb > Scr->MyDisplayHeight)
			    && ((Scr->MoveOffResistance < 0) 
				|| (yb < Scr->MyDisplayHeight + Scr->MoveOffResistance)))
			    yt = Scr->MyDisplayHeight - h;
		    }
		    CurrentDragX = xl;
		    CurrentDragY = yt;
		    if (Scr->OpaqueMove) {
			if (MoveFunction == F_MOVEPUSH && !moving_icon)
			    SetupWindow (tmp_win, xl, yt,
				tmp_win->frame_width, tmp_win->frame_height, -1);
			else 
			    XMoveWindow(dpy, DragWindow, xl, yt);
			WMapSetupWindow (tmp_win, xl, yt, -1, -1);
		    }
		    else
			MoveOutline(eventp->xmotion.root, xl, yt, w, h,
			    tmp_win->frame_bw, 
			    moving_icon ? 0 : tmp_win->title_height + tmp_win->frame_bw3D);
		}
	    }
	    else if (DragWindow != None)
	    {
		int xl, yt, xr, yb, w, h;
		if (!menuFromFrameOrWindowOrTitlebar) {
		  xl = eventp->xmotion.x_root - DragX - JunkBW;
		  yt = eventp->xmotion.y_root - DragY - JunkBW;
		}
		else {
		  xl = eventp->xmotion.x_root - (DragWidth / 2);
		  yt = eventp->xmotion.y_root - (DragHeight / 2);
		}		  
		w = DragWidth + 2 * JunkBW;
		h = DragHeight + 2 * JunkBW;

		if (Scr->DontMoveOff && MoveFunction != F_FORCEMOVE)
		    TryToGrid (tmp_win, &xl, &yt);
		if (!moving_icon && MoveFunction == F_MOVEPUSH && Scr->OpaqueMove)
		    TryToPush (tmp_win, xl, yt, 0);

		if (!moving_icon &&
		    (MoveFunction == F_MOVEPACK || MoveFunction == F_MOVEPUSH))
		    TryToPack (tmp_win, &xl, &yt);

		if (Scr->DontMoveOff && MoveFunction != F_FORCEMOVE)
		{
		    xr = xl + w;
		    yb = yt + h;

		    if ((xl < 0) && ((Scr->MoveOffResistance < 0) 
				     || (xl > -Scr->MoveOffResistance)))
			xl = 0;
		    if ((xr > Scr->MyDisplayWidth) 
			&& ((Scr->MoveOffResistance < 0)
			    || (xr < Scr->MyDisplayWidth + Scr->MoveOffResistance)))
			xl = Scr->MyDisplayWidth - w;

		    if ((yt < 0) && ((Scr->MoveOffResistance < 0)
				     || (yt > -Scr->MoveOffResistance)))
			yt = 0;
		    if ((yb > Scr->MyDisplayHeight)
			&& ((Scr->MoveOffResistance < 0)
			    || (yb < Scr->MyDisplayHeight + Scr->MoveOffResistance)))
			yt = Scr->MyDisplayHeight - h;
		}

		CurrentDragX = xl;
		CurrentDragY = yt;
		if (Scr->OpaqueMove) {
		    if (MoveFunction == F_MOVEPUSH && !moving_icon)
		        SetupWindow (tmp_win, xl, yt,
				tmp_win->frame_width, tmp_win->frame_height, -1);
		    else 
			XMoveWindow(dpy, DragWindow, xl, yt);
		    if (! moving_icon) WMapSetupWindow (tmp_win, xl, yt, -1, -1);
		}
		else
		    MoveOutline(eventp->xmotion.root, xl, yt, w, h,
			tmp_win->frame_bw,
			moving_icon ? 0 : tmp_win->title_height + tmp_win->frame_bw3D);
	    }
	    DisplayPosition (tmp_win, CurrentDragX, CurrentDragY);
	}
	XUnmapWindow (dpy, Scr->SizeWindow);

	if (!Scr->OpaqueMove && DragWindow == None)
	    UninstallRootColormap();
        break;

    case F_FUNCTION:
	{
	    MenuRoot *mroot;
	    MenuItem *mitem;

	    if ((mroot = FindMenuRoot(action)) == NULL)
	    {
		fprintf (stderr, "%s: couldn't find function \"%s\"\n", 
			 ProgramName, action);
		return TRUE;
	    }

	    if (NeedToDefer(mroot) && DeferExecution(context, func, Scr->SelectCursor))
		return TRUE;
	    else
	    {
		for (mitem = mroot->first; mitem != NULL; mitem = mitem->next)
		{
		    if (!ExecuteFunction (mitem->func, mitem->action, w,
					  tmp_win, eventp, context, pulldown))
		      break;
		}
	    }
	}
	break;

    case F_DEICONIFY:
    case F_ICONIFY:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	if (tmp_win->isicon)
	{
	    DeIconify(tmp_win);
	}
        else if (func == F_ICONIFY)
	{
	    Iconify (tmp_win, eventp->xbutton.x_root - 5,
		     eventp->xbutton.y_root - 5);
	}
	break;

    case F_SQUEEZE:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	Squeeze (tmp_win);
	break;

    case F_RAISELOWER:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	if (!WindowMoved) {
	    if (tmp_win->icon && w == tmp_win->icon->w) {
		RaiseLowerFrame(w, ONTOP_DEFAULT);
	    } else {
		RaiseLower(tmp_win);
		WMapRaiseLower (tmp_win);
	    }
	}
	break;
	
    case F_RAISE:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	/* check to make sure raise is not from the WindowFunction */
	if (tmp_win->icon && (w == tmp_win->icon->w) && Context != C_ROOT) 
	    XRaiseWindow(dpy, tmp_win->icon->w);
	else {
	    RaiseWindow (tmp_win);
	    WMapRaise   (tmp_win);
	}
	break;

    case F_LOWER:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	if (tmp_win->icon && (w == tmp_win->icon->w))
	    XLowerWindow(dpy, tmp_win->icon->w);
	else {
	    LowerWindow(tmp_win);
	    WMapLower (tmp_win);
	}
	break;

    case F_RAISEICONS:
	for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	    if (t->icon && t->icon->w) {
		XRaiseWindow (dpy, t->icon->w);	
	    }
	}
	break;

    case F_FOCUS:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	if (tmp_win->isicon == FALSE)
	{
	    if (!Scr->FocusRoot && Scr->Focus == tmp_win)
	    {
		FocusOnRoot();
	    }
	    else
	    {
		InstallWindowColormaps (0, tmp_win);
		SetFocus (tmp_win, eventp->xbutton.time);
		Scr->FocusRoot = FALSE;
	    }
	}
	break;

    case F_DESTROY:
	if (DeferExecution(context, func, Scr->DestroyCursor))
	    return TRUE;

	if (tmp_win->iconmgr ||
	    tmp_win == Scr->workSpaceMgr.workspaceWindow.twm_win ||
	    tmp_win == Scr->workSpaceMgr.occupyWindow.twm_win) {
	    XBell(dpy, 0);
	    break;
	}
	XKillClient(dpy, tmp_win->w);
	if (ButtonPressed != -1) {
	    XEvent kev;

	    XMaskEvent (dpy, ButtonReleaseMask, &kev);
	    if (kev.xbutton.window == tmp_win->w) kev.xbutton.window = Scr->Root;
	    XPutBackEvent (dpy, &kev);
	}
	break;

    case F_DELETE:
	if (DeferExecution(context, func, Scr->DestroyCursor))
	    return TRUE;

	if (tmp_win->iconmgr) {		/* don't send ourself a message */
	    HideIconManager ();
	    break;
	}
	if (tmp_win == Scr->workSpaceMgr.workspaceWindow.twm_win ||
	    tmp_win == Scr->workSpaceMgr.occupyWindow.twm_win) {
	    XBell (dpy, 0);
	    break;
	}
	if (tmp_win->protocols & DoesWmDeleteWindow) {
	    SendDeleteWindowMessage (tmp_win, LastTimestamp());
	    if (ButtonPressed != -1) {
		XEvent kev;

		XMaskEvent (dpy, ButtonReleaseMask, &kev);
		if (kev.xbutton.window == tmp_win->w) kev.xbutton.window = Scr->Root;
		XPutBackEvent (dpy, &kev);
	    }
	    break;
	}
	XBell (dpy, 0);
	break;

    case F_DELETEORDESTROY:
	if (DeferExecution(context, func, Scr->DestroyCursor)) return TRUE;

	if (tmp_win->iconmgr) {
	    HideIconManager ();
	    break;
	}
	if (tmp_win == Scr->workSpaceMgr.workspaceWindow.twm_win ||
	    tmp_win == Scr->workSpaceMgr.occupyWindow.twm_win) {
	    XBell (dpy, 0);
	    break;
	}
	if (tmp_win->protocols & DoesWmDeleteWindow) {
	    SendDeleteWindowMessage (tmp_win, LastTimestamp());
	} else {
	    XKillClient(dpy, tmp_win->w);
	}
	if (ButtonPressed != -1) {
	    XEvent kev;

	    XMaskEvent (dpy, ButtonReleaseMask, &kev);
	    if (kev.xbutton.window == tmp_win->w) kev.xbutton.window = Scr->Root;
	    XPutBackEvent (dpy, &kev);
	}
	break;

    case F_SAVEYOURSELF:
	if (DeferExecution (context, func, Scr->SelectCursor))
	  return TRUE;

	if (tmp_win->protocols & DoesWmSaveYourself)
	  SendSaveYourselfMessage (tmp_win, LastTimestamp());
	else
	  XBell (dpy, 0);
	break;

    case F_CIRCLEUP:
	XCirculateSubwindowsUp(dpy, Scr->Root);
	break;

    case F_CIRCLEDOWN:
	XCirculateSubwindowsDown(dpy, Scr->Root);
	break;

    case F_EXEC:
	PopDownMenu();
	if (!Scr->NoGrabServer) {
	    XUngrabServer (dpy);
	    XSync (dpy, 0);
	}
	XUngrabPointer (dpy, CurrentTime);
	XSync (dpy, 0);
	Execute(action);
	break;

    case F_UNFOCUS:
	FocusOnRoot();
	break;

    case F_CUT:
	strcpy(tmp, action);
	strcat(tmp, "\n");
	XStoreBytes(dpy, tmp, strlen(tmp));
	break;

    case F_CUTFILE:
	ptr = XFetchBytes(dpy, &count);
	if (ptr) {
	    if (sscanf (ptr, "%s", tmp) == 1) {
		XFree (ptr);
		ptr = ExpandFilename(tmp);
		if (ptr) {
#ifdef VMS
		    fd = open (ptr, O_RDONLY, 0);
#else
		    fd = open (ptr, 0);
#endif
		    if (fd >= 0) {
			count = read (fd, buff, MAX_FILE_SIZE - 1);
			if (count > 0) XStoreBytes (dpy, buff, count);
			close(fd);
		    } else {
			fprintf (stderr, 
				 "%s:  unable to open cut file \"%s\"\n", 
				 ProgramName, tmp);
		    }
		    if (ptr != tmp) free (ptr);
		} 
	    } else {
		XFree(ptr);
	    }
	} else {
	    fprintf(stderr, "%s:  cut buffer is empty\n", ProgramName);
	}
	break;

    case F_WARPTOSCREEN:
	{
	    if (strcmp (action, WARPSCREEN_NEXT) == 0) {
		WarpToScreen (Scr->screen + 1, 1);
	    } else if (strcmp (action, WARPSCREEN_PREV) == 0) {
		WarpToScreen (Scr->screen - 1, -1);
	    } else if (strcmp (action, WARPSCREEN_BACK) == 0) {
		WarpToScreen (PreviousScreen, 0);
	    } else {
		WarpToScreen (atoi (action), 0);
	    }
	}
	break;

    case F_COLORMAP:
	{
	    if (strcmp (action, COLORMAP_NEXT) == 0) {
		BumpWindowColormap (tmp_win, 1);
	    } else if (strcmp (action, COLORMAP_PREV) == 0) {
		BumpWindowColormap (tmp_win, -1);
	    } else {
		BumpWindowColormap (tmp_win, 0);
	    }
	}
	break;

    case F_WARPTO:
	{
	    register TwmWindow *t;
	    int len;

	    len = strlen(action);

	    for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
		if (!strncmp(action, t->full_name, len)) break;
		if (match (action, t->full_name)) break;
	    }
	    if (!t) {
		for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
		    if (!strncmp(action, t->class.res_name, len)) break;
		    if (match (action, t->class.res_name)) break;
		}
		if (!t) {
		    for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
			if (!strncmp(action, t->class.res_class, len)) break;
			if (match (action, t->class.res_class)) break;
		    }
		}
	    }

	    if (t) {
		if (Scr->WarpUnmapped || t->mapped) {
		    if (!t->mapped) DeIconify (t);
		    if (!Scr->NoRaiseWarp) RaiseWindow (t);
		    WarpToWindow (t);
		}
	    } else {
		XBell (dpy, 0);
	    }
	}
	break;

    case F_WARPTOICONMGR:
	{
	    TwmWindow *t;
	    int len;
	    Window raisewin = None, iconwin = None;

	    len = strlen(action);
	    if (len == 0) {
		if (tmp_win && tmp_win->list) {
		    raisewin = tmp_win->list->iconmgr->twm_win->frame;
		    iconwin = tmp_win->list->icon;
		} else if (Scr->iconmgr->active) {
		    raisewin = Scr->iconmgr->twm_win->frame;
		    iconwin = Scr->iconmgr->active->w;
		}
	    } else {
		for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
		    if (strncmp (action, t->icon_name, len) == 0) {
			if (t->list && t->list->iconmgr->twm_win->mapped) {
			    raisewin = t->list->iconmgr->twm_win->frame;
			    iconwin = t->list->icon;
			    break;
			}
		    }
		}
	    }

	    if (raisewin) {
		RaiseFrame(raisewin);
		XWarpPointer (dpy, None, iconwin, 0,0,0,0, 5, 5);
	    } else {
		XBell (dpy, 0);
	    }
	}
	break;
	
    case F_WARPRING:
	switch (action[0]) {
	  case 'n':
	    WarpAlongRing (&eventp->xbutton, True);
	    break;
	  case 'p':
	    WarpAlongRing (&eventp->xbutton, False);
	    break;
	  default:
	    XBell (dpy, 0);
	    break;
	}
	break;

    case F_FILE:
	action = ExpandFilename(action);
#ifdef VMS
	fd = open (action, O_RDONLY, 0);
#else
	fd = open(action, 0);
#endif
	if (fd >= 0)
	{
	    count = read(fd, buff, MAX_FILE_SIZE - 1);
	    if (count > 0)
		XStoreBytes(dpy, buff, count);

	    close(fd);
	}
	else
	{
	    fprintf (stderr, "%s:  unable to open file \"%s\"\n", 
		     ProgramName, action);
	}
	break;

    case F_REFRESH:
	{
	    XSetWindowAttributes attributes;
	    unsigned long valuemask;

	    valuemask = (CWBackPixel | CWBackingStore | CWSaveUnder);
	    attributes.background_pixel = Scr->Black;
	    attributes.backing_store = NotUseful;
	    attributes.save_under = False;
	    w = XCreateWindow (dpy, Scr->Root, 0, 0,
			       (unsigned int) Scr->MyDisplayWidth,
			       (unsigned int) Scr->MyDisplayHeight,
			       (unsigned int) 0,
			       CopyFromParent, (unsigned int) CopyFromParent,
			       (Visual *) CopyFromParent, valuemask,
			       &attributes);
	    XMapWindow (dpy, w);
	    XDestroyWindow (dpy, w);
	    XFlush (dpy);
	}
	break;

    case F_OCCUPY:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;
	Occupy (tmp_win);
	break;

    case F_OCCUPYALL:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;
	OccupyAll (tmp_win);
	break;

    case F_GOTOWORKSPACE:
	GotoWorkSpaceByName (action);
	break;

    case F_PREVWORKSPACE:
	GotoPrevWorkSpace ();
	break;

    case F_NEXTWORKSPACE:
	GotoNextWorkSpace ();
	break;

    case F_RIGHTWORKSPACE:
	GotoRightWorkSpace ();
	break;

    case F_LEFTWORKSPACE:
	GotoLeftWorkSpace ();
	break;

    case F_UPWORKSPACE:
	GotoUpWorkSpace ();
	break;

    case F_DOWNWORKSPACE:
	GotoDownWorkSpace ();
	break;

    case F_MENU:
	if (action && ! strncmp (action, "WGOTO : ", 8)) {
	    GotoWorkSpaceByName (action + 8);
	}
	else {
	    MenuItem *item;

	    item = ActiveItem;
	    while (item && item->sub) {
		if (!item->sub->defaultitem) break;
		if (item->sub->defaultitem->func != F_MENU) break;
		item = item->sub->defaultitem;
	    }
	    if (item && item->sub && item->sub->defaultitem) {
		ExecuteFunction (item->sub->defaultitem->func,
				 item->sub->defaultitem->action,
				 w, tmp_win, eventp, context, pulldown);
	    }
	}
	break;

    case F_WINREFRESH:
	if (DeferExecution(context, func, Scr->SelectCursor))
	    return TRUE;

	if (context == C_ICON && tmp_win->icon && tmp_win->icon->w)
	    w = XCreateSimpleWindow(dpy, tmp_win->icon->w,
		0, 0, 9999, 9999, 0, Scr->Black, Scr->Black);
	else
	    w = XCreateSimpleWindow(dpy, tmp_win->frame,
		0, 0, 9999, 9999, 0, Scr->Black, Scr->Black);

	XMapWindow(dpy, w);
	XDestroyWindow(dpy, w);
	XFlush(dpy);
	break;

    case F_ADOPTWINDOW:
	adoptWindow ();
	break;

    case F_TRACE:
	DebugTrace (action);
	break;
	
    case F_QUIT:
	Done();
	break;
    }

    if (ButtonPressed == -1) XUngrabPointer(dpy, CurrentTime);
    return do_next_action;
}



/***********************************************************************
 *
 *  Procedure:
 *	DeferExecution - defer the execution of a function to the
 *	    next button press if the context is C_ROOT
 *
 *  Inputs:
 *	context	- the context in which the mouse button was pressed
 *	func	- the function to defer
 *	cursor	- the cursor to display while waiting
 *
 ***********************************************************************
 */

int
DeferExecution(context, func, cursor)
int context, func;
Cursor cursor;
{
    if ((context == C_ROOT) || (context == C_ALTERNATE))
    {
	LastCursor = cursor;
	if (func == F_ADOPTWINDOW)
	    XGrabPointer(dpy, Scr->Root, True,
		ButtonPressMask | ButtonReleaseMask,
		GrabModeAsync, GrabModeAsync,
		None, cursor, CurrentTime);
	else
	    XGrabPointer(dpy, Scr->Root, True,
		ButtonPressMask | ButtonReleaseMask,
		GrabModeAsync, GrabModeAsync,
		Scr->Root, cursor, CurrentTime);
	RootFunction = func;

	return (TRUE);
    }
    
    return (FALSE);
}



/***********************************************************************
 *
 *  Procedure:
 *	ReGrab - regrab the pointer with the LastCursor;
 *
 ***********************************************************************
 */

ReGrab()
{
    XGrabPointer(dpy, Scr->Root, True,
	ButtonPressMask | ButtonReleaseMask,
	GrabModeAsync, GrabModeAsync,
	Scr->Root, LastCursor, CurrentTime);
}



/***********************************************************************
 *
 *  Procedure:
 *	NeedToDefer - checks each function in the list to see if it
 *		is one that needs to be defered.
 *
 *  Inputs:
 *	root	- the menu root to check
 *
 ***********************************************************************
 */

NeedToDefer(root)
MenuRoot *root;
{
    MenuItem *mitem;

    for (mitem = root->first; mitem != NULL; mitem = mitem->next)
    {
	switch (mitem->func)
	{
	case F_IDENTIFY:
	case F_RESIZE:
	case F_MOVE:
	case F_FORCEMOVE:
	case F_DEICONIFY:
	case F_ICONIFY:
	case F_RAISELOWER:
	case F_RAISE:
	case F_LOWER:
	case F_FOCUS:
	case F_DESTROY:
	case F_WINREFRESH:
	case F_ZOOM:
	case F_FULLZOOM:
	case F_HORIZOOM:
        case F_RIGHTZOOM:
        case F_LEFTZOOM:
        case F_TOPZOOM:
        case F_BOTTOMZOOM:
        case F_SQUEEZE:
	case F_AUTORAISE:
	    return TRUE;
	}
    }
    return FALSE;
}



/***********************************************************************
 *
 *  Procedure:
 *	Execute - execute the string by /bin/sh
 *
 *  Inputs:
 *	s	- the string containing the command
 *
 ***********************************************************************
 */

void
Execute(s)
    char *s;
{
#ifdef VMS
    createProcess(s);
#else
    static char buf[256];
    char *ds = DisplayString (dpy);
    char *colon, *dot1;
    char oldDisplay[256];
    char *doisplay;
    int restorevar = 0;
    Bool replace;
    char *subs, *name, *news;
    int len;

    oldDisplay[0] = '\0';
    doisplay=getenv("DISPLAY");
    if (doisplay)
	strcpy (oldDisplay, doisplay);

    /*
     * Build a display string using the current screen number, so that
     * X programs which get fired up from a menu come up on the screen
     * that they were invoked from, unless specifically overridden on
     * their command line.
     */
    colon = strrchr (ds, ':');
    if (colon) {			/* if host[:]:dpy */
	strcpy (buf, "DISPLAY=");
	strcat (buf, ds);
	colon = buf + 8 + (colon - ds);	/* use version in buf */
	dot1 = strchr (colon, '.');	/* first period after colon */
	if (!dot1) dot1 = colon + strlen (colon);  /* if not there, append */
	(void) sprintf (dot1, ".%d", Scr->screen);
	putenv (buf);
	restorevar = 1;
    }
    replace = False;
    subs = strstr (s, "$currentworkspace");
    name = GetCurrentWorkSpaceName ();
    if (subs && name) {
	len = strlen (s) - strlen ("$currentworkspace") + strlen (name);
	news = (char*) malloc (len + 1);
	*subs = '\0';
	strcpy (news, s);
	*subs = '$';
	strcat (news, name);
	subs += strlen ("$currentworkspace");
	strcat (news, subs);
	s = news;
	replace = True;
    }
    subs = strstr (s, "$redirect");
    if (subs) {
	if (captive) {
	    name = (char*) malloc (21 + strlen (captivename) + 1);
	    sprintf (name, "-xrm 'ctwm.redirect:%s'", captivename);
	} else name = "";
	len = strlen (s) - strlen ("$redirect") + strlen (name);
	news = (char*) malloc (len + 1);
	*subs = '\0';
	strcpy (news, s);
	*subs = '$';
	strcat (news, name);
	subs += strlen ("$redirect");
	strcat (news, subs);
	s = news;
	free (name);
	replace = True;
    }
#ifdef USE_SIGNALS
  {
    SigProc	sig;

    sig = signal (SIGALRM, SIG_IGN);
    (void) system (s);
    signal (SIGALRM, sig);
  }
#else  /* USE_SIGNALS */
    (void) system (s);
#endif  /* USE_SIGNALS */

    if (restorevar) {		/* why bother? */
	(void) sprintf (buf, "DISPLAY=%s", oldDisplay);
	putenv (buf);
    }
    if (replace) free (s);
#endif
}



Window lowerontop = -1;

void PlaceTransients (tmp_win, where)
TwmWindow *tmp_win;
int where;
{
    int	sp, sc;
    TwmWindow *t;
    XWindowChanges xwc;
    xwc.stack_mode = where;
    
    sp = tmp_win->frame_width * tmp_win->frame_height;
    for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	if ((t->transient && t->transientfor == tmp_win->w) ||
	    ((tmp_win->group == tmp_win->w) && (tmp_win->group == t->group) &&
	     (tmp_win->group != t->w))) {
	    if (t->frame) {
		sc = t->frame_width * t->frame_height;
		if (sc < ((sp * Scr->TransientOnTop) / 100)) {
		    xwc.sibling = tmp_win->frame;
		    XConfigureWindow(dpy, t->frame, CWSibling | CWStackMode, &xwc);
		    if (lowerontop == t->frame) {
			lowerontop = -1;
		    }
		}
	    }
	}
    }
}

#include <assert.h>

void PlaceOntop (ontop, where)
int ontop;
int where;
{
    TwmWindow *t;
    XWindowChanges xwc;
    xwc.stack_mode = where;

    lowerontop = -1;

    for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	if (t->ontoppriority > ontop) {
	    XConfigureWindow(dpy, t->frame, CWStackMode, &xwc);
	    PlaceTransients(t, Above);
	    if (lowerontop == -1) {
		lowerontop = t->frame;
	    }
	}
    }
}

void MapRaised (tmp_win)
TwmWindow *tmp_win;
{
    XMapWindow(dpy, tmp_win->frame);
    RaiseWindow(tmp_win);
}

void RaiseWindow (tmp_win)
TwmWindow *tmp_win;
{
    XWindowChanges xwc;
    int xwcm;

    if (tmp_win->ontoppriority == ONTOP_MAX) {
	XRaiseWindow(dpy, tmp_win->frame);
	if (lowerontop == -1) {
	    lowerontop = tmp_win->frame;
	} else if (lowerontop == tmp_win->frame) {
	    lowerontop = -1;
	}
    } else {
	if (lowerontop == -1) {
	    PlaceOntop(tmp_win->ontoppriority, Above);
	}
	xwcm = CWStackMode;
	if (lowerontop != -1) {
	    xwc.stack_mode = Below;
	    xwc.sibling = lowerontop;
	    xwcm |= CWSibling;
	} else {
	    xwc.stack_mode = Above;
	}
	XConfigureWindow(dpy, tmp_win->frame, xwcm, &xwc);
    }
    PlaceTransients(tmp_win, Above);
}

void RaiseLower (tmp_win)
TwmWindow *tmp_win;
{
    XWindowChanges xwc;

    PlaceOntop(tmp_win->ontoppriority, Below);
    PlaceTransients(tmp_win, Below);
    lowerontop = -1;
    xwc.stack_mode = Opposite;
    XConfigureWindow(dpy, tmp_win->frame, CWStackMode, &xwc);
    PlaceOntop(tmp_win->ontoppriority, Above);
    PlaceTransients(tmp_win, Above);
}

void RaiseLowerFrame (frame, ontop)
Window frame;
int ontop;
{
    XWindowChanges xwc;

    PlaceOntop(ontop, Below);
    lowerontop = -1;
    xwc.stack_mode = Opposite;
    XConfigureWindow(dpy, frame, CWStackMode, &xwc);
    PlaceOntop(ontop, Above);
}

void LowerWindow (tmp_win)
TwmWindow *tmp_win;
{
    XLowerWindow(dpy, tmp_win->frame);
    if (tmp_win->frame == lowerontop) {
	lowerontop = -1;
    }
    PlaceTransients(tmp_win, Above);
}

void RaiseFrame (frame)
Window frame;
{
    TwmWindow *tmp_win;

    if (XFindContext (dpy, frame, TwmContext, (XPointer *) &tmp_win) == XCNOENT)
	tmp_win = NULL;

    if (tmp_win != NULL) {
	RaiseWindow(tmp_win);
    } else {
	XRaiseWindow(dpy, frame);
    }
}
  
/***********************************************************************
 *
 *  Procedure:
 *	FocusOnRoot - put input focus on the root window
 *
 ***********************************************************************
 */

void
FocusOnRoot()
{
    SetFocus ((TwmWindow *) NULL, LastTimestamp());
    InstallWindowColormaps(0, &Scr->TwmRoot);
    if (! Scr->ClickToFocus) Scr->FocusRoot = TRUE;
}

DeIconify(tmp_win)
TwmWindow *tmp_win;
{
    TwmWindow *t;
    WList *wl;

    /* de-iconify the main window */
    if (Scr->WindowMask) XRaiseWindow (dpy, Scr->WindowMask);
    if (tmp_win->isicon)
    {
	if (tmp_win->icon_on && tmp_win->icon && tmp_win->icon->w)
	    Zoom(tmp_win->icon->w, tmp_win->frame);
	else if (tmp_win->group != (Window) 0)
	{
	    for (t = Scr->TwmRoot.next; t != NULL; t = t->next)
	    {
		if (tmp_win->group == t->w && t->icon_on && t->icon && t->icon->w)
		{
		    Zoom(t->icon->w, tmp_win->frame);
		    break;
		}
	    }
	}
    }

    if (!tmp_win->squeezed) XMapWindow(dpy, tmp_win->w);
    tmp_win->mapped = TRUE;
    if (Scr->NoRaiseDeicon)
	XMapWindow(dpy, tmp_win->frame);
    else
	MapRaised(tmp_win);
    SetMapStateProp(tmp_win, NormalState);

    if (tmp_win->icon && tmp_win->icon->w) {
	XUnmapWindow(dpy, tmp_win->icon->w);
	IconDown (tmp_win);
	if (Scr->SchrinkIconTitles) tmp_win->icon->title_schrinked = True;
    }
    if (tmp_win->list)
      for (wl = tmp_win->list; wl != NULL; wl = wl->nextv)
	XUnmapWindow(dpy, wl->icon);
    if ((Scr->WarpCursor ||
	 LookInList(Scr->WarpCursorL, tmp_win->full_name, &tmp_win->class)) &&
	tmp_win->isicon)
      WarpToWindow (tmp_win);
    tmp_win->isicon = FALSE;
    tmp_win->icon_on = FALSE;


    /* now de-iconify and window group transients */
	for (t = Scr->TwmRoot.next; t != NULL; t = t->next)
	{
	  if ((t->transient && t->transientfor == tmp_win->w) ||
	      ((tmp_win->group == tmp_win->w) && (tmp_win->group == t->group) &&
	       (tmp_win->group != t->w) && t->isicon))
	    {
	      if (t->icon_on)
		Zoom(t->icon->w, t->frame);
	      else
	      if (tmp_win->icon)
		Zoom(tmp_win->icon->w, t->frame);
	      
	      if (!t->squeezed) XMapWindow(dpy, t->w);
	      t->mapped = TRUE;
	      if (Scr->NoRaiseDeicon)
		XMapWindow(dpy, t->frame);
	      else
		MapRaised(t);
	      SetMapStateProp(t, NormalState);
	      
	      if (t->icon && t->icon->w) {
		XUnmapWindow(dpy, t->icon->w);
		IconDown (t);
	      }
	      if (t->list) XUnmapWindow(dpy, t->list->icon);
	      t->isicon = FALSE;
	      t->icon_on = FALSE;
	      WMapDeIconify (t);
	    }
	}
    WMapDeIconify (tmp_win);
    if (! Scr->WindowMask && Scr->DeIconifyFunction.func != 0) {
	char *action;
	XEvent event;

	action = Scr->DeIconifyFunction.item ?
		Scr->DeIconifyFunction.item->action : NULL;
	ExecuteFunction (Scr->DeIconifyFunction.func, action,
			   (Window) 0, tmp_win, &event, C_ROOT, FALSE);
    }
    XSync (dpy, 0);
}



Iconify(tmp_win, def_x, def_y)
TwmWindow *tmp_win;
int def_x, def_y;
{
    TwmWindow *t;
    int iconify;
    XWindowAttributes winattrs;
    unsigned long eventMask;
    WList *wl;
    Window leader;
    Window blanket;

    iconify = (!tmp_win->iconify_by_unmapping);
    t = (TwmWindow*) 0;
    if (tmp_win->transient) {
	leader = tmp_win->transientfor;
	for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	    if (t->w == leader) break;
	}
    }
    else
    if (tmp_win->group != tmp_win->w) {
	leader = tmp_win->group;
	for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	    if ((t->w == leader) && (t->group == t->w)) break;
	}
    }
    if (t && t->icon_on) iconify = False;
    if (iconify)
    {
	if (!tmp_win->icon || !tmp_win->icon->w)
	    CreateIconWindow(tmp_win, def_x, def_y);
	else
	    IconUp(tmp_win);
	if (OCCUPY (tmp_win, Scr->workSpaceMgr.activeWSPC)) {
	    if (Scr->WindowMask) {
		XRaiseWindow (dpy, Scr->WindowMask);
		XMapWindow(dpy, tmp_win->icon->w);
	    }
	    else
		XMapRaised(dpy, tmp_win->icon->w);
	}
    }
    if (tmp_win->list)
      for (wl = tmp_win->list; wl != NULL; wl = wl->nextv)
	XMapWindow(dpy, wl->icon);

    XGetWindowAttributes(dpy, tmp_win->w, &winattrs);
    eventMask = winattrs.your_event_mask;

    /* iconify transients and window group first */
    for (t = Scr->TwmRoot.next; t != NULL; t = t->next)
      {
	if ((t->transient && (t->transientfor == tmp_win->w)) ||
	    ((tmp_win->group == tmp_win->w) && (tmp_win->group == t->group) &&
		(tmp_win->group != t->w)))
	  {
	    if (iconify)
	      {
		if (t->icon_on)
			Zoom(t->icon->w, tmp_win->icon->w);
		else
		if (tmp_win->icon)
		  Zoom(t->frame, tmp_win->icon->w);
	      }
	    
	    /*
	     * Prevent the receipt of an UnmapNotify, since that would
	     * cause a transition to the Withdrawn state.
	     */
	    t->mapped = FALSE;
	    XSelectInput(dpy, t->w, eventMask & ~StructureNotifyMask);
	    XUnmapWindow(dpy, t->w);
	    XUnmapWindow(dpy, t->frame);
	    XSelectInput(dpy, t->w, eventMask);
	    if (t->icon && t->icon->w)
	      XUnmapWindow(dpy, t->icon->w);
	    SetMapStateProp(t, IconicState);
	    if (t == Scr->Focus)
	      {
		SetFocus ((TwmWindow *) NULL, LastTimestamp());
		if (! Scr->ClickToFocus) Scr->FocusRoot = TRUE;
	      }
	    if (t->list) XMapWindow(dpy, t->list->icon);
	    t->isicon = TRUE;
	    t->icon_on = FALSE;
	    WMapIconify (t);
	  }
      } 
    
    if (iconify)
	Zoom(tmp_win->frame, tmp_win->icon->w);

    /*
     * Prevent the receipt of an UnmapNotify, since that would
     * cause a transition to the Withdrawn state.
     */
    tmp_win->mapped = FALSE;

      /* RJVB 20020121: I'd like to have the special effects also for windows "iconified" to the Icon manager! */
    if (! Scr->WindowMask /* && iconify */ && Scr->DoZoom && Scr->SmartIconify) {
	XSetWindowAttributes attr;

	XGetWindowAttributes(dpy, tmp_win->frame, &winattrs);
	attr.backing_store = NotUseful;
	attr.save_under    = False;
	blanket = XCreateWindow (dpy, Scr->Root, winattrs.x, winattrs.y, winattrs.width, winattrs.height,
			(unsigned int) 0,
			CopyFromParent, (unsigned int) CopyFromParent,
			(Visual *) CopyFromParent, CWBackingStore | CWSaveUnder,
			&attr);
	XMapWindow (dpy, blanket);
    }
    XSelectInput(dpy, tmp_win->w, eventMask & ~StructureNotifyMask);
    XUnmapWindow(dpy, tmp_win->w);
    XUnmapWindow(dpy, tmp_win->frame);
    XSelectInput(dpy, tmp_win->w, eventMask);
    SetMapStateProp(tmp_win, IconicState);

    if (! Scr->WindowMask /* && iconify */ && Scr->DoZoom && Scr->SmartIconify) {
	MosaicFade (blanket, winattrs.width, winattrs.height);
	XDestroyWindow (dpy, blanket);
    }
    if (tmp_win == Scr->Focus)
    {
	SetFocus ((TwmWindow *) NULL, LastTimestamp());
	if (! Scr->ClickToFocus) Scr->FocusRoot = TRUE;
    }
    tmp_win->isicon = TRUE;
    if (iconify)
	tmp_win->icon_on = TRUE;
    else
	tmp_win->icon_on = FALSE;
    WMapIconify (tmp_win);
    if (! Scr->WindowMask && Scr->IconifyFunction.func != 0) {
	char *action;
	XEvent event;

	action = Scr->IconifyFunction.item ?
		Scr->IconifyFunction.item->action : NULL;
	ExecuteFunction (Scr->IconifyFunction.func, action,
			   (Window) 0, tmp_win, &event, C_ROOT, FALSE);
    }
    XSync (dpy, 0);
}

void AutoSqueeze (tmp_win)
TwmWindow *tmp_win;
{
    if (tmp_win->iconmgr) return;
    if (Scr->RaiseWhenAutoUnSqueeze && tmp_win->squeezed) XRaiseWindow (dpy, tmp_win->frame);
    Squeeze (tmp_win);
}
void Squeeze (tmp_win)
TwmWindow *tmp_win;
{
    long fx, fy, savex, savey;
    int  neww, newh, south;
    int	 grav = ((tmp_win->hints.flags & PWinGravity) 
		      ? tmp_win->hints.win_gravity : NorthWestGravity);
    XWindowAttributes winattrs;
    unsigned long eventMask;

    if (tmp_win->squeezed) {
	tmp_win->squeezed = False;
	if (!tmp_win->isicon) XMapWindow (dpy, tmp_win->w);
	SetupWindow (tmp_win, tmp_win->actual_frame_x, tmp_win->actual_frame_y,
		tmp_win->actual_frame_width, tmp_win->actual_frame_height, -1);
	return;
    }

    newh = tmp_win->title_height + 2 * tmp_win->frame_bw3D;
    if (newh < 3) { XBell (dpy, 0); return; }
    switch (grav) {
	case SouthWestGravity :
	case SouthGravity :
	case SouthEastGravity :
	    south = True; break;
	default :
	    south = False; break;
    }
    if (tmp_win->title_height) south = False;

    tmp_win->squeezed = True;
    tmp_win->actual_frame_width  = tmp_win->frame_width;
    tmp_win->actual_frame_height = tmp_win->frame_height;
    savex = fx = tmp_win->frame_x;
    savey = fy = tmp_win->frame_y;
    neww  = tmp_win->actual_frame_width;
    if (south) fy += tmp_win->frame_height - newh;
    if (tmp_win->squeeze_info) {
	fx  += tmp_win->title_x - tmp_win->frame_bw3D;
	neww = tmp_win->title_width + 2 * (tmp_win->frame_bw + tmp_win->frame_bw3D);
    }
    XGetWindowAttributes(dpy, tmp_win->w, &winattrs);
    eventMask = winattrs.your_event_mask;
    XSelectInput(dpy, tmp_win->w, eventMask & ~StructureNotifyMask);
    XUnmapWindow(dpy, tmp_win->w);
    XSelectInput(dpy, tmp_win->w, eventMask);

    if (fx + neww >= Scr->MyDisplayWidth)  fx = Scr->MyDisplayWidth  - neww;
    if (fy + newh >= Scr->MyDisplayHeight) fy = Scr->MyDisplayHeight - newh;
    SetupWindow (tmp_win, fx, fy, neww, newh, -1);
    tmp_win->actual_frame_x = savex;
    tmp_win->actual_frame_y = savey;
}

#include <unistd.h>
#include <pwd.h>
#include <syslog.h>

#define MAX_X_EVENT	LASTEvent

char *event_name( int type)
{
	switch( type){
		case KeyPress:
			return( "KeyPress" );
		case KeyRelease:
			return( "KeyRelease" );
		case ButtonPress:
			return( "ButtonPress" );
		case ButtonRelease:
			return( "ButtonRelease" );
		case MotionNotify:
			return( "MotionNotify" );
		case EnterNotify:
			return( "EnterNotify" );
		case LeaveNotify:
			return( "LeaveNotify" );
		case FocusIn:
			return( "FocusIn" );
		case FocusOut:
			return( "FocusOut" );
		case KeymapNotify:
			return( "KeymapNotify" );
		case Expose:
			return( "Expose" );
		case GraphicsExpose:
			return( "GraphicsExpose" );
		case NoExpose:
			return( "NoExpose" );
		case VisibilityNotify:
			return( "VisibilityNotify" );
		case CreateNotify:
			return( "CreateNotify" );
		case DestroyNotify:
			return( "DestroyNotify" );
		case UnmapNotify:
			return( "UnmapNotify" );
		case MapNotify:
			return( "MapNotify" );
		case MapRequest:
			return( "MapRequest" );
		case ReparentNotify:
			return( "ReparentNotify" );
		case ConfigureNotify:
			return( "ConfigureNotify" );
		case ConfigureRequest:
			return( "ConfigureRequest" );
		case GravityNotify:
			return( "GravityNotify" );
		case ResizeRequest:
			return( "ResizeRequest" );
		case CirculateNotify:
			return( "CirculateNotify" );
		case CirculateRequest:
			return( "CirculateRequest" );
		case PropertyNotify:
			return( "PropertyNotify" );
		case SelectionClear:
			return( "SelectionClear" );
		case SelectionRequest:
			return( "SelectionRequest" );
		case SelectionNotify:
			return( "SelectionNotify" );
		case ColormapNotify:
			return( "ColormapNotify" );
		case ClientMessage:
			return( "ClientMessage" );
		case MappingNotify:
			return( "MappingNotify" );
		default:
			return( "Unknown event type");
		}
}

#ifndef CheckMask
#	define	CheckMask(var,mask)	(((var)&(current=(mask)))==(mask))
#endif
#ifndef CheckExclMask
#	define	CheckExclMask(var,mask)	(((var)^(mask))==0)
#endif

char *event_mask_string( unsigned int mask, char *buf, int len)
{ int slen= strlen(buf);
  unsigned int current;
	if( CheckMask(mask, KeyPress) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "KeyPress", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~KeyPress;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, KeyRelease ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "KeyRelease", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~KeyRelease;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ButtonPress ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ButtonPress", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ButtonPress;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ButtonRelease ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ButtonRelease", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ButtonRelease;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, MotionNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "MotionNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~MotionNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, EnterNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "EnterNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~EnterNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, LeaveNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "LeaveNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~LeaveNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, FocusIn ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "FocusIn", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~FocusIn;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, FocusOut ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "FocusOut", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~FocusOut;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, KeymapNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "KeymapNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~KeymapNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, Expose ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "Expose", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~Expose;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, GraphicsExpose ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "GraphicsExpose", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~GraphicsExpose;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, NoExpose ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "NoExpose", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~NoExpose;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, VisibilityNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "VisibilityNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~VisibilityNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, CreateNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "CreateNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~CreateNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, DestroyNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "DestroyNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~DestroyNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, UnmapNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "UnmapNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~UnmapNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, MapNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "MapNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~MapNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, MapRequest ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "MapRequest", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~MapRequest;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ReparentNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ReparentNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ReparentNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ConfigureNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ConfigureNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ConfigureNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ConfigureRequest ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ConfigureRequest", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ConfigureRequest;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, GravityNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "GravityNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~GravityNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ResizeRequest ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ResizeRequest", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ResizeRequest;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, CirculateNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "CirculateNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~CirculateNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, CirculateRequest ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "CirculateRequest", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~CirculateRequest;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, PropertyNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "PropertyNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~PropertyNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, SelectionClear ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "SelectionClear", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~SelectionClear;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, SelectionRequest ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "SelectionRequest", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~SelectionRequest;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, SelectionNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "SelectionNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~SelectionNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ColormapNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ColormapNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ColormapNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ClientMessage ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ClientMessage", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ClientMessage;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, MappingNotify ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "MappingNotify", len- slen );
/* 			fprintf( stderr, "event_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~MappingNotify;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_mask_string( mask, buf, len) );
	}
	else{
		return( buf );
	}
}

char *event_request_mask_string( unsigned int mask, char *buf, int len)
{ int slen= strlen(buf);
  unsigned int current;
	if( CheckMask(mask, KeyPressMask) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "KeyPressM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~KeyPressMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, KeyReleaseMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "KeyReleaseM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~KeyReleaseMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ButtonPressMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ButtonPressM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ButtonPressMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ButtonReleaseMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ButtonReleaseM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ButtonReleaseMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, EnterWindowMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "EnterWindowM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~EnterWindowMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, LeaveWindowMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "LeaveWindowM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~LeaveWindowMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, PointerMotionMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "PointerMotionM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~PointerMotionMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, PointerMotionHintMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "PointerMotionHintM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~PointerMotionHintMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, Button1MotionMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "Button1MotionM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~Button1MotionMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, Button2MotionMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "Button2MotionM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~Button2MotionMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, Button3MotionMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "Button3MotionM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~Button3MotionMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, Button4MotionMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "Button4MotionM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~Button4MotionMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, Button5MotionMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "Button5MotionM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~Button5MotionMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ButtonMotionMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ButtonMotionM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ButtonMotionMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, KeymapStateMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "KeymapStateM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~KeymapStateMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ExposureMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ExposureM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ExposureMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, VisibilityChangeMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "VisibilityChangeM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~VisibilityChangeMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, StructureNotifyMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "StructureNotifyM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~StructureNotifyMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ResizeRedirectMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ResizeRedirectM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ResizeRedirectMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, SubstructureNotifyMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "SubstructureNotifyM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~SubstructureNotifyMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, SubstructureRedirectMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "SubstructureRedirectM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~SubstructureRedirectMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, FocusChangeMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "FocusChangeM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~FocusChangeMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, PropertyChangeMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "PropertyChangeM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~PropertyChangeMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, ColormapChangeMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "ColormapChangeM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~ColormapChangeMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else if( CheckMask( mask, OwnerGrabButtonMask ) ){
		if( slen ){
			strncat( buf, "|", len- slen );
			slen= strlen(buf);
		}
		strncat( buf, "OwnerGrabButtonM", len- slen );
/* 			fprintf( stderr, "event_request_mask_string(%s: 0x%lx-0x%lx=", buf, mask, current );	*/
		mask&= ~OwnerGrabButtonMask;
/* 			fprintf( stderr, "0x%lx)\n", mask );	*/
		return( event_request_mask_string( mask, buf, len) );
	}
	else{
		return( buf );
	}
}

/* password routine called by LockScreen()	*/
static void auto_lock(struct passwd *pw)
{
  unsigned long i;
  int keys, done= 0, j, l, len= 8;
  char *rsrpp= 0, *srpp = 0, pwbuf[32], _pwbuf[32];
  struct passwd *rpw;
  KeySym keysymbuffer[32];
  extern char *crypt(), *event_name();

      /* Save the user's password	*/
    if( pw!= 0 )
     srpp = pw->pw_passwd;
      /* The root password:	*/
    if( (rpw = getpwuid(0)) != 0 )
     rsrpp = strdup(rpw->pw_passwd);

    if( !srpp && !rsrpp ){
	    len= 31;
	}
    for (i = 0; i>= 0 ; i++) {
     char *rcrpp, *crpp;
		pwbuf[0]= '\0';
		l= 0;
		done= 0;
		  /* event-loop that reads keyboard input into the password buffer,
		   \ and passes selected other events to the appropriate eventhandlers
		   */
		do{
			XNextEvent( dpy, &Event);
			if( Event.xany.window== Scr->InfoWindow ){
			  /* Always stay on top of things	*/
				XRaiseWindow( dpy, Scr->InfoWindow );
			}
			switch( Event.type ){
				case KeyRelease:
					break;
				  /* XLookupString _might_ return more than one char at once:
				   \ the following code is prepared to handle that case.
				   \ It reads upto a '\n' or '\r' into a password string that
				   \ will eventually be <len> bytes long (IS THAT UNI(X|V)ERSAL?).
				   \ A ^u clears the buffer
				   */
				case KeyPress:
					keys = XLookupString(&Event.xkey, _pwbuf, sizeof(_pwbuf),
						(KeySym *) keysymbuffer, (XComposeStatus *) 0
					);
					_pwbuf[keys]= '\0';
					if( Event.xany.window== Scr->InfoWindow ){
						if( _pwbuf[keys-1]== '\n' || _pwbuf[keys-1]== '\r' ){
							_pwbuf[keys-1]= '\0';
							done= 1;
						}
						else{
							done= 0;
						}
						for( j= 0; j< keys ; j++ ){
							/* ^u clears	*/
							if( _pwbuf[j]== ('u'-'a'+1) ){
								l= 0;
							}
							else{
								pwbuf[l]= _pwbuf[j];
								if( l< len ){
									l++;
								}
							}
						}
						pwbuf[l]= '\0';
					}
#ifdef DEBUG
					else{
						fprintf( stderr, "ignored %s (\"%s\") event for window %d\n",
							event_name(Event.type), _pwbuf, (int) Event.xany.window );
					}
					break;
#endif
					break;
				case Expose:
				case CreateNotify:
				case DestroyNotify:
				case MapRequest:
				case MapNotify:
				case UnmapNotify:
				case MotionNotify:
				case EnterNotify:
				case LeaveNotify:
				case ConfigureRequest:
				case ClientMessage:
				case PropertyNotify:
				case ColormapNotify:
				case VisibilityNotify:
#ifdef DEBUG
					fprintf( stderr, "%s event in locked mode for window %d\n",
						event_name(Event.type), (int) Event.xany.window
					);
#endif
					(*EventHandler[Event.type])();
					break;
				case ButtonRelease:
				case ButtonPress:
#ifdef DEBUG
					fprintf( stderr, "ignored %s (%d) event in locked mode for window %d\n",
						event_name(Event.type), Event.type, (int) Event.xany.window
					);
					break;
#endif
				default:
					if( Event.type< MAX_X_EVENT ){
						(*EventHandler[Event.type])();
#ifdef DEBUG
						fprintf( stderr, "%s (%d) event in locked mode for window %d\n",
							event_name(Event.type), Event.type, (int) Event.xany.window
						);
					}
					else{
						fprintf( stderr, "Can't handle \"%s\" (%d>%d) event in locked mode for window %d\n",
							event_name(Event.type), Event.type, MAX_X_EVENT, (int) Event.xany.window
						);
#endif
					}
					break;
			}
		} while( !done );
		  /* First check the user's own password. If correct, return	*/
		if( srpp || rsrpp ){
		  char *msg= NULL, *rmsg= NULL;
			if( !pwbuf[0] ){
				msg= "empty pw";
			}
			if( srpp ){
				crpp = crypt( pwbuf ,   srpp ) ;
				if (strcmp(crpp, srpp) == 0) {
#define xfree(x)	if(x){free(x);}
					xfree( rsrpp );
					return;
				}
				if( !msg ){
					msg= "invalid user pw";
				}
			}
			  /* Hmm. Maybe it is root releasing locked-up user?	*/
			if( rsrpp ){
				rcrpp = crypt( pwbuf ,   rsrpp ) ;
				if( strcmp( crpp, rsrpp)== 0 ){
					xfree( rsrpp);
					return;
				}
				rmsg= ", invalid root pw";
			}
			syslog( LOG_WARNING, "%s[%d]: illegal password for user %s (or %s): %s%s\n",
				ProgramName, getpid(),pw->pw_name, rpw->pw_name,
				(msg)? msg : "",
				(rmsg)? rmsg : ""
			);
		}
		  /* Couldn't get a password to prompt for. We just use an internal password.	*/
		else{
			if( strncmp( pwbuf, "ctwm's internal password\n", len)== 0 ){
				return;
			}
		}
		  /* What are we doing here!! Someone trying to break-in???	*/
		XBell(dpy, (i%101) );
	    Info[InfoLines-2][0]= ' ';
	    {  /* copied from HandleExpose()	*/
		int i;
		int height;

#ifdef I18N
	    FB(Scr->DefaultC.fore, Scr->DefaultC.back);
#else
		FBF(Scr->DefaultC.fore, Scr->DefaultC.back,
		    Scr->InfoFont->font->fid);
#endif

		height = Scr->InfoFont->height+2;
		for (i = 0; i < InfoLines; i++)
		{
		    XDrawString(dpy, Scr->InfoWindow, Scr->NormalGC,
			5, (i*height) + Scr->InfoFont->y, Info[i], strlen(Info[i]));
		}
	    }
	    Info[InfoLines-2][0]= '\0';
	}
}

/* LockScreen():
 \ Pops up the InfoWindow (could be nicer, but why...)
 \ with a password prompt. It also grabs the pointer, disabling
 \ all new connections (?) to the server
 \ Added 950109 by RJB
 */
static void LockScreen ()
{
    int euid= (int) geteuid(), uid= (int) getuid();
    struct passwd *pw= getpwuid( euid ), PW;
    char *nm= NULL;

    int kgrabbed= 0, pgrabbed= 0, i, n, twidth, width, height;
    int px, py, dummy;
    unsigned udummy;
#ifdef I18N
    XRectangle inc_rect;
    XRectangle logical_rect;
#endif



    n = 0;
	PW.pw_passwd= NULL;
    if( pw ){
	    PW.pw_name= strdup(pw->pw_name);
	    PW.pw_passwd= strdup(pw->pw_passwd);
	    nm= PW.pw_name;
	}
	else{
	  char *c= getlogin();
		nm= (c)? strdup(c) : NULL;
		PW.pw_name= nm;
	}
	
    Info[n++][0] = '\0';
    sprintf( Info[n++], "Enter password for" );
    Info[n++][0] = '\0';
    sprintf( Info[n++], "     %s", (nm)? nm : (PW.pw_name= "(unknown)") );
    Info[n++][0] = '\0';
    sprintf( Info[n++], " INVALID PASSWORD " );
    Info[n++][0] = '\0';

	Scr->InfoFont= &Scr->TitleBarFont;
      /* figure out the width and height of the info window */
    height = n * (Scr->InfoFont->height+2);
    width = 1;
    for (i = 0; i < n; i++)
    {
#ifdef I18N
	XmbTextExtents(Scr->InfoFont->font_set, Info[i],
		       strlen(Info[i]), &inc_rect, &logical_rect);
	
	twidth = logical_rect.width;
#else
	twidth = XTextWidth(Scr->InfoFont->font, Info[i],
	    strlen(Info[i]));
#endif	
	if (twidth > width)
	    width = twidth;
    }

	  /* If we arrive by way of a menu, restore everything as
	   \ well as possible (taken from HandleButtonRelease()).
	   \ Only then can normal processing continue!
	   */
	if( Event.type== ButtonRelease || Event.type== ButtonPress ){
	  int mask = (Button1Mask|Button2Mask|Button3Mask|Button4Mask|Button5Mask);
		PopDownMenu();
	    switch (Event.xbutton.button)
	    {
		case Button1: mask &= ~Button1Mask; break;
		case Button2: mask &= ~Button2Mask; break;
		case Button3: mask &= ~Button3Mask; break;
		case Button4: mask &= ~Button4Mask; break;
		case Button5: mask &= ~Button5Mask; break;
	    }

	    if (RootFunction != 0 ||
		ResizeWindow != None ||
		DragWindow != None)
		ButtonPressed = -1;

	    if (RootFunction == 0 &&
			(Event.xbutton.state & mask) == 0 &&
			DragWindow == None &&
			ResizeWindow == None
		){
			XUngrabPointer(dpy, CurrentTime);
			XUngrabServer(dpy);
			XFlush(dpy);
			EventHandler[EnterNotify] = HandleEnterNotify;
			EventHandler[LeaveNotify] = HandleLeaveNotify;
	    }
	}

    if (InfoLines) XUnmapWindow(dpy, Scr->InfoWindow);
    InfoLines= n;
    Info[InfoLines-2][0]= '\0';

    width += 10;		/* some padding */
    if (XQueryPointer (dpy, Scr->Root, &JunkRoot, &JunkChild, &px, &py,
		       &dummy, &dummy, &udummy)
    ) {
	px -= (width / 2);
	py -= (height / 3);
	if (px + width + BW2 >= Scr->MyDisplayWidth) 
	  px = Scr->MyDisplayWidth - width - BW2;
	if (py + height + BW2 >= Scr->MyDisplayHeight) 
	  py = Scr->MyDisplayHeight - height - BW2;
	if (px < 0) px = 0;
	if (py < 0) py = 0;
    } else {
	px = py = 0;
    }
    XMoveResizeWindow(dpy, Scr->InfoWindow, px, py, width, height);
    XMapRaised(dpy, Scr->InfoWindow); 
	
      /* Grab the pointer, the keyboard, and make sure that the InfoWindow is there	*/
    if( XGrabPointer(dpy, Scr->InfoWindow, True,
		     (unsigned int) (ButtonPressMask|ButtonReleaseMask|
				     PointerMotionMask|PointerMotionHintMask),
		     GrabModeAsync, GrabModeAsync,
		     Scr->InfoWindow, Scr->SelectCursor, CurrentTime) == GrabSuccess
	){
		pgrabbed= 1;
	}
    if( XGrabKeyboard(dpy, Scr->InfoWindow, True,
		     GrabModeAsync, GrabModeAsync, CurrentTime) == GrabSuccess
	){
		kgrabbed= 1;
	}
	XFlush( dpy);
	XSync( dpy, False);

      /* Call the function that reads/checks the password	*/
    auto_lock(&PW);
    if( nm ){
	    free(nm);
	}
	if( PW.pw_passwd ){
		free( PW.pw_passwd );
	}

	if( kgrabbed ){
		XUngrabKeyboard( dpy, CurrentTime );
	}
	if( pgrabbed ){
		XUngrabPointer(dpy, CurrentTime);
	}

    XUnmapWindow(dpy, Scr->InfoWindow);
    InfoLines=0;
}

static char *zoom_state(int flag)
{
   switch (flag){
	   case ZOOM_NONE:
			return( "");
		  break;
	   case F_ZOOM:
			return( "(zoomed)");
		  break;
	   case F_HORIZOOM:
			return( "(horizoom)");
		  break;
	   case F_FULLZOOM:
			return( "(fullzoom)");
		  break;
	   case F_LEFTZOOM:
			return( "(leftzoom)");
		  break;
	   case F_RIGHTZOOM:
			return( "(rightzoom)");
		  break;
	   case F_TOPZOOM:
			return( "(topzoom)");
		  break;
	   case F_BOTTOMZOOM:
			return( "(bottomzoom)");
		  break;
    }
}

char *VisualClass[]= { "StaticGray", "GrayScale", "StaticColor", "PseudoColor", "TrueColor", "DirectColor" };
int VisualClasses= sizeof(VisualClass)/sizeof(char*);

static void Identify (t)
TwmWindow *t;
{
    int i, n, twidth, width, height;
    int x, y;
    unsigned int wwidth, wheight, bw, depth;
    Window target, junk;
    XWindowAttributes attr;
    int rx, ry, px, py, dummy;
    unsigned udummy;
    unsigned char	*prop;
    unsigned long	nitems, bytesafter;
    Atom		actual_type;
    int			actual_format;
#ifdef I18N
    XRectangle inc_rect;
    XRectangle logical_rect;
#endif

    n = 0;
    (void) sprintf(Info[n++], "(C)Twm version:  %s (%s,%s)", Version, __DATE__, __TIME__ );
    (void) sprintf(Info[n], "Compile time options:");
#ifdef XPM
    (void) strcat (Info[n], " XPM");
#endif
#ifdef IMCONV
    (void) strcat (Info[n], ", IMCONV");
#endif
#ifdef USEM4
    (void) strcat (Info[n], ", USEM4");
#endif
#ifdef SOUNDS
    (void) strcat (Info[n], ", SOUNDS");
#endif
#ifdef X11R6
    (void) strcat (Info[n], ", X11R6");
#endif
#ifdef DEBUG
    (void) strcat (Info[n], ", debug");
#endif
#ifdef I18N
    (void) strcat (Info[n], ", I18N");
#endif    
#ifdef _HAVE_XINERAMA_
    strcat( Info[n], ", XINERAMA" );
#endif

    n++;
    Info[n++][0] = '\0';
/* #if defined(SWITCHES)	*/
/* { char *c= SWITCHES;	*/
/* 	sprintf( Info[n], "Compiler options: " );	*/
/* 	strncat( Info[n], c, INFO_SIZE- strlen(Info[n])- 1 );	*/
/* 	Info[n][ INFO_SIZE- 1 ]= '\0';	*/
/* 	n++;	*/
/* }	*/
/* #endif	*/

    if (t) {
	target= t->w;
    }
    else{
	target= Scr->Root;
    }
    XGetWindowAttributes( dpy, target, &attr );
	XGetGeometry (dpy, target, &JunkRoot, &JunkX, &JunkY,
		      &wwidth, &wheight, &bw, &depth);
	(void) XTranslateCoordinates (dpy, target, Scr->Root, 0, 0,
				      &x, &y, &junk);
	(void) sprintf(Info[n++], "ID               = \"%d\"", target );
	(void) sprintf(Info[n++], "Name             = \"%s\"", (t)? t->name : "X11 Server's RootWindow" );
	if( t ){
		(void) sprintf(Info[n++], "      full       = \"%s\"", t->full_name);
		(void) sprintf(Info[n++], "      icon       = \"%s\"", t->icon_name);
		(void) sprintf(Info[n++], "Class.res_name   = \"%s\"", t->class.res_name);
		(void) sprintf(Info[n++], "Class.res_class  = \"%s\"", t->class.res_class);
		Info[n++][0] = '\0';
	}
	sprintf( Info[n++],       "Display          = %s ~ X11 server vendor \"%s\" release %d",
		DisplayString(dpy), ServerVendor(dpy), VendorRelease(dpy)
	);
	(void) sprintf(Info[n++], "Geometry/root    = %dx%d+%d+%d %s", wwidth, wheight,
		x, y, (t)? zoom_state( t->zoomed ) : ""
	);
#ifdef X11R6
	if( t && (t->widthEverChangedByUser || t->heightEverChangedByUser) ){
		(void) sprintf(Info[n++], "W/H Changed      = %s%s",
			(t->widthEverChangedByUser)? "yes" : "no",
			(t->heightEverChangedByUser)? "/yes": "/no"
		);
	}
#endif
	(void) sprintf(Info[n++], "Border width     = %d", bw);
	(void) sprintf(Info[n++], "Depth            = %d", depth);
	{ XVisualInfo *vi, templ;
	  long mask= VisualIDMask;
	  int N= 0;
		templ.visualid= attr.visual->visualid;
		if( (vi= XGetVisualInfo( dpy, mask, &templ, &N )) ){
			sprintf( Info[n++],       "Visual           = 0x%x, %dbits, %s, CMap[%d], %dbits/RGB",
				attr.visual->visualid, vi->depth,
				(vi->class< VisualClasses)? VisualClass[vi->class] : "(unknown type)",
				vi->colormap_size, vi->bits_per_rgb
			);
		}
		else{
			sprintf( Info[n++],       "Visual           = 0x%x, %s, CMap[%d], %dbits/RGB",
				attr.visual->visualid,
				(attr.visual->class< VisualClasses)? VisualClass[attr.visual->class] : "(unknown type)",
				attr.visual->map_entries, attr.visual->bits_per_rgb
			);
		}
	}
#ifdef _HAVE_XINERAMA_
	{ int width, height, basex=0, basey=0, head;
		width= theDisplayWidth( x+wwidth/2, y+wheight/2, &basex, &basey, &head );
		height= theDisplayHeight( x+wwidth/2, y+wheight/2, NULL, NULL, NULL);
		sprintf(Info[n++], "Window on Head   = #%d : %dx%d+%d+%d",
			head, width, height, basex, basey
		);
	}
#endif
	if( t && t->savegeometry.width> 0 ){
		(void) sprintf(Info[n++], "Saved geometry   = %dx%d+%d+%d",
			t->savegeometry.width, t->savegeometry.height,
			t->savegeometry.x, t->savegeometry.y
		);
	}
	if( t && t->wr ){
		(void) sprintf(Info[n++], "Window Region    = %dx%d+%d+%d",
			t->wr->w, t->wr->h,
			t->wr->x, t->wr->y
		);
	}

     if( XQueryPointer (dpy, target, &JunkRoot, &JunkChild,
		       &rx, &ry, &px, &py, &udummy)
	){
		sprintf( Info[n++], "Pointer Position = (%d,%d) (root (%d,%d))",
			px, py, rx, ry
		);
	}

	if (XGetWindowProperty (dpy, target, _XA_WM_CLIENT_MACHINE, 0L, 64, False,
				XA_STRING, &actual_type, &actual_format, &nitems,
				&bytesafter, &prop) == Success) {
	    if (nitems && prop) {
		(void) sprintf(Info[n++], "Client machine   = %s", (char*)prop);
		XFree ((char *) prop);
	    }
	}
	{ char *bs;
		switch( attr.backing_store ){
			case NotUseful:
				bs= "NotUseful";
				break;
			case WhenMapped:
				bs= "WhenMapped";
				break;
			case Always:
				bs= "Always";
				break;
		}
		sprintf( Info[n++],       "Backing store    = %s, Save Under= %s",
			bs, (attr.save_under)? "True" : "False"
		);
	}
/* 	attr.backing_store= NotUseful, WhenMapped, Always	*/
/* 	attr.save_under= True/False	*/
/* 	attr.visual	*/
	sprintf( Info[n++], "All events for this window: 0x%lx", attr.all_event_masks );
	Info[n][0]= ' '; Info[n][1]= '\0';
	event_request_mask_string( attr.all_event_masks, &(Info[n++][1]), INFO_SIZE );
	sprintf( Info[n++], "Events requested by ctwm: 0x%lx", attr.your_event_mask );
	Info[n][0]= ' '; Info[n][1]= '\0';
	event_request_mask_string( attr.your_event_mask, &(Info[n++][1]), INFO_SIZE );
	sprintf( Info[n++], "Events not to be propagated 0x%lx:", attr.do_not_propagate_mask );
	Info[n][0]= ' '; Info[n][1]= '\0';
	event_request_mask_string( attr.do_not_propagate_mask, &(Info[n++][1]), INFO_SIZE );
	sprintf(Info[n++], "Override structure control: %s", (attr.override_redirect)? "yes" : "no" );

	
    Info[n++][0] = '\0';
    (void) sprintf(Info[n++], "Click to dismiss....");

    Scr->InfoFont= &Scr->IconFont;
    /* figure out the width and height of the info window */
    height = n * (Scr->InfoFont->height+2);
    width = 1;
    for (i = 0; i < n; i++)
    {
#ifdef I18N
	XmbTextExtents(Scr->InfoFont->font_set, Info[i],
		       strlen(Info[i]), &inc_rect, &logical_rect);
	
	twidth = logical_rect.width;
#else
	twidth = XTextWidth(Scr->InfoFont->font, Info[i],
	    strlen(Info[i]));
#endif	
	if (twidth > width)
	    width = twidth;
    }
    if (InfoLines) XUnmapWindow(dpy, Scr->InfoWindow);

    width += 10;		/* some padding */
    height += 10;		/* some padding */
    if (XQueryPointer (dpy, Scr->Root, &JunkRoot, &JunkChild,
		       &dummy, &dummy, &px, &py, &udummy)) {
	px -= (width / 2);
	py -= (height / 3);
	if (px + width + BW2 >= Scr->MyDisplayWidth) 
	  px = Scr->MyDisplayWidth - width - BW2;
	if (py + height + BW2 >= Scr->MyDisplayHeight) 
	  py = Scr->MyDisplayHeight - height - BW2;
	if (px < 0) px = 0;
	if (py < 0) py = 0;
    } else {
	px = py = 0;
    }
    XMoveResizeWindow(dpy, Scr->InfoWindow, px, py, width, height);
    XMapRaised(dpy, Scr->InfoWindow); 
    InfoLines  = n;
    InfoWidth  = width;
    InfoHeight = height;
}



SetMapStateProp(tmp_win, state)
TwmWindow *tmp_win;
int state;
{
    unsigned long data[2];		/* "suggested" by ICCCM version 1 */
  
    data[0] = (unsigned long) state;
    data[1] = (unsigned long) (tmp_win->iconify_by_unmapping ? None : 
			   (tmp_win->icon ? tmp_win->icon->w : None));

    XChangeProperty (dpy, tmp_win->w, _XA_WM_STATE, _XA_WM_STATE, 32, 
		 PropModeReplace, (unsigned char *) data, 2);
}



Bool GetWMState (w, statep, iwp)
    Window w;
    int *statep;
    Window *iwp;
{
    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytesafter;
    unsigned long *datap = NULL;
    Bool retval = False;

    if (XGetWindowProperty (dpy, w, _XA_WM_STATE, 0L, 2L, False, _XA_WM_STATE,
			    &actual_type, &actual_format, &nitems, &bytesafter,
			    (unsigned char **) &datap) != Success || !datap)
      return False;

    if (nitems <= 2) {			/* "suggested" by ICCCM version 1 */
	*statep = (int) datap[0];
	*iwp = (Window) datap[1];
	retval = True;
    }

    XFree ((char *) datap);
    return retval;
}



WarpToScreen (n, inc)
    int n, inc;
{
    Window dumwin;
    int x, y, dumint;
    unsigned int dummask;
    ScreenInfo *newscr = NULL;

    while (!newscr) {
					/* wrap around */
	if (n < 0) 
	  n = NumScreens - 1;
	else if (n >= NumScreens)
	  n = 0;

	newscr = ScreenList[n];
	if (!newscr) {			/* make sure screen is managed */
	    if (inc) {			/* walk around the list */
		n += inc;
		continue;
	    }
	    fprintf (stderr, "%s:  unable to warp to unmanaged screen %d\n", 
		     ProgramName, n);
	    XBell (dpy, 0);
	    return (1);
	}
    }

    if (Scr->screen == n) return (0);	/* already on that screen */

    PreviousScreen = Scr->screen;
    XQueryPointer (dpy, Scr->Root, &dumwin, &dumwin, &x, &y,
		   &dumint, &dumint, &dummask);

    XWarpPointer (dpy, None, newscr->Root, 0, 0, 0, 0, x, y);
    Scr = newscr;
    return (0);
}




/*
 * BumpWindowColormap - rotate our internal copy of WM_COLORMAP_WINDOWS
 */

BumpWindowColormap (tmp, inc)
    TwmWindow *tmp;
    int inc;
{
    int i, j, previously_installed;
    ColormapWindow **cwins;

    if (!tmp) return (1);

    if (inc && tmp->cmaps.number_cwins > 0) {
	cwins = (ColormapWindow **) malloc(sizeof(ColormapWindow *)*
					   tmp->cmaps.number_cwins);
	if (cwins) {		
	    if (previously_installed =
		/* SUPPRESS 560 */(Scr->cmapInfo.cmaps == &tmp->cmaps &&
	        tmp->cmaps.number_cwins)) {
		for (i = tmp->cmaps.number_cwins; i-- > 0; )
		    tmp->cmaps.cwins[i]->colormap->state = 0;
	    }

	    for (i = 0; i < tmp->cmaps.number_cwins; i++) {
		j = i - inc;
		if (j >= tmp->cmaps.number_cwins)
		    j -= tmp->cmaps.number_cwins;
		else if (j < 0)
		    j += tmp->cmaps.number_cwins;
		cwins[j] = tmp->cmaps.cwins[i];
	    }

	    free((char *) tmp->cmaps.cwins);

	    tmp->cmaps.cwins = cwins;

	    if (tmp->cmaps.number_cwins > 1)
		memset (tmp->cmaps.scoreboard, 0, 
		       ColormapsScoreboardLength(&tmp->cmaps));

	    if (previously_installed)
		InstallWindowColormaps(PropertyNotify, (TwmWindow *) NULL);
	}
    } else
	FetchWmColormapWindows (tmp);
}



void ShowIconManager () {
    IconMgr		*i;
    WorkSpaceList	*wl;

    if (! Scr->workSpaceManagerActive) return;

    if (Scr->NoIconManagers) return;
    for (wl = Scr->workSpaceMgr.workSpaceList; wl != NULL; wl = wl->next) {
	for (i = wl->iconmgr; i != NULL; i = i->next) {
	    if (i->count == 0) continue;
	    if (OCCUPY (i->twm_win, Scr->workSpaceMgr.activeWSPC)) {
		SetMapStateProp (i->twm_win, NormalState);
		XMapWindow (dpy, i->twm_win->w);
		MapRaised (i->twm_win);
		if (i->twm_win->icon && i->twm_win->icon->w)
		    XUnmapWindow (dpy, i->twm_win->icon->w);
	    }
	    i->twm_win->mapped = TRUE;
	    i->twm_win->isicon = FALSE;
	}
    }
}


void HideIconManager () {
    IconMgr		*i;
    WorkSpaceList	*wl;

    if (Scr->NoIconManagers) return;
    for (wl = Scr->workSpaceMgr.workSpaceList; wl != NULL; wl = wl->next) {
	for (i = wl->iconmgr; i != NULL; i = i->next) {
	    SetMapStateProp (i->twm_win, WithdrawnState);
	    XUnmapWindow(dpy, i->twm_win->frame);
	    if (i->twm_win->icon && i->twm_win->icon->w) XUnmapWindow (dpy, i->twm_win->icon->w);
	    i->twm_win->mapped = FALSE;
	    i->twm_win->isicon = TRUE;
	}
    }
}




DestroyMenu (menu)
    MenuRoot *menu;
{
    MenuItem *item;

    if (menu->w) {
	XDeleteContext (dpy, menu->w, MenuContext);
	XDeleteContext (dpy, menu->w, ScreenContext);
	if (Scr->Shadow) XDestroyWindow (dpy, menu->shadow);
	XDestroyWindow(dpy, menu->w);
    }

    for (item = menu->first; item; ) {
	MenuItem *tmp = item;
	item = item->next;
	free ((char *) tmp);
    }
}



/*
 * warping routines
 */
#define ONSCREEN(r)  OCCUPY((r), Scr->workSpaceMgr.activeWSPC)

void WarpAlongRing (ev, forward)
    XButtonEvent *ev;
    Bool forward;
{
    TwmWindow *r, *head;

    if (Scr->RingLeader)
      head = Scr->RingLeader;
    else if (!(head = Scr->Ring)) 
      return;

    if (forward) {
	for (r = head->ring.next; r != head; r = r->ring.next) {
	    if (!r) break;
	    if (r->mapped && (Scr->WarpRingAnyWhere || ONSCREEN(r))) break;
	}
    } else {
	for (r = head->ring.prev; r != head; r = r->ring.prev) {
	    if (!r) break;
	    if (r->mapped && (Scr->WarpRingAnyWhere || ONSCREEN(r))) break;
	}
    }

    if (r && r != head) {
	TwmWindow *p = Scr->RingLeader, *t;

	Scr->RingLeader = r;
	WarpToWindow (r);

	if (p && p->mapped &&
	    XFindContext (dpy, ev->window, TwmContext, (XPointer *)&t) == XCSUCCESS &&
	    p == t) {
	    p->ring.cursor_valid = True;
	    p->ring.curs_x = ev->x_root - t->frame_x;
	    p->ring.curs_y = ev->y_root - t->frame_y;
	    if (p->ring.curs_x < -p->frame_bw || 
		p->ring.curs_x >= p->frame_width + p->frame_bw ||
		p->ring.curs_y < -p->frame_bw || 
		p->ring.curs_y >= p->frame_height + p->frame_bw) {
		/* somehow out of window */
		p->ring.curs_x = p->frame_width / 2;
		p->ring.curs_y = p->frame_height / 2;
	    }
	}
    }
}



void WarpToWindow (t)
    TwmWindow *t;
{
    int x, y;

    if (t->auto_raise || !Scr->NoRaiseWarp) AutoRaiseWindow (t);
    if (t->ring.cursor_valid) {
	x = t->ring.curs_x;
	y = t->ring.curs_y;
    } else {
	x = t->frame_width / 2;
	y = t->frame_height / 2;
    }
    if (! OCCUPY (t, Scr->workSpaceMgr.activeWSPC)) {
	WorkSpaceList *wlist;

	for (wlist = Scr->workSpaceMgr.workSpaceList; wlist != NULL; wlist = wlist->next) {
	    if (OCCUPY (t, wlist)) break;
	}
	if (wlist != NULL) GotoWorkSpace (wlist);
    }
    XWarpPointer (dpy, None, t->frame, 0, 0, 0, 0, x, y);
}




/*
 * ICCCM Client Messages - Section 4.2.8 of the ICCCM dictates that all
 * client messages will have the following form:
 *
 *     event type	ClientMessage
 *     message type	_XA_WM_PROTOCOLS
 *     window		tmp->w
 *     format		32
 *     data[0]		message atom
 *     data[1]		time stamp
 */
static void send_clientmessage (w, a, timestamp)
    Window w;
    Atom a;
    Time timestamp;
{
    XClientMessageEvent ev;

    ev.type = ClientMessage;
    ev.window = w;
    ev.message_type = _XA_WM_PROTOCOLS;
    ev.format = 32;
    ev.data.l[0] = a;
    ev.data.l[1] = timestamp;
    XSendEvent (dpy, w, False, 0L, (XEvent *) &ev);
}

SendDeleteWindowMessage (tmp, timestamp)
    TwmWindow *tmp;
    Time timestamp;
{
    send_clientmessage (tmp->w, _XA_WM_DELETE_WINDOW, timestamp);
}

SendSaveYourselfMessage (tmp, timestamp)
    TwmWindow *tmp;
    Time timestamp;
{
    send_clientmessage (tmp->w, _XA_WM_SAVE_YOURSELF, timestamp);
}


SendTakeFocusMessage (tmp, timestamp)
    TwmWindow *tmp;
    Time timestamp;
{
    send_clientmessage (tmp->w, _XA_WM_TAKE_FOCUS, timestamp);
}

MoveMenu (eventp)
XEvent *eventp;
{
    int    XW, YW, newX, newY, cont;
    Bool   newev;
    unsigned long event_mask;
    XEvent ev;

    if (! ActiveMenu) return (1);
    if (! ActiveMenu->pinned) return (1);

    XW = eventp->xbutton.x_root - ActiveMenu->x;
    YW = eventp->xbutton.y_root - ActiveMenu->y;
    XGrabPointer (dpy, ActiveMenu->w, True,
		ButtonPressMask  | ButtonReleaseMask | ButtonMotionMask,
		GrabModeAsync, GrabModeAsync,
		None, Scr->MoveCursor, CurrentTime);

    newX = ActiveMenu->x;
    newY = ActiveMenu->y;
    cont = TRUE;
    event_mask = ButtonPressMask | ButtonMotionMask | ButtonReleaseMask | ExposureMask;
    XMaskEvent (dpy, event_mask, &ev);
    while (cont) {
	ev.xbutton.x_root -= Scr->MyDisplayX;
	ev.xbutton.y_root -= Scr->MyDisplayY;
	switch (ev.xany.type) {
	    case ButtonRelease :
		cont = FALSE;
	    case MotionNotify :
		if (!cont) {
		    newev = False;
		    while (XCheckMaskEvent (dpy, ButtonMotionMask | ButtonReleaseMask, &ev)) {
			newev = True;
			if (ev.type == ButtonRelease) break;
		    }
		    if (ev.type == ButtonRelease) continue;
		    if (newev) {
			ev.xbutton.x_root -= Scr->MyDisplayX;
			ev.xbutton.y_root -= Scr->MyDisplayY;
		    }
		}
        	newX = ev.xbutton.x_root - XW;
        	newY = ev.xbutton.y_root - YW;
		if (Scr->DontMoveOff) {
		    int w = ActiveMenu->width;
		    int h = ActiveMenu->height;

		    if ((newX < 0) && ((Scr->MoveOffResistance < 0) ||
			(newX > -Scr->MoveOffResistance))) {
			newX = 0;
		    }
		    if (((newX + w) > Scr->MyDisplayWidth) &&
			((Scr->MoveOffResistance < 0) ||
			((newX + w) < Scr->MyDisplayWidth + Scr->MoveOffResistance))) {
			newX = Scr->MyDisplayWidth - w;
		    }
		    if ((newY < 0) && ((Scr->MoveOffResistance < 0) ||
			(newY > -Scr->MoveOffResistance))) {
			newY = 0;
		    }
		    if (((newY + h) > Scr->MyDisplayHeight) &&
			((Scr->MoveOffResistance < 0) ||
			((newY + h) < Scr->MyDisplayHeight + Scr->MoveOffResistance))) {
			newY = Scr->MyDisplayHeight - h;
		    }
		}
		XMoveWindow (dpy, ActiveMenu->w, newX, newY);
		XMaskEvent (dpy, event_mask, &ev);
		break;
	    case ButtonPress :
		cont = FALSE;
		newX = ActiveMenu->x;
		newY = ActiveMenu->y;
		break;
	    case Expose:
                Event = ev;
                DispatchEvent ();
		XMaskEvent (dpy, event_mask, &ev);
		break;
	}
    }
    XUngrabPointer (dpy, CurrentTime);
    if (ev.xany.type == ButtonRelease) ButtonPressed = -1;
    /*XPutBackEvent (dpy, &ev);*/
    XMoveWindow (dpy, ActiveMenu->w, newX, newY);
    ActiveMenu->x = newX;
    ActiveMenu->y = newY;
    MenuOrigins [MenuDepth - 1].x = newX;
    MenuOrigins [MenuDepth - 1].y = newY;
}

/***********************************************************************
 *
 *  Procedure:
 *      DisplayPosition - display the position in the dimensions window
 *
 *  Inputs:
 *      tmp_win - the current twm window
 *      x, y    - position of the window
 *
 ***********************************************************************
 */

void DisplayPosition (tmp_win, x, y)
TwmWindow *tmp_win;
int x, y;
{
    char str [100];
    char signx = '+';
    char signy = '+';

    if (x < 0) {
	x = -x;
	signx = '-';
    }
    if (y < 0) {
	y = -y;
	signy = '-';
    }
    (void) sprintf (str, " %c%-4d %c%-4d ", signx, x, signy, y);
    XRaiseWindow (dpy, Scr->SizeWindow);

    Draw3DBorder (Scr->SizeWindow, 0, 0,
		Scr->SizeStringOffset + Scr->SizeStringWidth + SIZE_HINDENT,
		Scr->SizeFont.height + SIZE_VINDENT * 2,
		2, Scr->DefaultC, off, False, False);

#ifdef I18N
    FB(Scr->DefaultC.fore, Scr->DefaultC.back);
    XmbDrawImageString (dpy, Scr->SizeWindow, Scr->SizeFont.font_set,
			Scr->NormalGC, Scr->SizeStringOffset,
			Scr->SizeFont.ascent + SIZE_VINDENT , str, 13);
#else    
    FBF (Scr->DefaultC.fore, Scr->DefaultC.back, Scr->SizeFont.font->fid);
    XDrawImageString (dpy, Scr->SizeWindow, Scr->NormalGC,
		      Scr->SizeStringOffset,
		      Scr->SizeFont.font->ascent + SIZE_VINDENT,
		      str, 13);
#endif    
}

MosaicFade (w, width, height)
Window	w;
int	width, height;
{
    int		srect;
    int		i, j, usec, nrects;
    Pixmap	mask;
    GC		gc;
    XGCValues	gcv;
#ifdef VMS
    float  timeout;
#else
    struct timeval timeout;
#endif
    XRectangle *rectangles;

    srect = (width < height) ? (width / 20) : (height / 20);
    mask  = XCreatePixmap (dpy, w, width, height, 1);

    gcv.foreground = 1;
    gc = XCreateGC (dpy, mask, GCForeground, &gcv);
    XFillRectangle (dpy, mask, gc, 0, 0, width, height);
    gcv.function = GXclear;
    XChangeGC (dpy, gc, GCFunction, &gcv);

#ifdef VMS
    timeout = 0.010;
#else
    usec = 10000;
    timeout.tv_usec = usec % (unsigned long) 1000000;
    timeout.tv_sec  = usec / (unsigned long) 1000000;
#endif

    nrects = ((width * height) / (srect * srect)) / 10;
    rectangles = (XRectangle*) malloc (nrects * sizeof (XRectangle));
    for (j = 0; j < nrects; j++) {
	rectangles [j].width  = srect;
	rectangles [j].height = srect;
    }

    for (i = 0; i < 10; i++) {
	for (j = 0; j < nrects; j++) {
	    rectangles [j].x = ((lrand48 () %  width) / srect) * srect;
	    rectangles [j].y = ((lrand48 () % height) / srect) * srect;
	}
	XFillRectangles (dpy, mask, gc, rectangles, nrects);
	XShapeCombineMask (dpy, w, ShapeBounding, 0, 0, mask, ShapeSet);
	XFlush (dpy);
#ifdef VMS
        lib$wait(&timeout);
#else
	select (0, (void *) 0, (void *) 0, (void *) 0, &timeout);
#endif
    }
    XFreePixmap (dpy, mask);
    XFreeGC (dpy, gc);
    free (rectangles);
}

void packwindow (tmp_win, direction)
TwmWindow *tmp_win;
char *direction;
{
    int			cons, newx, newy;
    int			x, y, px, py, junkX, junkY;
    unsigned int	junkB, junkD, junkK;
    Window		junkW;

    if (!strcmp (direction,   "left")) {
	cons  = FindConstraint (tmp_win, J_LEFT);
	if (cons == -1) return;
    	newx  = cons;
	newy  = tmp_win->frame_y;
    } else
    if (!strcmp (direction,  "right")) {
	cons  = FindConstraint (tmp_win, J_RIGHT);
	if (cons == -1) return;
    	newx  = cons;
	newx -= tmp_win->frame_width  + 2 * tmp_win->frame_bw;
	newy  = tmp_win->frame_y;
    } else
    if (!strcmp (direction,    "top")) {
	cons  = FindConstraint (tmp_win, J_TOP);
	if (cons == -1) return;
	newx  = tmp_win->frame_x;
    	newy  = cons;
    } else
    if (!strcmp (direction, "bottom")) {
	cons  = FindConstraint (tmp_win, J_BOTTOM);
	if (cons == -1) return;
	newx  = tmp_win->frame_x;
    	newy  = cons;
	newy -= tmp_win->frame_height  + 2 * tmp_win->frame_bw;
    } else return;

    XQueryPointer (dpy, Scr->Root, &junkW, &junkW, &junkX, &junkY, &x, &y, &junkK);
    px = x - tmp_win->frame_x + newx;
    py = y - tmp_win->frame_y + newy;
    XWarpPointer (dpy, Scr->Root, Scr->Root, 0, 0, 0, 0, px, py);
    XRaiseWindow(dpy, tmp_win->frame);
    XMoveWindow (dpy, tmp_win->frame, newx, newy);
    SetupWindow (tmp_win, newx, newy, tmp_win->frame_width, tmp_win->frame_height, -1);
}

void fillwindow (tmp_win, direction)
TwmWindow *tmp_win;
char *direction;
{
    int	cons, newx, newy, neww, newh, save;
    int	x, y, i;
    int	winx = tmp_win->frame_x;
    int	winy = tmp_win->frame_y;
    int	winw = tmp_win->frame_width  + 2 * tmp_win->frame_bw;
    int	winh = tmp_win->frame_height + 2 * tmp_win->frame_bw;

    if (!strcmp (direction, "left")) {
	cons = FindConstraint (tmp_win, J_LEFT);
	if (cons == -1) return;
    	newx = cons;
	newy = tmp_win->frame_y;
	neww = winw + winx - newx;
	newh = winh;
	ConstrainSize (tmp_win, &neww, &newh);
    } else
    if (!strcmp (direction, "right")) {
	for (i = 0; i < 2; i++) {
	    cons = FindConstraint (tmp_win, J_RIGHT);
	    if (cons == -1) return;
    	    newx = tmp_win->frame_x;
	    newy = tmp_win->frame_y;
    	    neww = cons - winx;
	    newh = winh;
	    save = neww;
	    ConstrainSize (tmp_win, &neww, &newh);
	    if ((neww != winw) || (newh != winh) || (cons == Scr->MyDisplayWidth)) break;
	    neww = save;
	    SetupWindow (tmp_win, newx, newy, neww, newh, -1);
	}
    } else
    if (!strcmp (direction, "top")) {
	cons = FindConstraint (tmp_win, J_TOP);
	if (cons == -1) return;
    	newx = tmp_win->frame_x;
	newy = cons;
	neww = winw;
	newh = winh + winy - newy;
	ConstrainSize (tmp_win, &neww, &newh);
    } else
    if (!strcmp (direction, "bottom")) {
	for (i = 0; i < 2; i++) {
	    cons = FindConstraint (tmp_win, J_BOTTOM);
	    if (cons == -1) return;
    	    newx = tmp_win->frame_x;
	    newy = tmp_win->frame_y;
    	    neww = winw;
	    newh = cons - winy;
	    save = newh;
	    ConstrainSize (tmp_win, &neww, &newh);
	    if ((neww != winw) || (newh != winh) || (cons == Scr->MyDisplayHeight)) break;
	    newh = save;
	    SetupWindow (tmp_win, newx, newy, neww, newh, -1);
	}
    } else return;
    SetupWindow (tmp_win, newx, newy, neww, newh, -1);
}

int FindConstraint (tmp_win, direction)
TwmWindow *tmp_win;
int direction;
{
    TwmWindow	*t;
    int		w, h;
    int		winx = tmp_win->frame_x;
    int		winy = tmp_win->frame_y;
    int		winw = tmp_win->frame_width  + 2 * tmp_win->frame_bw;
    int		winh = tmp_win->frame_height + 2 * tmp_win->frame_bw;
    int 	ret;

    switch (direction) {
	case J_LEFT   : if (winx < 0) return -1;
			ret = 0; break;
	case J_RIGHT  : if (winx + winw > Scr->MyDisplayWidth) return -1;
			ret = Scr->MyDisplayWidth; break;
	case J_TOP    : if (winy < 0) return -1;
			ret = 0; break;
	case J_BOTTOM : if (winy + winh > Scr->MyDisplayHeight) return -1;
			ret = Scr->MyDisplayHeight; break;
	default       : return -1;
    }
    for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	if (t == tmp_win) continue;
	if (!OCCUPY (t, Scr->workSpaceMgr.activeWSPC)) continue;
	if (!t->mapped) continue;
	w = t->frame_width  + 2 * t->frame_bw;
	h = t->frame_height + 2 * t->frame_bw;

	switch (direction) {
	    case J_LEFT :
		if (winx        <= t->frame_x + w) continue;
		if (winy        >= t->frame_y + h) continue;
		if (winy + winh <= t->frame_y    ) continue;
		ret = MAX (ret, t->frame_x + w);
		break;
	    case J_RIGHT :
		if (winx + winw >= t->frame_x    ) continue;
		if (winy        >= t->frame_y + h) continue;
		if (winy + winh <= t->frame_y    ) continue;
		ret = MIN (ret, t->frame_x);
		break;
	    case J_TOP :
		if (winy        <= t->frame_y + h) continue;
		if (winx        >= t->frame_x + w) continue;
		if (winx + winw <= t->frame_x    ) continue;
		ret = MAX (ret, t->frame_y + h);
		break;
	    case J_BOTTOM :
		if (winy + winh >= t->frame_y    ) continue;
		if (winx        >= t->frame_x + w) continue;
		if (winx + winw <= t->frame_x    ) continue;
		ret = MIN (ret, t->frame_y);
		break;
	}
    }
    return ret;
}

void TryToPack (tmp_win, x, y)
TwmWindow *tmp_win;
int *x, *y;
{
    TwmWindow	*t;
    int		newx, newy;
    int		w, h;
    int		winw = tmp_win->frame_width  + 2 * tmp_win->frame_bw;
    int		winh = tmp_win->frame_height + 2 * tmp_win->frame_bw;

    newx = *x;
    newy = *y;
    for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	if (t == tmp_win) continue;
	if (!OCCUPY (t, Scr->workSpaceMgr.activeWSPC)) continue;
	if (!t->mapped) continue;

	w = t->frame_width  + 2 * t->frame_bw;
	h = t->frame_height + 2 * t->frame_bw;
	if (newx >= t->frame_x + w) continue;
	if (newy >= t->frame_y + h) continue;
	if (newx + winw <= t->frame_x) continue;
	if (newy + winh <= t->frame_y) continue;

	if (newx + Scr->MovePackResistance > t->frame_x + w) { /* left */
	    newx = MAX (newx, t->frame_x + w);
	    continue;
	}
	if (newx + winw < t->frame_x + Scr->MovePackResistance) { /* right */
	    newx = MIN (newx, t->frame_x - winw);
	    continue;
	}
	if (newy + Scr->MovePackResistance > t->frame_y + h) { /* top */
	    newy = MAX (newy, t->frame_y + h);
	    continue;
	}
	if (newy + winh < t->frame_y + Scr->MovePackResistance) { /* bottom */
	    newy = MIN (newy, t->frame_y - winh);
	    continue;
	}
    }
    *x = newx;
    *y = newy;
}

void TryToPush (tmp_win, x, y, dir)
TwmWindow *tmp_win;
int x, y, dir;
{
    TwmWindow	*t;
    int		newx, newy, ndir;
    Boolean	move;
    int		w, h;
    int		winw = tmp_win->frame_width  + 2 * tmp_win->frame_bw;
    int		winh = tmp_win->frame_height + 2 * tmp_win->frame_bw;

    for (t = Scr->TwmRoot.next; t != NULL; t = t->next) {
	if (t == tmp_win) continue;
	if (!OCCUPY (t, Scr->workSpaceMgr.activeWSPC)) continue;
	if (!t->mapped) continue;

	w = t->frame_width  + 2 * t->frame_bw;
	h = t->frame_height + 2 * t->frame_bw;
	if (x >= t->frame_x + w) continue;
	if (y >= t->frame_y + h) continue;
	if (x + winw <= t->frame_x) continue;
	if (y + winh <= t->frame_y) continue;

	move = False;
	if ((dir == 0 || dir == J_LEFT) &&
	    (x + Scr->MovePackResistance > t->frame_x + w)) {
	    newx = x - w;
	    newy = t->frame_y;
	    ndir = J_LEFT;
	    move = True;
	}
	else
	if ((dir == 0 || dir == J_RIGHT) &&
	   (x + winw < t->frame_x + Scr->MovePackResistance)) {
	    newx = x + winw;
	    newy = t->frame_y;
	    ndir = J_RIGHT;
	    move = True;
	}
	else
	if ((dir == 0 || dir == J_TOP) &&
	    (y + Scr->MovePackResistance > t->frame_y + h)) {
	    newx = t->frame_x;
	    newy = y - h;
	    ndir = J_TOP;
	    move = True;
	}
	else
	if ((dir == 0 || dir == J_BOTTOM) &&
	    (y + winh < t->frame_y + Scr->MovePackResistance)) {
	    newx = t->frame_x;
	    newy = y + winh;
	    ndir = J_BOTTOM;
	    move = True;
	}
	if (move) {
	    TryToPush (t, newx, newy, ndir);
	    TryToPack (t, &newx, &newy);
	    TryNotToMoveOff (t, &newx, &newy);
	    SetupWindow (t, newx, newy, t->frame_width, t->frame_height, -1);
	}
    }
}

void TryToGrid (tmp_win, x, y)
TwmWindow *tmp_win;
int *x, *y;
{
    int	w    = tmp_win->frame_width  + 2 * tmp_win->frame_bw;
    int	h    = tmp_win->frame_height + 2 * tmp_win->frame_bw;
    int	grav = ((tmp_win->hints.flags & PWinGravity) 
		      ? tmp_win->hints.win_gravity : NorthWestGravity);

    switch (grav) {
	case ForgetGravity :
	case StaticGravity :
	case NorthWestGravity :
	case NorthGravity :
	case WestGravity :
	case CenterGravity :
	    *x = (*x / Scr->XMoveGrid) * Scr->XMoveGrid;
	    *y = (*y / Scr->YMoveGrid) * Scr->YMoveGrid;
	    break;
	case NorthEastGravity :
	case EastGravity :
	    *x = (((*x + w) / Scr->XMoveGrid) * Scr->XMoveGrid) - w;
	    *y = (*y / Scr->YMoveGrid) * Scr->YMoveGrid;
	    break;
	case SouthWestGravity :
	case SouthGravity :
	    *x = (*x / Scr->XMoveGrid) * Scr->XMoveGrid;
	    *y = (((*y + h) / Scr->YMoveGrid) * Scr->YMoveGrid) - h;
	    break;
	case SouthEastGravity :
	    *x = (((*x + w) / Scr->XMoveGrid) * Scr->XMoveGrid) - w;
	    *y = (((*y + h) / Scr->YMoveGrid) * Scr->YMoveGrid) - h;
	    break;
    }
}

Boolean TryNotToMoveOff (tmp_win, x, y)
TwmWindow *tmp_win;
int *x, *y;
{
    int	w = tmp_win->frame_width  + 2 * tmp_win->frame_bw;
    int	h = tmp_win->frame_height + 2 * tmp_win->frame_bw;

    if ((*x < 0) &&
	((Scr->MoveOffResistance < 0) ||
	(*x > -Scr->MoveOffResistance))) {
	    *x = 0;
	    return False;
    }
    if (((*x + w) > Scr->MyDisplayWidth) &&
	((Scr->MoveOffResistance < 0) ||
	((*x + w) < Scr->MyDisplayWidth + Scr->MoveOffResistance))) {
	    *x = Scr->MyDisplayWidth - w;
	    return False;
    }
    if ((*y < 0) &&
	((Scr->MoveOffResistance < 0) ||
	(*y > -Scr->MoveOffResistance))) {
	    *y = 0;
	    return False;
    }
    if (((*y + h) > Scr->MyDisplayHeight) &&
	((Scr->MoveOffResistance < 0) ||
	((*y + h) < Scr->MyDisplayHeight + Scr->MoveOffResistance))) {
	    *y = Scr->MyDisplayHeight - h;
	    return False;
    }
    return (True);
}

WarpCursorToDefaultEntry (menu)
MenuRoot *menu;
{
    MenuItem	*item;
    Window	 root;
    int		 i, x, y, xl, yt;
    unsigned int w, h, bw, d;

    for (i = 0, item = menu->first; item != menu->last; item = item->next) {
	if (item == menu->defaultitem) break;
	i++;
     }
     if (!XGetGeometry (dpy, menu->w, &root, &x, &y, &w, &h, &bw, &d)) return 0;
     xl = x + (menu->width / 2);
     yt = y + (i + 0.5) * Scr->EntryHeight;
	
     XWarpPointer (dpy, Scr->Root, Scr->Root,
		   Event.xbutton.x_root, Event.xbutton.y_root,
		   menu->width, menu->height, xl, yt);
}
