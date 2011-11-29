#ifndef _E4Gamma_IRENDERER_H
#define _E4Gamma_IRENDERER_H

namespace E4Gamma
{
  class IDataStore;
  class IMesh;
  class IMaterial;
  class IShader;
  class IModel;
  class ITexture;
  
  class IRenderer
  {
  public:
    virtual ~IRenderer() {}
    //low level
    virtual IShader* LoadShader(const char* szShader) = 0;
    virtual ITexture* LoadTexture(const char* szTexture) = 0;
    
    //mid level creatures
    virtual IMesh* LoadMesh(const char* sz) = 0;
    virtual IMaterial* LoadMaterial(IDataStore* pDataStore) = 0;
    
    //high level 
    virtual IModel* LoadModel(const char* szModel) = 0;
    
    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;
    virtual void Present() = 0;
  };
}

#endif//_E4Gamma_IRENDERER_H
