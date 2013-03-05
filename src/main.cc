#include "main.hh"

using namespace Engine;
using namespace Engine::Managers;
using namespace Engine::Stacks;

using namespace std;
using namespace chrono;
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


  TickMessage tickMessage;
  tickMessage.frameStart = steady_clock::now();
  tickMessage.frameDelta = microseconds( 1 );
  time_point<steady_clock> tmpTimePoint;

  while( sceneStack.Get( 0 )->Tick( &tickMessage ) )
  {
    tmpTimePoint = steady_clock::now();
    tickMessage.frameDelta = duration_cast<microseconds>( tmpTimePoint - tickMessage.frameStart );
    tickMessage.frameStart = tmpTimePoint;
    time_t endTime = steady_clock::to_time_t( tmpTimePoint );
    cout << "FrameDelta: " << tickMessage.frameDelta.count() << ", FrameStart: " << endTime << "\n";
  }

  // Start systems
  /*
  MovementSystem movementSystem;
  movementSystem.SetEntitySystem( &entitySystem );
  movementSystem.SetPriority( 1000 );
  pthread_t movementSystemThread;
  int       movementSystemId;
  void     *movementSystemStatus;

  movementSystemId = pthread_create( &movementSystemThread, NULL, MovementSystem::RunSystem, static_cast<void*>( &movementSystem ) );

  // Wait for the systems to stop
  pthread_join( movementSystemThread, &movementSystemStatus );
  */
  return 0;
}
