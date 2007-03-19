#include "CScriptManager.h"
namespace necropolis{
  void MessageCallback(const asSMessageInfo *msg, void *param)
  {
    const char *type = "ERR ";
    if( msg->type == asMSGTYPE_WARNING )
      type = "WARN";
    else if( msg->type == asMSGTYPE_INFORMATION )
      type = "INFO";

    CLog::dbgOut("AngelScript","MessageCallback","%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
  }

  CScriptManager::CScriptManager(){
    int r;

    // Create the script engine
    engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

    if( engine == 0 )
    {
      std::cout << "Failed to create script engine." << std::endl;
      return;
    }

    // The script compiler will send any compiler messages to the callback function
    engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    // Register the script string type
    // Look at the implementation for this function for more information
    // on how to register a custom string type, and other object types.
    // The implementation is in "/add_on/scriptstring/scriptstring.cpp"
    //RegisterScriptString(engine);

    // Register the functions that the scripts will be allowed to use
    /*r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(PrintString), asCALL_CDECL); assert( r >= 0 );
    r = engine->RegisterGlobalFunction("void Print(int)", asFUNCTION(PrintNumber), asCALL_CDECL); assert( r >= 0 );
    r = engine->RegisterGlobalFunction("void Sleep(uint)", asFUNCTION(ScriptSleep), asCALL_CDECL); assert( r >= 0 );*/

  };
}
