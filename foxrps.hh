/****** file guifox-refpersys/foxrps.hh ******
 * SPDX-License-Identifier: MIT
 * © Copyright 2023 Basile Starynkevitch
 *
 * A Fox toolkit graphical interface (see fox-toolkit.org)
 * to the RefPerSys open source (GPLv3+ licensed) inference engine
 *
 * See refpersys.org and code on https://github.com/RefPerSys/
 *
 ***************************************************/

#ifndef  FOXRPS_INCLUDED
#define FOXRPS_INCLUDED 1

#ifndef GIT_ID
#error GIT_ID should be defined by compilation command
#endif

#ifndef SHORTGIT_ID
#error SHORTGIT_ID should be defined by compilation command
#endif

#if __cplusplus < 201412L
#error expecting C++17 standard
#endif

/// C++ standard headers
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <functional>
#include <string>
#include <cstring>
#include <ostream>
#include <sstream>

/// POSIX headers
#include <getopt.h>
#include <libgen.h>
#include <dlfcn.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include <sys/stat.h>
#include <elf.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <signal.h>


/// from GNU libunistring
#include <unitypes.h>
#include <unistr.h>


#include "fx.h"

extern "C" const char*fxrps_progname;
extern "C" const char fxrps_git_id[];
extern "C" const char fxrps_shortgit_id[];
extern "C" char fxrps_myhostname[];
extern "C" const char fxrps_host[];
extern "C" const char fxrps_foxversion[];
extern "C" const char fxrps_arch[];
extern "C" const char fxrps_opersys[];
extern "C" const char fxrps_timestamp[];



extern "C" void* fxrps_dlhandle;
extern "C" bool fxrps_stderr_istty;

extern "C" [[noreturn]] void fxrps_fatal_stop_at(const char*fil, int lin);

#define FXRPS_TERMINAL_NORMAL_ESCAPE \
  ("\033[0m")
#define FXRPS_TERMINAL_BOLD_ESCAPE \
  ("\033[1m")
#define FXRPS_TERMINAL_FAINT_ESCAPE \
  ("\033[2m")
#define FXRPS_TERMINAL_ITALICS_ESCAPE \
  ("\033[3m")
#define FXRPS_TERMINAL_UNDERLINE_ESCAPE \
  ("\033[4m")
#define FXRPS_TERMINAL_BLINK_ESCAPE \
  ("\033[5m")

//////////////// fatal error - aborting
extern "C" void rps_fatal_stop_at (const char *, int) __attribute__((noreturn));

#define FXRPS_FATAL_AT_BIS(Fil,Lin,Fmt,...) do {		\
      bool ontty = fxrps_stderr_istty;				\
      fprintf(stderr, "\n\n"					\
              "%s*** foxrps FATAL:%s%s:%d: {%s}\n " Fmt "\n\n",	\
              (ontty?FXRPS_TERMINAL_BOLD_ESCAPE:""),		\
              (ontty?FXRPS_TERMINAL_NORMAL_ESCAPE:""),		\
              Fil, Lin, __PRETTY_FUNCTION__,			\
              ##__VA_ARGS__);					\
    };								\
  fxrps_fatal_stop_at (Fil,Lin); } while(0)
#define FXRPS_FATAL_AT(Fil,Lin,Fmt,...) FXRPS_FATAL_AT_BIS(Fil,Lin,Fmt,##__VA_ARGS__)
#define FXRPS_FATAL(Fmt,...) FXRPS_FATAL_AT(__FILE__,__LINE__,Fmt,##__VA_ARGS__)



#define FXRPS_FATALOUT_AT_BIS(Fil,Lin,...) do {         \
   std::ostringstream outl##Lin;                        \
   outl##Lin <<   __VA_ARGS__ << std::flush;            \
   outl##Lin.flush();                                   \
   bool ontty = fxrps_stderr_istty;                     \
   fprintf(stderr, "\n\n"                               \
           "%s*** fxrps FATAL:%s%s:%d: {%s}\n %s\n\n",  \
           (ontty?FXRPS_TERMINAL_BOLD_ESCAPE:""),       \
           (ontty?FXRPS_TERMINAL_NORMAL_ESCAPE:""),     \
           Fil, Lin, __PRETTY_FUNCTION__,               \
           outl##Lin.str().c_str());                    \
   fxrps_fatal_stop_at (Fil,Lin); } while(0)

#define FXRPS_FATALOUT_AT(Fil,Lin,...) FXRPS_FATALOUT_AT_BIS(Fil,Lin,##__VA_ARGS__)
// typical usage would be FXRPS_FATALOUT("x=" << x)
#define FXRPS_FATALOUT(...) FXRPS_FATALOUT_AT(__FILE__,__LINE__,##__VA_ARGS__)



class FoxRpsWindow : public FXMainWindow
{

  // Macro for class hierarchy declarations
  FXDECLARE(FoxRpsWindow);
private:
  FXVerticalFrame win_vertframe;
  FXMenuBar*win_menubar;
  FXMenuTitle*win_menulabel;
  FXLabel*win_toplabel;
  FXHorizontalSeparator*win_firstsep;
protected:
  FoxRpsWindow() : win_vertframe(this),
    win_menubar(nullptr),
    win_toplabel(nullptr), win_firstsep(nullptr) {};
public:
  virtual void create(void);
  virtual ~FoxRpsWindow();
  FoxRpsWindow(FXApp*app, int width, int height);
  static  FoxRpsWindow*main_window(void);
  enum
  {
    ID__FIRST= FXMainWindow::ID_LAST,
  };
}; // end class FoxRpsWindow


#endif /*   FOXRPS_INCLUDED */
// end of header file foxrps.hh
