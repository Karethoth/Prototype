#ifndef __MOVEMENTSYSTEM_HH__
#define __MOVEMENTSYSTEM_HH__

#include "baseSystem.hh"

class MovementSystem : public BaseSystem
{
 public:
  MovementSystem();
  ~MovementSystem();

 protected:
  virtual void* Run();
};

#endif // __MOVEMENTSYSTEM_HH__
