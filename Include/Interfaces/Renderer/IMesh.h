#ifndef _E4Gamma_IMESH_H
#define _E4Gamma_IMESH_H

namespace E4Gamma
{
  class IPose;

  class IMesh
  {
  public:
    virtual ~IMesh() {}
    virtual void RenderPose(IPose* pPose) = 0;
  };
}

#endif//_E4Gamm_IMESH_H
