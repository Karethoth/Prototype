#ifndef __VERTEX_HH__
#define __VERTEX_HH__

namespace Engine
{
  typedef struct
  {
    float x;
    float y;
    float z;
  } Vertex;

  typedef Vertex Vector;


  typedef struct
  {
    Vertex a;
    Vertex b;
    Vertex c;
  } Triangle;
}

#endif // __VERTEX_HH__
