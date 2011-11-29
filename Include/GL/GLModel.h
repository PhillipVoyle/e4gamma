#ifndef _E4Gamma_GLMODEL_H
#define _E4Gamma_GLMODEL_H

#include <Interfaces/Renderer/IModel.h>

namespace E4Gamma{
  class IDataStore;
  class CGLRenderer;
  class CGLModel: public IModel
  {
  public:
    CGLModel(CGLRenderer* pRenderer, IDataStore* pDataStore, const char* szModel);
    virtual ~CGLModel();
    void RenderPose(IPose* pPose);
  };
}

#endif//_E4Gamma_GLMODEL_H
