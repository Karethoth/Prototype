#include "main.hh"

using namespace Engine;
using namespace Engine::Managers;
using namespace Engine::Stacks;

using namespace std;
using namespace chrono;


EntitySystem entitySystem;


GLuint LoadShaders( const char * vertex_file_path,const char * fragment_file_path )
{
  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  string VertexShaderCode;
  ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if(VertexShaderStream.is_open())
  {
    string Line = "";
    while(getline(VertexShaderStream, Line))
        VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }

  // Read the Fragment Shader code from the file
  string FragmentShaderCode;
  ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if(FragmentShaderStream.is_open())
  {
    string Line = "";
    while(getline(FragmentShaderStream, Line))
        FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const * VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  std::vector<char> VertexShaderErrorMessage(InfoLogLength);
  glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
  fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const * FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
  glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
  fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

  // Link the program
  fprintf(stdout, "Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
  glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
  fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}



int main( int argc, char **argv )
{
  // Create the window
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
  }

  glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );
  //glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
  //glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 3 );
  //glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );


  if( !glfwOpenWindow( 600, 400, 0, 0, 0, 32, 0,0, GLFW_WINDOW ) )
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
  glCullFace( GL_BACK );
  glFrontFace( GL_CW );
  glEnable( GL_CULL_FACE );
  glClearColor( 0, 0, 0, 0 );
  glViewport( 0, 0, 600, 400 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 60.0, windowRatio, 1.0, 1024.0 );
  glMatrixMode( GL_MODELVIEW );


  // Set the Entity System up
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

  // Load shaders
  GLuint programID = LoadShaders( "testVertexShader.glsl", "testFragmentShader.glsl" );

  glfwEnable( GLFW_STICKY_KEYS );

  TickMessage tickMessage;
  tickMessage.frameStart = high_resolution_clock::now();
  tickMessage.frameDelta = GameTicks( 1 );
  time_point<high_resolution_clock> tmpTimePoint;

  bool running = true;
  while( running && sceneStack.Get( 0 )->Tick( &tickMessage ) )
  {
    if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS ||
       !glfwGetWindowParam( GLFW_OPENED ) )
    {
      running = false;
    }

    tmpTimePoint = high_resolution_clock::now();
    tickMessage.frameDelta = duration_cast<GameTicks>( tmpTimePoint - tickMessage.frameStart );
    tickMessage.frameStart = tmpTimePoint;
    time_t endTime = high_resolution_clock::to_time_t( tmpTimePoint );

    cout << "FPS@" << endTime << ": " << 1000 / tickMessage.frameDelta.count() << "\n";
  }

  glfwTerminate();

  return 0;
}
