#include "CGlobal.h"
namespace necropolis{
	bool run;
	void CGlobal::resetFPS()
	{
		framesPerSecond = 0;
	}
	void CGlobal::resetFPSCounter()
	{
		timeCurrent = SDL_GetTicks();
		timeSecond = timeCurrent;
	}
	void CGlobal::tickFPS()
	{
		timeCurrent = SDL_GetTicks();
		timeDelta = (timeCurrent - timeSecond);
		if(timeDelta > 1000)
		{
			CLog::dbgOut( "Global", "tickFPS", "%i", framesPerSecond);
			timeSecond = SDL_GetTicks();
			framesPerSecond = 0;
		}
	}
  bool CGlobal::isRunning(){
  	return run;
  }
	void CGlobal::setRunning(bool b){
 		run = b;
	}
	bool CGlobal::ProcessEvent(CEvent evt){
		switch(evt.EventType){
			case CEvent::EVT_WINDOWCLOSE:
				setRunning(false);
				break;
			case CEvent::EVT_KEYPRESS:
				if(evt.data.keyPress.key == SDLK_ESCAPE)
					setRunning(false);
				break;
		}
	}
}
