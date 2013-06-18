//
//  TAssetCache.h
//  E4Gamma
//
//  Created by Phillip Voyle on 20/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_TAssetCache_h
#define E4Gamma_TAssetCache_h

#include <Interfaces/Foundation/IAssetLoader.h>
#include <string>
#include <map>
namespace E4Gamma
{
  template<typename T>
  class TAssetCache:public IAssetLoader<T>{
  private:
    SharedPtr<IAssetLoader<T>> m_pLoader;
    std::map<std::string, SharedPtr<T>> m_assets;
  public:
    
    void Dispose()
    {
      m_pLoader = nullptr;
      m_assets.clear();
    }
    
    TAssetCache(SharedPtr<IAssetLoader<T>> pLoader):m_pLoader(pLoader)
    {
    }
    
    virtual ~TAssetCache() {
      Dispose();
    }
    
    virtual SharedPtr<T> LoadAsset(const std::string&sAssetName)
    {
      auto it = m_assets.find(sAssetName);
      if(it != m_assets.end())
      {
        return it->second;
      }
      else
      {
        SharedPtr<T> pAsset = m_pLoader->LoadAsset(sAssetName);
        m_assets[sAssetName] = pAsset;
        return pAsset;
      }
    }
  };
}

#endif
