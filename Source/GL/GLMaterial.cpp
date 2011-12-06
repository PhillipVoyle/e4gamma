
#include <OpenGL/gl.h>
#include <GL/GLRenderer.h>
#include <GL/GLMaterial.h>

namespace E4Gamma
{
  CGLMaterial::CGLMaterial(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string & sMaterial)
  :m_pRenderer(pRenderer)
  {
    m_bProgramDirty = false;
    m_nProgram = 0;
  }

  CGLMaterial::~CGLMaterial()
  {
  }


  void CGLMaterial::SetShader(GLuint nShaderID, const std::string& sShaderFilename)
  {
    m_glShaders[nShaderID] = m_pRenderer->LoadShader(sShaderFilename, nShaderID);
    m_bProgramDirty = true;
  }

  void CGLMaterial::SetTexture(GLuint nTextureID, const std::string& sTextureName)
  {
    m_glTextures[nTextureID] = m_pRenderer->LoadTexture(sTextureName);
  }

  void CGLMaterial::RenderSet()
  {
  }

  void CGLMaterial::RenderReset()
  {
  }
}
