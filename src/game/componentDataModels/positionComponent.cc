#include "positionComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


PositionComponent::PositionComponent()
{
  position = {0,0,0};
}



string PositionComponent::Print()
{
  string msg = "{";
  msg.append( to_string( position.x ) );
  msg.append( "," );
  msg.append( to_string( position.y ) );
  msg.append( "," );
  msg.append( to_string( position.z ) );
  msg.append( "}" );
  return msg;
}
