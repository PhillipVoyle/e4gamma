#ifndef _E4Gamma_IRENDERER_H
#define _E4Gamma_IRENDERER_H

#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma
{
  class IDataStore;
  class IMesh;
  class IMaterial;
  class IShader;
  class IModel;
  class ITexture;
  
  class IRenderer: IUnknown
  {
  public:
    virtual ~IRenderer() {}
    
    //mid level creatures
    virtual IMesh* LoadMesh(const char* szMesh) = 0;
    virtual IMaterial* LoadMaterial(const char* szMaterial) = 0;
    
    //high level 
    virtual IModel* LoadModel(const char* szModel) = 0;
    
    virtual void BeginScene() = 0;
    virtual void Present() = 0;
  };
}

#endif//_E4Gamma_IRENDERER_H
