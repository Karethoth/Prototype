#include "rotationComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


RotationComponent::RotationComponent()
{
  rotation = {0,0,0};
}



string RotationComponent::Print()
{
  string msg = "Rotation: {";
  msg.append( to_string( rotation.x ) );
  msg.append( "," );
  msg.append( to_string( rotation.y ) );
  msg.append( "," );
  msg.append( to_string( rotation.z ) );
  msg.append( "}" );
  return msg;
}

