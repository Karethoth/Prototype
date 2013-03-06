#ifndef __POSITIONCOMPONENT_HH__
#define __POSITIONCOMPONENT_HH__

#include "../../engine/entitySystem.hh"
#include "../../engine/vertex.hh"


class PositionComponent : public Engine::ComponentDataTemplate
{
 public:
  PositionComponent();
  PositionComponent( float, float, float );

  Engine::Vector position;

  std::string Print();
};

#endif // __POSITIONCOMPONENT_HH__
