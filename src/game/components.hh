#ifndef __COMPONENTS_HH__
#define __COMPONENTS_HH__

#include <memory>

#include "../engine/entitySystem.hh"
#include "componentDataModels/positionComponent.hh"
#include "componentDataModels/velocityComponent.hh"
#include "componentDataModels/rotationComponent.hh"
#include "componentDataModels/autoRotationComponent.hh"
#include "componentDataModels/meshComponent.hh"


enum eComponentType
{
  UNDEF,
  POSITION_COMPONENT,
  VELOCITY_COMPONENT,
  ROTATION_COMPONENT,
  AUTOROTATION_COMPONENT,
  MESH_COMPONENT
};


void SetupComponents( std::shared_ptr<Engine::EntitySystem> es );

#endif // COMPONENTS_HH_INCLUDED
