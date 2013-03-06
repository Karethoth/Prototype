#ifndef __RENDERSYSTEM_HH__
#define __RENDERSYSTEM_HH__

#include "../../engine/baseSystem.hh"
#include "../../engine/managers/meshManager.hh"


class RenderSystem : public Engine::BaseSystem
{
 public:
  RenderSystem();
  ~RenderSystem();

  virtual bool Tick( Engine::Message *message );

  void SetMeshManager( Engine::Managers::MeshManager* );


 protected:
  virtual void* Run();

  void PreRender();
  void PostRender();

  Engine::Managers::MeshManager *meshManager;
};

#endif // __RENDERSYSTEM_HH__
