#ifndef __SCENEMANAGER_HPP__
#define __SCENEMANAGER_HPP__

#include "templateManager.hh"
#include "../scene.hh"


namespace Engine
{
  namespace Managers
  {
    class SceneManager : public TemplateManager<Scene>
    {
     public:
      virtual bool Load( std::string& );
    };
  }
}

#endif
