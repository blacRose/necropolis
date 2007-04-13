#include "asScriptFunctions.h"
	extern necropolis::CScriptManager* ScriptManager;
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
	void as_LoadScript(std::string name)
	{
    ScriptManager->CompileScriptFromFile(name,name,name);
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
      ScriptManager->SetSleeping(ctx, milliSeconds);
    }
  }
  bool as_GetKeyPressed(int key)
  {
    return (SDL_GetKeyState(NULL)[key]==true);
  }
  void as_SetObjectX(objectRef_t object, int x)
  {
  	ObjCollector->GetObjectByRef(object)->physics.x = x;
	}
  int as_GetObjectX(objectRef_t object)
  {
  	return ObjCollector->GetObjectByRef(object)->physics.x;
	}
  void as_SetObjectY(objectRef_t object, int y)
  {
  	ObjCollector->GetObjectByRef(object)->physics.y = y;
	}
  int as_GetObjectY(objectRef_t object)
  {
  	return ObjCollector->GetObjectByRef(object)->physics.y;
	}
  void as_SetObjectTag(objectRef_t object, std::string tag)
  {
  	ObjCollector->GetObjectByRef(object)->_tag = tag;
	}
  std::string as_GetObjectTag(objectRef_t object)
  {
  	return ObjCollector->GetObjectByRef(object)->_tag;
	}
  objectRef_t as_New_object(int x, int y)
  {
    CObject* t_obj = new necropolis::CObject();
    t_obj->physics.x = x;
    t_obj->physics.y = y;
    t_obj->_surface = 0;
    objectRef_t obj = ObjCollector->NewObject(t_obj);
    CLog::dbgOut("AngelScript","Object","New Object %i", obj);
    return obj;
  }
  int as_SetObjectSprite(objectRef_t object, std::string fname)
  {
  	ObjCollector->GetObjectByRef(object)->setSprite(fname);
  }
}
