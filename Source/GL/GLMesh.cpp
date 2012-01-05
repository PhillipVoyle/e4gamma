#include <GL/GLMesh.h>
#include <Interfaces/Foundation/ISequenceReader.h>
#include <iostream>
#include <string>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include <stdcpp/FileSystemDataStore.h>
#include <GL/GLRenderContext.h>

using namespace std;

namespace E4Gamma
{
  CGLMesh::CGLMesh(SharedPtr<CGLRenderContext> renderContext, const std::string &sMeshFile):m_vertexBuffer(0), m_nVerts(0)
  {
    m_renderContext = renderContext;
    
    string sMesh;
    CFileSystemDataStore ds;
    SharedPtr<ISequenceReader> pSeq = ds.OpenTextSequence(sMeshFile); //get this from somewhere
    if(pSeq != nullptr)
    {
      if(pSeq->ReadString(sMesh) && sMesh == "mesh")
      {
        string sVerts;
        if(pSeq->ReadString(sVerts) && sVerts == "verts")
        {
          if(pSeq->ReadU32(m_nVerts))
          {
            MeshVertex *pVerts = new MeshVertex[m_nVerts];
            try {
              bool bFailed;
              for(int nVert = 0; nVert < m_nVerts; nVert++)
              {
                string sPos, sNrm, sUV;
                if(!(
                   pSeq->ReadString(sPos) && (sPos == "pos") &&
                   pSeq->ReadFloat(pVerts[nVert].x) &&
                   pSeq->ReadFloat(pVerts[nVert].y) &&
                   pSeq->ReadFloat(pVerts[nVert].z)))
                {
                  cout << "Bad pos at vert " << nVert << endl;
                  bFailed = true;
                  break;
                }
                
                if(!(
                   pSeq->ReadString(sNrm) && (sNrm == "nrm") &&
                   pSeq->ReadFloat(pVerts[nVert].nx) &&
                   pSeq->ReadFloat(pVerts[nVert].ny) &&
                   pSeq->ReadFloat(pVerts[nVert].nz)))
                {
                  cout << "Bad nrm at vert " << nVert << endl;
                  bFailed = true;
                  break;
                }                   
                
                if(!(
                   pSeq->ReadString(sUV) && (sUV == "uv") &&
                   pSeq->ReadFloat(pVerts[nVert].u) &&
                   pSeq->ReadFloat(pVerts[nVert].v)))
                {
                  cout << "Bad uv at vert " << nVert << endl;
                  bFailed = true;
                  break;
                }
              }
              
              if(!bFailed)
              {
                cout << "Read " << m_nVerts << " verts OK" << endl;
                
                glGenBuffers(1, &m_vertexBuffer);
                glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * m_nVerts, pVerts, GL_STATIC_DRAW);
                
              }
            }
            catch (...)
            {
              cout << "Exception!" << endl;
            }
            delete[] pVerts;
          }
        }
      }
    }
  }
  
  CGLMesh::~CGLMesh()
  {
  }
  
  void CGLMesh::RenderPose(IPose* pPose)
  {    
    m_renderContext->m_model = Matrix4();
    m_renderContext->FlushContext();
    
    glEnableClientState(GL_VERTEX_ARRAY);	 // Enable Vertex Arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);	// Enable Texture Coord Arrays
    glEnableClientState(GL_NORMAL_ARRAY);

    //fill in your array of vertices and texture coordinates with data
    // Set The Vertex Pointer To Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexPointer(3, GL_FLOAT, sizeof(MeshVertex), (GLvoid*)0); 
    glNormalPointer(GL_FLOAT, sizeof(MeshVertex), (GLvoid*)12);
    glTexCoordPointer(2, GL_FLOAT, sizeof(MeshVertex), (GLvoid*)24);

    glDrawArrays( GL_TRIANGLES, 0, m_nVerts ); //Draw the vertices 
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  
  class CGLMeshFactory: public IAssetLoader<CGLMesh>
  {
    SharedPtr<CGLRenderContext> m_renderContext;
  public:
    CGLMeshFactory(SharedPtr<CGLRenderContext> renderContext):m_renderContext(renderContext)
    {
    }
    
    virtual ~CGLMeshFactory() { }
    
    SharedPtr<CGLMesh> LoadAsset(const std::string& sAsset)
    {
      return new IUnknownImpl<CGLMesh>(m_renderContext, sAsset);
    }
  };
  
  SharedPtr<IAssetLoader<CGLMesh>> CGLMesh::createFactory(SharedPtr<CGLRenderContext> renderContext)
  {
    return new IUnknownImpl<CGLMeshFactory>(renderContext);
  }
}
