#ifndef CEVENTDIRECTOR_H
#define CEVENTDIRECTOR_H
#include "CEvent.h"
#include <list>
#include <SDL.h>
namespace necropolis{
  class CEventDirector{
	private:
		std::list<CEvent> evtStack;
  public:
		void ProcessEvents();
		int eventOnStack();
		void pushEvent(CEvent evt);
		CEvent popEvent(void);
		CEvent peekEvent(void);
  };
}
#endif
