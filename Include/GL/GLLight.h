//
//  GLLight.h
//  E4Gamma
//
//  Created by Phillip Voyle on 5/01/12.
//  Copyright (c) 2012 Phillip Voyle. All rights reserved.
//

#ifndef E4Gamma_GLLight_h
#define E4Gamma_GLLight_h

#include <Interfaces/Renderer/ILight.h>
#include <stdcpp/Frame.h>
#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma
{
  class CGLRenderContext;
  class CGLLight: public ILight
  {
    SharedPtr<CGLRenderContext> m_renderContext;
    AggregateImpl<CPositionFrame> m_frame;
    float m_fRadius;
    
  public:
    CGLLight(SharedPtr<CGLRenderContext> renderContext);
    virtual ~CGLLight();
    
    void SetRadius(float fRadius);
    float GetRadius();
    
    SharedPtr<IFrame> GetFrame();
    void Select();
  };
}

#endif
