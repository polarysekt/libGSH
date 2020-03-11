# example Makefile
# NOTE: much of this manual configuration will be performed by `pkg-config` in the future
# 2019.09.11, polarysekt

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

ghVERSION= 0.2.0.1

ghARCH= x86_64
#ghARCH= Intel64
#ghARCH= armv7l
ghPLATFORM= X
#ghPLATFORM= MSWIN

ghPLATFORMLIBS= -lX11
#ghPLATFORMLIBS= -luser

ghINCPATH= $(ghI)../$(ghVERSION)/
ghLIBPATH= $(ghL)../$(ghVERSION)/

# be very careful with this, especially if running clean command!!!
ghTARGETPATH= bin/

#TODO -- fix ghLIBPATH
ghLIBGH=../$(ghVERSION)/libGH$(ghDEBUGGING)-$(ghVERSION)-$(ghARCH)-$(ghPLATFORM)$(ghSTATICEXT)


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
