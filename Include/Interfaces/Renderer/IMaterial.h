#ifndef _E4Gamma_IMATERIAL_H
#define _E4Gamma_IMATERIAL_H

namespace E4Gamma
{
  class IMaterial
  {
  public:
    virtual ~IMaterial() {}
    virtual void RenderSet() = 0;
    virtual void RenderReset() = 0;
  };
}

#endif//_E4Gamma_IMATERIAL_H
