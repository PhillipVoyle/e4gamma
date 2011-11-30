#include <Interfaces/Renderer/ITexture.h>
#include <OpenGL/gl.h>

namespace E4Gamma
{
  class IDataStore;
  class CGLRenderer;
  
  class CGLTexture: public ITexture
  {
  private:
    CGLRenderer* m_pRenderer;
    GLuint m_nTextureID;
    
  public:
    CGLTexture(CGLRenderer* pRenderer, IDataStore*, const char* szDataStore);
    virtual ~CGLTexture();
    void RenderSet(int nTextureStage);
    void RenderReset(int nTextureStage);
  };
}