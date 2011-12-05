#ifndef _E4Gamma_GLSHADER_H
#define _E4Gamma_GLSHADER_H

#include <string>
#include <OpenGL/gl.h>
#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma
{
  class CGLRenderer;
  class IDataStore;

  class CGLShader: public IUnknown
  {
    CGLRenderer* m_pRenderer; // intentionally weak
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
