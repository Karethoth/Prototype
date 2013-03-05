#ifndef __MOVEMENTSYSTEM_HH__
#define __MOVEMENTSYSTEM_HH__

#include "../../engine/baseSystem.hh"

class MovementSystem : public Engine::BaseSystem
{
 public:
  MovementSystem();
  ~MovementSystem();

  virtual bool Tick( Engine::Message *message );


 protected:
  virtual void* Run();
};

#endif // __MOVEMENTSYSTEM_HH__
