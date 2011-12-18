#ifndef _E4Gamma_GLMESH_H
#define _E4Gamma_GLMESH_H

#include <Interfaces/Renderer/IMesh.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

namespace E4Gamma{
  
  class CGLRenderer;
  class IDataStore;
  class ISequenceReader;
  
  class CGLMesh: public IMesh
  {
    //static mesh vertex format
    struct MeshVertex
    {
      GLfloat x, y, z;
      GLfloat nx, ny, nz;
      GLfloat u, v;
    };
    
    GLuint m_vertexBuffer;
    GLuint m_nVerts;
    
  public:
    CGLMesh(SharedPtr<ISequenceReader> pSeq);
    virtual ~CGLMesh();

    virtual void RenderPose(IPose* pPose);
  };
}

#endif//_E4Gamma_GLMESH_H
