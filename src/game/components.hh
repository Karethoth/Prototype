#ifndef __COMPONENTS_HH__
#define __COMPONENTS_HH__

#include <memory>

#include "../engine/entitySystem.hh"
#include "componentDataModels/positionComponent.hh"


enum eComponentType
{
  UNDEF,
  POSITION_COMPONENT,
  ROTATION_COMPONENT
};


void SetupComponents( std::shared_ptr<Engine::EntitySystem> es );

#endif // COMPONENTS_HH_INCLUDED
