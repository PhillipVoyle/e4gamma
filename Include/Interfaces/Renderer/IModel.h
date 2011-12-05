#ifndef _E4Gamma_IMODEL_H
#define _E4Gamma_IMODEL_H

#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma{
  
  class IPose;
  
  class IModel:IUnknown
  {
  public:
    virtual ~IModel(){}
    
    virtual void RenderPose(IPose* pPose) = 0;    
  };
}

#endif//_E4Gamma_GLMODEL_H
