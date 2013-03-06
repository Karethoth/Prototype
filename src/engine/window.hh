#ifndef __WINDOW_HH__
#define __WINDOW_HH__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


namespace Engine
{
  class Window
  {
   public:
    Window();
    ~Window();

    bool SetSize( int width, int height );


   private:

  };
}

#endif // __WINDOW_HH__
