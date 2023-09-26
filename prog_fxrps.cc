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
  printf("\t compiled for FOX %s, running %d.%d.%d\n",
         fxrps_foxversion, fxversion[0], fxversion[1], fxversion[2]);
} // end fxrps_show_version

static void
fxrps_show_help(void)
{
  printf("%s usage (from %s:%d):\n", fxrps_progname, __FILE__, __LINE__);
  printf("\t --help               # give this help\n");
  printf("\t --version            # give version information\n");
  printf("# some FOX toolkit settings will be read from your configuration\n"
         "# file ~/.config/fox-refpersys.org/foxrps.rc\n");
#warning fxrps_show_help incomplete
} // end fxrps_show_help

// Message Map for the  class
FXDEFMAP(FoxRpsWindow) FoxRpsWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
};

// Macro for the FoxRpsWindow class hierarchy implementation
FXIMPLEMENT(FoxRpsWindow,FXMainWindow,FoxRpsWindowMap,
            ARRAYNUMBER(FoxRpsWindowMap));


FoxRpsWindow::~FoxRpsWindow()
{
  delete win_toplabel;
  win_toplabel=nullptr;
  delete win_firstsep;
  win_firstsep=nullptr;
#warning missing code in FoxRpsWindow::~FoxRpsWindow
} // end FoxRpsWindow::~FoxRpsWindow

void
FoxRpsWindow::create(void)
{
  FXMainWindow::create();
  char labuf[128];
  memset (labuf, 0, sizeof(labuf));
  snprintf(labuf, sizeof(labuf)-1, "%s git %s\n pid %d on %s",
           fxrps_progname,  SHORTGIT_ID, (int)getpid(), fxrps_myhostname);
  win_menubar = new FXMenuBar(this, LAYOUT_TOP);
  printf("@@@win_menubar=%p (%s:%d)\n", win_menubar, __FILE__, __LINE__);
  win_menulabel = new FXMenuTitle(win_menubar, FXString("App"));
  win_toplabel = new FXLabel(this, FXString(labuf));
  win_firstsep = new FXHorizontalSeparator(this);
  printf("@@@win_firstsep=%p (%s:%d)\n", win_firstsep, __FILE__, __LINE__);
  app_menu = new FXMenuPane(win_menubar);
  printf("@@@app_menu=%p (%s:%d)\n", app_menu, __FILE__, __LINE__);
  auto apptitle = new FXMenuTitle(win_menubar, tr("&App"),nullptr,app_menu);
  //apptitle->show();
  edit_menu = new FXMenuPane(win_menubar);
  auto edittitle = new FXMenuTitle(win_menubar, tr("Edit"),nullptr,edit_menu);
  //edittitle->show();
  win_menubar->show();
  win_vertframe.layout();
  layout();
#warning missing code in FoxRpsWindow::create
} // end FoxRpsWindow::create

static FoxRpsWindow*fxrps_first_window;

FoxRpsWindow*
FoxRpsWindow::main_window()
{
  return fxrps_first_window;
} // end FoxRpsWindow::main_window

FoxRpsWindow::FoxRpsWindow(FXApp*app, int width, int height)
  : FXMainWindow(app, FXString("foxrefpersys"),
                 (FXIcon*)nullptr, // icon
                 (FXIcon*)nullptr, // closed-icon
                 DECOR_ALL,
                 0, 0, //x,y
                 width, height
                ),
    win_vertframe(this)
{
} // end FoxRpsWindow::FoxRpsWindow


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
  if (fxversion[0] != FOX_MAJOR || fxversion[1] != FOX_MINOR)
    FXRPS_FATALOUT("FOX version mismatch, needs "
                   << FOX_MAJOR << "." << FOX_MINOR
                   << " got " << fxversion[0] << "." << fxversion[1]);
  FXApp app(basename((char*)fxrps_progname),
            "fox-refpersys.org");
  constexpr int minwidth=100, minheight=80;
  /// C++ code can now use FxApp::instance()
  app.init(argc, argv);
  if (argc > 1 && !strcmp(argv[1], "--help"))
    {
      fxrps_show_help();
      exit (EXIT_SUCCESS);
    };
  //#warning perhaps use FXSettings?
  //printf("@@@@before FXRegistry  %s:%d\n", __FILE__, __LINE__);
  fflush(stdout);
  FXRegistry& reg = app.reg();
  if (reg.read())
    printf("@@@@reg sysdirs=%s userdir=%s read/appkey=%s vendkey=%s no=%ld\n",
           reg.getSystemDirectories().text(),
           reg.getUserDirectory().text(),
           reg.getAppKey().text(), reg.getVendorKey().text(), reg.no());
  else
    printf("@@@failed to read registry sysdirs=%s userdir=%s %s:%d\n",
           reg.getSystemDirectories().text(),
           reg.getUserDirectory().text(),
           __FILE__, __LINE__);
  int width=reg.readIntEntry("mainwin","width");
  if (width<=minwidth)
    width=minwidth;
  //printf("@@@@ width=%d %s:%d\n", width, __FILE__, __LINE__);
  //fflush(stdout);
  int height=reg.readIntEntry("mainwin","height");
  if (height<=minheight)
    height=minheight;
  app.create();
  fxrps_first_window = new FoxRpsWindow(&app, width, height);
  fxrps_first_window->create();
  fxrps_first_window->show(PLACEMENT_SCREEN);
  ///
  app.addSignal(SIGINT,&app,FXApp::ID_QUIT);
  app.addSignal(SIGTERM,&app,FXApp::ID_QUIT);
  int ex= app.run();
  /// don't delete the fxrps_first_window, it will be by FOX
  return ex;
} // end main


void fxrps_fatal_stop_at(const char*fil, int lin)
{
  fprintf(stderr, "%s pid %d git %s aborting on file %s line %d\n",
          fxrps_progname, (int)getpid(), fxrps_shortgit_id, fil, lin);
  abort();
}

//// end of file prog_fxrps.cc
