#include "rotationSystem.hh"

#include "../components.hh"
#include "../../engine/entitySystem.hh"
#include "../messages/tickMessage.hh"

#include <iostream>
#include <memory>
#include <vector>

using namespace Engine;
using namespace std;


RotationSystem::RotationSystem()
{
  isRunning    = false;
  entitySystem = nullptr;
}



RotationSystem::~RotationSystem()
{
}



void* RotationSystem::Run()
{
  pthread_exit( NULL );
  return nullptr;
}



bool RotationSystem::Tick( Message *message )
{
  TickMessage *tickMessage = static_cast<TickMessage*>( message );
  isRunning = true;

  vector<ComponentDataTemplate*> *autoRotations = entitySystem->GetComponentDatasOfType( AUTOROTATION_COMPONENT );

  AutoRotationComponent *autoRotation;

  for( auto it : *autoRotations )
  {
    autoRotation = static_cast<AutoRotationComponent*>( it );

    autoRotation->Lock();

    vector<ComponentDataTemplate*> *rotations = entitySystem->GetComponentDataForEntry( ROTATION_COMPONENT, autoRotation->entityId );
    if( rotations->size() > 0 )
    {
      float multiplier = (float)tickMessage->frameDelta.count()/10000.0;
      RotationComponent *rotation = dynamic_cast<RotationComponent*>( (*rotations->begin()) );

      rotation->Lock();

      rotation->rotation.x += autoRotation->tickRotation.x * multiplier;
      rotation->rotation.y += autoRotation->tickRotation.y * multiplier;
      rotation->rotation.z += autoRotation->tickRotation.z * multiplier;

      if( rotation->rotation.x > 360 )
        rotation->rotation.x -= 360;
      else if( rotation->rotation.x < 0 )
        rotation->rotation.x += 360;

      if( rotation->rotation.y > 360 )
        rotation->rotation.y -= 360;
      else if( rotation->rotation.y < 0 )
        rotation->rotation.y += 360;

      if( rotation->rotation.z > 360 )
        rotation->rotation.z -= 360;
      else if( rotation->rotation.z < 0 )
        rotation->rotation.z += 360;

      rotation->Unlock();
    }

    autoRotation->Unlock();
  }

  isRunning = false;
  return nullptr;
}
