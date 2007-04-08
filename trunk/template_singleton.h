#ifndef TEMPLATE_SINGLETON_H
#define TEMPLATE_SINGLETON_H
#ifndef NULL
	#define NULL 0
#endif
template <typename T>
class Singleton
{
protected:
   Singleton() {}
   virtual ~Singleton() {}
   static T *my_singleton;
public:
   static void create() {my_singleton = new T();}
   static void destroy() {delete my_singleton; my_singleton = NULL;}
   static T *getPtr() {return my_singleton;}
   static T &getRef() {return *my_singleton;}
private:
   Singleton(const Singleton &s);
   Singleton &operator = (const Singleton &s);
};
#endif
