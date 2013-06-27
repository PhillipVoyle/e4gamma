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

  CGLMesh::CGLMesh(
    SharedPtr<CGLRenderContext> renderContext,
    const std::vector<Vector>& geometryVerts,
    const std::vector<Triangle>& triangles,
    const std::vector<Edge>& edges,
    const std::vector<TexturedVertex>& texturedVerts)
  {
    m_renderContext = renderContext;
    

    m_geometryVerts = geometryVerts;
    m_triangles = triangles;
    m_edges = edges;
    
    m_nTexturedVerts = (GLuint)texturedVerts.size();
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CGLMesh::TexturedVertex) * m_nTexturedVerts, &(texturedVerts[0]), GL_STATIC_DRAW);
  }
  
  CGLMesh::~CGLMesh()
  {
  }
  
  class CGLMeshShadowVolume: public IMesh
  {
    SharedPtr<CGLMesh> m_pParent;
  public:

    struct Vector4
    {
      float x, y, z, w;
    };

    std::vector<Vector4> m_shadowVolume;
    
    Vector m_lightPosition;
    
    static Vector4 tovec4(const Vector& v, float f)
    {
      return {v.x, v.y, v.z, f};
    }
    
    CGLMeshShadowVolume(SharedPtr<CGLMesh> pParent):m_pParent(pParent)
    {
      m_lightPosition = m_pParent->m_renderContext->m_vLightPosition;
      
      std::vector<bool> facingTri(m_pParent->m_triangles.size(), false);
      
      //float fAlpha = 10.0f;    
      for (int nTri = 0; nTri < m_pParent->m_triangles.size(); nTri++)
      {
        const CGLMesh::Triangle& tri = m_pParent->m_triangles[nTri];
        //bool bFacingTri = Dot(tri.normal, m_lightPosition) > tri.offset;
        if(Dot(tri.normal, m_lightPosition) > tri.offset)
        {
          facingTri[nTri] = true;
          //we don't need facing tris...
        }
        
        if(Dot(tri.normal, m_lightPosition) < tri.offset)
        {
          m_shadowVolume.push_back(tovec4(m_pParent->m_geometryVerts[tri.verts[0]], 1.0f));
          m_shadowVolume.push_back(tovec4(m_pParent->m_geometryVerts[tri.verts[1]], 1.0f));
          m_shadowVolume.push_back(tovec4(m_pParent->m_geometryVerts[tri.verts[2]], 1.0f));

          m_shadowVolume.push_back(tovec4(m_pParent->m_geometryVerts[tri.verts[1]] - m_lightPosition, 0.0f));
          m_shadowVolume.push_back(tovec4(m_pParent->m_geometryVerts[tri.verts[0]] - m_lightPosition, 0.0f));
          m_shadowVolume.push_back(tovec4(m_pParent->m_geometryVerts[tri.verts[2]] - m_lightPosition, 0.0f));
        }
      }
      
      for(int nEdge = 0; nEdge < m_pParent->m_edges.size(); nEdge ++)
      {
        const CGLMesh::Edge& edge = m_pParent->m_edges[nEdge];
        if((edge.t2 == -1) || (facingTri[edge.t1] != facingTri[edge.t2]))
        {

          bool bInvert = !facingTri[edge.t1];
          Vector v1 = m_pParent->m_geometryVerts[bInvert?edge.v2:edge.v1];
          Vector v2 = m_pParent->m_geometryVerts[bInvert?edge.v1:edge.v2];

          Vector v3 = v1 - m_lightPosition;
          Vector v4 = v2 - m_lightPosition; 
          
          m_shadowVolume.push_back(tovec4(v1, 1.0f));
          m_shadowVolume.push_back(tovec4(v2, 1.0f));
          m_shadowVolume.push_back(tovec4(v3, 0.0f));
          
          m_shadowVolume.push_back(tovec4(v3, 0.0f));
          m_shadowVolume.push_back(tovec4(v2, 1.0f));
          m_shadowVolume.push_back(tovec4(v4, 0.0f));
        }
      }
    }
    
    virtual ~CGLMeshShadowVolume()
    {
    }
    
    void RenderPose(SharedPtr<IFrame> pPose)
    {
      m_pParent->m_renderContext->m_model = Matrix4();
      m_pParent->m_renderContext->FlushContext();
      
      glEnableClientState(GL_VERTEX_ARRAY);	 // Enable Vertex Arrays
      
      glVertexPointer(4, GL_FLOAT, 0, (void*)&m_shadowVolume[0]);
      glDrawArrays(GL_TRIANGLES, 0, (int)m_shadowVolume.size());
      
      Matrix4 oldProjection = m_pParent->m_renderContext->m_projection;
      
      Matrix4 newProjection(
        -oldProjection._rx, 0, 0, 0,
        0, -oldProjection._uy, 0, 0,
        0, 0, 0, -1,
        0, 0, 0, 0);
      
      m_pParent->m_renderContext->m_projection = newProjection;
      m_pParent->m_renderContext->FlushContext();
      glDrawArrays(GL_TRIANGLES, 0, (int)m_shadowVolume.size());
      m_pParent->m_renderContext->m_projection = oldProjection;
      glDisableClientState(GL_VERTEX_ARRAY);
    }
    
    SharedPtr<IMesh> CreateShadowVolume()
    {
      return nullptr;
    }
  };
  
  SharedPtr<IMesh> CGLMesh::CreateShadowVolume()
  {
    return new IUnknownImpl<CGLMeshShadowVolume>(this);
  }

  void CGLMesh::RenderPose(SharedPtr<IFrame> pPose)
  {
    if (pPose.m_ptr == nullptr)
    {
      m_renderContext->m_model = Matrix4();
    }
    else
    {
      m_renderContext->m_model = pPose->GetTransform();
    }
    m_renderContext->FlushContext();
    
    glEnableClientState(GL_VERTEX_ARRAY);	 // Enable Vertex Arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);	// Enable Texture Coord Arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    //glEnableClientState(GL_INDEX_ARRAY);

    //fill in your array of vertices and texture coordinates with data
    // Set The Vertex Pointer To Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexPointer(3, GL_FLOAT, sizeof(TexturedVertex), (GLvoid*)(&((TexturedVertex*)0)->position)); 
    glNormalPointer(GL_FLOAT, sizeof(TexturedVertex), (GLvoid*)(&((TexturedVertex*)0)->normal));
    int nTangent = glGetAttribLocation(m_renderContext->m_nProgram, "in_tangent");
    if(nTangent > 0)
    {
      glEnableVertexAttribArray(nTangent);
      glVertexAttribPointer(nTangent, 3, GL_FLOAT, GL_TRUE, sizeof(TexturedVertex), (GLvoid*)(&((TexturedVertex*)0)->tangent));
    }
    
    int nBinormal = glGetAttribLocation(m_renderContext->m_nProgram, "in_binormal");
    if(nBinormal > 0)
    {
      glEnableVertexAttribArray(nBinormal);
      glVertexAttribPointer(nBinormal, 3, GL_FLOAT, GL_TRUE, sizeof(TexturedVertex), (GLvoid*)(&((TexturedVertex*)0)->binormal));
    }
    
    glTexCoordPointer(2, GL_FLOAT, sizeof(TexturedVertex), (GLvoid*)(&((TexturedVertex*)0)->u));

    glDrawArrays( GL_TRIANGLES, 0, m_nTexturedVerts ); //Draw the vertices 
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    //glDisableClientState(GL_INDEX_ARRAY);
  }
  
  class CGLMeshFactory: public IAssetLoader<CGLMesh>
  {
    SharedPtr<CGLRenderContext> m_renderContext;
  public:
    CGLMeshFactory(SharedPtr<CGLRenderContext> renderContext):m_renderContext(renderContext)
    {
    }
    
    virtual ~CGLMeshFactory() { }
    
    SharedPtr<CGLMesh> LoadAsset(const std::string& sMeshFile)
    {
      SharedPtr<CGLMesh> result;
      std::vector<Vector> geometryVerts;
      std::vector<Vector> normals;
      std::vector<CGLMesh::TexturedVertex> texturedVerts;
      std::vector<CGLMesh::Triangle> triangles;
      std::vector<CGLMesh::Edge> edges;

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
            uint32_t nVerts = 0;
            if(pSeq->ReadU32(nVerts))
            {
              geometryVerts.resize(nVerts);
              
              normals.resize(nVerts);

              bool bFailed = false;
              for(int nVert = 0; nVert < geometryVerts.size(); nVert++)
              {
                string sPos, sNrm, sUV;
                if(!(
                   pSeq->ReadString(sPos) && (sPos == "pos") &&
                   pSeq->ReadFloat(geometryVerts[nVert].x) &&
                   pSeq->ReadFloat(geometryVerts[nVert].y) &&
                   pSeq->ReadFloat(geometryVerts[nVert].z)))
                {
                  cout << sMeshFile << " Bad pos at vert " << nVert << endl;
                  bFailed = true;
                  break;
                }
                
                if(!(
                   pSeq->ReadString(sNrm) && (sNrm == "nrm") &&
                   pSeq->ReadFloat(normals[nVert].x) &&
                   pSeq->ReadFloat(normals[nVert].y) &&
                   pSeq->ReadFloat(normals[nVert].z)))
                {
                  cout << sMeshFile << " Bad nrm at vert " << nVert << endl;
                  bFailed = true;
                  break;
                }                   
              }
              
              
              string sMeshType;
              if(pSeq->ReadString(sMeshType))
              {
                if(sMeshType == "triangle_list")
                {
                  uint32_t nTriangles = 0;
                  if(pSeq->ReadU32(nTriangles))
                  {
                    triangles.resize(nTriangles);
                    texturedVerts.resize(nTriangles * 3);
                    
                    int nVert = 0;
                    for(int nTri = 0; nTri < triangles.size(); nTri ++)
                    {
                      string sEq;
                      if(
                        pSeq->ReadString(sEq) && (sEq == "eq") &&
                        pSeq->ReadFloat(triangles[nTri].normal.x) &&
                        pSeq->ReadFloat(triangles[nTri].normal.y) &&
                        pSeq->ReadFloat(triangles[nTri].normal.z) &&
                        pSeq->ReadFloat(triangles[nTri].offset)
                        )
                      {
                        for(int nTriVert = 0; nTriVert < 3; nTriVert++, nVert++)
                        {
                          string sV, sUV;
                          unsigned nVertexIndex = 0;
                        
                          if(
                            pSeq->ReadString(sV) && (sV == "v") &&
                            pSeq->ReadU32(nVertexIndex) &&
                            pSeq->ReadString(sUV) && (sUV == "uv") &&
                            pSeq->ReadFloat(texturedVerts[nVert].u) &&
                            pSeq->ReadFloat(texturedVerts[nVert].v))
                          {
                            triangles[nTri].verts[nTriVert] = nVertexIndex;
                            texturedVerts[nVert].position = geometryVerts[nVertexIndex];
                            texturedVerts[nVert].normal = normals[nVertexIndex];
                          }
                          else
                          {
                            cout << sMeshFile << " bad textured vertex " << nVert << endl;
                            bFailed = true;
                            break;
                          }
                        }
                        
                        CGLMesh::TexturedVertex& v1 = texturedVerts[nTri * 3 + 0];
                        CGLMesh::TexturedVertex& v2 = texturedVerts[nTri * 3 + 1];
                        CGLMesh::TexturedVertex& v3 = texturedVerts[nTri * 3 + 2];
                        
                        float x1 = v2.position.x - v1.position.x;
                        float x2 = v3.position.x - v1.position.x;
                        
                        float y1 = v2.position.y - v1.position.y;
                        float y2 = v3.position.y - v1.position.y;
                        
                        float z1 = v2.position.z - v1.position.z;
                        float z2 = v3.position.z - v1.position.z;
                        
                        float s1 = v2.u - v1.u;
                        float s2 = v3.u - v1.u;
                        
                        float t1 = v2.v - v1.v;
                        float t2 = v3.v - v1.v;
                        
                        float ir= (s1 * t2 - s2 * t1);
                        float r = 1.0f;
                        
                        if(fabs(ir) > FLT_EPSILON)
                        {
                          r = 1.0f / ir;
                        }
                        else
                        {
                          cout << "Degenerate tri at " << nTri << endl;
                        }
                        
                        Vector sdir(
                          (t2 * x1 - t1 * x2) * r,
                          (t2 * y1 - t1 * y2) * r,
                          (t2 * z1 - t1 * z2) * r);
                          
                        Vector tdir(
                          (s1 * x2 - s2 * x1) * r,
                          (s1 * y2 - s2 * y1) * r,
                          (s1 * z2 - s2 * z1) * r);
                        
                        v1.tangent = (sdir - v1.normal * Dot(sdir, v1.normal)).normalize();
                        v2.tangent = (sdir - v2.normal * Dot(sdir, v2.normal)).normalize(); 
                        v3.tangent = (sdir - v3.normal * Dot(sdir, v3.normal)).normalize();
                        
                        v1.binormal = (tdir - v1.normal * Dot(tdir, v1.normal)).normalize(); 
                        v2.binormal = (tdir - v2.normal * Dot(tdir, v2.normal)).normalize(); 
                        v3.binormal = (tdir - v3.normal * Dot(tdir, v3.normal)).normalize();                      
                      }
                      else
                      {
                        cout << sMeshFile << " bad tri " << nTri << endl;
                        bFailed = true;
                        break;
                      }
                    }
                  }
                  else
                  {
                    cout << sMeshFile << " could not read triangle count" << endl;
                    bFailed = true;
                  }
                }
                else
                {
                  cout << sMeshFile << " unrecognised mesh type: " << sMeshType << endl;
                  bFailed = true;
                }
              }
              
              string sEdges;
              uint32_t nEdges = 0;
              if (pSeq->ReadString(sEdges) && (sEdges == "edges") &&
                pSeq->ReadU32(nEdges))
              {
                edges.resize(nEdges);
                for(int nEdge = 0; nEdge < nEdges; nEdge ++)
                {
                  string sE, sV;
                  if(!(
                    pSeq->ReadString(sE) && (sE == "e") &&
                    pSeq->ReadI32(edges[nEdge].t1) &&
                    pSeq->ReadI32(edges[nEdge].t2) &&
                    pSeq->ReadString(sV) && (sV == "v") &&
                    pSeq->ReadU32(edges[nEdge].v1) &&
                    pSeq->ReadU32(edges[nEdge].v2)))
                  {
                    cout << sMeshFile << " error loading edge " << nEdge << endl;
                  }
                }
              }
              else
              {
                cout << sMeshFile << " error loading edges" << endl;
                bFailed = true;
              }
              
              if(!bFailed)
              {
                cout << sMeshFile << " Read " << geometryVerts.size() << " geometry verts OK" << endl;
                cout << sMeshFile << " Read " << texturedVerts.size() << " textured verts OK" << endl;
                result = new IUnknownImpl<CGLMesh>(m_renderContext, geometryVerts, triangles, edges, texturedVerts);
              }
              else
              {
                cout << sMeshFile << " Error during load" << endl;
              }
            }
          }
        }
      }

    
      return result;
    }
  };
  
  SharedPtr<IAssetLoader<CGLMesh>> CGLMesh::createFactory(SharedPtr<CGLRenderContext> renderContext)
  {
    return new IUnknownImpl<CGLMeshFactory>(renderContext);
  }
}
