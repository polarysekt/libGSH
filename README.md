libGH Distribution README
=========================
2019.09.07-polarysekt


# libGH Distribution

## Synopsis

libGH is a multiarchitecture, multiplatform windowing API.

libGH distribution builds with `C` bindings.

## Getting Started

The libs are built as static libraries into the version folders.

The include header for each version is included.

### Using the library

Be sure to include the `GH.h` header in the program:

```c
#include "GH.h"

...
```

NOTE: the GH in `GH.h` is CAPTITAL.

### Building against the library

The following (overly simplified) examples use `gcc`.

Here is a sample `C` source file to test:

```c
/** app.c
  * @file Simple, basic app to test libGH linking
  * @author polarysekt
  *
  * @copyright Copyright(c) 2019, polarysekt
  */

#include "GH.h"
  
int main( int argc, char* argv[] ) {

    return 0;
}

```

See the appendix and the `example/` folder for more advanced examples.

#### X

X applications should be statically linked against `libGH` and dynamically linked against `X11`.

Be sure to include the correct architecture and platform version of the lib.

This example assumes all files are in the same folder, the source is located in `app.c`, the output is an ELF binary called `app`, the libGH version is `2.0.0.0`, the architecture is `x86_64` and the platform is `X`. The `-Dghp=ghP_X` informs the libGH header of the target platform.

NOTE: In the future, this will be greatly simplified by `pkg-config`.

```c
$ gcc app.c -DghP=ghP_X libGH-2.0.0.0-x86_64-X.a -o app -lX11
```

While building without specifying a platform is allowed, it cripples the functionality of the native GUI bindings.
Omitting the target platform will cause the build to emit:

```
../../include/GH.h:70:6: warning: #warning !!! UNDETECTED PLATFORM !!! Errors to Ensue. [-Wcpp]
 #    warning !!! UNDETECTED PLATFORM !!! Errors to Ensue.
```

NOTE: more advanced configurations can utilize similar syntax with `-I` and `-L` to specify locations of include and library files.




#### MSWIN

TODO

## Appendix

### More Examples

#### libGH version information

```c
/** version.c
  * @file app to demo the ghVersionGet functions
  * @author polarysekt
  *
  * @copyright Copyright(c) 2019, polarysekt
  */

#include "GH.h"

int main( int argc, char* argv[] ) {

    gh_printf( 
        "libGH v%d.%d.%d.%d %s [%.4d] %s %s\n",
        ghVersionGetMajor(), 
		ghVersionGetMinor(), 
		ghVersionGetRevision(), 
		ghVersionGetRelease(), 
		ghVersionGetBuildType(),
		ghVersionGetBuild(), 
		ghVersionGetArchitecture(), 
		ghVersionGetPlatform()
    );

    return 0;
}
    
```

#### Console colors

```c
/** colors.c
  * @file app to demo some ghConsole functions
  * @author polarysekt
  *
  * @copyright Copyright(c) 2019, polarysekt
  */

#include "GH.h"

int main( int argc, char* argv[] ) {

    /* NOTE: this is an example, minimized for brevity.
     *       a proper implementation would detect the output
     *       target and determine whether it can/should
     *       accept colors (i.e. file,pipe,tty).
     */

    ghConsoleSetForecolor( ghCC_BLUE );
    ghConsoleSetAttribute( ghCA_BRIGHT );  
    gh_printf( "Colors\n" );
    
    ghConsoleSetAttribute( ghCA_DIM );
    gh_printf( "\tVarious colors and attributes on the console.\n\n" );

    for( ghCONSOLE_COLOR cccx = ghCC_BLACK; cccx<=ghCC_WHITE; cccx++ ) {
        for( ghCONSOLE_ATTRIBUTE cacx = ghCA_BRIGHT; cacx<ghCA_HIDDEN; cacx++ ) {
          ghConsoleSetForecolor( cccx );
          ghConsoleSetAttribute( cacx );
          gh_printf( "[c%d, a%d]", cccx, cacx );
          ghConsoleSetAttribute( ghCA_RESET );
        }
        gh_printf( "\n" );
    }

    ghConsoleSetAttribute( ghCA_RESET );
    gh_printf( "\n\tDon't forget to reset when you're done!\n\n");
    
    return 0;
}
    
```

#### A simple Window

```
/** window.c
 * @file Simple GUI Window Demo
 * @author polarysekt
 *
 * DETAILS:
 *  Window is created and initialized in two steps.
 *  This allows extra error checking (usually caused by OOM) 
 *  as well as individually early setting attributes.
 *
 *  The pre-init and post-init attribute settings are 
 *  handled differently, the former being faster, 
 *  especially if object is visible.
 *
 *  To instead create and initialize in one step:
 *       wndMain = ghWindowInit( ghWindowCreate() );
 *
 * @copyright Copyright(c) 2019, polarysekt
 */

#include "GH.h"

const int wndWidth = 640;
const int wndHeight = 480;

int main( int argc, char* argv[] ) {
    int ret = 0;

    // handle to the window
    ghWINDOW* wndMain;
    
    // Required for GUI
    ghInit( &argc, &argv );

    // Create window in memory - Requires Init to Register/Create with GUI
	wndMain = ghWindowCreate();

    // Confirm Window Creation
	if( !wndMain ) {
		gh_printf( "FATAL - Unable to CREATE wndMain!\n" );
		return 1;
	}

    ghWindowSetExtent( wndMain, wndWidth, wndHeight );
	ghWindowSetPosition( wndMain, ghMonitorGetWidth(0)/2 - wndWidth, ghMonitorGetHeight(0)/2 - wndHeight );

    ghWindowSetCaption( wndMain, "libGH Window" );
    ghWindowSetBackgroundColor( wndMain, 0 );

    // Register/Create window with WindowManager
	if( !ghWindowInit( wndMain ) ) {
		gh_printf( "FATAL - Unable to INIT wndMain!\n" );
		ghWindowDestroy( wndMain );
		return 2;
	}

    // Show the window on screen
    ghWindowShow( wndMain );

    // Run main message loop
	ret = ghRun();

    // This will soon be handled internally, automatically
	ghWindowDestroy( wndMain );

	return ret;

}
```
