#include "sceneNode.hh"

using namespace Engine;
using namespace std;


SceneNode::SceneNode()
{
  position.x = 0;
  position.y = 0;
  position.z = 0;
}


SceneNode::~SceneNode()
{
  children.clear();
}
