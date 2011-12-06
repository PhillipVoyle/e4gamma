#include <GL/GLTexture.h>
#include <stdcpp/Iris.h>
#include <Interfaces/Foundation/IDataStore.h>

namespace E4Gamma {
    
  CGLTexture::CGLTexture(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string& sTexture)
  {
    CIrisFile irisFile(sTexture, pDataStore);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &m_nTextureID);
    glBindTexture(GL_TEXTURE_2D, m_nTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, irisFile.GetWidth(), irisFile.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, irisFile.GetPixels());
    //glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  CGLTexture::~CGLTexture()
  {
    glDeleteTextures(1, &m_nTextureID);
  }

  void CGLTexture::RenderSet(int nTextureStage)
  {
    if(glIsTexture(m_nTextureID))
    {
      glActiveTexture(GL_TEXTURE0 + nTextureStage);
      glBindTexture(GL_TEXTURE_2D, m_nTextureID);
    }
  }

  void CGLTexture::RenderReset(int nTextureStage)
  {
    if(glIsTexture(m_nTextureID))
    {
      glActiveTexture(GL_TEXTURE0 + nTextureStage);
      glBindTexture(GL_TEXTURE_2D, 0);
    }    
  }
}
