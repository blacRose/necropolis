#ifndef CLOG_H
#define CLOG_H
#include <windows.h>
#define DEBUG_TRACE 0
#ifndef NULL
  #define NULL 0
#endif
namespace necropolis{
  class CLog{
    static CLog* _instance;
  public:
    CLog();
    static int dbgOut(char* cls, char* func, char* fmt,...);
    static CLog* getInstance();
  };
}
#endif
