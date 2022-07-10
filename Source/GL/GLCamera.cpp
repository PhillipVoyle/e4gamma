//
//  GLCamera.cpp
//  E4Gamma
//
//  Created by Phillip Voyle on 23/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <GL/GLCamera.h>
#include <GL/GLRenderContext.h>

#include <math.h>

namespace E4Gamma {

  CGLCamera::CGLCamera(SharedPtr<CGLRenderContext> renderContext, float fAspect, float znear, float zfar, float fovy):
    m_frame(this),
    m_renderContext(renderContext),
    m_projMat(ProjectionMatrix(fAspect, znear, zfar, fovy))
  {
  }
  
  CGLCamera::~CGLCamera()
  {
  }
  
  SharedPtr<IFrame> CGLCamera::GetFrame()
  {
    return SharedPtr<IFrame>(&m_frame);
  }
  
  //this perspective matrix flips the world in the z axis, so that the
  //verts sent to the opengl rasterizer are left handed.
  Matrix4 CGLCamera::ProjectionMatrix(float fAspect, float znear, float zfar, float fov) 
  {
    float cotfov = 1.0f/tanf((fov / 2.0f) * (2.0f * M_PI/360.0f));
    
    float xx = cotfov / fAspect;
    float yy = cotfov;

    float zz = (zfar + znear)/(zfar - znear);
    float tz = -(2.0f * zfar * znear)/(zfar - znear);
    float zw = 1.0f;
  
    return Matrix4(
      xx, 0.0, 0.0, 0.0,
      0.0, yy, 0.0, 0.0,
      0.0, 0.0, zz,  zw,
      0.0, 0.0, tz, 0.0);
  }
  
  void CGLCamera::Select()
  {
    m_renderContext->m_view = m_frame.GetTransform().Inverse();
    m_renderContext->m_projection = m_projMat;
  }
}
