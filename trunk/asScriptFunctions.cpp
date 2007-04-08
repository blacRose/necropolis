#include "asScriptFunctions.h"
namespace necropolis{
  void as_PrintString(std::string &str)
  {
    CLog::dbgOut("AngelScript","Game","%s", str.c_str());
  }

  void as_PrintNumber(int num)
  {
    CLog::dbgOut("AngelScript","Game","%i", num);
  }

  void as_WindowSetTitle(std::string name)
  {
    SDL_WM_SetCaption(name.c_str(),NULL);
  }

  void as_ScriptSleep(UINT milliSeconds)
  {
    /// Get a pointer to the context that s currently being executed
    asIScriptContext *ctx = asGetActiveContext();
    if( ctx )
    {
      /// Suspend it's execution. The VM will continue until the current
      /// statement is finished and then return from the Execute() method
      ctx->Suspend();

      /// Tell the context manager when the context is to continue execution
      CScriptManager::SetSleeping(ctx, milliSeconds);
    }
  }
  bool as_GetKeyPressed(int key)
  {
    return (SDL_GetKeyState(NULL)[key]==true);
  }
  void as_SetObjectX(CObject* object, int x)
              {object->physics.x = x;}
  int as_GetObjectX(CObject* object)
              {return object->physics.x;}
  void as_SetObjectY(CObject* object, int y)
              {object->physics.y = y;}
  int as_GetObjectY(CObject* object)
              {return object->physics.y;}
  void as_SetObjectTag(CObject* object, std::string tag)
              {object->_tag = tag;}
  std::string as_GetObjectTag(CObject* object)
              {return object->_tag;}
  CObject* as_New_object(int x, int y)
  {
    CObject* t_obj = new necropolis::CObject();
    t_obj->physics.x = x;
    t_obj->physics.y = y;
    t_obj->_surface = 0;
    int obj = necropolis::CObjectCollector::NewObject(t_obj);
    return t_obj;
  }
  int as_SetObjectSprite(CObject* object, std::string fname)
  {
  	object->setSprite(object, fname);
  }
}
