/** example/window.c
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