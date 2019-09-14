
#include <GL/GLIncludes.h>

#include <GL/GLRenderer.h>
#include <GL/GLMaterial.h>

#include <Interfaces/Foundation/ISequenceReader.h>
#include <stdcpp/FileSystemDataStore.h>


#include <iostream>

namespace E4Gamma
{
  CGLMaterial::CGLMaterial(const std::string& sMaterial, SharedPtr<IAssetLoader<CGLShaderProgram>> programFactory, SharedPtr<IAssetLoader<CGLTexture>> textureFactory)
  {
    CFileSystemDataStore ds;
    SharedPtr<ISequenceReader> pSeq = ds.OpenTextSequence(sMaterial);
    
    if(pSeq != nullptr)
    {
      std::string sMaterial;
      if((pSeq->ReadString(sMaterial) && sMaterial == "material"))
      {
        std::string sSettings;
        int nSettingCount = 0;
        if((pSeq->ReadString(sSettings) && sSettings == "settings") &&
           pSeq->ReadI32(nSettingCount))
        {
          for(int nSetting = 0; nSetting < nSettingCount; nSetting++)
          {
            std::string sSetting;
            if(pSeq->ReadString(sSetting))
            {
              if(sSetting == "texture")
              {
                GLuint nTexture;
                std::string sTexture;
                if(pSeq->ReadU32(nTexture) && pSeq->ReadString(sTexture))
                {
                  m_glTextures[GL_TEXTURE0 + nTexture] = textureFactory->LoadAsset(sTexture);
                }
              }
              else if(sSetting == "shader_program")
              {
                std::string sShaderProgram;
                if(pSeq->ReadString(sShaderProgram))
                {
                  m_program = programFactory->LoadAsset(sShaderProgram);
                }
              }
            }
          }
        }
      }
    }
  }
  
  CGLMaterial::~CGLMaterial()
  {
  }

  void CGLMaterial::RenderSet()
  {
    if(m_program != nullptr)
    {
      m_program->RenderSet();
    }
    
    for(auto it = m_glTextures.begin(); it != m_glTextures.end(); it++)
    {
      if(it->second != nullptr)
      {
        it->second->RenderSet(it->first);
      }
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }

  void CGLMaterial::RenderReset()
  {
    glUseProgram(0);
    
    for(auto it = m_glTextures.begin(); it != m_glTextures.end(); it++)
    {
      it->second->RenderReset(it->first);
    }
  }
  
  class CGLMaterialFactory: public IAssetLoader<CGLMaterial>
  {
    SharedPtr<IAssetLoader<CGLShaderProgram>> m_programFactory;
    SharedPtr<IAssetLoader<CGLTexture>> m_textureFactory;
    
  public:
    CGLMaterialFactory(SharedPtr<IAssetLoader<CGLShaderProgram>> programFactory, SharedPtr<IAssetLoader<CGLTexture>> textureFactory)
    : m_programFactory(programFactory), m_textureFactory(textureFactory)
    {
    }
    
    virtual ~CGLMaterialFactory() { }
    
    SharedPtr<CGLMaterial> LoadAsset(const std::string& sAsset)
    {
      return new IUnknownImpl<CGLMaterial>(sAsset, m_programFactory, m_textureFactory);
    }
  };
  
  SharedPtr<IAssetLoader<CGLMaterial>> CGLMaterial::createFactory(SharedPtr<IAssetLoader<CGLShaderProgram>> programFactory, SharedPtr<IAssetLoader<CGLTexture>> textureFactory)
  {
    return new IUnknownImpl<CGLMaterialFactory>(programFactory, textureFactory);
  }
}
