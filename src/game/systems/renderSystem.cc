#include "renderSystem.hh"

#include "../components.hh"
#include "../../engine/entitySystem.hh"
#include "../messages/tickMessage.hh"

#include <iostream>
#include <memory>
#include <vector>

using namespace Engine;
using namespace std;


RenderSystem::RenderSystem()
{
  isRunning    = false;
  entitySystem = nullptr;
}



RenderSystem::~RenderSystem()
{
}



void* RenderSystem::Run()
{
  pthread_exit( NULL );
  return nullptr;
}



bool RenderSystem::Tick( Message *message )
{
  TickMessage *tickMessage = static_cast<TickMessage*>( message );
  isRunning = true;

  vector<ComponentDataTemplate*> *meshes = entitySystem->GetComponentDatasOfType( MESH_COMPONENT );

  MeshComponent *mesh;

  for( auto it : *meshes )
  {
    mesh = static_cast<MeshComponent*>( it );

    mesh->Lock();

    vector<ComponentDataTemplate*> *positions = entitySystem->GetComponentDataForEntry( POSITION_COMPONENT, mesh->entityId );
    vector<ComponentDataTemplate*> *rotations = entitySystem->GetComponentDataForEntry( ROTATION_COMPONENT, mesh->entityId );

    if( positions->size() > 0 )
    {
      PositionComponent *position = dynamic_cast<PositionComponent*>( (*positions->begin()) );
      position->Lock();

      RotationComponent *rotation = nullptr;
      if( rotations->size() > 0 )
        rotation = dynamic_cast<RotationComponent*>( (*rotations->begin()) );

      if( rotation )
        rotation->Lock();


      cout << "Drawing entity ID " << mesh->entityId << ":\n";
      cout << "\t" << mesh->Print() << "\n";
      cout << "\t" << position->Print() << "\n";
      if( rotation )
      {
        cout << "\t" << rotation->Print() << "\n";
      }
      else
      {
        cout << "\tRotation: No rotation.\n";
      }

      position->Unlock();
      if( rotation )
        rotation->Unlock();

    }

    mesh->Unlock();
  }

  isRunning = false;
  return nullptr;
}
