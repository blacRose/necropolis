#include "CLog.h"
#include <stdio.h>
#include <stdarg.h>
#ifdef DEBUG_TRACE
  #include <windows.h>
#endif
namespace necropolis{
  ///Constructor handles the creation of the Debug Console.
  CLog::CLog(){
#ifdef DEBUG_TRACE
    ///If the console gets created
    if(AllocConsole())
    {
      ///then open the console to stdout
      freopen("CONOUT$", "wt", stdout);

      ///and set title and text color
      SetConsoleTitle("Necropolis : Debug Console");
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
      printf("============Necropolis Debug Console============\n\n");
    }
#endif
  };
  ///Print a message to the debug console.
  int CLog::dbgOut(char* cls, char* func, char* fmt,...){
			int retval=0;
      ///create va_list and load all arguments
#ifdef DEBUG_TRACE
      va_list ap;
			va_start(ap, fmt);
			if(cls!=NULL)
			{
				printf("  %s", cls);
				if(func!=NULL)
				{
					printf("::%s() - \"", func);
				}else{
					printf(" - \"");
				}
			retval = vprintf(fmt, ap); /// Call vprintf
			printf("\"");
			}
			else {
				retval = vprintf(fmt, ap); /// Call vprintf
			}
			printf("\n");

			va_end(ap); /// Cleanup the va_list
#endif
			return retval;
		};
}
