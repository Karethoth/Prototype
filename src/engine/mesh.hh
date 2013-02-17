#ifndef __MESH_HH__
#define __MESH_HH__

#include "vertex.hh"
#include <vector>


namespace Engine
{
  class Mesh
  {
   public:
    Mesh();
    ~Mesh();

    void AddTriangle( Triangle& );


   private:
    std::vector<Triangle> triangles;
  };
}

#endif // __MESH_HH__
