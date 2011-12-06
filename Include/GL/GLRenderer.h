#ifndef _E4Gamma_GLRENDERER_H
#define _E4Gamma_GLRENDERER_H

#include <Interfaces/Renderer/IRenderer.h>
#include <OpenGL/gl.h>

#include <GL/GLShader.h>
#include <GL/GLTexture.h>

namespace E4Gamma
{
  class IDataStore;
  class IMesh;
  class IMaterial;
  class IModel;
  
  class CGLRenderer: public IRenderer
  {
    IDataStore* m_pDataStore;
  public:
    CGLRenderer(IDataStore* pSettings);
    virtual ~CGLRenderer();
    
    //low level
    SharedPtr<CGLShader> LoadShader(const std::string& sShader, GLuint nShaderStage);
    SharedPtr<CGLTexture> LoadTexture(const std::string& sTexture);
    
    //mid level creatures
    SharedPtr<IMesh> LoadMesh(const char* szMesh);
    SharedPtr<IMaterial> LoadMaterial(const char* szMaterial);
    
    //high level 
    SharedPtr<IModel> LoadModel(const char* szModel);
    
    void BeginScene();
    void Present();
  };
}

#endif//_E4Gamam_GLRENDERER_H
