#include <string>
#include "CLog.h"
#include "CObjectCollector.h"
#include "CObject.h"
#include "CScriptManager.h"
#include "CTextureManager.h"
#include <angelscript.h>
#include "main.h"
extern necropolis::CObjectCollector* ObjCollector;
namespace necropolis{
  void as_PrintString(std::string &str);
  void as_PrintNumber(int num);
  void as_ScriptSleep(unsigned int milliSeconds);
  void as_WindowSetTitle(std::string name);
  bool as_GetKeyPressed(int key);
  void as_LoadScript(std::string name);
  ///Typedefinitions:
  /** Type: object
   ** use:  "
   **/
  void as_SetObjectTag(objectRef_t object, std::string tag);
  void as_SetObjectX(objectRef_t object, int x);
  void as_SetObjectY(objectRef_t object, int y);
  std::string as_GetObjectTag(objectRef_t object);
  int as_GetObjectX(objectRef_t object);
  int as_GetObjectY(objectRef_t object);
  int as_SetObjectSprite(objectRef_t object, std::string fname);
  objectRef_t as_New_object(int x, int y);
}
