#ifndef _E4Gamma_GLMATERIAL_H
#define _E4Gamma_GLMATERIAL_H

#include <Interfaces/Renderer/IMaterial.h>
#include <OpenGL/gl.h>

#include <map>
#include <string>

#include <GL/GLTexture.h>
#include <GL/GLShaderProgram.h>
#include <Interfaces/Foundation/IAssetLoader.h>

namespace E4Gamma
{
  class CGLRenderer;

  class CGLMaterial: public IMaterial
  {
  private:
    std::map<int, SharedPtr<CGLTexture>> m_glTextures;
    SharedPtr<CGLShaderProgram> m_program;
    
  public:
    CGLMaterial(const std::string& sMaterial, SharedPtr<IAssetLoader<CGLShaderProgram>> programFactory, SharedPtr<IAssetLoader<CGLTexture>> textureFactory);
    virtual ~CGLMaterial();
    
    virtual void RenderSet();
    virtual void RenderReset();
    
    static SharedPtr<IAssetLoader<CGLMaterial>> createFactory(SharedPtr<IAssetLoader<CGLShaderProgram>> programFactory, SharedPtr<IAssetLoader<CGLTexture>> textureFactory);
  };
}

#endif//_E4Gamma_GLMATERIAL_H
