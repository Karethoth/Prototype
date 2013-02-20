#ifndef __VELOCITYCOMPONENT_HH__
#define __VELOCITYCOMPONENT_HH__

#include "../../engine/entitySystem.hh"
#include "../../engine/vertex.hh"


class VelocityComponent : public Engine::ComponentDataTemplate
{
 public:
  VelocityComponent();
  Engine::Vector velocity;

  std::string Print();
};

#endif // __VELOCITYCOMPONENT_HH__
