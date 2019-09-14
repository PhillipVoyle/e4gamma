#ifndef _E4Gamma_GLTEXTURE_H
#define _E4Gamma_GLTEXTURE_H

#ifdef _WIN32
#include <Windows.h>
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif
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
