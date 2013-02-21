#include "baseSystem.hh"


bool BaseSystem::IsRunning()
{
  return isRunning;
}



void BaseSystem::SetPriority( int priority )
{
  this->priority = priority;
}



void BaseSystem::SetEntitySystem( Engine::EntitySystem *entitySystem )
{
  this->entitySystem = entitySystem;
}
