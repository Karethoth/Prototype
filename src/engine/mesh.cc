#include "mesh.hh"

using namespace Engine;


Mesh::Mesh()
{

}


Mesh::~Mesh()
{
  triangles.clear();
}


void Mesh::AddTriangle( Triangle &triangle )
{
  triangles.push_back( triangle );
}
