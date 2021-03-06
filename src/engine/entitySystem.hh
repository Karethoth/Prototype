#ifndef __ENTITYSYSTEM_HH__
#define __ENTITYSYSTEM_HH__

#include <thread>
#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <ostream>


namespace Engine
{
  typedef struct
  {
    unsigned long assemblageId;
    std::string label;
    std::string name;
    std::string description;
  } Assemblage;


  typedef struct
  {
    int componentId;
    std::string name;
    std::string description;
    std::string tableName;
  } Component;


  typedef struct
  {
    unsigned long entityId;
    int componentId;
    unsigned long componentDataId;
  } EntityComponent;



  class ComponentDataTemplate
  {
   public:
    virtual ~ComponentDataTemplate();

    int Lock();
    int Unlock();

    virtual std::string Print() = 0;

    void SetIds( unsigned long entity, unsigned long componentData );

    unsigned long entityId;
    unsigned long componentDataId;


   protected:
    std::mutex mtx;
  };



  class EntitySystem
  {
   public:
    EntitySystem();
    ~EntitySystem();

    unsigned long CreateNewEntity( std::string debugName );
    bool CreateComponent( Component component );
    unsigned long CreateEntityComponentAndAddTo( int componentType, unsigned long entityId, ComponentDataTemplate *initialValue );

    std::vector<ComponentDataTemplate*>* GetComponentDataForEntry( int componentType, unsigned long entityId );
    std::vector<ComponentDataTemplate*>* GetComponentDatasOfType( int componentType );
    EntityComponent* GetEntityComponent( int componentType, unsigned long componentId );


   protected:
    std::map<unsigned long, Assemblage> assemblages;
    std::map<unsigned long, unsigned long> assemblageComponents;
    std::map<int, Component> components;
    std::map<unsigned long, std::string> entities;
    std::multimap<unsigned long, EntityComponent> entityComponents;
    std::map< std::string, std::map<unsigned long, ComponentDataTemplate*> > componentData;


    Component* GetComponent( int componentType );

   private:
    std::mutex entitySystemMutex;
  };
}

#endif // __ENTITYSYSTEM_HH__
