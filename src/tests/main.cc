#include <cxxtest/TestSuite.h>
#include <iostream>

#include "../engine/entitySystem.cc"
#include "../game/componentDataModels/positionComponent.cc"

using namespace Engine;
using namespace std;


enum eComponentType
{
  UNDEF,
  POSITION_COMPONENT,
  ROTATION_COMPONENT
};



class EntitySystemTestSuite : public CxxTest::TestSuite
{
  EntitySystem entitySys;

 public:
  void testEmptySystem( void )
  {
    unsigned long invalidId = entitySys.CreateEntityComponentAndAddTo( 0, 0, nullptr );
    TS_ASSERT( invalidId == 0 );

    invalidId = entitySys.CreateEntityComponentAndAddTo( POSITION_COMPONENT, 1, nullptr );
    TS_ASSERT( invalidId == 0 );

    vector<ComponentDataTemplate*> *data = entitySys.GetComponentDataForEntry( POSITION_COMPONENT, 0 );
    TS_ASSERT( data != nullptr );
    TS_ASSERT( data->size() == 0 );
  }



  void testCreation( void )
  {
    // Set up the component types
    Component positionComponent = { POSITION_COMPONENT,
                                    "PositionComponent",
                                    "Contains position of an entity",
                                    "Positions" };

    Component rotationComponent = { ROTATION_COMPONENT,
                                    "RotationComponent",
                                    "Contains rotation of an entity",
                                    "Rotations" };

    // Create the component types
    entitySys.CreateComponent( positionComponent );
    entitySys.CreateComponent( rotationComponent );



    unsigned long invalidId = entitySys.CreateEntityComponentAndAddTo( POSITION_COMPONENT, 0, nullptr );
    TS_ASSERT( invalidId == 0 );

    invalidId = entitySys.CreateEntityComponentAndAddTo( POSITION_COMPONENT, 1, nullptr );
    TS_ASSERT( invalidId == 0 );


    // Create cube entity and create it's EntityComponents for it
    unsigned long testEntityId = entitySys.CreateNewEntity( "TestEntity" );
    unsigned long testEntity2Id = entitySys.CreateNewEntity( "TestEntity2" );
    TS_ASSERT( testEntityId != testEntity2Id );


    unsigned long positionEntityComponentId = entitySys.CreateEntityComponentAndAddTo( POSITION_COMPONENT, testEntityId, nullptr );
    entitySys.CreateEntityComponentAndAddTo( POSITION_COMPONENT, testEntityId, nullptr );
    unsigned long rotationEntityComponentId = entitySys.CreateEntityComponentAndAddTo( ROTATION_COMPONENT, testEntityId, nullptr );

    unsigned long positionEntityComponent2Id = entitySys.CreateEntityComponentAndAddTo( POSITION_COMPONENT, testEntity2Id, nullptr );
    unsigned long rotationEntityComponent2Id = entitySys.CreateEntityComponentAndAddTo( ROTATION_COMPONENT, testEntity2Id, nullptr );

    TS_ASSERT( positionEntityComponentId != positionEntityComponent2Id );
    TS_ASSERT( rotationEntityComponentId != rotationEntityComponent2Id );

    vector<ComponentDataTemplate*> *positionData = entitySys.GetComponentDataForEntry( POSITION_COMPONENT, testEntityId );
    TS_ASSERT( positionData != nullptr );
    TS_ASSERT( positionData->size() == 2 );

    for( vector<ComponentDataTemplate*>::iterator it = positionData->begin(); it != positionData->end(); ++it )
    {
      TS_ASSERT( (*it) == nullptr );
    }

    positionData = entitySys.GetComponentDataForEntry( POSITION_COMPONENT, testEntity2Id );
    TS_ASSERT( positionData != nullptr );
    TS_ASSERT( positionData->size() == 1 );

    for( vector<ComponentDataTemplate*>::iterator it = positionData->begin(); it != positionData->end(); ++it )
    {
      TS_ASSERT( (*it) == nullptr );
    }
  }
};
