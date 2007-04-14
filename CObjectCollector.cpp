#include "CObjectCollector.h"
namespace necropolis{
  objectRef CObjectCollector::NewObject(CObject* a_objectPtr)
  {
    mObjectList.push_back(a_objectPtr);
    return mObjectList.size();
  };
  objectRef CObjectCollector::NewObject(CObject& a_objectPtr)
  {
    mObjectList.push_back(&a_objectPtr);
    return mObjectList.size();
  };
  objectRef CObjectCollector::NewObject(CObject a_objectPtr)
  {
    mObjectList.push_back(&a_objectPtr);
    return mObjectList.size();
  };
  void CObjectCollector::FreeObject(objectRef a_objectRef){};
  CObject* CObjectCollector::GetObjectByRef(objectRef oRef)
  {
  	return mObjectList[oRef-1];
  }
  void CObjectCollector::DrawAllObjects(SDL_Surface* screen)
  {
  	std::vector<necropolis::CObject*>::iterator it = mObjectList.begin();
		for(;it != mObjectList.end(); it++)
		{
			TexMan->DrawTexture((*it)->_surface,(*it)->physics.x,(*it)->physics.y,screen);
		}
  }
}


