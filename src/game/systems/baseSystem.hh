#ifndef __BASESYSTEM_HH__
#define __BASESYSTEM_HH__

#include "../../engine/entitySystem.hh"

class BaseSystem
{
 public:
  virtual ~BaseSystem(){};

  bool IsRunning();
  void SetPriority( int );
  void SetEntitySystem( Engine::EntitySystem *entitySystem );

  static void* RunSystem( void *system )
  {
    BaseSystem *sys = static_cast<BaseSystem*>( system );
    return sys->Run();
  };


 protected:
  virtual void* Run() = 0;

  bool isRunning;
  int priority;

  Engine::EntitySystem *entitySystem;
};



#endif // __BASESYSTEM_HH__
