#ifndef _E4Gamma_ISHADER_H
#define _E4Gamma_ISHADER_H

namespace E4Gamma
{
  class IShader
  {
  public:
    virtual ~IShader() {}
    virtual void RenderSet(int nShaderStage) = 0;
    virtual void RenderReset(int nShaderStage) = 0;
  };
}

#endif//_E4Gamma_ISHADER_H
