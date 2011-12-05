#include <GL/GLMaterial.h>
#include <OpenGL/gl.h>

namespace E4Gamma
{
  CGLMaterial::CGLMaterial(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string & sMaterial)
  :m_pRenderer(pRenderer)
  {
  }

  CGLMaterial::~CGLMaterial()
  {
  }


  void CGLMaterial::SetShader(GLuint nShaderID, const std::string& sShaderFilename)
  {
  }

  void CGLMaterial::SetTexture(GLuint nTextureID, const std::string& sTextureName)
  {
    //m_glTextures = m_pRenderer->LoadTexture();
  }

  void CGLMaterial::RenderSet()
  {
  }

  void CGLMaterial::RenderReset()
  {
  }
}
