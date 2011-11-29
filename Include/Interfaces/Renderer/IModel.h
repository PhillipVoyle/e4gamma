#ifndef _E4Gamma_IMODEL_H
#define _E4Gamma_IMODEL_H

namespace E4Gamma{
  
  class IPose;
  
  class IModel
  {
  public:
    virtual ~IModel(){}
    
    virtual void RenderPose(IPose* pPose) = 0;    
  };
}

#endif//_E4Gamma_GLMODEL_H
