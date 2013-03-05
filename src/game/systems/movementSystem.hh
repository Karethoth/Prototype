#ifndef __MOVEMENTSYSTEM_HH__
#define __MOVEMENTSYSTEM_HH__

#include "../../engine/baseSystem.hh"

class MovementSystem : public Engine::BaseSystem
{
 public:
  MovementSystem();
  ~MovementSystem();

 protected:
  virtual void* Run();
  virtual bool Tick( Engine::Message *message );
};

#endif // __MOVEMENTSYSTEM_HH__
