/* -*- mode: C; tab-width: 2; indent-tabs-mode: t; c-basic-offset: 2 -*- */
/** GH.h
 * @file the YOLOSTRAT ^ruddy^ *OFFICIAL* master include file
 *
 * @since 0.0.0.0
 * 
 * @copyright Copyright (c) 2012-2017,2019 polarysekt, kb3c
 */

// stdlib headers [required for now] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  include <limits.h>	// INT_MIN
#  include <stdarg.h>	// __VA_ARGS__, va_, ... (argument notation)
#  include <stddef.h>	// size_t

// DEBUGGING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  ifndef NDEBUG
#    define ghDBGprintf(...)		gh_printf( __VA_ARGS__ )
#    ifdef GHDBG_VERBOSE
#      define ghDBGVRBprintf(...)	gh_printf( __VA_ARGS__ )
#    else
#      define ghDBGVRBprintf(...)	((void)0)
#    endif
#  else
#    define ghDBGprintf(...)	((void)0)
#    define ghDBGVRBprintf(...)	((void)0)
#  endif

// shortened ALIASes
#define ghDpf ghDBGprintf
#define ghDVpf ghDBGVRBprintf

// PLATFORMs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 															SHORT REF
#  define ghP_NONE		0
#  define ghP_CURSES	100				// 'C'

#  define ghP_MSWIN		201				// 'W'
#  define ghP_MSWIN64 202
#  define ghP_WIN		ghP_MSWIN

#  define ghP_MAC		300					// 'M'
#  define ghP_CARBON 301
#  define ghP_OSX		302
#  define ghP_IOS		303					// 'I'

#  define ghP_X			400					// 'X'
#  define ghP_X11 		ghP_X

#  define ghP_ANDROID	401				// 'A'

// TODO! --> consolidate MACs, MSWINs, etc.

// CHECK for UNDEFINED PLATFORM (should be set by CMakeList.txt)
#ifndef ghP
#  define ghP ghP_NONE					// default to NONE [2016apr16:gsh]
#endif

#  if (ghP==ghP_MSWIN)
#    include "windows.h"
// TODO: further windows includes
#  elif (ghP==ghP_X11)
#    include "X11/Xlib.h"
//#    include "curses.h"
// TODO: further X.org includes
#  elif (ghP==ghP_OSX)
#  elif (ghP==ghP_IOS)
#  elif (ghP==ghP_CURSES)
#    include "curses.h"
#  else
#    warning !!! UNDETECTED PLATFORM !!! Errors to Ensue.
#  endif

// TYPES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#  define ghNULL 0
typedef unsigned char ghBOOL;
#  define ghTRUE 1
#  define ghFALSE 0
typedef int ghRET;
typedef unsigned int ghUINT;
typedef unsigned long ghULONG;
typedef ghUINT ghMONITOR;


// libGH DEBUG ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#  ifndef NDEBUG
#    define ghDBGprintf(...)	gh_printf( __VA_ARGS__ )
#    ifdef GHDBG_VERBOSE
#      define ghDBGVRBprintf(...)	gh_printf( __VA_ARGS__ )
#    else
#      define ghDBGVRBprintf(...)	((void)0)
#    endif
#  else
#    define ghDBGprintf(...)	((void)0)
#    define ghDBGVRBprintf(...)	((void)0)
#  endif

// Shorten ghDEBUG refs
#define ghDpf 	ghDBGprintf
#define ghDVpf	ghDBGVRBprintf


// stdlib ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int						gh_atexit( void (*fn)(void) );
void					gh_free( void* ptr );
void*					gh_malloc( size_t size );
int						gh_printf( const char *fmt, ... );
int 					gh_sprintf( char* str, const char* fmt, ... );
char*					gh_strcpy( char* s1, const char* s2 );
int						gh_strcmp( const char* s1, const char* s2 );
int						gh_strncmp( const char* s1, const char* s2, size_t n );
size_t				gh_strlen( const char* s );
unsigned int	gh_sleep( unsigned int s );


// ghERROR Interface ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	NOTE: new errors should be appended to ghErrorGetString() ~~~~~~~~~~~~~~~~~

typedef enum t_ghERROR {
	ghERR_GENERIC = INT_MIN,
	ghERR_UNIMPLEMENTED,		// Function or PLATFORM unimplemented
	ghERR_OOM,							// Out of Memory
	ghERR_ALREADY_INIT,			// libGH already initialized
	ghERR_ARG_INVALID,			// Specified ARGUMENT not valid
	ghERR_OBJ_INVALID,			// Specified OBJECT not valid
	ghERR_OBJ_NOT_INIT,			// Object not yet initialized
	ghERR_OBJ_REINIT,				// Attempt to RE-INIT object
	ghERR_LIB_NOT_INIT,			// libGH not yet initialized
	ghERR_X11_DISP_INVALID,
	ghERR_NONE = 0
} ghERROR;

typedef ghERROR ghERR;								// Shorten ghERROR

int			ghErrorEnum( void );
int			ghErrorClear( void );
ghERR		ghErrorPeek( void );
ghERR		ghErrorPop( void );
ghERR		ghErrorPush( ghERR e );

ghUINT	ghErrorGetStringLength( ghERROR e );
char*		ghErrorGetString( ghERROR e );
ghRET		ghErrorGetStringSZ( ghERROR e, char pszErr[] );

// DEFINE some ALIASes
#define ghErrorCount ghErrorEnum
#define ghErrCount ghErrorEnum
#define ghErrEnum ghErrorEnum


// libGH VERSION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ghUINT ghVersionGetMajor( void );
ghUINT ghVersionGetMinor( void );
ghUINT ghVersionGetRevision( void );
ghUINT ghVersionGetRelease( void );
//TODO:
ghUINT ghVersionGetBuild( void );

const char* ghVersionGetArchitecture( void );
const char* ghVersionGetPlatform( void );
const char* ghVersionGetBuildType( void );


// libGH MONITOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ghRET		ghMonitorGetExtent2ui( ghUINT m, ghUINT* w, ghUINT* h );
#define ghMonitorGetExtent ghMonitorGetExtent2ui
ghRET		ghMonitorGetExtentMM2ui( ghUINT m, ghUINT* w, ghUINT* h );
#define ghMonitorGetExtentMM ghMonitorGetExtentMM2ui
ghUINT ghMonitorGetWidth( ghUINT m );
ghUINT ghMonitorGetHeight( ghUINT m );
ghUINT ghMonitorGetWidthMM( ghUINT m );
ghUINT ghMonitorGetHeightMM( ghUINT m );
ghMONITOR ghMonitorGetDefault( void );


// libgh CONSOLE ***********************************************************
// NOTE: this is not complete!                                             

typedef enum t_ghCONSOLE_SEQUENCE {
  ghCS_CUU = 'A',			// Cursor Up
  ghCS_CUD,						// Cursor Down
  ghCS_CUF,						// Cursor Forward
  ghCS_CUB,						// Cursor Back
  ghCS_CNL,						// Cursor Next Line
  ghCS_CPL,						// Cursor Previous Line
  ghCS_CHA,						// Cursor Horizontal Absolute
  ghCS_CUP,						// Cursor Position [2 param]
  ghCS_ED = 'J',			// Erase Display [0, 1, or 2]
  ghCS_EL,						// Erase Line
  ghCS_SU = 'S',			// Scroll Up (whole page)
  ghCS_SD,						// Scroll Down (whole page)
  ghCS_HVP = 'f',			// Horiz and Vert Position [same as CUP]
  ghCS_SGR = 'm',			// Select Graphic Rendition
  ghCS_SCP = 's',			// Save Cursor Position [no param]
  ghCS_RCP = 'u'			// Restore Cursor Position [no param]
} ghCONSOLE_SEQUENCE;

typedef enum t_ghCONSOLE_COLOR {
  ghCC_BLACK = 0,
  ghCC_RED,
  ghCC_GREEN,
  ghCC_YELLOW,
  ghCC_BLUE,
  ghCC_MAGENTA,
  ghCC_CYAN,
  ghCC_WHITE
} ghCONSOLE_COLOR;

typedef enum t_ghCONSOLE_ATTRIBUTE {
  ghCA_RESET = 0,
  ghCA_BRIGHT,
  ghCA_DIM,
  ghCA_ITALIC,
  ghCA_UNDERLINE,
  ghCA_BLINK,
  /* skip blink rapid */
  ghCA_REVERSE = 7,
  ghCA_HIDDEN,
  ghCA_STRIKETHRU,
  /* skip font setting */
  ghCA_DOUBLEUNDERLINE = 21, /* sometimes bold off? */
  ghCA_NORMAL,
  ghCA_NOITALIC,			/* also no fraktur */
  ghCA_NOUNDERLINE,
  ghCA_NOBLINK,
  /* skips */
  ghCA_NOHIDDEN = 28,
  ghCA_NOSTRIKETHRU
} ghCONSOLE_ATTRIBUTE;

void 	ghConsoleSetColor2i( ghCONSOLE_COLOR fg, ghCONSOLE_COLOR bg );
#define ghConsoleSetColor		ghConsoleSetColor2i
#define ghTerminalSetColor2i	ghConsoleSetColor2i
#define ghTerminalSetColor		ghConsoleSetColor2i
#define ghConsoleSetColour2i	ghConsoleSetColor2i
#define ghConsoleSetColour		ghConsoleSetColor2i
#define ghTerminalSetColour2i	ghConsoleSetColor2i
#define ghTerminalSetColour		ghConsoleSetColor2i
void 	ghConsoleSetAttribute( ghCONSOLE_ATTRIBUTE a );
#define ghTerminalSetAttribute	ghConsoleSetAttribute
void 	ghConsoleSetForecolor( ghCONSOLE_COLOR c );
#define ghConsoleSetForeground	ghConsoleSetForecolor
#define ghTerminalSetForecolor	ghConsoleSetForecolor
#define ghTerminalSetForeground ghConsoleSetForecolor
#define ghConsoleSetForecolour	ghConsoleSetForecolor
#define ghTerminalSetForecolour	ghConsoleSetForecolor


/*** libgh RUNNABLE **********************************************************
                                                                             */
typedef struct t_ghRUNNABLE ghRUNNABLE;

ghRUNNABLE*	ghInit( int* pargc, char*** pargv );
ghRET		ghRun( void );
void		ghShutdown( );


/*** libgh RECT **************************************************************
                                                                             */
typedef struct t_ghRECT ghRECT;
ghRECT*	ghRectCreate( void );
ghRET	ghRectDestroy( ghRECT* pr );
ghRET	ghRectGetExtent2ui( ghRECT* pr, ghUINT* width, ghUINT* height );
#define ghRectGetExtent ghRectGetExtent2ui
ghRET	ghRectGetExtentPosition2i( ghRECT* pr, int* x2, int* y2 );
#define ghRectGetExtentPosition ghRectSetExtentPosition2i
unsigned int ghRectGetHeight( ghRECT* pr );
#define ghRectGetExtentY ghRectGetHeight
ghRET	ghRectGetPosition2i( ghRECT* pr, int* x, int* y );
#define ghRectGetPosition ghRectGetPosition2i
unsigned int ghRectGetWidth( ghRECT* pr );
#define ghRectGetExtentX ghRectGetWidth
int		ghRectGetX( ghRECT* pr );
#define ghRectGetLeft ghRectGetX
int		ghRectGetX2( ghRECT* pr );
#define ghRectGetExtentPositionX ghRectGetX2
#define ghRectGetRight ghRectGetX2
int		ghRectGetY( ghRECT* pr );
#define ghRectGetTop ghRectGetY
int		ghRectGetY2( ghRECT* pr );
#define ghRectGetExtentPositionY ghRectGetY2
#define ghRectGetBottom ghRectGetY2
ghRET	ghRectSetExtent2ui( ghRECT* pr, ghUINT width, ghUINT height );
#define ghRectSetExtent ghRectSetExtent2ui
ghRET	ghRectSetExtentPosition2i( ghRECT* pr, int x2, int y2 );
#define ghRectSetExtentPosition ghRectSetExtentPosition2i
ghRET	ghRectSetHeight( ghRECT* pr, ghUINT height );
#define ghRectSetExtentY ghRectSetHeight
ghRET	ghRectSetPosition2i( ghRECT* pr, int x, int y );
#define ghRectSetPosition ghRectSetPosition2i
ghRET	ghRectSetWidth( ghRECT* pr, ghUINT width );
#define ghRectSetExtentX ghRectSetWidth
ghRET	ghRectSetX( ghRECT* pr, int x );
#define ghRectSetLeft ghRectSetX
ghRET	ghRectSetX2( ghRECT* pr, int x2 );
#define ghRectSetExtentPositionX ghRectSetX2
#define ghRectSetRight ghRectSetX2
ghRET	ghRectSetY( ghRECT* pr, int y );
#define ghRectSetTop ghRectSetY
ghRET	ghRectSetY2( ghRECT* pr, int y2 );
#define ghRectSetExtentPositionY ghRectSetY2
#define ghRectSetBottom ghRectSetY2

// libGH FONT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct t_ghFONT ghFONT;

ghFONT*		ghFontCreate( void );
ghRET			ghFontDestroy( ghFONT* pf );
ghFONT*		ghFontInit( ghFONT* pf );
ghRET			ghFontShutdown( ghFONT* pf );



// libGH WINDOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct t_ghWINDOW ghWINDOW;

ghWINDOW* 	ghWindowCreate( void );
ghRET 		ghWindowDestroy( ghWINDOW* pw );
ghWINDOW*	ghWindowInit( ghWINDOW* pw );
ghRET 		ghWindowShutdown( ghWINDOW* pw );


ghRET		ghWindowCheckInit( ghWINDOW* pw );

ghRET		ghWindowShow( ghWINDOW* pw );
ghRET		ghWindowHide( ghWINDOW* pw );


ghRET ghWindowDrawArc( ghWINDOW* pw, int x, int y, ghUINT w, ghUINT h, int a1, int a2 );
ghRET ghWindowDrawFilledArc( ghWINDOW* pw, int x, int y, ghUINT w, ghUINT h, int a1, int a2 );
ghRET ghWindowDrawLine( ghWINDOW* pw, int x, int y, int x2, int y2 );
ghRET ghWindowDrawPoint( ghWINDOW* pw, int x, int y );
ghRET ghWindowDrawRectangle( ghWINDOW* pw, int x, int y, ghUINT w, ghUINT h );
ghRET ghWindowDrawFilledRectangle( ghWINDOW* pw, int x, int y, ghUINT w, ghUINT h );
ghRET ghWindowDrawString( ghWINDOW* pw, int x, int y, char* str );

ghULONG		ghWindowGetBackgroundColor( ghWINDOW* pw );

ghUINT		ghWindowGetBorderWidth( ghWINDOW* pw );
int		ghWindowGetX( ghWINDOW* pw );
#define		ghWindowGetLeft	ghWindowGetX
int		ghWindowGetX2( ghWINDOW* pw );
#define		ghWindowGetExtentPositionX	ghWindowGetX2
#define		ghWindowGetRight ghWindowGetX2
int		ghWindowGetY( ghWINDOW* pw );
#define		ghWindowGetTop	ghWindowGetY
int		ghWindowGetY2( ghWINDOW* pw );
#define		ghWindowGetExtentPositionY	ghWindowGetY2
#define		ghWindowGetBottom ghWindowGetY2
ghRET ghWindowGetExtent2ui( ghWINDOW* pw, ghUINT* w, ghUINT* y );
#define ghWindowGetExtent ghWindowGetExtent2ui
ghRET ghWindowGetExtentPosition2i( ghWINDOW* pw, int* x2, int* y2 );
#define ghWindowGetExtentPosition ghWindowGetExtentPosition2i
ghRET ghWindowGetPosition2i( ghWINDOW* pw, int* x, int* y );
#define		ghWindowGetPosition ghWindowGetPosition2i
ghUINT ghWindowGetHeight( ghWINDOW* pw );
ghUINT ghWindowGetWidth( ghWINDOW* pw );

ghWINDOW* ghWindowGetParent( ghWINDOW* pw );

ghRET ghWindowSetBackgroundColor( ghWINDOW* pw, ghULONG color );
ghRET ghWindowSetBorderWidth( ghWINDOW* pw, ghUINT bw );
ghRET ghWindowSetCaption( ghWINDOW* pw, const char* s );

ghRET ghWindowSetDrawFont( ghWINDOW* pw, ghFONT* pf );
ghRET ghWindowSetDrawForecolor( ghWINDOW* pw, ghULONG fc );

#define  ghWindowSetTitle ghWindowSetCaption
ghRET ghWindowSetExtent2ui( ghWINDOW* pw, ghUINT width, ghUINT height );
#define ghWindowSetExtent ghWindowSetExtent2ui
ghRET ghWindowSetParent( ghWINDOW* pw, ghWINDOW* pp );
ghRET ghWindowSetPosition2i( ghWINDOW* pw, int x, int y );
#define ghWindowSetPosition ghWindowSetPosition2i
ghRET		ghWindowSetShowstate( ghWINDOW* pw );
ghRET ghWindowSetX( ghWINDOW* pw, int x );
#define ghWindowSetLeft ghWindowSetX
ghRET ghWindowSetX2( ghWINDOW* pw, int x2 );
#define ghWindowSetRight ghWindowSetX2
ghRET ghWindowSetY( ghWINDOW* pw, int y );
#define ghWindowSetTop ghWindowSetY
ghRET ghWindowSetY2( ghWINDOW* pw, int y2 );
#define ghWindowSetBottom ghWindowSetY2


// libGH IMAGE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct t_ghIMAGE ghIMAGE;

ghIMAGE*	ghImageCreate( void );
ghRET			ghImageDestroy( ghIMAGE* pi );

// libGH CANVAS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct t_ghCANVAS ghCANVAS;

ghCANVAS*	ghCanvasCreate( void );
ghRET			ghCanvasDestroy( ghCANVAS* pc );
