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
const char fxrps_shortgit_id[] = SHORTGIT_ID;
const char fxrps_gitid[] = GIT_ID;
const char fxrps_host[]= FXRPS_HOST;
const char fxrps_foxversion[] = FXRPS_FOXVERSION;
const char fxrps_arch[] = FXRPS_ARCH;
const char fxrps_opersys[] = FXRPS_OPERSYS;
const char fxrps_timestamp[] = __DATE__ "@" __TIME__;

char fxrps_myhostname[80];
void* fxrps_dlhandle;
bool fxrps_stderr_istty;

static void
fxrps_show_version(void)
{
  printf("%s version information (on %s):\n", fxrps_progname, fxrps_myhostname);
  printf("\t git %s\n", fxrps_gitid);
  printf("\t built %s\n", fxrps_timestamp);
  printf("\t for OS: %s and arch %s\n", fxrps_opersys, fxrps_arch);
  printf("\t compiled on %s\n", fxrps_host);
  printf("\t compiled for FOX %s\n", fxrps_foxversion);
}

// Message Map for the  class
FXDEFMAP(FoxRpsWindow) FoxRpsWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
};

// Macro for the ScribbleApp class hierarchy implementation
FXIMPLEMENT(FoxRpsWindow,FXMainWindow,FoxRpsWindowMap,
            ARRAYNUMBER(FoxRpsWindowMap));


FoxRpsWindow::~FoxRpsWindow()
{
#warning missing code in FoxRpsWindow::~FoxRpsWindow
} // end FoxRpsWindow::~FoxRpsWindow

void
FoxRpsWindow::create(void)
{
#warning missing code in FoxRpsWindow::create
} // end FoxRpsWindow::create

int
main(int argc, char**argv)
{
  assert(argc>0);
  fxrps_progname = argv[0];
  fxrps_stderr_istty = isatty(STDERR_FILENO);
  memset (fxrps_myhostname, 0, sizeof(fxrps_myhostname));
  gethostname(fxrps_myhostname, sizeof(fxrps_myhostname)-4);
  if (argc > 1 && !strcmp(argv[1], "--version"))
    {
      fxrps_show_version();
      exit (EXIT_SUCCESS);
    };
  fxrps_dlhandle = dlopen(nullptr, RTLD_NOW| RTLD_GLOBAL);
  if (!fxrps_dlhandle)
    FXRPS_FATALOUT("failed to dlopen main program: " << dlerror());
} // end main


void fxrps_fatal_stop_at(const char*fil, int lin)
{
  fprintf(stderr, "%s pid %d git %s aborting on file %s line %d\n",
          fxrps_progname, (int)getpid(), fxrps_shortgit_id, fil, lin);
  abort();
}

//// end of file prog_fxrps.cc
