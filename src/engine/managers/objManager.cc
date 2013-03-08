#include "objManager.hh"

using namespace Engine;
using namespace Engine::Managers;
using std::string;


bool OBJManager::Load( string &name )
{
  std::shared_ptr<OBJ> obj( new OBJ() );
  if( !obj->Load( name ) )
    return false;

  Add( name, obj );
  return true;
}
