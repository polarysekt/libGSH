/** example/version.c
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