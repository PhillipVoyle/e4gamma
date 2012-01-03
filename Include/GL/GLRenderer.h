#ifndef _E4Gamma_GLRENDERER_H
#define _E4Gamma_GLRENDERER_H

#include <Interfaces/Renderer/IRenderer.h>
#include <OpenGL/gl.h>

#include <GL/GLShader.h>
#include <GL/GLTexture.h>
#include <GL/GLShaderProgram.h>
#include <GL/GLMesh.h>
#include <GL/GLMaterial.h>
#include <GL/GLModel.h>

#include <Interfaces/Foundation/IAssetLoader.h>

namespace E4Gamma
{
  class IMesh;
  class IMaterial;
  class IModel;
  
  class CGLRenderer: public IRenderer
  {
    SharedPtr<IAssetLoader<CGLShader>>        m_vshCache;
    SharedPtr<IAssetLoader<CGLShader>>        m_fshCache;
    SharedPtr<IAssetLoader<CGLShaderProgram>> m_programCache;
    SharedPtr<IAssetLoader<CGLTexture>>       m_textureCache;
    SharedPtr<IAssetLoader<CGLMaterial>>      m_materialCache;
    SharedPtr<IAssetLoader<CGLMesh>>          m_meshCache;
    SharedPtr<IAssetLoader<CGLModel>>         m_modelCache;
    
    Matrix4 m_model;
    Matrix4 m_view;
    Matrix4 m_projection;
        
  public:
  
    void SetModelMatrix(const Matrix4& model);
    void SetViewMatrix(const Matrix4& view);
    void SetProjectionMatrix(const Matrix4& projection);
  
    CGLRenderer();
    virtual ~CGLRenderer();
    void PostConstruct();
    
    SharedPtr<CGLShader>        LoadShader(const std::string& sShader, GLuint nShaderStage);
    
    SharedPtr<CGLShaderProgram> LoadProgram(const std::string& sProgram);
    SharedPtr<CGLTexture>       LoadTexture(const std::string& sTexture);
    
    //mid level creatures
    SharedPtr<IMesh>            LoadMesh(const std::string& sMesh);
    SharedPtr<IMaterial>        LoadMaterial(const std::string& sMaterial);
    
    //high level 
    SharedPtr<IModel>           LoadModel(const std::string& sModel);
    
    SharedPtr<ICamera>          CreateCamera(float aspect, float znear, float zfar, float fovy);
    
    void BeginScene();
    void Present();
  };
}

#endif//_E4Gamam_GLRENDERER_H
