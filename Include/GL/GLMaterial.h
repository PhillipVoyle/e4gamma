#ifndef _E4Gamma_GLMATERIAL_H
#define _E4Gamma_GLMATERIAL_H

#include <Interfaces/Renderer/IMaterial.h>
#include <OpenGL/gl.h>

#include <map>
#include <string>

#include <GL/GLTexture.h>
#include <GL/GLShader.h>
#include <Interfaces/Foundation/IDataStore.h>

namespace E4Gamma
{
  class CGLRenderer;

  class CGLMaterial: public IMaterial
  {
  private:
    GLuint m_nProgram;
    bool m_bProgramDirty;
    
    CGLRenderer* m_pRenderer; //weak pointer
    std::map<int, SharedPtr<CGLTexture>> m_glTextures;
    std::map<int, SharedPtr<CGLShader>> m_glShaders;
    
  public:
    CGLMaterial(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string& sMaterial);
    CGLMaterial(CGLRenderer* pRenderer);
    
    virtual ~CGLMaterial();
    void SetShader(GLuint nShaderID, const std::string& sShaderSrc);
    void SetTexture(GLuint nTextureID, SharedPtr<ISequenceReader> pSequence);
    
    virtual void RenderSet();
    virtual void RenderReset();
  };
}

#endif//_E4Gamma_GLMATERIAL_H
