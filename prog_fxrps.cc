/****** file guifox-refpersys/prog_fxrps.cc ******
 * SPDX-License-Identifier: MIT
 * © Copyright 2023 Basile Starynkevitch
 ******/

#include "foxrps.hh"



const char*fxrps_progname;
const char fxrps_shortgitid[] = "";
char fxrps_myhostname[80];
void* fxrps_dlhandle;
 bool fxrps_stderr_istty;

int
main(int argc, char**argv)
{
  assert(argc>0);
  fxrps_progname = argv[0];
  fxrps_stderr_istty = isatty(STDERR_FILENO);
  memset (fxrps_myhostname, 0, sizeof(fxrps_myhostname));
  gethostname(fxrps_myhostname, sizeof(fxrps_myhostname)-4);
  fxrps_dlhandle = dlopen(nullptr, RTLD_NOW| RTLD_GLOBAL);
  if (!fxrps_dlhandle) {
  }
} // end main


void fxrps_fatal_stop_at(const char*fil, int lin)
{
    fprintf(stderr, "%s pid %d git %s aborting on file %s line %d\n",
	    fxrps_progname, (int)getpid(), fil, lin);
    abort();
}
