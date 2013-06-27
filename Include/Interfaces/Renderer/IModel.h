#ifndef _E4Gamma_IMODEL_H
#define _E4Gamma_IMODEL_H

#include <Interfaces/Foundation/IUnknown.h>
#include <Interfaces/Foundation/IFrame.h>

namespace E4Gamma{
  
  class IModel:public IUnknown
  {
  public:
    virtual ~IModel(){}
    
    virtual void RenderPose(SharedPtr<IFrame> pPose) = 0;
  };
}

#endif//_E4Gamma_GLMODEL_H
