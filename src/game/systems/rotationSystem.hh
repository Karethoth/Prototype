#ifndef __ROTATIONSYSTEM_HH__
#define __ROTATIONSYSTEM_HH__

#include "../../engine/baseSystem.hh"

class RotationSystem : public Engine::BaseSystem
{
 public:
  RotationSystem();
  ~RotationSystem();

  virtual bool Tick( Engine::Message *message );


 protected:
  virtual void* Run();
};

#endif // __ROTATIONSYSTEM_HH__
