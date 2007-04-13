#ifndef CVIDEO_H
#define CVIDEO_H
#include <SDL.h>
#include "CLog.h"
#include "template_singleton.h"
namespace necropolis{
	class CVideo{
	private:
		//static SDL_Surface* screen;
	public:
		int Initialize(int w = 640, int h = 480, int bpp = 32);
		void OutputDiagnostic();
		SDL_Surface* getScreen();
	};
}
#endif
