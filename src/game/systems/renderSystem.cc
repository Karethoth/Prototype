#include "renderSystem.hh"

#include "../components.hh"
#include "../../engine/entitySystem.hh"
#include "../messages/tickMessage.hh"

#include <iostream>
#include <memory>
#include <vector>
#include <SDL/SDL.h>
#include <GL/gl.h>

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
        glBegin( GL_TRIANGLES );

        auto triangles = meshPointer->GetTriangles();
        for( auto triangle : *triangles )
        {
          glColor3f( 1.0, 1.0, 0.0 );
          glVertex3f( triangle.a.x, triangle.a.y, triangle.a.z );
          glColor3f( 1.0, 0.0, 1.0 );
          glVertex3f( triangle.b.x, triangle.b.y, triangle.b.z );
          glColor3f( 0.0, 1.0, 1.0 );
          glVertex3f( triangle.c.x, triangle.c.y, triangle.c.z );
        }

        glEnd();
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

  glMatrixMode( GL_MODELVIEW );
  glEnable( GL_DEPTH_TEST );
  glLoadIdentity();
  glTranslatef( 0,0, -7 );

  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_LINE);
}



void RenderSystem::PostRender()
{
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);

  SDL_GL_SwapBuffers( );
}
