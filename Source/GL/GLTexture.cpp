#include <GL/GLTexture.h>
#include <stdcpp/Iris.h>
#include <Interfaces/Foundation/IDataStore.h>
#include <Interfaces/Foundation/ISequenceReader.h>


namespace E4Gamma {
    
  CGLTexture::CGLTexture(const std::string& sTexture)
  {
    CIrisFile irisFile(sTexture);
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

  void CGLTexture::RenderSet(GLuint nTextureStage)
  {
    if(glIsTexture(m_nTextureID))
    {
      glActiveTexture(nTextureStage);
      glBindTexture(GL_TEXTURE_2D, m_nTextureID);
    }
  }

  void CGLTexture::RenderReset(GLuint nTextureStage)
  {
    if(glIsTexture(m_nTextureID))
    {
      glActiveTexture(nTextureStage);
      glBindTexture(GL_TEXTURE_2D, 0);
    }    
  }

  class CGLTextureFactory: public IAssetLoader<CGLTexture>
  {
  public:
    CGLTextureFactory() { }
    virtual ~CGLTextureFactory() { }
    
    SharedPtr<CGLTexture> LoadAsset(const std::string& sAsset)
    {
      return new IUnknownImpl<CGLTexture>(sAsset);
    }
  };
  
  SharedPtr<IAssetLoader<CGLTexture>> CGLTexture::createFactory()
  {
    return new IUnknownImpl<CGLTextureFactory>();
  }
}
