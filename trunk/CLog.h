#ifndef CLOG_H
#define CLOG_H
#ifdef DEBUG_TRACE
  #include <windows.h>
#endif
#ifndef NULL
  #define NULL 0
#endif
#include "template_singleton.h"
namespace necropolis{
  class CLog: public
		Singleton<CLog>{
  public:
    CLog();
    static int dbgOut(char* cls, char* func, char* fmt,...);
  };
}
#endif
