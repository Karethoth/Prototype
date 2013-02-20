#include "main.hh"

using namespace Engine;
using namespace Engine::Managers;
using namespace Engine::Stacks;

using namespace std;
using std::cout;

EntitySystem entitySystem;


int main( int argc, char **argv )
{
  // Set the Entity System up
  entitySystem = EntitySystem();
  shared_ptr<EntitySystem> entitySys = shared_ptr<EntitySystem>( &entitySystem );

  // Set all of the different component types up
  SetupComponents( entitySys );

  // Set the managers and stacks up
  SceneManager         sceneManager;
  TemplateStack<Scene> sceneStack;


  // Create instance of the Intro Scene
  shared_ptr<IntroScene> introScene( new IntroScene() );
  introScene->SetEntitySystem( entitySys );
  string introSceneName( "IntroScene" );

  // Insert it to the scene manager
  sceneManager.Add( introSceneName, introScene );

  // And push it to the stack as the topmost scene
  sceneStack.Push( sceneManager.Get( introSceneName ) );

  // Finally actually create it
  introScene->CreateScene();

  // Start systems
  pthread_t movementSystemThread;
  int       movementSystemId;
  void     *movementSystemStatus;
  movementSystemId = pthread_create( &movementSystemThread, NULL, StartMovementSystem, static_cast<void*>( &entitySystem ) );

  // Wait for the systems to stop
  pthread_join( movementSystemThread, &movementSystemStatus );

  return 0;
}
