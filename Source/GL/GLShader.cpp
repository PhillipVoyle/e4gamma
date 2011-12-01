#include <GL/GLShader.h>
#include <iostream>
#include <Interfaces/Foundation/IDataStore.h>

using namespace std;

namespace E4Gamma
{
  CGLShader::CGLShader(CGLRenderer* pRenderer, IDataStore* pDataStore, const char* szShader)
  {
    m_pRenderer = pRenderer;
    m_sSource = "";
    pDataStore->ReadString(szShader, m_sSource);
    cout << m_sSource << endl; 
  }
  CGLShader::~CGLShader()
  {
  }
  void CGLShader::RenderSet(int nShaderStage)
  {
    
  }
  void CGLShader::RenderReset(int nShaderStage)
  {
  }
}