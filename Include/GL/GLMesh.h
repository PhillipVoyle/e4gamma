#ifndef _E4Gamma_GLMESH_H
#define _E4Gamma_GLMESH_H

#include <Interfaces/Renderer/IMesh.h>

namespace E4Gamma
{
  class CGLRenderer;
  
  class CGLMesh: public IMesh
  {
  public:
    CGLMesh(CGLRenderer* pRenderer, IDataStore*pDataStore, const char* szMesh);
    virtual ~CGLMesh();

    virtual void RenderPose(IPose* pPose);
  };
}

#endif//_E4Gamma_GLMESH_H
