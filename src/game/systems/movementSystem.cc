#include "movementSystem.hh"

#include "../components.hh"
#include "../../engine/entitySystem.hh"

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
  isRunning = true;

  // Got to do some timing stuff here

  vector<ComponentDataTemplate*> *velocities = entitySystem->GetComponentDatasOfType( VELOCITY_COMPONENT );
  cout << "MS: velocities.size() = " << velocities->size() << "\n";

  VelocityComponent *velocity;

  for( vector<ComponentDataTemplate*>::iterator it = velocities->begin(); it != velocities->end(); ++it )
  {
    velocity = dynamic_cast<VelocityComponent*>( *it );

    velocity->Lock();

    vector<ComponentDataTemplate*> *positions = entitySystem->GetComponentDataForEntry( POSITION_COMPONENT, velocity->entityId );
    if( positions->size() > 0 )
    {
      PositionComponent *position = dynamic_cast<PositionComponent*>( (*positions->begin()) );
      position->Lock();
      position->position.x += velocity->velocity.x;
      position->position.y += velocity->velocity.y;
      position->position.z += velocity->velocity.z;
      position->Unlock();
    }

    velocity->Unlock();
  }

  isRunning = false;
  pthread_exit( NULL );
  return nullptr;
}
