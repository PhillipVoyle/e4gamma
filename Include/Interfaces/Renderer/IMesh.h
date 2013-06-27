#ifndef _E4Gamma_IMESH_H
#define _E4Gamma_IMESH_H

#include <Interfaces/Foundation/IUnknown.h>
#include <Interfaces/Foundation/IFrame.h>

namespace E4Gamma
{

  class IMesh: public IUnknown
  {
  public:
    virtual ~IMesh() {}
    virtual void RenderPose(SharedPtr<IFrame> pPose) = 0;
    virtual SharedPtr<IMesh> CreateShadowVolume() = 0;
  };
}

#endif//_E4Gamm_IMESH_H
