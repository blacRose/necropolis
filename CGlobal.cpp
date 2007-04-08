#include "CGlobal.h"
namespace necropolis{
	bool run;
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
