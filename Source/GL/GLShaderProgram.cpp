//
//  GLShaderProgram.cpp
//  E4Gamma
//
//  Created by Phillip Voyle on 20/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#define GL_GLEXT_PROTOTYPES

#include <Interfaces/Foundation/IUnknown.h>
#include <GL/GLShader.h>
#include <GL/GLShaderProgram.h>
#include <stdcpp/FileSystemDataStore.h>
#include <Interfaces/Foundation/ISequenceReader.h>
#include <GL/GLRenderContext.h>

#include <iostream>
using namespace std;

namespace E4Gamma
{
  CGLShaderProgram::CGLShaderProgram(
    SharedPtr<CGLRenderContext> renderContext, 
    const std::string &sProgram,
    SharedPtr<IAssetLoader<CGLShader>> vertexShaderFactory,
    SharedPtr<IAssetLoader<CGLShader>> fragmentShaderFactory):
      m_renderContext(renderContext)
  {
    m_nProgram = 0;
    
    CFileSystemDataStore ds;
    SharedPtr<ISequenceReader> pSeq = ds.OpenTextSequence(sProgram);
    
    if(pSeq != nullptr)
    {
      string sShaderProgram;
      int nShaders = 0;
      if(pSeq->ReadString(sShaderProgram) && (sShaderProgram == "shader_program") && pSeq->ReadI32(nShaders))
      {
        for(int nShader = 0; nShader < nShaders; nShader++)
        {
          string sShaderType;
          string sShaderLocation;
          if(pSeq->ReadString(sShaderType) && pSeq->ReadString(sShaderLocation))
          {
            if(sShaderType == "vertex_shader")
            {
              m_shaders.push_back(vertexShaderFactory->LoadAsset(sShaderLocation));
            }
            else if (sShaderType == "fragment_shader")
            {
              m_shaders.push_back(fragmentShaderFactory->LoadAsset(sShaderLocation));
            }
          }
        }
      }
    }
    
    m_nProgram = glCreateProgram();
    for(auto it = m_shaders.begin(); it != m_shaders.end(); it++)
    {
      glAttachShader(m_nProgram, (*it)->GetShader());
    }
    
    int nStatus = 0;
    glLinkProgram(m_nProgram);
    glGetProgramiv(m_nProgram, GL_LINK_STATUS, &nStatus);
    if(!nStatus)
    {
      int loglen;
      glGetProgramiv(m_nProgram, GL_INFO_LOG_LENGTH, &loglen);
      if(loglen > 1) {
        char *infolog = new char[loglen];
        int written;
        glGetProgramInfoLog(m_nProgram, loglen, &written, infolog);
        cout << "engine: error linking shader program: " << infolog << endl;
        delete infolog;
      }
      glDeleteProgram(m_nProgram);
      m_nProgram = 0;
    }
    else
    {
      cout << "loaded shader program " << sProgram << endl;
    }
  }
  
  CGLShaderProgram::~CGLShaderProgram()
  {
  }
  
  void CGLShaderProgram::RenderSet()
  {
    m_renderContext->m_nProgram = m_nProgram;
  }
  
  class CGLShaderProgramFactory: public IAssetLoader<CGLShaderProgram>
  {
    SharedPtr<CGLRenderContext> m_renderContext;
    SharedPtr<IAssetLoader<CGLShader>> m_vertexShaderFactory;
    SharedPtr<IAssetLoader<CGLShader>> m_fragmentShaderFactory;
  public:
  CGLShaderProgramFactory(SharedPtr<CGLRenderContext> renderContext, SharedPtr<IAssetLoader<CGLShader>> vertexShaderFactory, SharedPtr<IAssetLoader<CGLShader>> fragmentShaderFactory)
    :m_renderContext(renderContext), m_vertexShaderFactory(vertexShaderFactory), m_fragmentShaderFactory(fragmentShaderFactory)
    {
    }
    
    SharedPtr<CGLShaderProgram> LoadAsset(const std::string& sAsset)
    {
      return new IUnknownImpl<CGLShaderProgram>(m_renderContext, sAsset, m_vertexShaderFactory, m_fragmentShaderFactory);
    }
  };
  
  SharedPtr<IAssetLoader<CGLShaderProgram>> CGLShaderProgram::createFactory(SharedPtr<CGLRenderContext> renderContext, SharedPtr<IAssetLoader<CGLShader>> vertexShaderFactory, SharedPtr<IAssetLoader<CGLShader>> fragmentShaderFactory)
  {
    return new IUnknownImpl<CGLShaderProgramFactory>(renderContext, vertexShaderFactory, fragmentShaderFactory);
  }
}