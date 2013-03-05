#ifndef __MESHCOMPONENT_HH__
#define __MESHCOMPONENT_HH__

#include "../../engine/entitySystem.hh"
#include "../../engine/mesh.hh"


class MeshComponent : public Engine::ComponentDataTemplate
{
 public:
  MeshComponent();
  MeshComponent( std::string );
  std::string mesh;

  std::string Print();
};

#endif // __VELOCITYCOMPONENT_HH__
