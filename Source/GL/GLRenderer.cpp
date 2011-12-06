#include <OpenGL/GL.h>

#include <GL/GLRenderer.h>
#include <GL/GLShader.h>
#include <GL/GLTexture.h>
#include <GL/GLMesh.h>
#include <GL/GLMaterial.h>
#include <GL/GLModel.h>
#include <iostream>

using namespace std;

namespace E4Gamma
{

  CGLRenderer::CGLRenderer(IDataStore* pSettings):m_pDataStore(pSettings)
  {
    glClearColor(0,0,0,0);
  }
  
  CGLRenderer::~CGLRenderer()
  {
  }
  
  //low level
  SharedPtr<CGLShader> CGLRenderer::LoadShader(const std::string& sShader, GLuint nShaderStage)
  {
    return new IUnknownImpl<CGLShader>(this, m_pDataStore, sShader, nShaderStage);
  }
  
  SharedPtr<CGLTexture> CGLRenderer::LoadTexture(const std::string& sTexture)
  {
    return new IUnknownImpl<CGLTexture>(this, m_pDataStore, sTexture);
  }
  
  //mid level creatures
  SharedPtr<IMesh> CGLRenderer::LoadMesh(const char* szMesh)
  {
    return new IUnknownImpl<CGLMesh>(this, m_pDataStore, szMesh);
  }
  
  SharedPtr<IMaterial> CGLRenderer::LoadMaterial(const char* szMaterial)
  {
    return new IUnknownImpl<CGLMaterial>(this, m_pDataStore, szMaterial);
  }
  
  //high level 
  SharedPtr<IModel> CGLRenderer::LoadModel(const char* szModel)
  {
    return new IUnknownImpl<CGLModel>(this, m_pDataStore, szModel);
  }
  
  void CGLRenderer::BeginScene()
  {
    glClear(GL_COLOR_BUFFER_BIT);//Clear the screen   
  }
  
  void CGLRenderer::Present()
  {
    glFlush();//Draw everything to the screen
  }
}
