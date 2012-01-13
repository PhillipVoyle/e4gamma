#ifndef _E4Gamma_GLMESH_H
#define _E4Gamma_GLMESH_H

#include <Interfaces/Renderer/IMesh.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <Interfaces/Foundation/IAssetLoader.h>
#include <Math/Vector.h>

#include <vector>

namespace E4Gamma{
  
  class CGLRenderContext;
  class IDataStore;
  class ISequenceReader;
  class Vector;
  
  class CGLMesh: public IMesh
  {
  public:
    //static textured vertex format
    struct TexturedVertex
    {
      Vector position;
      Vector normal;
      Vector tangent;
      Vector binormal;
      GLfloat u, v;
    };
    
    struct Triangle
    {
      Vector normal;
      GLfloat offset;
      unsigned verts[3];
    };
    
    struct Edge
    {
      int t1, t2; //triangle
      unsigned v1, v2; //edge
    };
    
    
    GLuint m_nEdges;
    Edge* m_edges;
    
    GLuint m_nTriangles;
    Triangle* m_triangles;
    
    GLuint m_vertexBuffer;
    GLuint m_nTexturedVerts;

  public:

    SharedPtr<CGLRenderContext> m_renderContext;
    GLuint m_nGeometryVerts;
    Vector* m_geometryVerts;

    CGLMesh(SharedPtr<CGLRenderContext> renderContext, const std::string& sMesh);
    virtual ~CGLMesh();

    virtual void RenderPose(IPose* pPose);
    SharedPtr<IMesh> CreateShadowVolume();
    void GenerateSilhouette(std::vector<int>& vSil);
    
    static SharedPtr<IAssetLoader<CGLMesh>> createFactory(SharedPtr<CGLRenderContext> rendercontext);
  };
}

#endif//_E4Gamma_GLMESH_H
