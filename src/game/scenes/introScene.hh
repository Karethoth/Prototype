#ifndef __INTROSCENE_HPP_
#define __INTROSCENE_HPP_

#include "../../engine/scene.hh"


class IntroScene : public Engine::Scene
{
 public:
  IntroScene();
  virtual ~IntroScene();

  virtual void CreateScene();
  virtual void DestroyScene();

  virtual bool Tick( Engine::Message *message );


 protected:
  unsigned long sceneLengthMs;
};

#endif

