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
  CGLMesh::CGLMesh(SharedPtr<CGLRenderContext> renderContext, const std::string &sMeshFile):m_vertexBuffer(0), m_geometryVerts(nullptr), m_nGeometryVerts(0), m_nTexturedVerts(0)
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
          if(pSeq->ReadU32(m_nGeometryVerts))
          {
            m_geometryVerts = new Vector[m_nGeometryVerts];
            Vector *pNormals = new Vector[m_nGeometryVerts];

            bool bFailed = false;
            for(int nVert = 0; nVert < m_nGeometryVerts; nVert++)
            {
              string sPos, sNrm, sUV;
              if(!(
                 pSeq->ReadString(sPos) && (sPos == "pos") &&
                 pSeq->ReadFloat(m_geometryVerts[nVert].x) &&
                 pSeq->ReadFloat(m_geometryVerts[nVert].y) &&
                 pSeq->ReadFloat(m_geometryVerts[nVert].z)))
              {
                cout << sMeshFile << " Bad pos at vert " << nVert << endl;
                bFailed = true;
                break;
              }
              
              if(!(
                 pSeq->ReadString(sNrm) && (sNrm == "nrm") &&
                 pSeq->ReadFloat(pNormals[nVert].x) &&
                 pSeq->ReadFloat(pNormals[nVert].y) &&
                 pSeq->ReadFloat(pNormals[nVert].z)))
              {
                cout << sMeshFile << " Bad nrm at vert " << nVert << endl;
                bFailed = true;
                break;
              }                   
            }
            
            TexturedVertex* pTexturedVerts = nullptr;
            string sMeshType;
            if(pSeq->ReadString(sMeshType))
            {
              if(sMeshType == "triangle_list")
              {
                if(pSeq->ReadU32(m_nTriangles))
                {
                  m_triangles = new Triangle[m_nTriangles];
                  m_nTexturedVerts = m_nTriangles * 3;
                  pTexturedVerts = new TexturedVertex[m_nTexturedVerts];
                  int nVert = 0;
                  for(int nTri = 0; nTri < m_nTriangles; nTri ++)
                  {
                    string sEq;
                    if(
                      pSeq->ReadString(sEq) && (sEq == "eq") &&
                      pSeq->ReadFloat(m_triangles[nTri].normal.x) &&
                      pSeq->ReadFloat(m_triangles[nTri].normal.y) &&
                      pSeq->ReadFloat(m_triangles[nTri].normal.z) &&
                      pSeq->ReadFloat(m_triangles[nTri].offset)
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
                          pSeq->ReadFloat(pTexturedVerts[nVert].u) &&
                          pSeq->ReadFloat(pTexturedVerts[nVert].v))
                        {
                          m_triangles[nTri].verts[nTriVert] = nVertexIndex;
                          pTexturedVerts[nVert].position = m_geometryVerts[nVertexIndex];
                          pTexturedVerts[nVert].normal = pNormals[nVertexIndex];
                        }
                        else
                        {
                          cout << sMeshFile << " bad textured vertex " << nVert << endl;
                          bFailed = true;
                          break;
                        }
                      }
                      
                      TexturedVertex& v1 = pTexturedVerts[nTri * 3 + 0];
                      TexturedVertex& v2 = pTexturedVerts[nTri * 3 + 1];
                      TexturedVertex& v3 = pTexturedVerts[nTri * 3 + 2];
                      
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
            if (pSeq->ReadString(sEdges) && (sEdges == "edges") &&
              pSeq->ReadU32(m_nEdges))
            {
              m_edges = new Edge[m_nEdges];
              for(int nEdge = 0; nEdge < m_nEdges; nEdge ++)
              {
                string sE, sV;
                if(!(
                  pSeq->ReadString(sE) && (sE == "e") &&
                  pSeq->ReadI32(m_edges[nEdge].t1) &&
                  pSeq->ReadI32(m_edges[nEdge].t2) &&
                  pSeq->ReadString(sV) && (sV == "v") &&
                  pSeq->ReadU32(m_edges[nEdge].v1) &&
                  pSeq->ReadU32(m_edges[nEdge].v2)))
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
              cout << sMeshFile << " Read " << m_nGeometryVerts << " geometry verts OK" << endl;
              cout << sMeshFile << " Read " << m_nTexturedVerts << " textured verts OK" << endl;
              
              glGenBuffers(1, &m_vertexBuffer);
              glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
              glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * m_nTexturedVerts, pTexturedVerts, GL_STATIC_DRAW);
            }
            else if (m_geometryVerts != nullptr)
            {
              cout << sMeshFile << " Error during load" << endl;
              delete [] m_geometryVerts;
              m_geometryVerts = nullptr;
            }
            if(pNormals != nullptr)
            {
              delete[] pNormals;
            }
            if(pTexturedVerts != nullptr)
            {
              delete[] pTexturedVerts;
            }
          }
        }
      }
    }
  }
  
  CGLMesh::~CGLMesh()
  {
  }
  
  class CGLMeshShadowVolume: public IMesh
  {
    SharedPtr<CGLMesh> m_pParent;
  public:

    std::vector<Vector> m_shadowVolume;
    
    Vector m_lightPosition;
    
    CGLMeshShadowVolume(SharedPtr<CGLMesh> pParent):m_pParent(pParent)
    {
      m_lightPosition = m_pParent->m_renderContext->m_vLightPosition;
      
      std::vector<bool> facingTri(m_pParent->m_nTriangles, false);
      
      float fAlpha = 10.0f;    
      for (int nTri = 0; nTri < m_pParent->m_nTriangles; nTri++)
      {
        const CGLMesh::Triangle& tri = m_pParent->m_triangles[nTri];
        bool bFacingTri = Dot(tri.normal, m_lightPosition) > tri.offset;
        if(bFacingTri)
        {
          facingTri[nTri] = true;
          //we don't need facing tris...
          
        }
        else
        {
          m_shadowVolume.push_back(m_pParent->m_geometryVerts[tri.verts[0]]);
          m_shadowVolume.push_back(m_pParent->m_geometryVerts[tri.verts[1]]);
          m_shadowVolume.push_back(m_pParent->m_geometryVerts[tri.verts[2]]);

          m_shadowVolume.push_back(m_pParent->m_geometryVerts[tri.verts[1]] * fAlpha + m_lightPosition * (1.0f - fAlpha));
          m_shadowVolume.push_back(m_pParent->m_geometryVerts[tri.verts[0]] * fAlpha + m_lightPosition * (1.0f - fAlpha));
          m_shadowVolume.push_back(m_pParent->m_geometryVerts[tri.verts[2]] * fAlpha + m_lightPosition * (1.0f - fAlpha));
        }
      }
      
      for(int nEdge = 0; nEdge < m_pParent->m_nEdges; nEdge ++)
      {
        const CGLMesh::Edge& edge = m_pParent->m_edges[nEdge];
        if((edge.t2 == -1) || (facingTri[edge.t1] != facingTri[edge.t2]))
        {

          bool bInvert = !facingTri[edge.t1];
          Vector v1 = m_pParent->m_geometryVerts[bInvert?edge.v2:edge.v1];
          Vector v2 = m_pParent->m_geometryVerts[bInvert?edge.v1:edge.v2];

          Vector v3 = v1 * fAlpha + m_lightPosition * (1.0f - fAlpha);
          Vector v4 = v2 * fAlpha + m_lightPosition * (1.0f - fAlpha); 
          
          m_shadowVolume.push_back(v1);
          m_shadowVolume.push_back(v2);
          m_shadowVolume.push_back(v3);
          
          m_shadowVolume.push_back(v3);
          m_shadowVolume.push_back(v2);
          m_shadowVolume.push_back(v4);
        }
      }
    }
    
    virtual ~CGLMeshShadowVolume()
    {
    }
    
    void RenderPose(IPose* pPose)
    {
      m_pParent->m_renderContext->m_model = Matrix4();
      m_pParent->m_renderContext->FlushContext();
      
      glEnableClientState(GL_VERTEX_ARRAY);	 // Enable Vertex Arrays
      
      glVertexPointer(3, GL_FLOAT, 0, (void*)&m_shadowVolume[0]);
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

  void CGLMesh::RenderPose(IPose* pPose)
  {    
    m_renderContext->m_model = Matrix4();
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
