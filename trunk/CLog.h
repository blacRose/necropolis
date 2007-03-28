#ifndef CLOG_H
#define CLOG_H
#ifndef __LINUX__
  #define DEBUG_TRACE
#endif
#ifdef DEBUG_TRACE
  #include <windows.h>
#endif
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
