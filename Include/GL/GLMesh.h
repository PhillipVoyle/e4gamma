#ifndef _E4Gamma_GLMESH_H
#define _E4Gamma_GLMESH_H

#include <Interfaces/Renderer/IMesh.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <Interfaces/Foundation/IAssetLoader.h>

namespace E4Gamma{
  
  class CGLRenderContext;
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
    
    SharedPtr<CGLRenderContext> m_renderContext;
    
  public:
    CGLMesh(SharedPtr<CGLRenderContext> renderContext, const std::string& sMesh);
    virtual ~CGLMesh();

    virtual void RenderPose(IPose* pPose);
    
    static SharedPtr<IAssetLoader<CGLMesh>> createFactory(SharedPtr<CGLRenderContext> rendercontext);
  };
}

#endif//_E4Gamma_GLMESH_H
