#ifndef _E4Gamma_GLSHADER_H
#define _E4Gamma_GLSHADER_H

#include <string>
#include <OpenGL/gl.h>

namespace E4Gamma
{
  class CGLRenderer;
  class IDataStore;

  class CGLShader
  {
    CGLRenderer* m_pRenderer;
    std::string m_sSource;
    GLuint m_nShaderStage;
    GLuint m_nShader;
  public:
    
    CGLShader(CGLRenderer* pRenderer, IDataStore* pDataStore, const char* szShader, GLuint nShaderStage);
    ~CGLShader();
    int GetShader() {return m_nShader;}
  };
}

#endif//_E4Gamma_GLSHADER_H
