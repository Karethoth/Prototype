#include "renderSystem.hh"

#include "../components.hh"
#include "../../engine/entitySystem.hh"
#include "../messages/tickMessage.hh"

#include <iostream>
#include <memory>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw.h>

using namespace Engine;
using namespace Engine::Managers;
using namespace std;


RenderSystem::RenderSystem()
{
  isRunning    = false;
  entitySystem = nullptr;
}



RenderSystem::~RenderSystem()
{
}



void* RenderSystem::Run()
{
  pthread_exit( NULL );
  return nullptr;
}



void RenderSystem::SetMeshManager( MeshManager *meshMan )
{
  meshManager = meshMan;
}



bool RenderSystem::Tick( Message *message )
{
  //TickMessage *tickMessage = static_cast<TickMessage*>( message );
  isRunning = true;

  PreRender();

  vector<ComponentDataTemplate*> *meshes = entitySystem->GetComponentDatasOfType( MESH_COMPONENT );

  MeshComponent *mesh;

  for( auto it : *meshes )
  {
    glPushMatrix();

    mesh = static_cast<MeshComponent*>( it );

    mesh->Lock();

    vector<ComponentDataTemplate*> *positions = entitySystem->GetComponentDataForEntry( POSITION_COMPONENT, mesh->entityId );
    vector<ComponentDataTemplate*> *rotations = entitySystem->GetComponentDataForEntry( ROTATION_COMPONENT, mesh->entityId );

    if( positions->size() > 0 )
    {
      PositionComponent *position = dynamic_cast<PositionComponent*>( (*positions->begin()) );
      position->Lock();

      RotationComponent *rotation = nullptr;
      if( rotations->size() > 0 )
        rotation = dynamic_cast<RotationComponent*>( (*rotations->begin()) );

      if( rotation )
        rotation->Lock();

      glTranslatef( position->position.x, position->position.y, position->position.z );

      if( rotation )
      {
        glRotatef( rotation->rotation.x, 1.0, 0.0, 0.0 );
        glRotatef( rotation->rotation.y, 0.0, 1.0, 0.0 );
        glRotatef( rotation->rotation.z, 0.0, 0.0, 1.0 );
      }


      shared_ptr<Mesh> meshPointer = meshManager->Get( mesh->mesh );

      if( meshPointer )
      {
        auto triangles = meshPointer->GetTriangles();

        /*for( auto triangle : *triangles )
        {
          glBegin( GL_TRIANGLE_STRIP );
          {
            glColor3f( 0.0, 1.0, 1.0 );
            glVertex3f( triangle.a.x, triangle.a.y, triangle.a.z );
            glColor3f( 1.0, 1.0, 0.0 );
            glVertex3f( triangle.b.x, triangle.b.y, triangle.b.z );
            glColor3f( 1.0, 0.0, 1.0 );
            glVertex3f( triangle.c.x, triangle.c.y, triangle.c.z );
          }
          glEnd();
        }*/
        //glEnableClientState( GL_VERTEX_ARRAY );
        glUseProgram(3);

        GLuint vbo;
        glGenBuffers( 1, &vbo );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, triangles->size(), triangles, GL_STATIC_DRAW );

        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glDrawArrays( GL_TRIANGLES, 0, triangles->size() );
        //glDisableClientState( GL_VERTEX_ARRAY );

        glDisableVertexAttribArray( 0 );
        glUseProgram( 0 );
      }


      position->Unlock();
      if( rotation )
        rotation->Unlock();
    }

    glPopMatrix();
    mesh->Unlock();
  }

  PostRender();

  isRunning = false;
  return true;
}



void RenderSystem::PreRender()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glLoadIdentity();
  glTranslatef( 0,0, -20 );
}



void RenderSystem::PostRender()
{
  glfwSwapBuffers();
}
