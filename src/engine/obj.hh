#ifndef __OBJ_HH__
#define __OBJ_HH__

#include "vertex.hh"
#include <vector>
#include <glm/glm.hpp>
#include <iostream>


namespace Engine
{
  class OBJ
  {
   public:
    OBJ();
    ~OBJ();

    bool Load( std::string filepath );


   private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
  };
}

#endif // __MESH_HH__
