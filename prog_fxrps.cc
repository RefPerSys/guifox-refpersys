/****** file guifox-refpersys/prog_fxrps.cc ******
 * SPDX-License-Identifier: MIT
 * © Copyright 2023 Basile Starynkevitch
 ******/

#include "foxrps.hh"

#ifndef SHORTGIT_ID
#error undefined SHORTGIT_ID
#endif

#ifndef GIT_ID
#error undefined GIT_ID
#endif

#ifndef FXRPS_HOST
#error undefined FXRPS_HOST
#endif


#ifndef FXRPS_FOXVERSION
#error undefined FXRPS_FOXVERSION
#endif

#ifndef FXRPS_ARCH
#error undefined FXRPS_ARCH
#endif

#ifndef FXRPS_OPERSYS
#error undefined FXRPS_OPERSYS
#endif


const char*fxrps_progname;
const char fxrps_shortgitid[] = SHORTGIT_ID;
const char fxrps_gitid[] = GIT_ID;
const char fxrps_host[]= FXRPS_HOST;
const char fxrps_foxversion[] = FXRPS_FOXVERSION;
const char fxrps_arch[] = FXRPS_ARCH;
const char fxrps_opersys[] = FXRPS_OPERSYS;
const char fxrps_timestamp[] = __DATE__ "@" __TIME__;

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
  if (!fxrps_dlhandle)
      FXRPS_FATALOUT("failed to dlopen main program: " << dlerror());
} // end main


void fxrps_fatal_stop_at(const char*fil, int lin)
{
  fprintf(stderr, "%s pid %d git %s aborting on file %s line %d\n",
          fxrps_progname, (int)getpid(), fil, lin);
  abort();
}
