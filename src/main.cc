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
  // Create the window
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
  }

  /*
  glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 3 );
  glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
  */

  if( !glfwOpenWindow( 600, 400, 0,0,0,0, 32,0, GLFW_WINDOW ) )
  {
    fprintf( stderr, "Failed to open GLFW window\n" );
    glfwTerminate();
    return -1;
  }

  // Initialize GLEW
  bool glewExperimental = true; // Needed in core profile
  if( glewInit() != GLEW_OK ) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  glfwSetWindowTitle( "Prototype" );

  // Setup OpenGL
  float windowRatio = (float) 600 / (float) 400;
  //glShadeModel( GL_SMOOTH );
  //glCullFace( GL_BACK );
  //glFrontFace( GL_CW );
  //glEnable( GL_CULL_FACE );
  glClearColor( 0, 0, 0, 0 );
  glViewport( 0, 0, 600, 400 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
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

  glfwEnable( GLFW_STICKY_KEYS );

  bool running = true;
  while( running && sceneStack.Get( 0 )->Tick( &tickMessage ) )
  {
    tmpTimePoint = high_resolution_clock::now();
    tickMessage.frameDelta = duration_cast<GameTicks>( tmpTimePoint - tickMessage.frameStart );
    tickMessage.frameStart = tmpTimePoint;
    time_t endTime = high_resolution_clock::to_time_t( tmpTimePoint );

    cout << "FPS@" << endTime << ": " << 1000 / tickMessage.frameDelta.count() << "\n";

    if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS ||
       !glfwGetWindowParam( GLFW_OPENED ) )
    {
      running = false;
    }
  }

  glfwTerminate();

  return 0;
}
