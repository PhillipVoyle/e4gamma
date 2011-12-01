#ifndef _E4Gamma_GLRENDERER_H
#define _E4Gamma_GLRENDERER_H

#include <Interfaces/Renderer/IRenderer.h>

namespace E4Gamma
{
  class IDataStore;
  class IMesh;
  class IMaterial;
  class IModel;
  
  class CGLShader;
  class CGLTexture;
  
  class CGLRenderer: public IRenderer
  {
    IDataStore* m_pDataStore;
  public:
    CGLRenderer(IDataStore* pSettings);
    virtual ~CGLRenderer();
    
    //low level
    CGLShader* LoadShader(const char* szShader);
    CGLTexture* LoadTexture(const char* szTexture);
    
    //mid level creatures
    IMesh* LoadMesh(const char* szMesh);
    IMaterial* LoadMaterial(const char* szMaterial);
    
    //high level 
    IModel* LoadModel(const char* szModel);
    
    void BeginScene();
    void Present();
  };
}

#endif//_E4Gamam_GLRENDERER_H
