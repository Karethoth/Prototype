#include "velocityComponent.hh"

#include <string>

using namespace Engine;
using namespace std;


VelocityComponent::VelocityComponent()
{
  velocity = {0,0,0};
}



VelocityComponent::VelocityComponent( float x, float y, float z )
{
  velocity = {x,y,z};
}



string VelocityComponent::Print()
{
  string msg = "Velocity: {";
  msg.append( to_string( velocity.x ) );
  msg.append( "," );
  msg.append( to_string( velocity.y ) );
  msg.append( "," );
  msg.append( to_string( velocity.z ) );
  msg.append( "}" );
  return msg;
}

