### file guifox-refpersys/Makefile
## SPDX-License-Identifier: MIT

CXX= g++

FXRPS_HOST := $(shell /bin/hostname -f)
FXRPS_ARCH := $(shell /bin/uname -m)
FXRPS_OPERSYS := $(shell /bin/uname -o | /bin/sed 1s/[^a-zA-Z0-9_]/_/g )


CXXSOURCES= $(sort $(wildcard [a-z]*.cc))
OBJECTS= $(patsubst %.cc, %.o, $(CXXSOURCES))
RM= /bin/rm -vf
FXRPS_GIT_ID:= $(shell ./do-generate-gitid.sh)
FXRPS_SHORTGIT_ID:= $(shell ./do-generate-gitid.sh -s)
CXXFLAGS= -O2 -g3 -DGIT_ID=\"$(FXRPS_GIT_ID)\" -DSHORTGIT_ID=\"$(FXRPS_SHORTGIT_ID)\" \
     -DFXRPS_HOST=\"$(FXRPS_HOST)\" -DFXRPS_ARCH=\"$(FXRPS_ARCH)" \
      -DFXRPS_OPERSSYS=\"$(FXRPS_OPERSYS)" \
     -DFXRPS_FOXVERSION=\"$(shell fox-config --version)\" \
     $(shell foxconfig --cflags)
.PHONY: all clean indent gitpush

all: foxrps

clean:
	$(RM) $(wildcard *.o) foxrps *~ *.orig

foxrps: $(OBJECTS)
	$(LINK.cc) $(OBJECTS) $(shell fox-config --libs) -o $@
