#include "introScene.hh"
#include "../../engine/mesh.hh"
#include "../components.hh"
#include "../messages/tickMessage.hh"
#include "../systems/movementSystem.hh"
#include "../systems/rotationSystem.hh"
#include "../systems/renderSystem.hh"

#include <iostream>
#include <vector>
#include <pthread.h>


using namespace Engine;
using namespace std;


IntroScene::IntroScene()
{
  sceneLengthMs = 5000;

  MovementSystem *movementSystem = new MovementSystem();
  RotationSystem *rotationSystem = new RotationSystem();
  RenderSystem *renderSystem = new RenderSystem();
  renderSystem->SetMeshManager( &meshManager );

  systems[1000] = movementSystem;
  systems[2000] = rotationSystem;
  systems[3000] = renderSystem;
}



IntroScene::~IntroScene()
{
  DestroyScene();
}



void IntroScene::CreateScene()
{
  // Create cube mesh and give it to the mesh manager
  shared_ptr<Mesh> cube( new Mesh() );

  Triangle t = {
    { -1, 1, 1 },
    { 1, 1, 1 },
    { 1, -1, 1 }
  };
  cube->AddTriangle( t );
  t = {
    { -1, 1, 1 },
    { 1, -1, 1 },
    { -1, -1, 1 }
  };
  cube->AddTriangle( t );

  t = {
    { 1, -1, -1 },
    { 1, 1, -1 },
    { -1, 1, -1 }
  };
  cube->AddTriangle( t );
  t = {
    { 1, -1, -1 },

    { -1, 1, -1 },
    { -1, -1, -1 }
  };
  cube->AddTriangle( t );

  t = {
    { -1, -1, -1 },
    { -1, 1, -1 },
    { -1, 1, 1 }
  };
  cube->AddTriangle( t );
  t = {
    { -1, -1, 1 },
    { -1, 1, 1 },
    { -1, -1, -1 }
  };
  cube->AddTriangle( t );

  t = {
    { 1, -1, -1 },
    { 1, 1, -1 },
    { 1, 1, 1 }
  };
  cube->AddTriangle( t );
  t = {
    { 1, -1, 1 },
    { 1, 1, 1 },
    { 1, -1, -1 }
  };
  cube->AddTriangle( t );

  string cubeName = "Cube";

  meshManager.Add( cubeName, cube );


  // Create cube entity and create it's EntityComponents for it
  cubeEntityId = entitySystem->CreateNewEntity( "CubeEntity" );
  unsigned long positionEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( POSITION_COMPONENT, cubeEntityId, new PositionComponent() );
  unsigned long velocityEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( VELOCITY_COMPONENT, cubeEntityId, new VelocityComponent() );
  unsigned long rotationEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( ROTATION_COMPONENT, cubeEntityId, new RotationComponent() );
  unsigned long autoRotationEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( AUTOROTATION_COMPONENT, cubeEntityId, new AutoRotationComponent( 0, 90, 0 ) );
  unsigned long meshEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( MESH_COMPONENT, cubeEntityId, new MeshComponent( cubeName ) );

  cout << "CubeEntityId = " << cubeEntityId << "\n";
  cout << "positionEntityComponentId = " << positionEntityComponentId << "\n";
  cout << "velocityEntityComponentId = " << velocityEntityComponentId << "\n";
  cout << "rotationEntityComponentId = " << rotationEntityComponentId << "\n";
  cout << "autoRotationEntityComponentId = " << autoRotationEntityComponentId << "\n";
  cout << "meshEntityComponentId = " << meshEntityComponentId << "\n";

  // Get position component(s) for the cube
  vector<ComponentDataTemplate*> *positionData = entitySystem->GetComponentDataForEntry( ROTATION_COMPONENT, cubeEntityId );
  cout << "positionData.size() = " << positionData->size() << "\n";

  for( vector<ComponentDataTemplate*>::iterator it = positionData->begin(); it != positionData->end(); ++it )
  {
    cout << (*it)->Print() << "\n";
  }
}



bool IntroScene::Tick( Message *message )
{
  TickMessage *tickMessage = static_cast<TickMessage*>( message );

  for( auto sys : systems )
  {
    if( !sys.second->Tick( message ) )
      return false;
  }

  return true;
}


void IntroScene::DestroyScene()
{
}
