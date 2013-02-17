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


 protected:
  unsigned long cubeEntityId;
  unsigned long sceneLengthMs;
};

#endif

