//
//  GLLight.cpp
//  E4Gamma
//
//  Created by Stacey Voyle on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <GL/GLLight.h>
#include <GL/GLRenderContext.h>
#include <stdcpp/Frame.h>

namespace E4Gamma {

    CGLLight::CGLLight(SharedPtr<CGLRenderContext> renderContext):m_frame(this), m_renderContext(renderContext)
    {
    }
    
    CGLLight::~CGLLight()
    {
    }
    
    SharedPtr<IFrame> CGLLight::GetFrame()
    {
      return &m_frame;
    }
    
    float CGLLight::GetRadius()
    {
      return m_fRadius;
    }
    
    void CGLLight::SetRadius(float fRadius)
    {
      m_fRadius = fRadius;
    }
    
    void CGLLight::Select()
    {
      m_renderContext->m_vLightPosition = m_frame.GetPosition();
      m_renderContext->m_fLightRadius = m_fRadius;
    }
}
