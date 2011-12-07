#ifndef _E4Gamma_GLMODEL_H
#define _E4Gamma_GLMODEL_H

#include <Interfaces/Renderer/IModel.h>
#include <Interfaces/Foundation/IDataStore.h>
#include <string>

namespace E4Gamma
{
  class CGLRenderer;

  class CGLModel: public IModel
  {
  public:
    CGLModel(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string& szModel);
    virtual ~CGLModel();
    void RenderPose(IPose* pPose);
  };
}

#endif//_E4Gamma_GLMODEL_H
