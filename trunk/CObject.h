#ifndef COBJECT_H
#define COBJECT_H
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
      int hspeed:8;
      int vspeed:8;
      int direction:16;
    }physics;
    CObject(){};
    CObject(int a_x, int a_y)
    {
      physics.x = a_x;
      physics.y = a_y;
    };
    void Constructor(CObject *obj)
    {
      obj = new CObject();
    };
    void Destructor(CObject *obj)
    {
      obj->~CObject();
    }
    virtual ~CObject(){};
    virtual void setInstance(int a_inst){};
  };
}
#endif
