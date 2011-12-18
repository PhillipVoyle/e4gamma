#include <OpenGL/GL.h>

#include <Interfaces/Foundation/ISequenceReader.h>
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

  CGLRenderer::CGLRenderer()
  {
    glClearColor(0,0,0,0);
  }
  
  CGLRenderer::~CGLRenderer()
  {
  }
  
  //low level
  SharedPtr<CGLShader> CGLRenderer::LoadShader(const std::string& sShader, GLuint nShaderStage)
  {
    return new IUnknownImpl<CGLShader>(sShader, nShaderStage);
  }
  
  SharedPtr<CGLTexture> CGLRenderer::LoadTexture(SharedPtr<ISequenceReader> pReader)
  {
    return new IUnknownImpl<CGLTexture>(this, pReader);
  }
  
  //mid level creatures
  SharedPtr<IMesh> CGLRenderer::LoadMesh(const char* szMesh)
  {
    return nullptr;// new IUnknownImpl<CGLMesh>(this, szMesh);
  }
  
  SharedPtr<IMaterial> CGLRenderer::LoadMaterial(const char* szMaterial)
  {
    return nullptr;// new IUnknownImpl<CGLMaterial>(this, szMaterial);
  }
  
  //high level 
  SharedPtr<IModel> CGLRenderer::LoadModel(const char* szModel)
  {
    return nullptr;// new IUnknownImpl<CGLModel>(this, szModel);
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
