#include <GL/GLMesh.h>
#include <Interfaces/Foundation/ISequenceReader.h>
#include <iostream>
#include <string>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
using namespace std;

namespace E4Gamma
{
  CGLMesh::CGLMesh(SharedPtr<ISequenceReader> pSeq):m_vertexBuffer(0), m_nVerts(0)
  {
    string sMesh;
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
                 pSeq->ReadFloat(pVerts[nVert].z) &&
                 pSeq->ReadString(sNrm) && (sNrm == "nrm") &&
                 pSeq->ReadFloat(pVerts[nVert].nx) &&
                 pSeq->ReadFloat(pVerts[nVert].ny) &&
                 pSeq->ReadFloat(pVerts[nVert].nz) &&
                 pSeq->ReadString(sUV) && (sUV == "uv") &&
                 pSeq->ReadFloat(pVerts[nVert].u) &&
                 pSeq->ReadFloat(pVerts[nVert].v)))
              {
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
  
  CGLMesh::~CGLMesh()
  {
  }
  
  void CGLMesh::RenderPose(IPose* pPose)
  {
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
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}
