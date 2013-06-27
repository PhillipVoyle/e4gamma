#include <GL/GLModel.h>
#include <GL/GLMesh.h>
#include <GL/GLMaterial.h>
#include <stdcpp/FileSystemDataStore.h>
#include <Interfaces/Foundation/ISequenceReader.h>

#include <iostream>

namespace E4Gamma
{
  CGLModel::CGLModel(const std::string& sModel, SharedPtr<IAssetLoader<E4Gamma::CGLMesh> > meshFactory, SharedPtr<IAssetLoader<E4Gamma::CGLMaterial> > materialFactory)
  {
    CFileSystemDataStore ds;
    
    SharedPtr<ISequenceReader> pSeq = ds.OpenTextSequence(sModel);
    
    if(pSeq != nullptr)
    {
      string sModel;
      if(pSeq->ReadString(sModel) && sModel == "model")
      {
        int nSurfaces = 0;
        string sSurfaces;
        if((pSeq->ReadString(sSurfaces) && sSurfaces == "surfaces") && pSeq->ReadI32(nSurfaces))
        {
          for(int nSurface = 0; nSurface < nSurfaces; nSurface++)
          {
            string sMesh;
            string sMeshLocation;
            string sMaterial;
            string sMaterialLocation;
            
            if((pSeq->ReadString(sMesh) && sMesh == "mesh") && pSeq->ReadString(sMeshLocation) &&
               (pSeq->ReadString(sMaterial) && sMaterial == "material") && pSeq->ReadString(sMaterialLocation))
            {
              cout << "Mesh " << sMeshLocation << endl;
              cout << "Material " << sMaterialLocation << endl;
              Surface surface = {meshFactory->LoadAsset(sMeshLocation), materialFactory->LoadAsset(sMaterialLocation)};
              m_surfaces.push_back(surface);
            }
          }
        }
      }
    }
  }
  
  CGLModel::~CGLModel()
  {
  }

  void CGLModel::RenderPose(SharedPtr<IFrame> pPose)
  {
    for(auto it = m_surfaces.begin(); it != m_surfaces.end(); it++)
    {
      it->material->RenderSet();
      it->mesh->RenderPose(pPose); //todo: we probably need to map poses some how.. bone indices?
    }
  }
  
  class CGLModelFactory: public IAssetLoader<CGLModel>
  {
    SharedPtr<IAssetLoader<E4Gamma::CGLMesh> > m_meshFactory;
    SharedPtr<IAssetLoader<E4Gamma::CGLMaterial> > m_materialFactory;
    
  public:
    CGLModelFactory(SharedPtr<IAssetLoader<E4Gamma::CGLMesh> > meshFactory, SharedPtr<IAssetLoader<E4Gamma::CGLMaterial> > materialFactory)
    : m_meshFactory(meshFactory), m_materialFactory(materialFactory)
    {
    }
    
    virtual ~CGLModelFactory() { }
    
    SharedPtr<CGLModel> LoadAsset(const std::string& sAsset)
    {
      return new IUnknownImpl<CGLModel>(sAsset, m_meshFactory, m_materialFactory);
    }
  };
  
  SharedPtr<IAssetLoader<CGLModel>> CGLModel::createFactory(SharedPtr<IAssetLoader<E4Gamma::CGLMesh> > meshFactory, SharedPtr<IAssetLoader<E4Gamma::CGLMaterial> > materialFactory)
  {
    return new IUnknownImpl<CGLModelFactory>(meshFactory, materialFactory);
  }
  
}