#ifndef BINSTANCE_H
#define BINSTANCE_H
namespace necropolis{
  template <T>
  class T{
    static T* _instance;
  public:
    static T* getInstance(){
    if(_instance!=NULL){
      _instance = new T;
      return _instance;
    }
    else{
      return _instance;
    }
  };
}
#endif

