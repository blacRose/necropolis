#ifndef CGLOBAL_H
#define CGLOBAL_H
#ifndef NULL
  #define NULL 0
#endif
#include "CLog.h"
#include "CEvent.h"
#include <SDL.h>
extern bool run;
namespace necropolis{
  class CGlobal{
  public:
		Uint32 timeCurrent, timeSecond, timeDelta;
		int framesPerSecond;

		/// void resetFPSCounter()
		///	-resets the variables
		///
		void resetFPSCounter();

		/// void tickFPS()
		///
		///
		void tickFPS();

		/// void resetFPS()
		///
		///
		void resetFPS();
		static bool isRunning();
		static void setRunning(bool b=true);
		static bool ProcessEvent(CEvent evt);
  };
}
#endif

