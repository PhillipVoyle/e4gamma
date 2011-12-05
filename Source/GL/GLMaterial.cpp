#include <GL/GLMaterial.h>
#include <OpenGL/gl.h>

namespace E4Gamma
{
  CGLMaterial::CGLMaterial(CGLRenderer* pRenderer, IDataStore* pDataStore, const char* szMaterial)
  :m_pRenderer(pRenderer)
  {
  }

  CGLMaterial::~CGLMaterial()
  {
  }

/*
  void CGLMaterial::SetShader(int nShaderID, const char* szShaderFilename)
  {
  }

  void CGLMaterial::SetTexture(int nTextureID, const char* szTextureName)
  {
    //m_glTextures = m_pRenderer->LoadTexture();
  }
  */
  void CGLMaterial::RenderSet()
  {
  }

  void CGLMaterial::RenderReset()
  {
  }
}
