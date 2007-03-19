#ifndef CGLOBAL_H
#define CGLOBAL_H
#ifndef NULL
  #define NULL 0
#endif
namespace necropolis{
  class CGlobal{
    static CGlobal* _instance;
  public:
    CGlobal();
    static CGlobal* getInstance();
  };
}
#endif

