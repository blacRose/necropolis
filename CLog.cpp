#include "CLog.h"
#include <stdio.h>
#include <stdarg.h>
#ifdef DEBUG_TRACE
  #include <windows.h>
#endif
namespace necropolis{
  ///Set instance to NULL so that there is no problem with the singleton.
  CLog* CLog::_instance = NULL;

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

  ///getInstance returns the instance of the singleton, creating it if not already done.
  CLog* CLog::getInstance(){
    ///is there an instance already?
    if(_instance==NULL){
      ///if not, create it and return it.
      _instance = new CLog();
      return _instance;
    }
    ///if there is, just return it.
    else{
      return _instance;
    }
  }

  ///Print a message to the debug console.
  int CLog::dbgOut(char* cls, char* func, char* fmt,...){
			int retval=0;
      ///create va_list and load all arguments
#ifdef DEBUG_TRACE
      va_list ap;
			va_start(ap, fmt);
			printf("  ");
			if(cls!=NULL)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED);
				printf("%s", cls);
				if(func!=NULL)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
					printf("::");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
					printf("%s", func);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
					printf("() - \"");
				}else{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
					printf(" - \"");
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
			retval = vprintf(fmt, ap); /* Call vprintf */
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			printf("\"\n");
			va_end(ap); /* Cleanup the va_list */
#endif
			return retval;
		};
}
