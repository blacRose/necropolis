#include <string>
#include "CLog.h"
#include "CObjectCollector.h"
#include "CObject.h"
#include "CScriptManager.h"
#include "CTextureManager.h"
#include <angelscript.h>
namespace necropolis{
  void as_PrintString(std::string &str);
  void as_PrintNumber(int num);
  void as_ScriptSleep(unsigned int milliSeconds);
  bool as_GetKeyPressed(int key);
  ///Typedefinitions:
  /** Type: object
   ** use:  "
   **/
  void as_SetObjectTag(CObject* object, std::string tag);
  void as_SetObjectX(CObject* object, int x);
  void as_SetObjectY(CObject* object, int y);
  std::string as_GetObjectTag(CObject* object);
  int as_GetObjectX(CObject* object);
  int as_GetObjectY(CObject* object);
  int as_SetObjectSprite(CObject* object, std::string fname);
  CObject* as_New_object(int x, int y);
}
