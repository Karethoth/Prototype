#include "entitySystem.hh"

#include <iostream>

using namespace Engine;
using namespace std;


ComponentDataTemplate::~ComponentDataTemplate()
{
}



int ComponentDataTemplate::Lock()
{
  mtx.lock();
  return 0;
}



int ComponentDataTemplate::Unlock()
{
  mtx.unlock();
  return 0;
}



void ComponentDataTemplate::SetIds( unsigned long entity, unsigned long componentData )
{
  entityId        = entity;
  componentDataId = componentData;
}



EntitySystem::EntitySystem()
{
}



EntitySystem::~EntitySystem()
{
  assemblages.clear();
  assemblageComponents.clear();
  components.clear();
  entities.clear();
  entityComponents.clear();

  // MEMORY LEAK:
  componentData.clear();
}



unsigned long EntitySystem::CreateNewEntity( string debugName )
{
  unsigned long entityId;

  entitySystemMutex.lock();

  if( entities.size() > 0 )
  {
    entityId = entities.rbegin()->first + 1;
  }
  else
  {
    entityId = 1;
  }

  // entityId should be tested just to be sure it's unique

  entities[entityId] = debugName;

  entitySystemMutex.unlock();

  return entityId;
}



bool EntitySystem::CreateComponent( Component component )
{
  entitySystemMutex.lock();

  components[component.componentId] = component;

  // Ignoring assemblage for now

  entitySystemMutex.unlock();
  return true;
}



unsigned long EntitySystem::CreateEntityComponentAndAddTo( int componentType, unsigned long entityId, ComponentDataTemplate *initialValue )
{
  unsigned long componentDataId;
  string tableName;

  // Check that the entity exists
  if( entities.find( entityId ) == entities.end() )
  {
    return 0;
  }

  Component *component = GetComponent( componentType );
  if( !component )
  {
    return 0;
  }

  entitySystemMutex.lock();

  if( componentData[component->tableName].size() > 0 )
  {
    componentDataId = componentData[component->tableName].rbegin()->first + 1;
  }
  else
  {
    componentDataId = 1;
  }

  initialValue->SetIds( entityId, componentDataId );

  componentData[component->tableName][componentDataId] = initialValue;


  EntityComponent entityComponent = { entityId, componentType, componentDataId };
  entityComponents.insert( pair<unsigned long, EntityComponent>( entityId, entityComponent ) );

  entitySystemMutex.unlock();
  return componentDataId;
}



vector<ComponentDataTemplate*>* EntitySystem::GetComponentDataForEntry( int componentType, unsigned long entityId )
{
  vector<ComponentDataTemplate*> *components = new vector<ComponentDataTemplate*>();
  Component *component = GetComponent( componentType );
  if( !component )
  {
    return components;
  }

  entitySystemMutex.lock();

  pair< multimap<unsigned long, EntityComponent>::iterator,
        multimap<unsigned long, EntityComponent>::iterator > ret;

  ret = entityComponents.equal_range( entityId );
  for( multimap<unsigned long, EntityComponent>::iterator it=ret.first; it!=ret.second; ++it )
  {
    // Push componentData[component->tableName][entityComponent.componentDataId].second to vector
    if( (*it).second.componentId != componentType )
    {
      continue;
    }

    if( componentData.find( component->tableName ) == componentData.end() )
    {
      continue;
    }

    // Save the reference to the table in a variable
    map<unsigned long, ComponentDataTemplate*> table = componentData[component->tableName];

    if( table.find( (*it).second.componentDataId ) == table.end() )
    {
      continue;
    }

    components->push_back( table[(*it).second.componentDataId] );
  }

  entitySystemMutex.unlock();

  // Return vector
  return components;
};



vector<ComponentDataTemplate*>* EntitySystem::GetComponentDatasOfType( int componentType )
{
  vector<ComponentDataTemplate*> *components = new vector<ComponentDataTemplate*>();
  Component *component = GetComponent( componentType );
  if( !component )
  {
    return components;
  }

  entitySystemMutex.lock();

  if( !component )
    return components;


  // Save the reference to the table in a variable
  map<unsigned long, ComponentDataTemplate*> table = componentData[component->tableName];

  for( map<unsigned long, ComponentDataTemplate*>::iterator cit = table.begin(); cit != table.end(); ++cit )
  {
    components->push_back( (*cit).second );
  }

  entitySystemMutex.unlock();

  // Return vector
  return components;
}



EntityComponent* EntitySystem::GetEntityComponent( int componentType, unsigned long componentId )
{
  EntityComponent *entityComponent = nullptr;
  std::multimap<unsigned long, EntityComponent>::iterator it;

  entitySystemMutex.lock();

  for( it = entityComponents.begin(); it != entityComponents.end(); ++it )
  {
    if( (*it).second.componentId == componentType &&
        (*it).second.componentDataId == componentId )
    {
      entityComponent = &((*it).second);
      break;
    }
  }

  entitySystemMutex.unlock();

  return entityComponent;
}



Component* EntitySystem::GetComponent( int componentType )
{
  if( components.find( componentType ) != components.end() )
  {
    return &components[componentType];
  }

  return nullptr;
}
