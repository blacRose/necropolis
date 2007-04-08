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
extern std::vector<SDL_Surface*> mTextureList;
namespace necropolis{
	typedef unsigned int textureRef_t;
  class CTextureManager : public
					Singleton<CTextureManager>{
  private:
  public:
    static unsigned int iTexPos;
    CTextureManager();
    ~CTextureManager();
    static void DrawTexture(unsigned int tID, int x, int y, SDL_Surface* screen);
    static unsigned int LoadTexture(std::string fname);
    static bool FreeTexture(unsigned int texid);
  };
}
#endif


