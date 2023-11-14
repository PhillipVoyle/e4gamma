//
//  GLFrameBuffer.cpp
//  E4Gamma
//
//  Created by Phillip Voyle on 15/01/12.
//  Copyright (c) 2012 Phillip Voyle. All rights reserved.
//

#include <GL/GLIncludes.h>

#include <GL/GLTexture.h>
#include <GL/GLFrameBuffer.h>

namespace E4Gamma {
  
  CGLFrameBuffer::CGLFrameBuffer(int nWidth, int nHeight, GLuint nTargets, GLuint *pFormats, GLuint *pTargets)
  {
    glGenFramebuffers(1, &m_nFrameBuffer);
  }
  
  CGLFrameBuffer::~CGLFrameBuffer()
  {
    glDeleteFramebuffers(1, &m_nFrameBuffer);
  }
  
  SharedPtr<CGLTexture> CGLFrameBuffer::GetTexture()
  {
    return nullptr;
  }
  
  void CGLFrameBuffer::RenderSet()
  {
    glBindFramebuffer(GL_RENDERBUFFER, m_nFrameBuffer);
  }
};