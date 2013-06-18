#ifndef _E4Gamma_GLSHADER_H
#define _E4Gamma_GLSHADER_H

#include <string>
#include <OpenGL/gl.h>
#include <Interfaces/Foundation/IUnknown.h>
#include <Interfaces/Foundation/IAssetLoader.h>

namespace E4Gamma
{
  class CGLRenderer;
  class IDataStore;

  class CGLShader: public IUnknown
  {
    std::string m_sSource;
    GLuint m_nShaderStage;
    GLuint m_nShader;
  public:
    
    CGLShader(const std::string sShaderSource, GLuint nShaderStage);
    ~CGLShader();
    
    GLuint GetShader() {return m_nShader;}
    
    static SharedPtr<IAssetLoader<CGLShader>> createFactory(GLuint shaderStage);
  };
}

#endif//_E4Gamma_GLSHADER_H
