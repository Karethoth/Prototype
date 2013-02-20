#include "positionComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


PositionComponent::PositionComponent()
{
  mutex = PTHREAD_MUTEX_INITIALIZER;
  position = {0,0,0};
}



string PositionComponent::Print()
{
  string msg = "Position: {";
  msg.append( to_string( position.x ) );
  msg.append( "," );
  msg.append( to_string( position.y ) );
  msg.append( "," );
  msg.append( to_string( position.z ) );
  msg.append( "}" );
  return msg;
}
