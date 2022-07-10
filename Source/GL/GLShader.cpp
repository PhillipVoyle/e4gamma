#include <GL/GLShader.h>
#include <iostream>

#include <stdcpp/FileSystemDataStore.h>

using namespace std;

namespace E4Gamma
{
 
  CGLShader::CGLShader(const std::string sShader, GLuint nShaderStage)
  {
    CFileSystemDataStore ds;
    
    m_nShaderStage = nShaderStage;
    m_nShader = 0;
    if(ds.ReadString(sShader, m_sSource))
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
          cout << sShader << ":" << infolog << endl;
          delete infolog;
        }
        glDeleteShader(m_nShader);
        m_nShader = 0;
      }
      else
      {
        cout << "loaded shader " << sShader << endl;
      }
    }
  }
  
  CGLShader::~CGLShader()
  {
    if(m_nShader != 0)
    {
      glDeleteShader(m_nShader);
    }
  }
  
  class CGLShaderFactory: public IAssetLoader<CGLShader>
  {
    GLuint m_nShaderStage;
  public:
    CGLShaderFactory(GLuint nShaderStage):m_nShaderStage(nShaderStage) { }
    virtual ~CGLShaderFactory() { }
    
    SharedPtr<CGLShader> LoadAsset(const std::string& sAsset)
    {
      return new IUnknownImpl<CGLShader>(sAsset, m_nShaderStage);
    }
  };
  
  SharedPtr<IAssetLoader<CGLShader>> CGLShader::createFactory(GLuint shaderStage)
  {
    return new IUnknownImpl<CGLShaderFactory>(shaderStage);
  }
}