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
 * $XConsortium: twm.c,v 1.124 91/05/08 11:01:54 dave Exp $
 *
 * twm - "Tom's Window Manager"
 *
 * 27-Oct-87 Thomas E. LaStrange	File created
 * 10-Oct-90 David M. Sternlicht        Storing saved colors on root
 *
 * Do the necessary modification to be integrated in ctwm.
 * Can no longer be used for the standard twm.
 *
 * 22-April-92 Claude Lecommandeur.
 *
 ***********************************************************************/

#ifndef SWITCHES
#	ifdef DEBUG
#		define _IDENTIFY(s,i)	"@(#) $Id:'" __FILE__ "'-[" __DATE__ "," __TIME__ "]-(\015\013\t\t" s "\015\013\t) DEBUG version" i "$"
#	else
#		define _IDENTIFY(s,i)	"@(#) $Id:'" __FILE__ "'-[" __DATE__ "," __TIME__ "]-(\015\013\t\t" s "\015\013\t)" i "$"
#	endif
#else
  /* SWITCHES contains the compiler name and the switches given to the compiler.	*/
#	define _IDENTIFY(s,i)	"@(#) '" __FILE__ "'-[" __DATE__ "," __TIME__ "]-(\015\013\t\t" s "\015\013\t)["SWITCHES"]"
#endif

#ifdef PROFILING
#	define __IDENTIFY(s,i)\
	static char *ident= _IDENTIFY(s,i);
#else
#	define __IDENTIFY(s,i)\
	static char *ident_stub(){ static char *ident= _IDENTIFY(s,i);\
		static char called=0;\
		if( !called){\
			called=1;\
			return(ident_stub());\
		}\
		else{\
			called= 0;\
			return(ident);\
		}}
#endif

#ifdef __GNUC__
#	define IDENTIFY(s)	__IDENTIFY(s," (gcc)")
#else
#	define IDENTIFY(s)	__IDENTIFY(s," (cc)")
#endif

IDENTIFY( "ctwm-3.5" );

#if defined(USE_SIGNALS) && defined(__sgi)
#  define _BSD_SIGNALS
#endif

#include <stdio.h>
#include <signal.h>

#ifdef __WAIT_FOR_CHILDS
#  include <sys/wait.h>
#endif

#ifdef VMS
#include <string.h>
#else
#include <fcntl.h>
#endif
#include "twm.h"
#include "add_window.h"
#include "gc.h"
#include "parse.h"
#include "version.h"
#include "menus.h"
#include "events.h"
#include "util.h"
#include "gram.h"
#include "screen.h"
#include "icons.h"
#include "iconmgr.h"

#if defined(__MACH__) || defined(__APPLE_CC__)
#	include <stdlib.h>
#endif

#ifdef VMS
#  include <stdlib.h>
#  include <decw$include/Xproto.h>
#  include <decw$include/Xatom.h>
#  include <X11Xmu/Error.h>
#  include "vms_cmd_services.h"

#  ifndef NO_LOCALE
#    include <locale.h>
#  endif /* NO_LOCALE */

#  ifndef PIXMAP_DIRECTORY
#    define PIXMAP_DIRECTORY "DECW$BITMAPS:"
#  endif
#else /* VMS */
#  include <X11/Xproto.h>
#  include <X11/Xatom.h>
#  include <X11/Xmu/Error.h>

#  ifdef X11R6
#    include <X11/SM/SMlib.h>
#  endif /* X11R6 */

#ifdef I18N
#include <X11/Xlocale.h>
#else
#  ifndef NO_LOCALE
#    include <locale.h>
#  endif /* NO_LOCALE */
#endif

#  ifndef PIXMAP_DIRECTORY
#    define PIXMAP_DIRECTORY "/usr/lib/X11/twm"
#  endif /* PIXMAP_DIRECTORY */
#endif /* VMS */

#  ifdef X11R6
XtAppContext appContext;	/* Xt application context */
#endif /* X11R6 */

Display *dpy;			/* which display are we talking to */
#ifdef USEM4
char *display_name = NULL;      /* JMO 2/13/90 for m4 */
int KeepTmpFile = False;        /* JMO 3/28/90 for m4 */
int GoThroughM4 = False;
#endif
Window ResizeWindow;		/* the window we are resizing */

int  captive      = FALSE;
char *captivename = NULL;

int MultiScreen = TRUE;		/* try for more than one screen? */
int Monochrome  = FALSE;	/* Force monochrome, for testing purpose */
int NumScreens;			/* number of screens in ScreenList */
int HasShape;			/* server supports shape extension? */
int ShapeEventBase, ShapeErrorBase;
ScreenInfo **ScreenList;	/* structures for each screen */
ScreenInfo *Scr = NULL;		/* the cur and prev screens */
int PreviousScreen;		/* last screen that we were on */
int FirstScreen;		/* TRUE ==> first screen of display */
Bool PrintErrorMessages = False;	/* controls error messages */
Bool ShowWelcomeWindow = True;
static int RedirectError;	/* TRUE ==> another window manager running */
static int CatchRedirectError();	/* for settting RedirectError */
static int TwmErrorHandler();	/* for everything else */
char Info[INFO_LINES][INFO_SIZE];		/* info strings to print */
int InfoLines,InfoWidth,InfoHeight;
char *InitFile = NULL;
static Window CreateRootWindow ();
static void DisplayInfo ();
int InternUsefulAtoms ();
int InitVariables();
int CreateFonts();

Cursor	UpperLeftCursor;
Cursor	TopRightCursor,
	TopLeftCursor,
	BottomRightCursor,
	BottomLeftCursor,
	LeftCursor,
	RightCursor,
	TopCursor,
	BottomCursor;
       
Cursor RightButt;
Cursor MiddleButt;
Cursor LeftButt;

XContext TwmContext;		/* context for twm windows */
XContext MenuContext;		/* context for all menu windows */
XContext IconManagerContext;	/* context for all window list windows */
XContext ScreenContext;		/* context to get screen data */
XContext ColormapContext;	/* context for colormap operations */

XClassHint NoClass;		/* for applications with no class */

XGCValues Gcv;

char *Home;			/* the HOME environment variable */
int HomeLen;			/* length of Home */
int ParseError;			/* error parsing the .twmrc file */

int HandlingEvents = FALSE;	/* are we handling events yet? */

Window JunkRoot;		/* junk window */
Window JunkChild;		/* junk window */
int JunkX;			/* junk variable */
int JunkY;			/* junk variable */
unsigned int JunkWidth, JunkHeight, JunkBW, JunkDepth, JunkMask;

char *ProgramName;
int Argc;
char **Argv;
#ifndef VMS
char **Environ;
#endif

Bool RestartPreviousState = False;	/* try to restart in previous state */
#ifdef NOTRAP
Bool TrapExceptions = False;
#else
Bool TrapExceptions = True;
#endif

unsigned long black, white;

extern void assign_var_savecolor();
SIGNAL_T Restart(int sig);
SIGNAL_T Crash(int sig);
#ifdef __WAIT_FOR_CHILDS
  SIGNAL_T ChildExit();
#endif

extern Atom _XA_WM_WORKSPACESLIST;

/***********************************************************************
 *
 *  Procedure:
 *	main - start of twm
 *
 ***********************************************************************
 */

#ifdef VMS
main(int argc, char **argv)
#else
main(argc, argv, environ)
    int argc;
    char **argv;
    char **environ;
#endif
{
    Window root, parent, *children;
    unsigned int nchildren;
    int i, j;
    char *display_name = NULL;
    unsigned long valuemask;	/* mask for create windows */
    XSetWindowAttributes attributes;	/* attributes for create windows */
    int numManaged, firstscrn, lastscrn, scrnum;
    extern ColormapWindow *CreateColormapWindow();
#ifdef X11R6
    int zero = 0;
    char *restore_filename = NULL;
    char *client_id = NULL;
#endif
    char *welcomefile;
    int  screenmasked;
    static int rootx = 100;
    static int rooty = 100;
    static unsigned int rootw = 800;
    static unsigned int rooth = 500;
    Window capwin = (Window) 0;
    IconRegion *ir;

#ifdef I18N
    XRectangle ink_rect;
    XRectangle logical_rect;

    (void)setlocale(LC_ALL, "");
    
#else    
#ifndef NO_LOCALE
    (void)setlocale(LC_ALL, NULL);
#endif
#endif    

#ifdef VMS
#if 0
    vms_do_init();
#endif
	{
        char *ep;
        ProgramName = strrchr(argv[0], ']');
        ProgramName++;
        ep = strchr(ProgramName, '.');
        if (ep != NULL) *ep = '\0';
	}
    Argc = argc;
    Argv = argv;
    initRun(ProgramName);
#else
    ProgramName = argv[0];
    Argc = argc;
    Argv = argv;
    Environ = environ;
#endif

    for (i = 1; i < argc; i++) {
	if (argv[i][0] == '-') {
	    switch (argv[i][1]) {
	      case 'd':				/* -display dpy */
		if (++i >= argc) goto usage;
		display_name = argv[i];
		continue;
	      case 's':				/* -single */
		MultiScreen = FALSE;
		continue;
	      case 'f':				/* -file twmrcfilename */
		if (++i >= argc) goto usage;
		InitFile = argv[i];
		continue;
	      case 'm':				/* -mono */
		if (strcmp(argv[i],"-mono")) goto usage;
		Monochrome = TRUE;
		continue;
	      case 'v':				/* -verbose */
		if (!strcmp(argv[i],"-version")) {
		    (void) printf ("%s\n", VersionNumber);
		    exit (0);
		}
		PrintErrorMessages = True;
		continue;
#ifdef X11R6
	      case 'c':				/* -clientId */
		if (++i >= argc) goto usage;
		client_id = argv[i];
		continue;
	      case 'r':				/* -restore */
		if (++i >= argc) goto usage;
		restore_filename = argv[i];
		continue;
#endif
	      case 'q':				/* -quiet */
		PrintErrorMessages = False;
		continue;
	      case 'W':				/* -nowelcome */
		ShowWelcomeWindow = False;
		continue;
	      case 'w':				/* -window */
		captive     = True;
		MultiScreen = False;
		if ((i + 1) >= argc) continue;
		if (*(argv [i + 1]) == '-') continue;
		if (sscanf (argv [i + 1], "%x", &capwin) != 1) continue;
		i++;
		continue;
	      case 'k':				/* -keep m4 tmp file */
#ifdef USEM4
		KeepTmpFile = True;
		continue;
#else
		continue;
#endif
	      case 'n':				/* -don't preprocess through m4 */
#ifdef USEM4
		if (!strcmp(argv[i],"-name")) {
		    if (++i >= argc) goto usage;
		    captivename = argv[i];
		    continue;
		}
		GoThroughM4 = !GoThroughM4;
		continue;
#else
		continue;
#endif
	      case 'x':				/* -xrm resource */
		if (strcmp(argv[i],"-xrm")) goto usage;
		if (++i >= argc) goto usage;
		continue;
	      case 'i':
		if (!strcmp(argv[i],"-info")) {
		    DisplayInfo ();
		    exit (0);
		}
		goto usage;
	    }
	}
      usage:
	fprintf (stderr, "usage: %s [-display dpy] [-version] [-info]", ProgramName);
#ifdef USEM4
	fprintf (stderr, " [-f file] [-s] [-q] [-v] [-W] [-w [wid]] [-k] [-n]\n");
#else
	fprintf (stderr, " [-f file] [-s] [-q] [-v] [-W] [-w [wid]]\n");
#endif
	exit (1);
    }

#define newhandler(sig, action) \
    if (signal (sig, SIG_IGN) != SIG_IGN) (void) signal (sig, action)

    newhandler (SIGINT, Done);
    newhandler (SIGHUP, Restart);
    newhandler (SIGQUIT, Done);
    newhandler (SIGTERM, Done);
#ifdef __WAIT_FOR_CHILDS
    newhandler (SIGCHLD, ChildExit);
#endif
    signal (SIGALRM, SIG_IGN);
    { char *c= getenv( "CTWM_TRAP_EXCEPTIONS");
	    if( c ){
		    if( strcasecmp( c, "yes")== 0 || strcasecmp( c, "true")== 0 || atoi(c) ){
			    fprintf( stderr, "CTWM_TRAP_EXCEPTIONS=%s: trapping bus error and segv\n", c );
			    TrapExceptions= True;
		    }
		    else{
			    fprintf( stderr, "CTWM_TRAP_EXCEPTIONS=%s: NOT trapping bus error and segv\n", c );
			    TrapExceptions= False;
		    }
	    }
    }
    if (TrapExceptions) {
	signal (SIGSEGV, Crash);
	signal (SIGBUS,  Crash);
    }

#undef newhandler

    Home = getenv("HOME");
    if (Home == NULL)
#ifdef VMS
        Home = "[]";
#else
	Home = "./";
#endif

    HomeLen = strlen(Home);

    NoClass.res_name = NoName;
    NoClass.res_class = NoName;

#ifdef X11R6
    XtToolkitInitialize ();
    appContext = XtCreateApplicationContext ();

    if (!(dpy = XtOpenDisplay (appContext, display_name, "twm", "twm",
	NULL, 0, &zero, NULL))) {
#else

    if (!(dpy = XOpenDisplay(display_name))) {
#endif
	fprintf (stderr, "%s:  unable to open display \"%s\"\n",
		 ProgramName, XDisplayName(display_name));
	exit (1);
    }

#ifndef VMS
    if (fcntl(ConnectionNumber(dpy), F_SETFD, 1) == -1) {
	fprintf (stderr, 
		 "%s:  unable to mark display connection as close-on-exec\n",
		 ProgramName);
	exit (1);
    }
#endif
#ifdef X11R6
    if (restore_filename) ReadWinConfigFile (restore_filename);
#endif
    HasShape = XShapeQueryExtension (dpy, &ShapeEventBase, &ShapeErrorBase);
    TwmContext = XUniqueContext();
    MenuContext = XUniqueContext();
    IconManagerContext = XUniqueContext();
    ScreenContext = XUniqueContext();
    ColormapContext = XUniqueContext();

    InternUsefulAtoms ();


    /* Set up the per-screen global information. */

    NumScreens = ScreenCount(dpy);

    if (MultiScreen)
    {
	firstscrn = 0;
	lastscrn = NumScreens - 1;
    }
    else
    {
	firstscrn = lastscrn = DefaultScreen(dpy);
    }

    InfoLines = 0;

    /* for simplicity, always allocate NumScreens ScreenInfo struct pointers */
    ScreenList = (ScreenInfo **) calloc (NumScreens, sizeof (ScreenInfo *));
    if (ScreenList == NULL)
    {
	fprintf (stderr, "%s: Unable to allocate memory for screen list, exiting.\n",
		 ProgramName);
	exit (1);
    }
    numManaged = 0;
    PreviousScreen = DefaultScreen(dpy);
    FirstScreen = TRUE;
    for (scrnum = firstscrn ; scrnum <= lastscrn; scrnum++)
    {
	if (captive) {
	    XWindowAttributes wa;
	    if (capwin && XGetWindowAttributes (dpy, capwin, &wa)) {
		Window junk;

		root  = capwin;
		rootw = wa.width;
		rooth = wa.height;
		XTranslateCoordinates (dpy, capwin, wa.root, 0, 0, &rootx, &rooty, &junk);
	    }
	    else {
		root = CreateRootWindow (rootx, rooty, rootw, rooth);
	    }
	}
	else {
	    root = RootWindow (dpy, scrnum);
	}

        /* Make sure property priority colors is empty */
        XChangeProperty (dpy, root, _XA_MIT_PRIORITY_COLORS,
			 XA_CARDINAL, 32, PropModeReplace, NULL, 0);
	XSync(dpy, 0); /* Flush possible previous errors */
	RedirectError = FALSE;
	XSetErrorHandler(CatchRedirectError);
	if (captive) 
	    XSelectInput(dpy, root,
		ColormapChangeMask | EnterWindowMask | PropertyChangeMask | 
		SubstructureRedirectMask | KeyPressMask |
		ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);
	else
	    XSelectInput(dpy, root,
		ColormapChangeMask | EnterWindowMask | PropertyChangeMask | 
		SubstructureRedirectMask | KeyPressMask |
		ButtonPressMask | ButtonReleaseMask);
	XSync(dpy, 0);
	XSetErrorHandler(TwmErrorHandler);

	if (RedirectError)
	{
	    fprintf (stderr, "%s:  another window manager is already running",
		     ProgramName);
	    if (MultiScreen && NumScreens > 0)
		fprintf(stderr, " on screen %d?\n", scrnum);
	    else
		fprintf(stderr, "?\n");
	    continue;
	}

	numManaged ++;

	/* Note:  ScreenInfo struct is calloc'ed to initialize to zero. */
	Scr = ScreenList[scrnum] = 
	    (ScreenInfo *) calloc(1, sizeof(ScreenInfo));
  	if (Scr == NULL)
  	{
  	    fprintf (stderr, "%s: unable to allocate memory for ScreenInfo structure for screen %d.\n",
  		     ProgramName, scrnum);
  	    continue;
  	}

	/* initialize list pointers, remember to put an initialization
	 * in InitVariables also
	 */
	Scr->BorderColorL = NULL;
	Scr->IconBorderColorL = NULL;
	Scr->BorderTileForegroundL = NULL;
	Scr->BorderTileBackgroundL = NULL;
	Scr->TitleForegroundL = NULL;
	Scr->TitleBackgroundL = NULL;
	Scr->IconForegroundL = NULL;
	Scr->IconBackgroundL = NULL;
	Scr->NoBorder = NULL;
	Scr->NoIconTitle = NULL;
	Scr->NoTitle = NULL;
	Scr->OccupyAll = NULL;
	Scr->UnmapByMovingFarAway = NULL;
	Scr->DontSetInactive = NULL;
	Scr->AutoSqueeze = NULL;
	Scr->StartSqueezed = NULL;
	Scr->MakeTitle = NULL;
	Scr->AutoRaise = NULL;
	Scr->IconNames = NULL;
	Scr->NoHighlight = NULL;
	Scr->NoStackModeL = NULL;
	Scr->AlwaysOnTopL = NULL;
	Scr->NoTitleHighlight = NULL;
	Scr->DontIconify = NULL;
	Scr->IconMgrNoShow = NULL;
	Scr->IconMgrShow = NULL;
	Scr->IconifyByUn = NULL;
	Scr->IconManagerFL = NULL;
	Scr->IconManagerBL = NULL;
	Scr->IconMgrs = NULL;
	Scr->StartIconified = NULL;
	Scr->SqueezeTitleL = NULL;
	Scr->DontSqueezeTitleL = NULL;
	Scr->WindowRingL = NULL;
	Scr->WarpCursorL = NULL;
	Scr->OpaqueMoveList = NULL;
	Scr->NoOpaqueMoveList = NULL;
	Scr->OpaqueResizeList = NULL;
	Scr->NoOpaqueResizeList = NULL;
	Scr->ImageCache = NULL;
	Scr->HighlightPixmapName = NULL;
	Scr->Workspaces = (MenuRoot*) 0;


	/* remember to put an initialization in InitVariables also
	 */

	Scr->screen = scrnum;
	Scr->d_depth = DefaultDepth(dpy, scrnum);
	Scr->d_visual = DefaultVisual(dpy, scrnum);
	Scr->Root = root;
	XSaveContext (dpy, Scr->Root, ScreenContext, (XPointer) Scr);
	if (captive) {
	    AddToCaptiveList ();
	    if (captivename) {
		XSetStandardProperties (dpy, root, captivename, captivename,
				None, NULL, 0, NULL);
	    }
	} else {
	    captivename = "Root";
	}
	Scr->TwmRoot.cmaps.number_cwins = 1;
	Scr->TwmRoot.cmaps.cwins =
		(ColormapWindow **) malloc(sizeof(ColormapWindow *));
	Scr->TwmRoot.cmaps.cwins[0] =
		CreateColormapWindow(Scr->Root, True, False);
	Scr->TwmRoot.cmaps.cwins[0]->visibility = VisibilityPartiallyObscured;

	Scr->cmapInfo.cmaps = NULL;
	Scr->cmapInfo.maxCmaps =
		MaxCmapsOfScreen(ScreenOfDisplay(dpy, Scr->screen));
	Scr->cmapInfo.root_pushes = 0;
	InstallWindowColormaps(0, &Scr->TwmRoot);

	Scr->StdCmapInfo.head = Scr->StdCmapInfo.tail = 
	  Scr->StdCmapInfo.mru = NULL;
	Scr->StdCmapInfo.mruindex = 0;
	LocateStandardColormaps();

	Scr->TBInfo.nleft = Scr->TBInfo.nright = 0;
	Scr->TBInfo.head = NULL;
	Scr->TBInfo.border = -100; /* trick to have different default value if ThreeDTitles
					is set or not */
	Scr->TBInfo.width = 0;
	Scr->TBInfo.leftx = 0;
	Scr->TBInfo.titlex = 0;

	if (captive) {
	    Scr->MyDisplayX      = rootx;
	    Scr->MyDisplayY      = rooty;
	    Scr->MyDisplayWidth  = rootw;
	    Scr->MyDisplayHeight = rooth;
	}
	else {
	    Scr->MyDisplayX      = 0;
	    Scr->MyDisplayY      = 0;
	    Scr->MyDisplayWidth  = DisplayWidth(dpy, scrnum);
	    Scr->MyDisplayHeight = DisplayHeight(dpy, scrnum);
	}

	Scr->MaxWindowWidth = 32767 - Scr->MyDisplayWidth;
	Scr->MaxWindowHeight = 32767 - Scr->MyDisplayHeight;

	Scr->XORvalue = (((unsigned long) 1) << Scr->d_depth) - 1;

	if (Monochrome || DisplayCells(dpy, scrnum) < 3)
	    Scr->Monochrome = MONOCHROME;
	else
	    Scr->Monochrome = COLOR;

	/* setup default colors */
	Scr->FirstTime = TRUE;
	GetColor(Scr->Monochrome, &black, "black");
	Scr->Black = black;
	GetColor(Scr->Monochrome, &white, "white");
	Scr->White = white;

	if (FirstScreen)
	{
	    SetFocus ((TwmWindow *)NULL, CurrentTime);

	    /* define cursors */

	    NewFontCursor(&TopLeftCursor, "top_left_corner");
	    NewFontCursor(&TopRightCursor, "top_right_corner");
	    NewFontCursor(&BottomLeftCursor, "bottom_left_corner");
	    NewFontCursor(&BottomRightCursor, "bottom_right_corner");
	    NewFontCursor(&LeftCursor, "left_side");
	    NewFontCursor(&RightCursor, "right_side");
	    NewFontCursor(&TopCursor, "top_side");
	    NewFontCursor(&BottomCursor, "bottom_side");

	    NewFontCursor(&UpperLeftCursor, "top_left_corner");
	    NewFontCursor(&RightButt, "rightbutton");
	    NewFontCursor(&LeftButt, "leftbutton");
	    NewFontCursor(&MiddleButt, "middlebutton");
	}

	Scr->iconmgr = NULL;
	AllocateIconManager ("TWM", "Icons", "", 1);

	Scr->IconDirectory = NULL;
	Scr->PixmapDirectory = PIXMAP_DIRECTORY;
	Scr->siconifyPm = None;
	Scr->pullPm = None;
	Scr->tbpm.xlogo = None;
	Scr->tbpm.resize = None;
	Scr->tbpm.question = None;
	Scr->tbpm.menu = None;
	Scr->tbpm.delete = None;

	Scr->WindowMask = (Window) 0;
	screenmasked = 0;
	if (ShowWelcomeWindow && (welcomefile = getenv ("CTWM_WELCOME_FILE"))) {
	    screenmasked = 1;
	    MaskScreen (welcomefile);
	}
	InitVariables();
	InitMenus();
	InitWorkSpaceManager ();

	/* Parse it once for each screen. */
	ParseTwmrc(InitFile);
	if (ShowWelcomeWindow && ! screenmasked) MaskScreen (NULL);
	if (Scr->ClickToFocus) {
	    Scr->FocusRoot  = FALSE;
	    Scr->TitleFocus = FALSE;
	}
	ConfigureWorkSpaceManager ();

	if (Scr->use3Dtitles) {
	    if (Scr->FramePadding  == -100) Scr->FramePadding  = 0;
	    if (Scr->TitlePadding  == -100) Scr->TitlePadding  = 0;
	    if (Scr->ButtonIndent  == -100) Scr->ButtonIndent  = 0;
	    if (Scr->TBInfo.border == -100) Scr->TBInfo.border = 0;
	}
	else {
	    if (Scr->FramePadding  == -100) Scr->FramePadding  = 2; /* values that look */
	    if (Scr->TitlePadding  == -100) Scr->TitlePadding  = 8; /* "nice" on */
	    if (Scr->ButtonIndent  == -100) Scr->ButtonIndent  = 1; /* 75 and 100dpi displays */
	    if (Scr->TBInfo.border == -100) Scr->TBInfo.border = 1;
	    Scr->TitleShadowDepth	= 0;
	    Scr->TitleButtonShadowDepth	= 0;
	}
	if (! Scr->use3Dborders)	Scr->BorderShadowDepth = 0;
	if (! Scr->use3Dmenus)		Scr->MenuShadowDepth = 0;
	if (! Scr->use3Diconmanagers)	Scr->IconManagerShadowDepth = 0;

	if (Scr->use3Dtitles  && !Scr->BeNiceToColormap) GetShadeColors (&Scr->TitleC);
	if (Scr->use3Dmenus   && !Scr->BeNiceToColormap) GetShadeColors (&Scr->MenuC);
	if (Scr->use3Dmenus   && !Scr->BeNiceToColormap) GetShadeColors (&Scr->MenuTitleC);
	if (Scr->use3Dborders && !Scr->BeNiceToColormap) GetShadeColors (&Scr->BorderColorC);
	if (! Scr->use3Dborders) Scr->ThreeDBorderWidth = 0;

        for (ir = Scr->FirstRegion; ir; ir = ir->next) {
	    if (ir->TitleJustification == J_UNDEF)
		ir->TitleJustification = Scr->IconJustification;
	    if (ir->Justification == J_UNDEF)
		ir->Justification = Scr->IconRegionJustification;
	    if (ir->Alignement == J_UNDEF)
		ir->Alignement = Scr->IconRegionAlignement;
	}

	assign_var_savecolor(); /* storeing pixels for twmrc "entities" */
	if (Scr->SqueezeTitle == -1) Scr->SqueezeTitle = FALSE;
	if (!Scr->HaveFonts) CreateFonts();
	CreateGCs();
	MakeMenus();

	Scr->TitleBarFont.y += Scr->FramePadding;
	Scr->TitleHeight = Scr->TitleBarFont.height + Scr->FramePadding * 2;
	if (Scr->use3Dtitles) Scr->TitleHeight += 2 * Scr->TitleShadowDepth;
	/* make title height be odd so buttons look nice and centered */
	if (!(Scr->TitleHeight & 1)) Scr->TitleHeight++;

	InitTitlebarButtons ();		/* menus are now loaded! */

	XGrabServer(dpy);
	XSync(dpy, 0);

	JunkX = 0;
	JunkY = 0;

	CreateWindowRegions ();
	AllocateOthersIconManagers ();
	CreateIconManagers();
	CreateWorkSpaceManager ();
	MakeWorkspacesMenu ();

	XQueryTree(dpy, Scr->Root, &root, &parent, &children, &nchildren);
	/*
	 * weed out icon windows
	 */
	for (i = 0; i < nchildren; i++) {
	    if (children[i]) {
		XWMHints *wmhintsp = XGetWMHints (dpy, children[i]);

		if (wmhintsp) {
		    if (wmhintsp->flags & IconWindowHint) {
			for (j = 0; j < nchildren; j++) {
			    if (children[j] == wmhintsp->icon_window) {
				children[j] = None;
				break;
			    }
			}
		    }
		    XFree ((char *) wmhintsp);
		}
	    }
	}

	/*
	 * map all of the non-override windows
	 */
	for (i = 0; i < nchildren; i++)
	{
	    if (children[i] && MappedNotOverride(children[i]))
	    {
		XUnmapWindow(dpy, children[i]);
		SimulateMapRequest(children[i]);
	    }
	}
	if (Scr->ShowWorkspaceManager && Scr->workSpaceManagerActive)
	{
	    if (Scr->WindowMask) XRaiseWindow (dpy, Scr->WindowMask);
	    SetMapStateProp (Scr->workSpaceMgr.workspaceWindow.twm_win, NormalState);
	    XMapWindow (dpy, Scr->workSpaceMgr.workspaceWindow.twm_win->frame);
	    if (Scr->workSpaceMgr.workspaceWindow.twm_win->StartSqueezed)
		Squeeze (Scr->workSpaceMgr.workspaceWindow.twm_win);
	    else
		XMapWindow (dpy, Scr->workSpaceMgr.workspaceWindow.w);
	    Scr->workSpaceMgr.workspaceWindow.twm_win->mapped = TRUE;
	}
	
	if (!Scr->BeNiceToColormap) GetShadeColors (&Scr->DefaultC);
	attributes.border_pixel = Scr->DefaultC.fore;
	attributes.background_pixel = Scr->DefaultC.back;
	attributes.event_mask = (ExposureMask | ButtonPressMask |
				 KeyPressMask | ButtonReleaseMask);
	attributes.backing_store = NotUseful;
	attributes.cursor = XCreateFontCursor (dpy, XC_hand2);
	valuemask = (CWBorderPixel | CWBackPixel | CWEventMask | 
		     CWBackingStore | CWCursor);
	Scr->InfoWindow = XCreateWindow (dpy, Scr->Root, 0, 0, 
					 (unsigned int) 5, (unsigned int) 5,
					 (unsigned int) 0, 0,
					 (unsigned int) CopyFromParent,
					 (Visual *) CopyFromParent,
					 valuemask, &attributes);

#ifdef I18N
	XmbTextExtents(Scr->SizeFont.font_set,
		       " 8888 x 8888 ", 13,
		       &ink_rect, &logical_rect);
	Scr->SizeStringWidth = logical_rect.width;
#else	
	Scr->SizeStringWidth = XTextWidth (Scr->SizeFont.font,
					   " 8888 x 8888 ", 13);
#endif	
	valuemask = (CWBorderPixel | CWBackPixel | CWBitGravity);
	attributes.bit_gravity = NorthWestGravity;

	{
	    int sx, sy;
	    if (Scr->CenterFeedbackWindow) {
		sx = (Scr->MyDisplayWidth  / 2) - (Scr->SizeStringWidth / 2);
		sy = (Scr->MyDisplayHeight / 2) - ((Scr->SizeFont.height + SIZE_VINDENT*2) / 2);
		attributes.save_under = True;
		valuemask |= CWSaveUnder;
	    } else {
		sx = 0;
		sy = 0;
	    }
	    Scr->SizeWindow = XCreateWindow (dpy, Scr->Root, sx, sy, 
					 (unsigned int) Scr->SizeStringWidth,
					 (unsigned int) (Scr->SizeFont.height +
							 SIZE_VINDENT*2),
					 (unsigned int) 0, 0,
					 (unsigned int) CopyFromParent,
					 (Visual *) CopyFromParent,
					 valuemask, &attributes);
	}
	Scr->ShapeWindow = XCreateSimpleWindow (dpy, Scr->Root, 0, 0, Scr->MyDisplayWidth,
				Scr->MyDisplayHeight, 0, 0, 0);

	XUngrabServer(dpy);
	if (ShowWelcomeWindow) UnmaskScreen ();

#ifdef _HAVE_XINERAMA_
	{ int event_base, error_base;
		if( XineramaQueryExtension( dpy, &event_base, &error_base ) ){
			Scr->HeadInfo= XineramaQueryScreens( dpy, &Scr->NumHeads );
		}
	}
#endif

	FirstScreen = FALSE;
    	Scr->FirstTime = FALSE;
    } /* for */

    if (numManaged == 0) {
	if (MultiScreen && NumScreens > 0)
	  fprintf (stderr, "%s:  unable to find any unmanaged screens\n",
		   ProgramName);
	exit (1);
    }
#ifdef X11R6
    (void) ConnectToSessionManager (client_id);
#endif
#ifdef SOUNDS
    play_startup_sound();
#endif


#if defined(__MACH__) || defined(__APPLE_CC__)
	unsetenv( "MallocBadFreeAbort" );
	unsetenv( "MallocGuardEdges" );
	unsetenv( "MallocScribble" );
#endif

    RestartPreviousState = True;
    HandlingEvents = TRUE;
    InitEvents();
    StartAnimation ();
    HandleEvents();
    return (0);
}

/***********************************************************************
 *
 *  Procedure:
 *	InitVariables - initialize twm variables
 *
 ***********************************************************************
 */

InitVariables()
{
    FreeList(&Scr->BorderColorL);
    FreeList(&Scr->IconBorderColorL);
    FreeList(&Scr->BorderTileForegroundL);
    FreeList(&Scr->BorderTileBackgroundL);
    FreeList(&Scr->TitleForegroundL);
    FreeList(&Scr->TitleBackgroundL);
    FreeList(&Scr->IconForegroundL);
    FreeList(&Scr->IconBackgroundL);
    FreeList(&Scr->IconManagerFL);
    FreeList(&Scr->IconManagerBL);
    FreeList(&Scr->IconMgrs);
    FreeList(&Scr->NoBorder);
    FreeList(&Scr->NoIconTitle);
    FreeList(&Scr->NoTitle);
    FreeList(&Scr->OccupyAll);
    FreeList(&Scr->MakeTitle);
    FreeList(&Scr->AutoRaise);
    FreeList(&Scr->IconNames);
    FreeList(&Scr->NoHighlight);
    FreeList(&Scr->NoStackModeL);
    FreeList(&Scr->AlwaysOnTopL);
    FreeList(&Scr->NoTitleHighlight);
    FreeList(&Scr->DontIconify);
    FreeList(&Scr->IconMgrNoShow);
    FreeList(&Scr->IconMgrShow);
    FreeList(&Scr->IconifyByUn);
    FreeList(&Scr->StartIconified);
    FreeList(&Scr->IconManagerHighlightL);
    FreeList(&Scr->SqueezeTitleL);
    FreeList(&Scr->DontSqueezeTitleL);
    FreeList(&Scr->WindowRingL);
    FreeList(&Scr->WarpCursorL);
    FreeList(&Scr->UnmapByMovingFarAway);
    FreeList(&Scr->DontSetInactive);
    FreeList(&Scr->AutoSqueeze);
    FreeList(&Scr->StartSqueezed);

    NewFontCursor(&Scr->FrameCursor, "top_left_arrow");
    NewFontCursor(&Scr->TitleCursor, "top_left_arrow");
    NewFontCursor(&Scr->IconCursor, "top_left_arrow");
    NewFontCursor(&Scr->IconMgrCursor, "top_left_arrow");
    NewFontCursor(&Scr->MoveCursor, "fleur");
    NewFontCursor(&Scr->ResizeCursor, "fleur");
    NewFontCursor(&Scr->MenuCursor, "sb_left_arrow");
    NewFontCursor(&Scr->ButtonCursor, "hand2");
    NewFontCursor(&Scr->WaitCursor, "watch");
    NewFontCursor(&Scr->SelectCursor, "dot");
    NewFontCursor(&Scr->DestroyCursor, "pirate");
    NewFontCursor(&Scr->AlterCursor, "question_arrow");

    Scr->workSpaceManagerActive = FALSE;
    Scr->Ring = NULL;
    Scr->RingLeader = NULL;

    Scr->DefaultC.fore = black;
    Scr->DefaultC.back = white;
    Scr->BorderColorC.fore = white;
    Scr->BorderColorC.back = black;
    Scr->BorderTileC.fore = black;
    Scr->BorderTileC.back = white;
    Scr->TitleC.fore = black;
    Scr->TitleC.back = white;
    Scr->MenuC.fore = black;
    Scr->MenuC.back = white;
    Scr->MenuTitleC.fore = black;
    Scr->MenuTitleC.back = white;
    Scr->MenuShadowColor = black;
    Scr->IconC.fore = black;
    Scr->IconC.back = white;
    Scr->IconBorderColor = black;
    Scr->IconManagerC.fore = black;
    Scr->IconManagerC.back = white;
    Scr->IconManagerHighlight = black;

    Scr->FramePadding = -100;	/* trick to have different default value if ThreeDTitles
				is set or not */
    Scr->TitlePadding = -100;
    Scr->ButtonIndent = -100;
    Scr->SizeStringOffset = 0;
    Scr->ThreeDBorderWidth = 6;
    Scr->BorderWidth = BW;
    Scr->IconBorderWidth = BW;
    Scr->NumAutoRaises = 0;
    Scr->TransientOnTop = 30;
    Scr->NoDefaults = FALSE;
    Scr->UsePPosition = PPOS_OFF;
    Scr->UseSunkTitlePixmap = FALSE;
    Scr->FocusRoot = TRUE;
    Scr->Focus = NULL;
    Scr->WarpCursor = FALSE;
    Scr->ForceIcon = FALSE;
    Scr->NoGrabServer = FALSE;
    Scr->NoRaiseMove = FALSE;
    Scr->NoRaiseResize = FALSE;
    Scr->NoRaiseDeicon = FALSE;
    Scr->NoRaiseWarp = FALSE;
    Scr->DontMoveOff = FALSE;
    Scr->DoZoom = FALSE;
    Scr->TitleFocus = TRUE;
    Scr->IconManagerFocus = TRUE;
    Scr->StayUpMenus = FALSE;
    Scr->WarpToDefaultMenuEntry = FALSE;
    Scr->ClickToFocus = FALSE;
    Scr->NoIconTitlebar = FALSE;
    Scr->NoTitlebar = FALSE;
    Scr->DecorateTransients = FALSE;
    Scr->IconifyByUnmapping = FALSE;
    Scr->ShowIconManager = FALSE;
    Scr->ShowWorkspaceManager = FALSE;
    Scr->WMgrButtonShadowDepth = 2;
    Scr->WMgrVertButtonIndent  = 5;
    Scr->WMgrHorizButtonIndent = 5;
    Scr->BorderShadowDepth = 2;
    Scr->TitleShadowDepth = 2;
    Scr->TitleButtonShadowDepth = 2;
    Scr->MenuShadowDepth = 2;
    Scr->IconManagerShadowDepth = 2;
    Scr->AutoOccupy = FALSE;
    Scr->TransientHasOccupation = FALSE;
    Scr->DontPaintRootWindow = FALSE;
    Scr->IconManagerDontShow =FALSE;
    Scr->BackingStore = TRUE;
    Scr->SaveUnder = TRUE;
    Scr->RandomPlacement = RP_OFF;
    Scr->DoOpaqueMove = FALSE;
    Scr->OpaqueMove = FALSE;
    Scr->OpaqueMoveThreshold = 200;
    Scr->OpaqueResize = FALSE;
    Scr->DoOpaqueResize = FALSE;
    Scr->OpaqueResizeThreshold = 1000;
    Scr->Highlight = TRUE;
    Scr->StackMode = TRUE;
    Scr->TitleHighlight = TRUE;
    Scr->MoveDelta = 1;		/* so that f.deltastop will work */
    Scr->MoveOffResistance = -1;
    Scr->MovePackResistance = 20;
    Scr->ZoomCount = 8;
    Scr->SortIconMgr = FALSE;
    Scr->Shadow = TRUE;
    Scr->InterpolateMenuColors = FALSE;
    Scr->NoIconManagers = FALSE;
    Scr->ClientBorderWidth = FALSE;
    Scr->SqueezeTitle = -1;
    Scr->FirstRegion = NULL;
    Scr->LastRegion = NULL;
    Scr->FirstWindowRegion = NULL;
    Scr->FirstTime = TRUE;
    Scr->HaveFonts = FALSE;		/* i.e. not loaded yet */
    Scr->CaseSensitive = TRUE;
    Scr->WarpUnmapped = FALSE;
    Scr->WindowRingAll = FALSE;
    Scr->WarpRingAnyWhere = TRUE;
    Scr->ShortAllWindowsMenus = FALSE;
    Scr->use3Diconmanagers = FALSE;
    Scr->use3Dmenus = FALSE;
    Scr->use3Dtitles = FALSE;
    Scr->use3Dborders = FALSE;
    Scr->use3Dwmap = FALSE;
    Scr->SunkFocusWindowTitle = FALSE;
    Scr->ClearShadowContrast = 50;
    Scr->DarkShadowContrast  = 40;
    Scr->BeNiceToColormap = FALSE;
    Scr->BorderCursors = FALSE;
    Scr->IconJustification = J_CENTER;
    Scr->IconRegionJustification = J_CENTER;
    Scr->IconRegionAlignement = J_CENTER;
    Scr->TitleJustification = J_LEFT;
    Scr->SmartIconify = FALSE;
    Scr->MaxIconTitleWidth = Scr->MyDisplayWidth;
    Scr->ReallyMoveInWorkspaceManager = FALSE;
    Scr->ShowWinWhenMovingInWmgr = FALSE;
    Scr->ReverseCurrentWorkspace = FALSE;
    Scr->DontWarpCursorInWMap = FALSE;
    Scr->XMoveGrid = 1;
    Scr->YMoveGrid = 1;
    Scr->FastServer = True;
    Scr->CenterFeedbackWindow = False;
    Scr->SchrinkIconTitles = False;
    Scr->AutoRaiseIcons = False;
    Scr->AutoFocusToTransients = False; /* kai */
    Scr->use3Diconborders = False;
    Scr->OpenWindowTimeout = 0;
    Scr->RaiseWhenAutoUnSqueeze = False;
    Scr->RaiseOnClick = False;
    Scr->RaiseOnClickButton = 1;
    Scr->IgnoreLockModifier = False;
    Scr->PackNewWindows = False;

    /* setup default fonts; overridden by defaults from system.twmrc */
#define DEFAULT_NICE_FONT "variable"
#define DEFAULT_FAST_FONT "fixed"

#ifdef I18N
    Scr->TitleBarFont.font_set = NULL;
    Scr->TitleBarFont.basename = DEFAULT_NICE_FONT;
    Scr->MenuFont.font_set = NULL;
    Scr->MenuFont.basename = DEFAULT_NICE_FONT;
    Scr->IconFont.font_set = NULL;
    Scr->IconFont.basename = DEFAULT_NICE_FONT;
    Scr->SizeFont.font_set = NULL;
    Scr->SizeFont.basename = DEFAULT_FAST_FONT;
    Scr->IconManagerFont.font_set = NULL;
    Scr->IconManagerFont.basename = DEFAULT_NICE_FONT;
    Scr->DefaultFont.font_set = NULL;
    Scr->DefaultFont.basename = DEFAULT_FAST_FONT;
#else    
    Scr->TitleBarFont.font = NULL;
    Scr->TitleBarFont.name = DEFAULT_NICE_FONT;
    Scr->MenuFont.font = NULL;
    Scr->MenuFont.name = DEFAULT_NICE_FONT;
    Scr->IconFont.font = NULL;
    Scr->IconFont.name = DEFAULT_NICE_FONT;
    Scr->SizeFont.font = NULL;
    Scr->SizeFont.name = DEFAULT_FAST_FONT;
    Scr->IconManagerFont.font = NULL;
    Scr->IconManagerFont.name = DEFAULT_NICE_FONT;
    Scr->DefaultFont.font = NULL;
    Scr->DefaultFont.name = DEFAULT_FAST_FONT;
#endif    

}


CreateFonts ()
{
    GetFont(&Scr->TitleBarFont);
    GetFont(&Scr->MenuFont);
    GetFont(&Scr->IconFont);
    GetFont(&Scr->SizeFont);
    GetFont(&Scr->IconManagerFont);
    GetFont(&Scr->DefaultFont);
    GetFont(&Scr->workSpaceMgr.workspaceWindow.windowFont);
    Scr->HaveFonts = TRUE;
}


RestoreWithdrawnLocation (tmp)
    TwmWindow *tmp;
{
    int gravx, gravy;
    unsigned int bw, mask;
    XWindowChanges xwc;

    if (tmp->UnmapByMovingFarAway && !VISIBLE(tmp)) {
	XMoveWindow (dpy, tmp->frame, tmp->frame_x, tmp->frame_y);
    }
    if (tmp->squeezed) Squeeze (tmp);
    if (XGetGeometry (dpy, tmp->w, &JunkRoot, &xwc.x, &xwc.y, 
		      &JunkWidth, &JunkHeight, &bw, &JunkDepth)) {

	GetGravityOffsets (tmp, &gravx, &gravy);
	if (gravy < 0) xwc.y -= tmp->title_height;
	xwc.x += gravx * tmp->frame_bw3D;
	xwc.y += gravy * tmp->frame_bw3D;

	if (bw != tmp->old_bw) {
	    int xoff, yoff;

	    if (!Scr->ClientBorderWidth) {
		xoff = gravx;
		yoff = gravy;
	    } else {
		xoff = 0;
		yoff = 0;
	    }

	    xwc.x -= (xoff + 1) * tmp->old_bw;
	    xwc.y -= (yoff + 1) * tmp->old_bw;
	}
	if (!Scr->ClientBorderWidth) {
	    xwc.x += gravx * tmp->frame_bw;
	    xwc.y += gravy * tmp->frame_bw;
	}

	mask = (CWX | CWY);
	if (bw != tmp->old_bw) {
	    xwc.border_width = tmp->old_bw;
	    mask |= CWBorderWidth;
	}

	XConfigureWindow (dpy, tmp->w, mask, &xwc);

	if (tmp->wmhints && (tmp->wmhints->flags & IconWindowHint)) {
	    XUnmapWindow (dpy, tmp->wmhints->icon_window);
	}

    }
}


/***********************************************************************
 *
 *  Procedure:
 *	Done - cleanup and exit twm
 *
 *  Returned Value:
 *	none
 *
 *  Inputs:
 *	none
 *
 *  Outputs:
 *	none
 *
 *  Special Considerations:
 *	none
 *
 ***********************************************************************
 */

void Reborder (time)
Time time;
{
    TwmWindow *tmp;			/* temp twm window structure */
    int scrnum;
    ScreenInfo *savedScreen;	        /* Its better to avoid coredumps */

    /* put a border back around all windows */

    XGrabServer (dpy);
    savedScreen = Scr;
    for (scrnum = 0; scrnum < NumScreens; scrnum++)
    {
	if ((Scr = ScreenList[scrnum]) == NULL)
	    continue;

	InstallWindowColormaps (0, &Scr->TwmRoot);	/* force reinstall */
	for (tmp = Scr->TwmRoot.next; tmp != NULL; tmp = tmp->next)
	{
	    RestoreWithdrawnLocation (tmp);
	    XMapWindow (dpy, tmp->w);
	}
    }
    Scr = savedScreen;
    XUngrabServer (dpy);
    SetFocus ((TwmWindow*)NULL, time);
}

SIGNAL_T Done()
{
#ifdef SOUNDS
    play_exit_sound();
#endif
    Reborder (CurrentTime);
#if defined(VMS) && EXIT_ENDSESSION /* was: #ifdef VMS */
    createProcess("run sys$system:decw$endsession.exe");
    sleep(10);  /* sleep until stopped */
#else
    XDeleteProperty (dpy, Scr->Root, _XA_WM_WORKSPACESLIST);
    if (captive) RemoveFromCaptiveList ();
    XCloseDisplay(dpy);
#ifdef VMS
    exit(20);			/* Will generate a fatal error, even
				   when compiled with DEC C 5.3 and above. */
#else
    exit(0);
#endif
#endif
}

SIGNAL_T Crash (int sig)
{ char *c= NULL;
    if( ( c= getenv("CTWM_EXCEPTIONS_ABORT")) ){
	    Reborder (CurrentTime);
	    XDeleteProperty (dpy, Scr->Root, _XA_WM_WORKSPACESLIST);
	    if (captive) RemoveFromCaptiveList ();
	    XCloseDisplay(dpy);
    }

    fprintf (stderr, "\nCongratulations, you have found a bug in ctwm\n");

    if( !c ){
	    fprintf( stderr,
	    	"Restarting now because CTWM_EXCEPTIONS_ABORT is not set.\n"
		"If you want to help in tracing the bug, please set this\n"
		"environmental variable, and see if a core dump is generated.\n"
	    );
	    Restart(sig);
    }
    else{
	    fprintf (stderr, "If a core file was generated in your directory,\n");
	    fprintf (stderr, "can you please try extract the stack trace,\n");
	    fprintf (stderr, "and mail the results, and a description of what you were doing,\n");
	    fprintf (stderr, "to Claude.Lecommandeur@epfl.ch.  Thank you for your support.\n");
	    fprintf( stderr, "To obtain a useful core dump, you may have to set CTWM_TRAP_EXCEPTIONS to False.\n" );
	    fprintf (stderr, "...exiting ctwm now on signal %d.\n\n", sig);
	    abort();
    }
}


SIGNAL_T Restart(int sig)
{
#ifdef X11R6
	extern SmcConn smcConn;
#endif

    fprintf( stderr, "%s: Restart'ing on signal %d\n", ProgramName, sig );

    StopAnimation ();
    XSync (dpy, 0);
    Reborder (CurrentTime);
    XSync (dpy, 0);
#ifdef VMS
    fprintf (stderr, "%s:  restart capabilities not yet supported\n",
	     ProgramName);
#else
#ifdef X11R6
	if (smcConn) SmcCloseConnection (smcConn, 0, NULL);
#endif /* X11R6 */
    execvp(*Argv, Argv);
#endif
    fprintf (stderr, "%s:  unable to restart:  %s\n", ProgramName, *Argv);
    exit (1);
}

#ifdef __WAIT_FOR_CHILDS
/*
 * Handler for SIGCHLD. Needed to avoid zombies when an .xinitrc
 * execs ctwm as the last client. (All processes forked off from
 * within .xinitrc have been inherited by ctwm during the exec.)
 * Jens Schweikhardt <jens@kssun3.rus.uni-stuttgart.de>
 */
SIGNAL_T
ChildExit (int signum)
{
    int Errno = errno;
    signal (SIGCHLD, ChildExit); /* reestablish because we're a one-shot */
    waitpid (-1, NULL, WNOHANG);  /* reap dead child, ignore status */
    errno = Errno;               /* restore errno for interrupted sys calls */
}
#endif

/*
 * Error Handlers.  If a client dies, we'll get a BadWindow error (except for
 * GetGeometry which returns BadDrawable) for most operations that we do before
 * manipulating the client's window.
 */

Bool ErrorOccurred = False;
XErrorEvent LastErrorEvent;

static int TwmErrorHandler(display, event)
    Display *display;
    XErrorEvent *event;
{
    LastErrorEvent = *event;
    ErrorOccurred = True;

    if (PrintErrorMessages && 			/* don't be too obnoxious */
	event->error_code != BadWindow &&	/* watch for dead puppies */
	(event->request_code != X_GetGeometry &&	 /* of all styles */
	 event->error_code != BadDrawable))
      XmuPrintDefaultErrorMessage (display, event, stderr);
    return 0;
}


/* ARGSUSED*/
static int CatchRedirectError(display, event)
    Display *display;
    XErrorEvent *event;
{
    RedirectError = TRUE;
    LastErrorEvent = *event;
    ErrorOccurred = True;
    return 0;
}

Atom _XA_MIT_PRIORITY_COLORS;
Atom _XA_WM_CHANGE_STATE;
Atom _XA_WM_STATE;
Atom _XA_WM_COLORMAP_WINDOWS;
Atom _XA_WM_PROTOCOLS;
Atom _XA_WM_TAKE_FOCUS;
Atom _XA_WM_SAVE_YOURSELF;
Atom _XA_WM_DELETE_WINDOW;
Atom _XA_WM_CLIENT_MACHINE;
#ifdef X11R6
  Atom _XA_SM_CLIENT_ID;
  Atom _XA_WM_CLIENT_LEADER;
  Atom _XA_WM_WINDOW_ROLE;
#endif

InternUsefulAtoms ()
{
    /* 
     * Create priority colors if necessary.
     */
    _XA_MIT_PRIORITY_COLORS = XInternAtom(dpy, "_MIT_PRIORITY_COLORS", False);   
    _XA_WM_CHANGE_STATE = XInternAtom (dpy, "WM_CHANGE_STATE", False);
    _XA_WM_STATE = XInternAtom (dpy, "WM_STATE", False);
    _XA_WM_COLORMAP_WINDOWS = XInternAtom (dpy, "WM_COLORMAP_WINDOWS", False);
    _XA_WM_PROTOCOLS = XInternAtom (dpy, "WM_PROTOCOLS", False);
    _XA_WM_TAKE_FOCUS = XInternAtom (dpy, "WM_TAKE_FOCUS", False);
    _XA_WM_SAVE_YOURSELF = XInternAtom (dpy, "WM_SAVE_YOURSELF", False);
    _XA_WM_DELETE_WINDOW = XInternAtom (dpy, "WM_DELETE_WINDOW", False);
    _XA_WM_CLIENT_MACHINE = XInternAtom (dpy, "WM_CLIENT_MACHINE", False);
#ifdef X11R6
    _XA_SM_CLIENT_ID = XInternAtom (dpy, "SM_CLIENT_ID", False);
    _XA_WM_CLIENT_LEADER = XInternAtom (dpy, "WM_CLIENT_LEADER", False);
    _XA_WM_WINDOW_ROLE = XInternAtom (dpy, "WM_WINDOW_ROLE", False);
#endif
}

static Window CreateRootWindow (x, y, width, height)
int		x, y;
unsigned int	width, height;
{
    int		scrnum;
    Window	ret;
    XWMHints	wmhints;
    Atom	_XA_WM_CTWM_ROOT;

    scrnum = DefaultScreen (dpy);
    ret = XCreateSimpleWindow (dpy, RootWindow (dpy, scrnum),
			x, y, width, height, 2, WhitePixel (dpy, scrnum),
			BlackPixel (dpy, scrnum));
    XSetStandardProperties (dpy, ret, "Captive ctwm", NULL, None, NULL, 0, NULL);
    wmhints.initial_state = NormalState;
    wmhints.input         = True;
    wmhints.flags         = InputHint | StateHint;
    XSetWMHints (dpy, ret, &wmhints);

    _XA_WM_CTWM_ROOT = XInternAtom (dpy, "WM_CTWM_ROOT", False);
    XChangeProperty (dpy, ret, _XA_WM_CTWM_ROOT, XA_WINDOW, 32, 
		     PropModeReplace, (unsigned char *) &ret, 4);
    XMapWindow (dpy, ret);
    return (ret);
}

static void DisplayInfo () {
    (void) printf ("Twm version:  %s\n", Version);
    (void) printf ("Compile time options :");
#ifdef XPM
    (void) printf (" XPM");
#endif
#ifdef IMCONV
    (void) printf (" IMCONV");
#endif
#ifdef USEM4
    (void) printf (" USEM4");
#endif
#ifdef SOUNDS
    (void) printf (" SOUNDS");
#endif
#ifdef I18N
    (void) printf (" I18N");
#endif    
    (void) printf ("\n");
}

