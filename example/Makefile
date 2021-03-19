# example Makefile
# NOTE: much of this manual configuration will be performed by `pkg-config` in the future
# 2021.03.18::gsh

#ghCC= cc
ghCC= gcc
ghMKDIR= mkdir -p
ghI= -I
ghL= -L
ghSTATICEXT= .a
#ghSTATICEXT= .lib

## TODO:
ghEXECEXT=
#ghEXECEXT= .exe

#ghDEBUGGING= -debugv
ghDEBUGGING=

ghVERSION= 0.7.0.1

ghARCH= x86_64
#ghARCH= Intel64
#ghARCH= armv7l
ghPLATFORM= X
#ghPLATFORM= MSWIN

ghPLATFORMLIBS= -lX11
#ghPLATFORMLIBS= -luser

#$(ghVERSION)/include/
ghINCPATH= $(ghI)../include
#$(ghVERSION)/lib/
ghLIBPATH= $(ghL)../lib

# be very careful with this, especially if running clean command!!!
ghTARGETPATH= bin/

#TODO -- fix ghLIBPATH
#../lib/libGH$(ghDEBUGGING)-$(ghVERSION)-$(ghARCH)-$(ghPLATFORM)$(ghSTATICEXT)
ghLIBGH= ../lib/libGH.a

.PHONY: all

all: check_path $(ghTARGETPATH)version $(ghTARGETPATH)window $(ghTARGETPATH)colors

# WARNING! Verify target path!!!
clean:
	rm -fr $(ghTARGETPATH)

check_path:
	$(ghMKDIR) $(ghTARGETPATH)

# for targetpath building
$(ghTARGETPATH)%: %.c
	$(ghCC) $< -o $@ -DghP=ghP_$(ghPLATFORM) $(ghINCPATH) $(ghLIBGH) $(ghPLATFORMLIBS)

# for in-folder building
%: %.c
	$(ghCC) $< -o $@ -DghP=ghP_$(ghPLATFORM) $(ghINCPATH) $(ghLIBGH) $(ghPLATFORMLIBS)
