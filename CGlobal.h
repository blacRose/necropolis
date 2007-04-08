#ifndef CGLOBAL_H
#define CGLOBAL_H
#ifndef NULL
  #define NULL 0
#endif
#include "template_singleton.h"
#include "CEvent.h"
#include <SDL.h>
namespace necropolis{
  class CGlobal : public
					Singleton<CGlobal>{
  public:
		//bool run;
		bool isRunning();
		void setRunning(bool b=true);
		bool ProcessEvent(CEvent evt);
  };
}
#endif

