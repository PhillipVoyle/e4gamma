#ifndef _E4Gamma_IRENDERER_H
#define _E4Gamma_IRENDERER_H

#include <Interfaces/Foundation/IUnknown.h>
#include <Interfaces/Renderer/IMesh.h>
#include <Interfaces/Renderer/IMaterial.h>
#include <Interfaces/Renderer/IModel.h>

namespace E4Gamma
{
  
  class IRenderer: public IUnknown
  {
  public:
    virtual ~IRenderer() {}
    
    //mid level creatures
    virtual SharedPtr<IMesh> LoadMesh(const char* szMesh) = 0;
    virtual SharedPtr<IMaterial> LoadMaterial(const char* szMaterial) = 0;
    
    //high level 
    virtual SharedPtr<IModel> LoadModel(const char* szModel) = 0;
    
    virtual void BeginScene() = 0;
    virtual void Present() = 0;
  };
}

#endif//_E4Gamma_IRENDERER_H
