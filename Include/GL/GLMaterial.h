#ifndef _E4Gamma_GLMATERIAL_H
#define _E4Gamma_GLMATERIAL_H

#include <Interfaces/Renderer/IMaterial.h>

namespace E4Gamma
{
  class CGLRenderer;
  class CGLTexture;
  class CGLShader;
  class IDataStore;

  class CGLMaterial: public IMaterial
  {
  private:
    CGLRenderer* m_pRenderer;
    CGLTexture** m_glTextures;
    CGLShader** m_glShaders;
    
  public:
    CGLMaterial(CGLRenderer* pRenderer, IDataStore* pDataStore, const char* szMaterial);
    virtual ~CGLMaterial();
    void SetShader(int nShaderID, const char* szShaderFilename);
    void SetTexture(int nTextureID, const char* szTextureName);
    
    virtual void RenderSet();
    virtual void RenderReset();
  };
}

#endif//_E4Gamma_GLMATERIAL_H
