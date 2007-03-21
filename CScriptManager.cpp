#include "CScriptManager.h"
#include "CObject.h"
#include "scriptstring/scriptstring.h"
#include <algorithm>
namespace necropolis{
  asIScriptEngine *CScriptManager::engine;
  CScriptManager* CScriptManager::_instance = NULL;
  std::vector<SContextInfo> CScriptManager::contexts;
  std::vector<SContextInfo>::iterator CScriptManager::iter;
  void RegisterTypes(asIScriptEngine *Engine);
  void RegisterGlobalFunctions(asIScriptEngine *Engine);
  void MessageCallback(const asSMessageInfo *msg, void *param)
  {
    ///make use of the speed boost given by using
    ///the ternary operator
    const char *type = ( msg->type == asMSGTYPE_WARNING ) ? type = "WARN"
                      :( msg->type == asMSGTYPE_INFORMATION ) ? type = "INFO" : type = "ERR";

    CLog::dbgOut("AngelScript","MessageCallback","%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
  }
  void as_PrintString(std::string &str)
  {
    CLog::dbgOut("AngelScript","Game","%s", str.c_str());
  }

  void as_PrintNumber(int num)
  {
    CLog::dbgOut("AngelScript","Game","%i", num);
  }

  void as_ScriptSleep(UINT milliSeconds)
  {
    // Get a pointer to the context that s currently being executed
    asIScriptContext *ctx = asGetActiveContext();
    if( ctx )
    {
      // Suspend it's execution. The VM will continue until the current
      // statement is finished and then return from the Execute() method
      ctx->Suspend();

      // Tell the context manager when the context is to continue execution
      CScriptManager::SetSleeping(ctx, milliSeconds);
    }
  }
  CScriptManager* CScriptManager::getInstance(){
    ///is there an instance already?
    if(_instance==NULL){
      ///if not, create it and return it.
      _instance = new CScriptManager();
      return _instance;
    }
    ///if there is, just return it.
    else{
      return _instance;
    }
  }
  CScriptManager::CScriptManager(){
    int r;

    // Create the script engine
    engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

    if( engine == 0 )
    {
      CLog::dbgOut("Script Manager","Constructor","%s", "Failed to create script engine.");
      return;
    }

    // The script compiler will send any compiler messages to the callback function
    engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    // Register the script string type
    // Look at the implementation for this function for more information
    // on how to register a custom string type, and other object types.
    // The implementation is in "/add_on/scriptstring/scriptstring.cpp"
    RegisterScriptString(engine);

    // Register the functions that the scripts will be allowed to use
    RegisterTypes(engine);
    RegisterGlobalFunctions(engine);
  };
  int CScriptManager::CompileScript(std::string &str, std::string &module, std::string &scriptname)
  {
    // Build the two script into separate modules. This will make them have
    // separate namespaces, which allows them to use the same name for functions
    // and global variables.
    int r = engine->AddScriptSection(module.c_str(), scriptname.c_str(), str.c_str(), str.length(), 0, false);
    if( r < 0 ){
      CLog::dbgOut("Script Manager","CompileScript","%s", "AddScriptSection() failed.");
      return -1;
    }

    r = engine->Build(scriptname.c_str());
    if( r < 0 ){
      CLog::dbgOut("Script Manager","CompileScript","%s", "Build() failed.");
      return -1;
    }
    AddContext(engine->GetFunctionIDByDecl(scriptname.c_str(), "void main()"));
    return 0;
  }
  void CScriptManager::ExecuteScripts()
  {
    // Check if the system time is higher than the time set for the contexts
    UINT time = timeGetTime();
    std::for_each( contexts.begin(), contexts.end(), ContextAbort );
    for( iter = contexts.begin(); iter != contexts.end(); iter++)
    {
      if( ( iter->ctx ) && ( iter->sleepUntil < time ) )
      {
        int r = iter->ctx->Execute();
        if( r != asEXECUTION_SUSPENDED )
        {
          iter->ctx->Release();
          iter->ctx = 0;
        }
      }
    }
  }
  void ContextAbort(SContextInfo context)
  {
    if( context.ctx )
      {
        context.ctx->Abort();
        context.ctx->Release();
        context.ctx = 0;
      }
  }
  void CScriptManager::AbortAll()
  {
    // Abort all contexts and release them. The script engine will make
    // sure that all resources held by the scripts are properly released.
    std::for_each( contexts.begin(), contexts.end(), ContextAbort );
    /*for( int n = 0; n < (signed)contexts.size(); n++ )
    {
      if( contexts[n].ctx )
      {
        contexts[n].ctx->Abort();
        contexts[n].ctx->Release();
        contexts[n].ctx = 0;
      }
    }*/
  }

  void CScriptManager::AddContext(int funcID)
  {
    // Create the new context
    asIScriptContext *ctx = engine->CreateContext();
    if( ctx == 0 )
    {
      CLog::dbgOut("Script Manager","AddContext","%s", "Failed to create context - \"%n\"",funcID);
      return;
    }

    // Prepare it to execute the function
    if( ctx->Prepare(funcID) < 0 )
    {
      CLog::dbgOut("Script Manager","AddContext","%s", "Failed to prepare the context - \"%n\"",funcID);
      return;
    }

    // Add the context to the list for execution
    SContextInfo info = {0, ctx};
    contexts.push_back(info);
  }

  void CScriptManager::SetSleeping(asIScriptContext *ctx, UINT milliSeconds)
  {
    // Find the context and update the timeStamp
    // for when the context is to be continued
    for( int n = 0; n < (signed)contexts.size(); n++ )
    {
      if( contexts[n].ctx == ctx )
      {
        contexts[n].sleepUntil = timeGetTime() + milliSeconds;
      }
    }
  }
  void RegisterTypes(asIScriptEngine *engine)
  {
    engine->RegisterObjectType(     "object", sizeof(CObject), asOBJ_CLASS | asOBJ_CLASS_CONSTRUCTOR);
    engine->RegisterObjectProperty( "object", "int x", offsetof(CObject, physics.x));
    engine->RegisterObjectProperty( "object", "int y", offsetof(CObject, physics.y));
    engine->RegisterObjectBehaviour("object", asBEHAVE_CONSTRUCT, "void f()", asMETHOD(CObject, Constructor), asCALL_CDECL_OBJLAST);
  }
  ///Registers all global functions used in the scripting language.
  ///if the function library becomes too large, this function can
  ///be branched off into several other functions that register
  ///them by category.
  void RegisterGlobalFunctions(asIScriptEngine *engine)
  {
    int r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(as_PrintString), asCALL_CDECL);
    if( r >= 0 )
      r = engine->RegisterGlobalFunction("void Print(int)", asFUNCTION(as_PrintNumber), asCALL_CDECL);
    else return;
    if( r >= 0 )
      r = engine->RegisterGlobalFunction("void Sleep(uint)", asFUNCTION(as_ScriptSleep), asCALL_CDECL);
    else return;
    if( r >= 0 );
    else return;
  }
}
