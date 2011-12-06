#ifndef _E4Gamma_GLTEXTURE_H
#define _E4Gamma_GLTEXTURE_H

#include <OpenGL/gl.h>

#include <Interfaces/Foundation/IDatastore.h>

namespace E4Gamma
{
  class IDataStore;
  class CGLRenderer;
  
  class CGLTexture : public IUnknown
  {
  private:
    CGLRenderer* m_pRenderer; //intentionally weak
    GLuint m_nTextureID;
    
  public:
    CGLTexture(CGLRenderer* pRenderer, SharedPtr<IDataStore>, const std::string& szDataStore);
    virtual ~CGLTexture();
    void RenderSet(int nTextureStage);
    void RenderReset(int nTextureStage);
  };
}

#endif//_E4Gamma_GLTEXTURE_H
