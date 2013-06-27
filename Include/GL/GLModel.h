#ifndef _E4Gamma_GLMODEL_H
#define _E4Gamma_GLMODEL_H

#include <Interfaces/Renderer/IModel.h>
#include <Interfaces/Foundation/IDataStore.h>
#include <string>
#include <GL/GLMesh.h>
#include <GL/GLMaterial.h>

namespace E4Gamma
{
  class CGLRenderer;

  class CGLModel: public IModel
  {
    struct Surface
    {
      SharedPtr<CGLMesh> mesh;
      SharedPtr<CGLMaterial> material;
    };
    
    std::list<Surface> m_surfaces;
    
  public:
    CGLModel(const std::string& szModel, SharedPtr<IAssetLoader<E4Gamma::CGLMesh> > meshFactory, SharedPtr<IAssetLoader<E4Gamma::CGLMaterial> > materialFactory);
    virtual ~CGLModel();
    void RenderPose(SharedPtr<IFrame> pPose);
    
    static SharedPtr<IAssetLoader<CGLModel>> createFactory(SharedPtr<IAssetLoader<CGLMesh>> meshFactory, SharedPtr<IAssetLoader<CGLMaterial>> materialFactory);
  };
}

#endif//_E4Gamma_GLMODEL_H
