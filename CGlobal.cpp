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
			DBGOUT( "Global", "tickFPS", "%i", framesPerSecond);
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
	void CGlobal::Init()
	{
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      DBGOUT( "CGlobal", "Init", "Unable to init SDL: %s\n", SDL_GetError());
      return;
    }
	}
	void CGlobal::Shutdown()
	{
    // all is well ;)
    SDL_Quit();
    DBGOUT( NULL, NULL, "Exited cleanly");
	}
}
