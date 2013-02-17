#include "main.hh"

using namespace Engine;
using namespace Engine::Managers;
using namespace Engine::Stacks;

using namespace std;
using std::cout;



int main( int argc, char **argv )
{
  // Set the Entity System up
  shared_ptr<EntitySystem> entitySystem( new EntitySystem() );

  // Set all of the different component types up
  SetupComponents( entitySystem );

  // Set the managers and stacks up
  SceneManager         sceneManager;
  TemplateStack<Scene> sceneStack;


  // Create instance of the Intro Scene
  shared_ptr<IntroScene> introScene( new IntroScene() );
  introScene->SetEntitySystem( entitySystem );
  string introSceneName( "IntroScene" );

  // Insert it to the scene manager
  sceneManager.Add( introSceneName, introScene );

  // And push it to the stack as the topmost scene
  sceneStack.Push( sceneManager.Get( introSceneName ) );

  // Finally actually create it
  introScene->CreateScene();

  return 0;
}
