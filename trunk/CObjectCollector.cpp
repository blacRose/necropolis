#include "CObjectCollector.h"
namespace necropolis{
  std::vector<CObject*> CObjectCollector::mObjectList;

  objectRef CObjectCollector::NewObject(CObject* a_objectPtr)
  {
    mObjectList.push_back(a_objectPtr);

    return true;
  };
  objectRef CObjectCollector::NewObject(CObject& a_objectPtr)
  {
    mObjectList.push_back(&a_objectPtr);
    return true;
  };
  objectRef CObjectCollector::NewObject(CObject a_objectPtr)
  {
    mObjectList.push_back(&a_objectPtr);
    return true;
  };
  void CObjectCollector::FreeObject(objectRef a_objectRef){};
}


