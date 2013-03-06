#ifndef __RENDERSYSTEM_HH__
#define __RENDERSYSTEM_HH__

#include "../../engine/baseSystem.hh"

class RenderSystem : public Engine::BaseSystem
{
 public:
  RenderSystem();
  ~RenderSystem();

  virtual bool Tick( Engine::Message *message );


 protected:
  virtual void* Run();

  void PreRender();
  void PostRender();
};

#endif // __RENDERSYSTEM_HH__
