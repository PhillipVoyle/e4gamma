#ifndef _E4Gamma_GLSHADER_H
#define _E4Gamma_GLSHADER_H

#include <string>

namespace E4Gamma
{
  class CGLRenderer;
  class IDataStore;

  class CGLShader
  {
    CGLRenderer* m_pRenderer;
    std::string m_sSource;
  public:
    
    //probably shouldn't be exposed to IShader, which is a good reason why things should
    //be loaded by material, and that's where the encapsulation boundary should be
    enum ShaderStage
    {
      ssVertexShader,
      ssFragmentShader,
      ssGeometryShader,
      ssTessellator,
      ssTessellationControl
    };
    
    CGLShader(CGLRenderer* pRenderer, IDataStore* pDataStore, const char* szShader);
    virtual ~CGLShader();
    virtual void RenderSet(int nShaderStage);
    virtual void RenderReset(int nShaderStage);
  };
}

#endif//_E4Gamma_GLSHADER_H
