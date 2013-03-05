#include "scene.hh"

using namespace Engine;
using namespace std;


Scene::Scene( void )
{
}



Scene::~Scene()
{
  DestroyScene();
}



void Scene::SetEntitySystem( std::shared_ptr<EntitySystem> es )
{
  entitySystem = es;
  for( auto sys : systems )
  {
    sys.second->SetEntitySystem( entitySystem );
  }
}



void Scene::CreateScene()
{
}



void Scene::DestroyScene()
{
}



bool Scene::Run()
{
  return false;
}



bool Scene::Tick( Message *message )
{
  return true;
}



void Scene::Stop()
{
  DestroyScene();
}



bool Scene::Setup()
{
  // Create the scene
  CreateScene();

  return true;
};
