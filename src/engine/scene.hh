#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <memory>

#include "managers/meshManager.hh"
#include "entitySystem.hh"
#include "message.hh"
#include "baseSystem.hh"


namespace Engine
{
  class Scene
  {
   public:
    Scene();
    virtual ~Scene();

    virtual bool Run();
    virtual void Stop();
    virtual bool Tick( Message *message );

    void SetEntitySystem( std::shared_ptr<EntitySystem> es );


   protected:
    virtual bool Setup();
    virtual void CreateScene();
    virtual void DestroyScene();

    Managers::MeshManager meshManager;
    std::shared_ptr<EntitySystem> entitySystem;
    std::map<int, BaseSystem*> systems;
  };
}

#endif

