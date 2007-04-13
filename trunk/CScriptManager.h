#ifndef CSCRIPTMANAGER_H
#define CSCRIPTMANAGER_H
#include "CLog.h"
#include <iostream>  /// cout
#include <assert.h>  /// assert()
#include <vector>
#include <angelscript.h>
#include "scriptstring/scriptstring.h"
#include "template_singleton.h"

#ifndef __LINUX__
#include <fstream>
#include <string>
#include <iterator>
#include <conio.h>   /// kbhit(), getch()
  #include <windows.h> /// timeGetTime()
#else
  typedef unsigned int UINT;
#endif
///I add this into most headers because I was getting an
///error I have never gotten about NULL not being defined
#ifndef NULL
  #define NULL 0
#endif
///Forward declaration
struct SContextInfo;
namespace necropolis{
  ///Callback for AngelScript Warnings, Errors, and Info
  void MessageCallback(const asSMessageInfo *msg, void *param);

  class CScriptManager{
  private:
     asIScriptEngine *engine;
  public:
     int iKeyArray[256];
    ~CScriptManager();
     void Initialize();
     void AddContext(int funcID);
     void ExecuteScripts();
     static void SetSleeping(asIScriptContext *ctx, UINT milliSeconds);
     void AbortAll();
     int CompileScript(std::string &str, std::string &module, std::string &scriptname);
     int CompileScriptFromFile(std::string &fname, std::string &module, std::string &scriptname);
     int CompileScriptFromFile(std::string fname);
     std::vector<SContextInfo>::iterator iter;
     static std::vector<SContextInfo> contexts;
     static std::vector<SContextInfo> contextTodo;
     static bool isInScript;
  };
}
///The following classes are used for concurrent script
///execution with AngelScript, and should only be modified
///by somebody who knows exactly what they're doing.
struct SContextInfo
{
	UINT sleepUntil;
	asIScriptContext *ctx;
};
#endif
