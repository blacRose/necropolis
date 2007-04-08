#ifndef CEVENTDIRECTOR_H
#define CEVENTDIRECTOR_H
#include <list>
#include "CEvent.h"
#include <SDL.h>
#include "template_singleton.h"
namespace necropolis{
  class CEventDirector: public
		Singleton<CEventDirector>{
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
