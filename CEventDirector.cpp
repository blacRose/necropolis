#include "CEventDirector.h"
namespace necropolis{
	void CEventDirector::pushEvent(CEvent evt){
		evtStack.push_back(evt);
	}
	CEvent CEventDirector::popEvent(void){
		CEvent t_evt = evtStack.front();
		evtStack.pop_front();
		return t_evt;
	}
	CEvent CEventDirector::peekEvent(void){
		return evtStack.front();
	}
	void CEventDirector::ProcessEvents(){
		SDL_Event event;
		CEvent t_evt;
		while (SDL_PollEvent(&event))
		{
				// check for messages
				switch (event.type)
				{
						// exit if the window is closed
				case SDL_QUIT:
								t_evt.EventType = CEvent::EVT_WINDOWCLOSE;
								pushEvent(t_evt);
								break;

						// check for keypresses
				case SDL_KEYDOWN:
						{
								t_evt.EventType = CEvent::EVT_KEYPRESS;
								t_evt.data.keyPress.key = event.key.keysym.sym;
								pushEvent(t_evt);
								break;
						}
				case SDL_KEYUP:
						{
								t_evt.EventType = CEvent::EVT_KEYRELEASE;
								t_evt.data.keyRelease.key = event.key.keysym.sym;
								pushEvent(t_evt);
								break;
						}
				case SDL_MOUSEBUTTONDOWN:
						{
								t_evt.EventType = CEvent::EVT_MOUSEPRESS;
								t_evt.data.mousePress.button = event.button.button;
								t_evt.data.mousePress.x = event.button.x;
								t_evt.data.mousePress.y = event.button.y;
								pushEvent(t_evt);
								break;
						}
				case SDL_MOUSEBUTTONUP:
						{
								t_evt.EventType = CEvent::EVT_MOUSERELEASE;
								t_evt.data.mouseRelease.button = event.button.button;
								t_evt.data.mouseRelease.x = event.button.x;
								t_evt.data.mouseRelease.y = event.button.y;
								break;
								pushEvent(t_evt);
						}
				default:
						break;
				} // end switch
		} // end of message processing
	}
	int CEventDirector::eventOnStack(){
		return (evtStack.size() <= 1 );
	}
}
