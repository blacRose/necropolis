#include "CVideo.h"
extern necropolis::CLog* Log;
namespace necropolis{
	int CVideo::Initialize(int w, int h, int bpp){
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      //Log->dbgOut( NULL, NULL, "Unable to init SDL: %s\n", SDL_GetError());
      return false;
    }
    if ( !SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE|SDL_DOUBLEBUF) )
    {
			Log->dbgOut( NULL, NULL, "Unable to set 640x480 video: %s\n", SDL_GetError());
      return false;
    }
    return true;
	}

	SDL_Surface* CVideo::getScreen(){
		//return screen;
		return SDL_GetVideoSurface();
	}

	void CVideo::OutputDiagnostic(){
    const SDL_VideoInfo *info = SDL_GetVideoInfo();
    Log->dbgOut( NULL, NULL, "Allow Hardware Surfaces: %i", info->hw_available);
    Log->dbgOut( NULL, NULL, "Window Manager Available: %i", info->wm_available);
    Log->dbgOut( NULL, NULL, "Hardware Accelerated Blits: %i", info->blit_hw);
    Log->dbgOut( NULL, NULL, "Software Accelerated Blits: %i", info->blit_sw);
    Log->dbgOut( NULL, NULL, "Available Video Memory: %i", info->video_mem);
	}
}
