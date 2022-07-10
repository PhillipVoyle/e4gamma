//
//  GLShaderProgram.h
//  E4Gamma
//
//  Created by Phillip Voyle on 20/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_GLShaderProgram_h
#define E4Gamma_GLShaderProgram_h

#include "GL/GLIncludes.h"

#include <Interfaces/Foundation/IUnknown.h>
#include <list>

#include <GL/GLShader.h>

namespace E4Gamma {
  class CGLRenderContext;
  class CGLShaderProgram: public IUnknown
  {
    SharedPtr<CGLRenderContext> m_renderContext;
    std::list<SharedPtr<CGLShader>> m_shaders;
    GLuint m_nProgram;
    
  public:
    CGLShaderProgram(SharedPtr<CGLRenderContext> renderContext, const std::string& sProgram, SharedPtr<IAssetLoader<CGLShader>> m_vertexShaderFactory, SharedPtr<IAssetLoader<CGLShader>> m_fragmentShaderFactory);
    virtual ~CGLShaderProgram();
    void RenderSet();
    
    static SharedPtr<IAssetLoader<CGLShaderProgram>> createFactory(SharedPtr<CGLRenderContext> renderContext, SharedPtr<IAssetLoader<CGLShader>> m_vertexShaderFactory, SharedPtr<IAssetLoader<CGLShader>> m_fragmentShaderFactory);
  };
  
}

#endif
