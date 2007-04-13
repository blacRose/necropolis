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
}


