#include "autoRotationComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


AutoRotationComponent::AutoRotationComponent()
{
  AutoRotationComponent( 0, 0, 0 );
}



AutoRotationComponent::AutoRotationComponent( float x, float y, float z )
{
  tickRotation = {x,y,z};
}



string AutoRotationComponent::Print()
{
  string msg = "AutoRotation: {";
  msg.append( to_string( tickRotation.x ) );
  msg.append( "," );
  msg.append( to_string( tickRotation.y ) );
  msg.append( "," );
  msg.append( to_string( tickRotation.z ) );
  msg.append( "}" );
  return msg;
}

