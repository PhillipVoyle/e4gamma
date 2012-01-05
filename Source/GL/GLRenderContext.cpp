//
//  GLRenderContext.cpp
//  E4Gamma
//
//  Created by Stacey Voyle on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <OpenGL/GL.h>
#include <GL/GLRenderContext.h>

#include <iostream>

using namespace std;

namespace E4Gamma
{
  CGLRenderContext::CGLRenderContext()
  {
  }
  
  CGLRenderContext::~CGLRenderContext()
  {
  }
  
  void CGLRenderContext::FlushContext()
  {
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_AMBIENT, (float[]){0.2, 0.2, 0.2, 1.0});
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (float[]){1.0, 1.0, 1.0, 1.0});
    glLightfv(GL_LIGHT0, GL_SPECULAR, (float[]){1.0, 1.0, 1.0, 1.0});
    glLightfv(GL_LIGHT0, GL_POSITION, (float[]){m_vLightPosition.x, m_vLightPosition.y, -m_vLightPosition.z, 1.0f});
 
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((float*) &m_projection);
    
    glMatrixMode(GL_MODELVIEW);
    Matrix4 m = Matrix4::Transform(m_view, m_model); 
    glLoadMatrixf((float*)&m);
    
    glUseProgram(m_nProgram);
    
  }
}