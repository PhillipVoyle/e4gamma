//
//  GLFrameBuffer.h
//  E4Gamma
//
//  Created by Phillip Voyle on 15/01/12.
//  Copyright (c) 2012 Phillip Voyle. All rights reserved.
//

#ifndef E4Gamma_GLFrameBuffer_h
#define E4Gamma_GLFrameBuffer_h

#include <Interfaces/Foundation/IUnknown.h>
#include <Interfaces/Foundation/IAssetLoader.h>
#include <string>
#include <GL/GLIncludes.h>

namespace E4Gamma {
  
  class CGLTexture;
  
  class CGLFrameBuffer: public IUnknown
  {
    GLuint m_nFrameBuffer;
    GLuint m_nTexture;
   
  public:
    CGLFrameBuffer(int nWidth, int nHeight, GLuint nTargets, GLuint *pFormats, GLuint *pTargets);
    virtual ~CGLFrameBuffer();
    
    SharedPtr<CGLTexture> GetTexture();
    
    void RenderSet();
  };
}

#endif
