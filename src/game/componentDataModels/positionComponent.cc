#include "positionComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


PositionComponent::PositionComponent()
{
  PositionComponent( 0, 0, 0 );
}



PositionComponent::PositionComponent( float x, float y, float z )
{
  mutex = PTHREAD_MUTEX_INITIALIZER;
  position = {x,y,z};
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
