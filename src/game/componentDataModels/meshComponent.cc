#include "meshComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


MeshComponent::MeshComponent()
{
  MeshComponent( "NULL" );
}



MeshComponent::MeshComponent( string meshName )
{
  mesh = meshName;
}



string MeshComponent::Print()
{
  string msg = "Mesh: {'";
  msg.append( mesh );
  msg.append( "'}" );
  return msg;
}

