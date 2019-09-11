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

    // Bright Blue
    ghConsoleSetForecolor( ghCC_BLUE );
    ghConsoleSetAttribute( ghCA_BRIGHT );
    
    gh_printf( "Colors\n" );
    
    // Dim
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

    // reset attributes
    ghConsoleSetAttribute( ghCA_RESET );
    gh_printf( "\n\tDon't forget to reset when you're done!\n\n");
    
    return 0;
}