#include "CVideo.h"
extern necropolis::CLog* Log;
namespace necropolis{
	int CVideo::Initialize(int w, int h, int bpp){
    if ( !SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE|SDL_DOUBLEBUF) )
    {
			DBGOUT( NULL, NULL, "Unable to set 640x480 video: %s\n", SDL_GetError());
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
    DBGOUT( NULL, NULL, "Allow Hardware Surfaces: %i", info->hw_available);
    DBGOUT( NULL, NULL, "Window Manager Available: %i", info->wm_available);
    DBGOUT( NULL, NULL, "Hardware Accelerated Blits: %i", info->blit_hw);
    DBGOUT( NULL, NULL, "Software Accelerated Blits: %i", info->blit_sw);
    DBGOUT( NULL, NULL, "Available Video Memory: %i", info->video_mem);
	}
}
