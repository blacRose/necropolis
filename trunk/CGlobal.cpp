#include "CGlobal.h"
namespace necropolis{
  ///Set instance to NULL so that there is no problem with the singleton.
  CGlobal* CGlobal::_instance = NULL;

  ///Constructor handles the creation of the Debug Console.
  CGlobal::CGlobal(){
  };

  ///getInstance returns the instance of the singleton, creating it if not already done.
  CGlobal* CGlobal::getInstance(){
    ///is there an instance already?
    if(_instance==NULL){
      ///if not, create it and return it.
      _instance = new CGlobal();
      return _instance;
    }
    ///if there is, just return it.
    else{
      return _instance;
    }
  }
}

