#ifndef _E4Gamma_IRENDERER_H
#define _E4Gamma_IRENDERER_H

#include <string>
#include <Interfaces/Foundation/IUnknown.h>
#include <Interfaces/Renderer/IMesh.h>
#include <Interfaces/Renderer/IMaterial.h>
#include <Interfaces/Renderer/IModel.h>
#include <Interfaces/Renderer/ICamera.h>

namespace E4Gamma
{
  class IRenderer: public IUnknown
  {
  public:
    virtual ~IRenderer() {}
    
    //mid level creatures
    virtual SharedPtr<IMesh> LoadMesh(const std::string& sMesh) = 0;
    virtual SharedPtr<IMaterial> LoadMaterial(const std::string& sMaterial) = 0;
    
    //high level 
    virtual SharedPtr<IModel> LoadModel(const std::string& sModel) = 0;
    
    virtual SharedPtr<ICamera> CreateCamera(float aspect, float znear, float zfar, float fovy) = 0;
    
    virtual void BeginScene() = 0;
    virtual void Present() = 0;
  };
}

#endif//_E4Gamma_IRENDERER_H
