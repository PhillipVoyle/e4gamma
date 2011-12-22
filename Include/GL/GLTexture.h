#ifndef _E4Gamma_GLTEXTURE_H
#define _E4Gamma_GLTEXTURE_H

#include <OpenGL/gl.h>
#include <Interfaces/Foundation/IAssetLoader.h>

namespace E4Gamma
{
  class CGLTexture : public IUnknown
  {
  private:
    GLuint m_nTextureID;
    
  public:
    CGLTexture(const std::string& sTexture);
    virtual ~CGLTexture();
    void RenderSet(GLuint nTextureStage);
    void RenderReset(GLuint nTextureStage);
    
    static SharedPtr<IAssetLoader<CGLTexture>> createFactory();
  };
}

#endif//_E4Gamma_GLTEXTURE_H
