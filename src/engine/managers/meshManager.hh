#ifndef __MESHMANAGER_HH__
#define __MESHMANAGER_HH__

#include "templateManager.hh"
#include "../mesh.hh"


namespace Engine
{
  namespace Managers
  {
    class MeshManager : public TemplateManager<Mesh>
    {
     public:
      virtual bool Load( std::string& );
    };
  }
}

#endif // __MESHMANAGER_HH__

