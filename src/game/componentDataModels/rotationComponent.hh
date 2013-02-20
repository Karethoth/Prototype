#ifndef __ROTATIONCOMPONENT_HH__
#define __ROTATIONCOMPONENT_HH__

#include "../../engine/entitySystem.hh"
#include "../../engine/vertex.hh"


class RotationComponent : public Engine::ComponentDataTemplate
{
 public:
  RotationComponent();
  Engine::Vector rotation;

  std::string Print();
};

#endif // __ROTATIONCOMPONENT_HH__
