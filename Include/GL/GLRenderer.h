#ifndef _E4Gamma_GLRENDERER_H
#define _E4Gamma_GLRENDERER_H

#include <Interfaces/Renderer/IRenderer.h>
#include "GL/GLIncludes.h"

#include <Interfaces/Foundation/IAssetLoader.h>


namespace E4Gamma
{
  class CGLShader;
  class CGLShaderProgram;
  class CGLTexture;
  class CGLMaterial;
  class CGLMesh;
  class CGLMaterial;
  class CGLModel;
  class CGLRenderContext;
  
  class IMesh;
  class IMaterial;
  class IModel;
  class ICamera;
  class ILight;

  class CGLRenderer: public IRenderer
  {
    SharedPtr<IAssetLoader<CGLShader>>        m_vshCache;
    SharedPtr<IAssetLoader<CGLShader>>        m_fshCache;
    SharedPtr<IAssetLoader<CGLShaderProgram>> m_programCache;
    SharedPtr<IAssetLoader<CGLTexture>>       m_textureCache;
    SharedPtr<IAssetLoader<CGLMaterial>>      m_materialCache;
    SharedPtr<IAssetLoader<CGLMesh>>          m_meshCache;
    SharedPtr<IAssetLoader<CGLModel>>         m_modelCache;
    
    SharedPtr<CGLRenderContext>               m_renderContext;
  public:
 
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
    SharedPtr<ILight>           CreateLight();
    
    SharedPtr<CGLRenderContext> GetRenderContext();
    
    void BeginScene();
    void Present();
  };
}

#endif//_E4Gamam_GLRENDERER_H
