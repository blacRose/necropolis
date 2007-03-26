#ifndef COBJECT_H
#define COBJECT_H
#include <string>
#include <SDL.h>
#include "CLog.h"
#ifndef NULL
  #define NULL 0
#endif
namespace necropolis{
  class CObject{
  private:
    unsigned int _instance;
  public:
    ///the physics struct contains all information related to
    ///the objects location, speed, and direction
    struct{
      int x;
      int y;
      int hspeed;
      int vspeed;
      int direction;
    }physics;
    //SDL_Surface* _surface;
    unsigned int _surface;
    std::string _tag;
    CObject()
    {
      physics.x = 0;
      physics.y = 0;
      CLog::dbgOut("CObject","Costructor","New Object Created");
    };
    void Constructor(CObject *obj)
    {
      obj = new CObject();
      obj->physics.x = 0;
      obj->physics.y = 0;
      obj->_tag = "";
      obj->_surface = 0;
    };
    void Destructor(CObject *obj)
    {
      obj->~CObject();
      obj = 0;
    }
    void Update(CObject *obj)
    {
      //obj->_surface->clip_rect.x = obj->physics.x;
      //obj->_surface->clip_rect.y = obj->physics.y;
    }
    virtual ~CObject(){};
    virtual void setInstance(int a_inst){};
  };
}
#endif
