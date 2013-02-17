#ifndef __TEMPLATESTACK_HPP__
#define __TEMPLATESTACK_HPP__

#include <vector>
#include <memory>


namespace Engine
{
  namespace Stacks
  {
    template<typename T>
    class TemplateStack
    {
     protected:
      std::vector< std::shared_ptr<T> > stack;


     public:
      virtual ~TemplateStack()
      {
        stack.clear();
      }



      virtual bool Push( std::shared_ptr<T> item )
      {
        stack.insert( stack.begin(), item );
        return true;
      }



      virtual std::shared_ptr<T> Get( unsigned int index )
      {
        return stack.at( index );
      }



      virtual std::shared_ptr<T> Pop()
      {
        std::shared_ptr<T> ret = stack.front();
        stack.clear();
        return ret;
      }
    };


  }
}

#endif

