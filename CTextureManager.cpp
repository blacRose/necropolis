#include "CTextureManager.h"
#include <SDL_image.h>
namespace necropolis{
  unsigned int CTextureManager::LoadTexture(std::string fname)
  {
    if(iTexPos%31 == 0)
      mTextureList.resize(mTextureList.size()+32);
    mTextureList[iTexPos] = IMG_Load(fname.c_str());
    if(!mTextureList[iTexPos])
    {
      return 0;
    }else{
      return iTexPos++;
    }
  }
  bool CTextureManager::FreeTexture(unsigned int texid)
  {
  	if((texid<1)||(texid>iTexPos))
  	{
  		SDL_FreeSurface(mTextureList.at(texid));
  		//std::vector<SDL_Surface*>::iterator t_iterator = mTextureList.at(texid);
			return true;
  	}
  	else return false;
  }
  void CTextureManager::DrawTexture(unsigned int tID, int x, int y, SDL_Surface* screen)
  {
    if((tID<1)||(tID>iTexPos))
      return;
    else
    {
      SDL_Rect drct = {x,y, mTextureList[tID]->w, mTextureList[tID]->h};
      SDL_BlitSurface(mTextureList[tID], NULL, screen, &drct);
    }
  }
}
