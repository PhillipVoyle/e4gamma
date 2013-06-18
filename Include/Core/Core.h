//
//  Core.h
//  E4Gamma
//
//  Created by Phillip Voyle on 30/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_Core_h
#define E4Gamma_Core_h

#include <Interfaces/Foundation/IUnknown.h>

#include <string>

class IInput;
class ILoader;

namespace E4Gamma {
  class IE4Gamma
  {
  public:
    virtual void SetInput(const std::string& sName, SharedPtr<IInput> pInput) = 0;
    virtual SharedPtr<IInput> GetInput(const std::string& sName) = 0;
    
    virtual void SetLoader(const std::string& sName, SharedPtr<ILoader> pCodec) = 0;
    virtual SharedPtr<ILoader> GetLoader(const std::string& sName) = 0; 
    
    
  };
}

#endif
