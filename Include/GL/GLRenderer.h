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
  public:
    CGLRenderer();
    virtual ~CGLRenderer();
    
    SharedPtr<CGLShader>        LoadShader(const std::string& sShader, GLuint nShaderStage);
    
    SharedPtr<CGLShaderProgram> LoadProgram(const std::string& sProgram);
    SharedPtr<CGLTexture>       LoadTexture(const std::string& sTexture);
    
    //mid level creatures
    SharedPtr<IMesh>            LoadMesh(const std::string& sMesh);
    SharedPtr<IMaterial>        LoadMaterial(const std::string& sMaterial);
    
    //high level 
    SharedPtr<IModel>           LoadModel(const std::string& sModel);
    
    void BeginScene();
    void Present();
  };
}

#endif//_E4Gamam_GLRENDERER_H
