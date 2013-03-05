#ifndef __AUTOROTATIONCOMPONENT_HH__
#define __AUTOROTATIONCOMPONENT_HH__

#include "../../engine/entitySystem.hh"
#include "../../engine/vertex.hh"


class AutoRotationComponent : public Engine::ComponentDataTemplate
{
 public:
  AutoRotationComponent();
  AutoRotationComponent( float, float, float );
  Engine::Vector tickRotation;

  std::string Print();
};

#endif // __AUTOROTATIONCOMPONENT_HH__
