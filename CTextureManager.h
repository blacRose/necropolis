#ifndef CTEXTUREANAGER_H
#define CTEXTUREANAGER_H
#include <SDL.h>
#include <vector>
#include <string>
#include "template_singleton.h"
///I add this into most headers because I was getting an
///error I have never gotten about NULL not being defined
#ifndef NULL
  #define NULL 0
#endif
namespace necropolis{
	typedef unsigned int textureRef_t;
  class CTextureManager{
  private:
		std::vector<SDL_Surface*> mTextureList;
  public:
    unsigned int iTexPos;
    CTextureManager(){iTexPos = 1;mTextureList.reserve(32);};
    ~CTextureManager();
    void DrawTexture(unsigned int tID, int x, int y, SDL_Surface* screen);
    unsigned int LoadTexture(std::string fname);
    bool FreeTexture(unsigned int texid);
  };
}
#endif


