
#include <OpenGL/gl.h>
#include <GL/GLRenderer.h>
#include <GL/GLMaterial.h>

#include <Interfaces/Foundation/ISequenceReader.h>


#include <iostream>

namespace E4Gamma
{
  CGLMaterial::CGLMaterial(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string & sMaterial)
  :CGLMaterial(pRenderer)
  {
  }
  
  CGLMaterial::CGLMaterial(CGLRenderer* pRenderer)
  :m_pRenderer(pRenderer)
  {
    m_bProgramDirty = false;
    m_nProgram = 0;
  }
  
  CGLMaterial::~CGLMaterial()
  {
  }


  void CGLMaterial::SetShader(GLuint nShaderID, const std::string& sShaderSource)
  {
    m_glShaders[nShaderID] = m_pRenderer->LoadShader(sShaderSource, nShaderID);
    if(!m_bProgramDirty)
    {
      m_bProgramDirty = true;
      glDeleteProgram(m_nProgram);
      m_nProgram = 0;
    }
  }

  void CGLMaterial::SetTexture(GLuint nTextureID, SharedPtr<ISequenceReader> pSeq)
  {
    m_glTextures[nTextureID] = m_pRenderer->LoadTexture(pSeq);
  }

  void CGLMaterial::RenderSet()
  {
    if(m_bProgramDirty)
    {
      m_nProgram = glCreateProgram();
      for(auto it = m_glShaders.begin(); it != m_glShaders.end(); it++)
      {
        glAttachShader(m_nProgram, it->second->GetShader());
      }
      
      int nStatus = 0;
      glLinkProgram(m_nProgram);
      glGetProgramiv(m_nProgram, GL_LINK_STATUS, &nStatus);
      if(!nStatus) {
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
      m_bProgramDirty = false;
    }
    
    glUseProgram(m_nProgram);
    
    for(auto it = m_glTextures.begin(); it != m_glTextures.end(); it++)
    {
      it->second->RenderSet(it->first);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }

  void CGLMaterial::RenderReset()
  {
    glUseProgram(0);
    
    for(auto it = m_glTextures.begin(); it != m_glTextures.end(); it++)
    {
      it->second->RenderReset(it->first);
    }
  }
}
