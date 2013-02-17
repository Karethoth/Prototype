#ifndef __SCENENODE_HH__
#define __SCENENODE_HH__

#include <vector>
#include <memory>

#include "vertex.hh"


namespace Engine
{
  class SceneNode
  {
   public:
    SceneNode();
    ~SceneNode();


   protected:
    Vector position;

    std::vector< std::shared_ptr<SceneNode> > children;
  };
}

#endif // __SCENENODE_HH__
