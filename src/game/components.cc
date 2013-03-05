#include "components.hh"

using namespace Engine;

void SetupComponents( std::shared_ptr<Engine::EntitySystem> es )
{
  // Set up the component types
  Component positionComponent = { POSITION_COMPONENT,
                                  "PositionComponent",
                                  "Contains the position of an entity",
                                  "Positions" };

  Component velocityComponent = { VELOCITY_COMPONENT,
                                  "VelocityComponent",
                                  "Contains the velocity of an entity",
                                  "Velocities" };

  Component rotationComponent = { ROTATION_COMPONENT,
                                  "RotationComponent",
                                  "Contains the rotation of an entity",
                                  "Rotations" };


  Component autoRotationComponent = { AUTOROTATION_COMPONENT,
                                  "AutoRotationComponent",
                                  "Contains the rotation rate of an entity",
                                  "AutoRotations" };

  // Create the component types
  es->CreateComponent( positionComponent );
  es->CreateComponent( velocityComponent );
  es->CreateComponent( rotationComponent );
  es->CreateComponent( autoRotationComponent );
}
