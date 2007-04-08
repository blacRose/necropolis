#ifndef COBJECTCOLLECTOR_H
#define COBJECTCOLLECTOR_H
#include "CObject.h"
#include <vector>
#include "template_singleton.h"
///I add this into most headers because I was getting an
///error I have never gotten about NULL not being defined
#ifndef NULL
  #define NULL 0
#endif
///the type 'objectRef' is given to every object so that
///they can easily be tracked by the object collector.
typedef unsigned int objectRef;
namespace necropolis{
  class CObjectCollector : public
					Singleton<CObjectCollector>{
  private:
  public:
    static std::vector<CObject*> mObjectList;
    ~CObjectCollector();
    ///NewObject( CObject* a_objectPtr )
    ///adds an object to the list and returns it's reference.
    static objectRef NewObject(CObject* a_objectPtr);
    static objectRef NewObject(CObject& a_objectPtr);
    static objectRef NewObject(CObject a_objectPtr);
    ///FreeObject( objectRef a_objectRef )
    ///removes an object from the list, freeing it in the process
    static void FreeObject(objectRef a_objectRef);
  };
}
#endif

