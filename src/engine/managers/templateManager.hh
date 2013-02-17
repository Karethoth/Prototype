#ifndef __TEMPLATEMANAGER_HPP__
#define __TEMPLATEMANAGER_HPP__

#include <map>
#include <string>
#include <memory>


namespace Engine
{
  namespace Managers
  {

    template<typename T>
    class TemplateManager
    {
     protected:
      std::map< std::string, std::shared_ptr<T> > items;


     public:
      virtual ~TemplateManager()
      {
        items.clear();
      }



      virtual bool Load( std::string& ) = 0;



      virtual bool Add( std::string &key, std::shared_ptr<T> item )
      {
        items[key] = item;
        return true;
      }



      virtual std::shared_ptr<T> Get( std::string &key )
      {
        return items[key];
      }



      virtual std::shared_ptr<T> Get( const char *key )
      {
        return items[std::string(key)];
      }



      virtual std::shared_ptr<T> Remove( std::string &key )
      {
        std::shared_ptr<T> ret = items[key];
        items.erase(key);
        return ret;
      }



      virtual std::map< std::string, std::shared_ptr<T> > *GetPointer()
      {
        return &items;
      }
    };


  }
}

#endif
