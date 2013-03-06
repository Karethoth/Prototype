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
  unsigned long cubeEntityId = entitySystem->CreateNewEntity( "CubeEntity1" );
  entitySystem->CreateEntityComponentAndAddTo( POSITION_COMPONENT, cubeEntityId, new PositionComponent() );
  entitySystem->CreateEntityComponentAndAddTo( ROTATION_COMPONENT, cubeEntityId, new RotationComponent() );
  entitySystem->CreateEntityComponentAndAddTo( AUTOROTATION_COMPONENT, cubeEntityId, new AutoRotationComponent( 0, 90, 0 ) );
  entitySystem->CreateEntityComponentAndAddTo( MESH_COMPONENT, cubeEntityId, new MeshComponent( cubeName ) );

  // Create second cube
  unsigned long cubeEntity2Id = entitySystem->CreateNewEntity( "CubeEntity2" );
  entitySystem->CreateEntityComponentAndAddTo( POSITION_COMPONENT, cubeEntity2Id, new PositionComponent( 3, 2, 0 ) );
  entitySystem->CreateEntityComponentAndAddTo( ROTATION_COMPONENT, cubeEntity2Id, new RotationComponent() );
  entitySystem->CreateEntityComponentAndAddTo( AUTOROTATION_COMPONENT, cubeEntity2Id, new AutoRotationComponent( 0, 180, 0 ) );
  entitySystem->CreateEntityComponentAndAddTo( MESH_COMPONENT, cubeEntity2Id, new MeshComponent( cubeName ) );

  // Create third cube
  unsigned long cubeEntity3Id = entitySystem->CreateNewEntity( "CubeEntity3" );
  entitySystem->CreateEntityComponentAndAddTo( POSITION_COMPONENT, cubeEntity3Id, new PositionComponent( -3, -2, 0 ) );
  entitySystem->CreateEntityComponentAndAddTo( ROTATION_COMPONENT, cubeEntity3Id, new RotationComponent() );
  entitySystem->CreateEntityComponentAndAddTo( AUTOROTATION_COMPONENT, cubeEntity3Id, new AutoRotationComponent( 0, 45, 0 ) );
  entitySystem->CreateEntityComponentAndAddTo( MESH_COMPONENT, cubeEntity3Id, new MeshComponent( cubeName ) );

  // Create fourth cube
  unsigned long cubeEntity4Id = entitySystem->CreateNewEntity( "CubeEntity4" );
  entitySystem->CreateEntityComponentAndAddTo( POSITION_COMPONENT, cubeEntity4Id, new PositionComponent( 3, -2, 0 ) );
  entitySystem->CreateEntityComponentAndAddTo( VELOCITY_COMPONENT, cubeEntity4Id, new VelocityComponent( -0.5, 0, 0 ) );
  entitySystem->CreateEntityComponentAndAddTo( ROTATION_COMPONENT, cubeEntity4Id, new RotationComponent() );
  entitySystem->CreateEntityComponentAndAddTo( MESH_COMPONENT, cubeEntity4Id, new MeshComponent( cubeName ) );
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
