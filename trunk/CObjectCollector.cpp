#include "CObjectCollector.h"
namespace necropolis{
  ///Set instance to NULL so that there is no problem with the singleton.
  CObjectCollector* CObjectCollector::_instance = NULL;

  CObjectCollector::CObjectCollector(){
  };

  ///getInstance returns the instance of the singleton, creating it if not already done.
  CObjectCollector* CObjectCollector::getInstance(){
    ///is there an instance already?
    if(_instance==NULL){
      ///if not, create it and return it.
      _instance = new CObjectCollector();
      return _instance;
    }
    ///if there is, just return it.
    else{
      return _instance;
    }
  }
  objectRef CObjectCollector::NewObject(CObject* a_objectPtr){return true;};
  objectRef CObjectCollector::NewObject(CObject& a_objectPtr){return true;};
  objectRef CObjectCollector::NewObject(CObject a_objectPtr){return true;};
  void CObjectCollector::FreeObject(objectRef a_objectRef){};
}


