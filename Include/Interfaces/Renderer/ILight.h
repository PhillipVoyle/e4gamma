//
//  ILight.h
//  E4Gamma
//
//  Created by Phillip Voyle on 5/01/12.
//  Copyright (c) 2012 Phillip Voyle. All rights reserved.
//

#ifndef E4Gamma_ILight_h
#define E4Gamma_ILight_h

#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma {

  class IFrame;

  class ILight: public IUnknown
  {
  public:
    virtual ~ILight() {}

    virtual SharedPtr<IFrame> GetFrame() = 0;
    
    virtual float GetRadius() = 0;
    virtual void SetRadius(float fIntensity) = 0;
    
    virtual void Select() = 0;
  };
}

#endif
