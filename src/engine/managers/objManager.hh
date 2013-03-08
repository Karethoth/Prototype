#ifndef __OBJMANAGER_HH__
#define __OBJMANAGER_HH__

#include "templateManager.hh"
#include "../obj.hh"


namespace Engine
{
  namespace Managers
  {
    class OBJManager : public TemplateManager<OBJ>
    {
     public:
      virtual bool Load( std::string& );
    };
  }
}

#endif // __OBJMANAGER_HH__
