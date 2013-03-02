#include "introScene.hh"
#include "../../engine/mesh.hh"
#include "../components.hh"
#include "../messages/tickMessage.hh"

#include <iostream>
#include <vector>
#include <pthread.h>


using namespace Engine;
using namespace std;


IntroScene::IntroScene()
{
  sceneLengthMs = 5000;
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
    { 0, 0, 0 },
    { 10, 0, 0 },
    { 0, 10, 0 }
  };
  cube->AddTriangle( t );

  t = {
    { 10, 10, 0 },
    { 10, 0, 0 },
    { 0, 10, 0 }
  };
  cube->AddTriangle( t );
  string cubeName = "Cube";

  meshManager.Add( cubeName, cube );


  // Create cube entity and create it's EntityComponents for it
  cubeEntityId = entitySystem->CreateNewEntity( "CubeEntity" );
  unsigned long positionEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( POSITION_COMPONENT, cubeEntityId, new PositionComponent() );
  unsigned long velocityEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( VELOCITY_COMPONENT, cubeEntityId, new VelocityComponent() );
  unsigned long rotationEntityComponentId = entitySystem->CreateEntityComponentAndAddTo( ROTATION_COMPONENT, cubeEntityId, new RotationComponent() );

  cout << "CubeEntityId = " << cubeEntityId << "\n";
  cout << "positionEntityComponentId = " << positionEntityComponentId << "\n";
  cout << "velocityEntityComponentId = " << velocityEntityComponentId << "\n";
  cout << "rotationEntityComponentId = " << rotationEntityComponentId << "\n";

  // Get position component(s) for the cube
  vector<ComponentDataTemplate*> *positionData = entitySystem->GetComponentDataForEntry( ROTATION_COMPONENT, cubeEntityId );
  cout << "positionData.size() = " << positionData->size() << "\n";

  for( vector<ComponentDataTemplate*>::iterator it = positionData->begin(); it != positionData->end(); ++it )
  {
    cout << (*it)->Print() << "\n";
  }
}



void IntroScene::DestroyScene()
{
}
