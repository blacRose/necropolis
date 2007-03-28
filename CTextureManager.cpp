#include "CTextureManager.h"
#include <SDL_image.h>
namespace necropolis{
  ///Set instance to NULL so that there is no problem with the singleton.
  CTextureManager* CTextureManager::_instance = NULL;
  unsigned int CTextureManager::iTexPos = 1;
  CTextureManager::CTextureManager(){
  };

  ///getInstance returns the instance of the singleton, creating it if not already done.
  CTextureManager* CTextureManager::getInstance(){
    ///is there an instance already?
    if(_instance==NULL){
      ///if not, create it and return it.
      _instance = new CTextureManager();
      return _instance;
    }
    ///if there is, just return it.
    else{
      return _instance;
    }
  }
  unsigned int CTextureManager::LoadTexture(std::string fname)
  {
    mTextureList[iTexPos] = IMG_Load(fname.c_str());
    if(iTexPos%31 == 0)
      mTextureList.resize(mTextureList.size()+32);
    if(!mTextureList[iTexPos])
    {
      return 0;
    }else{
      return iTexPos++;
    }
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
