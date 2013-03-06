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
  // Init SDL
  SDL_Init( SDL_INIT_VIDEO );
  SDL_WM_SetCaption( "Prototype", nullptr );
  SDL_Surface *screen = SDL_SetVideoMode( 600, 400, 32, SDL_OPENGL | SDL_RESIZABLE );

  // Setup OpenGL
  float windowRatio = (float) 600 / (float) 400;
  glShadeModel( GL_SMOOTH );
  glCullFace( GL_BACK );
  glFrontFace( GL_CCW );
  glEnable( GL_CULL_FACE );
  glClearColor( 0, 0, 0, 0 );
  glViewport( 0, 0, 600, 400 );
  gluPerspective( 60.0, windowRatio, 1.0, 1024.0 );


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
  tickMessage.frameStart = high_resolution_clock::now();
  tickMessage.frameDelta = GameTicks( 1 );
  time_point<high_resolution_clock> tmpTimePoint;

  bool running = true;

  while( running && sceneStack.Get( 0 )->Tick( &tickMessage ) )
  {
    tmpTimePoint = high_resolution_clock::now();
    tickMessage.frameDelta = duration_cast<GameTicks>( tmpTimePoint - tickMessage.frameStart );
    tickMessage.frameStart = tmpTimePoint;
    time_t endTime = high_resolution_clock::to_time_t( tmpTimePoint );
    cout << "FrameDelta: " << tickMessage.frameDelta.count() << ", FrameStart: " << endTime << "\n";

    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
      switch( event.type )
      {
       case SDL_KEYDOWN:
       case SDL_QUIT:
        running = false;
        break;
      }
    }
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
  SDL_Quit();
  return 0;
}
