//
//  IAssetLoader.h
//  E4Gamma
//
//  Created by Phillip Voyle on 20/12/11.
//  Copyright (c) 2011 Phillip Voyle. All rights reserved.
//

#ifndef E4Gamma_IAssetLoader_h
#define E4Gamma_IAssetLoader_h

#include <Interfaces/Foundation/IUnknown.h>

#include <string>

namespace E4Gamma
{
  template<typename T>
  class IAssetLoader: public IUnknown
  {
  public:
    virtual ~IAssetLoader() {}
    virtual SharedPtr<T> LoadAsset(const std::string&sAssetName) = 0;
  };
};


#endif
