#include "components.hh"

using namespace Engine;

void SetupComponents( std::shared_ptr<Engine::EntitySystem> es )
{
  // Set up the component types
  Component positionComponent = { POSITION_COMPONENT,
                                  "PositionComponent",
                                  "Contains position of an entity",
                                  "Positions" };

  Component rotationComponent = { ROTATION_COMPONENT,
                                  "RotationComponent",
                                  "Contains rotation of an entity",
                                  "Rotations" };

  // Create the component types
  es->CreateComponent( positionComponent );
  es->CreateComponent( rotationComponent );

}
