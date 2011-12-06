#include <GL/GLShader.h>
#include <iostream>
#include <Interfaces/Foundation/IDataStore.h>

#include <OpenGL/gl.h>

using namespace std;

namespace E4Gamma
{
 
  CGLShader::CGLShader(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string sShader, GLuint nShaderStage)
  {
    m_pRenderer = pRenderer;
    m_nShaderStage = nShaderStage;
    m_nShader = 0;
    m_sSource = "";
    if(pDataStore->ReadString(sShader, m_sSource))
    {
      m_nShader = glCreateShader(nShaderStage);
      
      //hand waving to get around type system.
      const char* pSource = m_sSource.c_str();
      glShaderSource(m_nShader, 1, &pSource, 0);
      
      glCompileShader(m_nShader);
      GLint nStatus = 0;
      glGetShaderiv(m_nShader, GL_COMPILE_STATUS, &nStatus);
      if(!nStatus) {	
        int loglen;
        glGetShaderiv(m_nShader, GL_INFO_LOG_LENGTH, &loglen);
        if(loglen > 1) {
          char *infolog = new char[loglen];
          int written;
          glGetShaderInfoLog(m_nShader, loglen, &written, infolog);
          cout << "engine: error compiling shader: " << infolog << endl;
          delete infolog;
        }
        glDeleteShader(m_nShader);
        m_nShader = 0;
      }
    }
  }

  CGLShader::~CGLShader()
  {
    glDeleteShader(m_nShader);
  }
}