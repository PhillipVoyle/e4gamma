//
//  GLCamera.h
//  E4Gamma
//
//  Created by Phillip Voyle on 23/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_GLCamera_h
#define E4Gamma_GLCamera_h

#include <Interfaces/Renderer/ICamera.h>
#include <stdcpp/Frame.h>
#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma
{
  class CGLRenderer;
  class CGLCamera: public ICamera
  {
    SharedPtr<CGLRenderer> m_renderer;
    AggregateImpl<CMatrix4Frame> m_frame;
    
    
    Matrix4 m_projMat;
    
  public:
    static Matrix4 ProjectionMatrix(float fAspect, float znear, float zfar, float fov);
  
    //perspective
    CGLCamera(SharedPtr<CGLRenderer> renderer, float fAspect, float znear, float zfar, float fovy);
    virtual ~CGLCamera();
        
    SharedPtr<IFrame> GetFrame();
    
    void Select();
  };
}

#endif
