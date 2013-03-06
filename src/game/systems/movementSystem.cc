#include "movementSystem.hh"

#include "../components.hh"
#include "../../engine/entitySystem.hh"
#include "../messages/tickMessage.hh"

#include <iostream>
#include <memory>
#include <vector>

using namespace Engine;
using namespace std;


MovementSystem::MovementSystem()
{
  isRunning    = false;
  entitySystem = nullptr;
}



MovementSystem::~MovementSystem()
{
}



void* MovementSystem::Run()
{
  pthread_exit( NULL );
  return nullptr;
}



bool MovementSystem::Tick( Message *message )
{
  TickMessage *tickMessage = static_cast<TickMessage*>( message );
  isRunning = true;

  vector<ComponentDataTemplate*> *velocities = entitySystem->GetComponentDatasOfType( VELOCITY_COMPONENT );

  VelocityComponent *velocity;

  for( auto it : *velocities )
  {
    velocity = static_cast<VelocityComponent*>( it );

    velocity->Lock();

    vector<ComponentDataTemplate*> *positions = entitySystem->GetComponentDataForEntry( POSITION_COMPONENT, velocity->entityId );
    if( positions->size() > 0 )
    {
      float multiplier = (float)tickMessage->frameDelta.count()/10000.0;
      PositionComponent *position = dynamic_cast<PositionComponent*>( (*positions->begin()) );
      position->Lock();
      position->position.x += velocity->velocity.x * multiplier;
      position->position.y += velocity->velocity.y * multiplier;
      position->position.z += velocity->velocity.z * multiplier;
      position->Unlock();
    }

    velocity->Unlock();
  }

  isRunning = false;
  return true;
}
