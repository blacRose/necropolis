#ifndef CSCRIPTMANAGER_H
#define CSCRIPTMANAGER_H
#include "CLog.h"
#include <iostream>  /// cout
#include <assert.h>  /// assert()
#include <vector>
#include <angelscript.h>
#include "scriptstring/scriptstring.h"

#include <conio.h>   /// kbhit(), getch()
#include <windows.h> /// timeGetTime()
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
    static asIScriptEngine *engine;
    static CScriptManager* _instance;
  public:
    static int iKeyArray[256];
    CScriptManager();
    ~CScriptManager();
    static CScriptManager* getInstance();
    static void AddContext(int funcID);
    static void ExecuteScripts();
    static void SetSleeping(asIScriptContext *ctx, UINT milliSeconds);
    static void AbortAll();
    static int CompileScript(std::string &str, std::string &module, std::string &scriptname);
    static std::vector<SContextInfo>::iterator iter;
    static std::vector<SContextInfo> contexts;
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
