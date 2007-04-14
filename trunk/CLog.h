#ifndef CLOG_H
#define CLOG_H
#ifdef DEBUG_TRACE
  #include <windows.h>
  #define DBGOUT CLog::dbgOut
#else
	#define DBGOUT //
#endif
#ifndef NULL
  #define NULL 0
#endif
namespace necropolis{
  class CLog{
  public:
    CLog();
    static int dbgOut(char* cls, char* func, char* fmt,...);
  };
}
#endif
