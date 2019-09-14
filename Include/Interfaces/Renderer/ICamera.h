//
//  ICamera.h
//  E4Gamma
//
//  Created by Phillip Voyle on 23/12/11.
//  Copyright (c) 2011 Phillip Voyle. All rights reserved.
//

#ifndef E4Gamma_ICamera_h
#define E4Gamma_ICamera_h

#include <Interfaces/Foundation/IUnknown.h>
#include <Interfaces/Foundation/IFrame.h>

namespace E4Gamma {
  class ICamera : public IUnknown
  {
  public:
    virtual ~ICamera() {}
    virtual SharedPtr<IFrame> GetFrame() = 0;
    virtual void Select() = 0;
  };
}

#endif
