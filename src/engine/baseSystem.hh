#ifndef __BASESYSTEM_HH__
#define __BASESYSTEM_HH__

#include "entitySystem.hh"
#include "message.hh"

#include <memory>


namespace Engine
{
  class BaseSystem
  {
   public:
    virtual ~BaseSystem(){};

    bool IsRunning();
    void SetPriority( int );
    void SetEntitySystem( std::shared_ptr<Engine::EntitySystem> );

    static void* RunSystem( void *system )
    {
      BaseSystem *sys = static_cast<BaseSystem*>( system );
      return sys->Run();
    };

    virtual bool Tick( Message *message ) = 0;


   protected:
    virtual void* Run() = 0;

    bool isRunning;
    int priority;

    std::shared_ptr<Engine::EntitySystem> entitySystem;
  };
}


#endif // __BASESYSTEM_HH__
