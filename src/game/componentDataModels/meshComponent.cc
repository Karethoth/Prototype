#include "meshComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


MeshComponent::MeshComponent()
{
  mutex = PTHREAD_MUTEX_INITIALIZER;
  mesh = "NULL";
}



MeshComponent::MeshComponent( string meshName )
{
  mutex = PTHREAD_MUTEX_INITIALIZER;
  mesh = meshName;
}



string MeshComponent::Print()
{
  string msg = "Mesh: {'";
  msg.append( mesh );
  msg.append( "'}" );
  return msg;
}
