#include <OpenGL/GL.h>

#include <Interfaces/Foundation/ISequenceReader.h>
#include <Interfaces/Foundation/TAssetCache.h>
#include <GL/GLRenderer.h>
#include <GL/GLShader.h>
#include <GL/GLTexture.h>
#include <GL/GLMesh.h>
#include <GL/GLMaterial.h>
#include <GL/GLModel.h>
#include <GL/GLShaderProgram.h>
#include <GL/GLCamera.h>
#include <Interfaces/Foundation/IUnknown.h>
#include <GL/GLRenderContext.h>

#include <GL/GLShader.h>
#include <GL/GLTexture.h>
#include <GL/GLShaderProgram.h>
#include <GL/GLMesh.h>
#include <GL/GLMaterial.h>
#include <GL/GLModel.h>
#include <GL/GLLight.h>

#include <iostream>

using namespace std;

namespace E4Gamma
{

  CGLRenderer::CGLRenderer() : m_renderContext(new IUnknownImpl<CGLRenderContext>())
  {
  }
  
  void CGLRenderer::PostConstruct()
  {
    m_vshCache = new IUnknownImpl<TAssetCache<CGLShader>>(CGLShader::createFactory(GL_VERTEX_SHADER));
    m_fshCache = new IUnknownImpl<TAssetCache<CGLShader>>(CGLShader::createFactory(GL_FRAGMENT_SHADER));
    m_programCache = new IUnknownImpl<TAssetCache<CGLShaderProgram>>(CGLShaderProgram::createFactory(m_renderContext, m_vshCache, m_fshCache));
    m_textureCache = new IUnknownImpl<TAssetCache<CGLTexture>>(CGLTexture::createFactory());
    m_materialCache = new IUnknownImpl<TAssetCache<CGLMaterial>>(CGLMaterial::createFactory(m_programCache, m_textureCache));
    m_meshCache = new IUnknownImpl<TAssetCache<CGLMesh>>(CGLMesh::createFactory(m_renderContext));
    m_modelCache = new IUnknownImpl<TAssetCache<CGLModel>>(CGLModel::createFactory(m_meshCache, m_materialCache));
  }
  
  CGLRenderer::~CGLRenderer()
  {
  }
  
  //low level
  SharedPtr<CGLShader> CGLRenderer::LoadShader(const std::string& sShader, GLuint nShaderStage)
  {
    if(nShaderStage == GL_VERTEX_SHADER)
    {
      return m_vshCache->LoadAsset(sShader);
    }
    else if(nShaderStage == GL_FRAGMENT_SHADER)
    {
      return m_fshCache->LoadAsset(sShader);
    }
    else
    {
      return nullptr;
    }
  }
  
  SharedPtr<CGLShaderProgram> CGLRenderer::LoadProgram(const std::string &sProgram)
  {
    return m_programCache->LoadAsset(sProgram);
  }
  
  SharedPtr<CGLTexture> CGLRenderer::LoadTexture(const std::string& sTexture)
  {
    return m_textureCache->LoadAsset(sTexture);
  }
  
  //mid level creatures
  SharedPtr<IMesh> CGLRenderer::LoadMesh(const std::string& sMesh)
  {
    return m_meshCache->LoadAsset(sMesh);
  }
  
  SharedPtr<IMaterial> CGLRenderer::LoadMaterial(const std::string& sMaterial)
  {
    return m_materialCache->LoadAsset(sMaterial);
  }
  
  //high level 
  SharedPtr<IModel> CGLRenderer::LoadModel(const std::string& sModel)
  {
    return m_modelCache->LoadAsset(sModel);
  }
  
  void CGLRenderer::BeginScene()
  {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//Clear the screen   
  }
  
  void CGLRenderer::Present()
  {
    glFlush();//Draw everything to the screen
  }
  
  SharedPtr<ICamera> CGLRenderer::CreateCamera(float aspect, float znear, float zfar, float fovy)
  {
    return new IUnknownImpl<CGLCamera>(m_renderContext, aspect, znear, zfar, fovy);
  }
  
  SharedPtr<ILight> CGLRenderer::CreateLight()
  {
    return new IUnknownImpl<CGLLight>(m_renderContext);
  }
}
