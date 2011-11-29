#ifndef _E4Gamma_GLSHADER_H
#define _E4Gamma_GLSHADER_H

#include <Interfaces/Renderer/IShader.h>

namespace E4Gamma
{
  class CGLRenderer;
  class IDataStore;

  class CGLShader: public IShader
  {
  public:
    CGLShader(CGLRenderer* pRenderer, IDataStore* pDataStore, const char* szShader);
    virtual ~CGLShader();
    virtual void RenderSet(int nShaderStage);
    virtual void RenderReset(int nShaderStage);
  };
}

#endif//_E4Gamma_GLSHADER_H
