#include "baseSystem.hh"

using namespace Engine;
using namespace std;


bool BaseSystem::IsRunning()
{
  return isRunning;
}



void BaseSystem::SetPriority( int priority )
{
  this->priority = priority;
}



void BaseSystem::SetEntitySystem( shared_ptr<EntitySystem> entitySystem )
{
  this->entitySystem = entitySystem;
}
