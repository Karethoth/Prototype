#include "movementSystem.hh"

#include "../components.hh"
#include "../../engine/entitySystem.hh"

#include <iostream>
#include <memory>
#include <vector>

using namespace Engine;
using namespace std;


void* StartMovementSystem( void *entitySystem )
{
  EntitySystem *es = static_cast<EntitySystem*>( entitySystem );
  cout << "Starting Movement System.\n";

  // So far the rest of this function is useless

  vector<ComponentDataTemplate*> *positionData = es->GetComponentDataForEntry( POSITION_COMPONENT, 1 );
  cout << "MS: positionData.size() = " << positionData->size() << "\n";

  PositionComponent *pc;
  for( vector<ComponentDataTemplate*>::iterator it = positionData->begin(); it != positionData->end(); ++it )
  {
    pc = dynamic_cast<PositionComponent*>( *it );

    pc->Lock();
    pc->position.x += 1;
    cout << "MS: " << pc->Print() << "\n";
    pc->Unlock();
  }

  pthread_exit( NULL );
  return nullptr;
}
