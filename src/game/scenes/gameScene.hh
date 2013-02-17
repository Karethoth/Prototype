#ifndef __GAMESCENE_HPP__
#define __GAMESCENE_HPP__

#include "../../engine/scene.hh"


class GameScene : public Engine::Scene
{
 public:
  GameScene();
  virtual ~GameScene();

 protected:
  virtual void CreateScene();
  virtual void DestroyScene();
};

#endif

