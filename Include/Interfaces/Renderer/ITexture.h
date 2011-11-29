#ifndef _E4Gamma_ITEXTURE_H
#define _E4Gamma_ITEXTURE_H

namespace E4Gamma
{
  class ITexture
  {
  public:
    virtual ~ITexture() {}
    virtual void RenderSet(int nTextureStage) = 0;
    virtual void RenderReset(int nTextureStage) = 0;
  };
}

#endif//_E4Gamma_ITEXTURE_H
