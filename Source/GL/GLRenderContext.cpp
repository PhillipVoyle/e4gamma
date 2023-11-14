//
//  GLRenderContext.cpp
//  E4Gamma
//
//  Created by Phillip Voyle on 5/01/12.
//  Copyright (c) 2012 Phillip Voyle. All rights reserved.
//

#include <GL/GLIncludes.h>

#include <GL/GLRenderContext.h>

#include <map>
#include <list>

using namespace std;

namespace E4Gamma
{
/*

  void glSetEnabled(GLuint setting, GLboolean isEnabled);

  class IRenderable: virtual public IUnknown
  {
  public:
    virtual void Render() = 0;
  };

  class CRenderBatch: public IRenderable
  {
    SharedPtr<IRenderable> m_context;
    SharedPtr<IRenderable> m_mesh;
  public:
    CRenderBatch(SharedPtr<IRenderable> context, SharedPtr<IRenderable> mesh):
      m_context(context),
      m_mesh(mesh)
    {
    }
    
    void Render()
    {
      m_context->Render();
      m_mesh->Render();
    }
  };
  
  class CRenderContextList: public IRenderable
  {
    list<SharedPtr<IRenderable>> m_contextList;
  public:
    void AddContext(SharedPtr<IRenderable> context)
    {
      m_contextList.push_back(context);
    }
    void Render()
    {
      for(auto it = m_contextList.begin(); it != m_contextList.end(); it++)
      {
        (*it)->Render();
      }
    }
  };
  
  class CModelViewContext
  {
    Matrix4 m_model;
    Matrix4 m_view;
    bool m_bDirty;
    
    Matrix4 m_modelView;
    
  public:
    void Apply()
    {
      if(m_bDirty)
      {
        glMatrixMode(GL_MODELVIEW);
        Matrix4 m = Matrix4::Transform(m_view, m_model); 
        glLoadMatrixf((float*)&m);
        m_bDirty = false;
      }
    }
    
    void SetModel(const Matrix4 model)
    {
      m_model = model;
      m_bDirty = true;
    }
    
    void SetView(const Matrix4 view)
    {
      m_view = view;
      m_bDirty = true;
    }
  };
  
  class CProjectionContext
  {
    Matrix4 m_projection;
  public:
    void Apply()
    {
      glMatrixMode(GL_PROJECTION);
      glLoadMatrixf((float*) &m_projection);
    }
    
    void SetProjecton(const Matrix4& projection)
    {
      m_projection = projection;
    }
  };
  
  template<typename TTrans, typename TValue, typename TFunction, TFunction function, GLuint...settings>
  class TDirtyContext
  {
    bool m_bDirty;
    TValue m_value;
  public:
    TDirtyContext()
    {
      m_bDirty = false;
    }
    
    TDirtyContext(TTrans trans):m_value(trans)
    {
      m_bDirty = true;
    }
    
    void SetValue(TTrans trans)
    {
      m_value = trans;
    }
    void Apply()
    {
      if(m_bDirty)
      {
        function(settings..., m_value);
        m_bDirty = false;
      }  
    }
  };
  
  void glSetEnabled(GLuint setting, GLboolean isEnabled)
  {
    if(isEnabled == GL_TRUE)
    {
      glEnable(setting);
    }
    else
    {
      glDisable(setting);
    }
  }
  
  template<GLuint lightID>
  class CLightContext
  {
    TDirtyContext<GLboolean, GLboolean, decltype(glSetEnabled), glSetEnabled, lightID> m_enabled;
    TDirtyContext<float(&)[4],float[4], decltype(glLightfv), glLightfv, lightID, GL_AMBIENT> m_ambient;
    TDirtyContext<float(&)[4],float[4], decltype(glLightfv), glLightfv, lightID, GL_DIFFUSE> m_diffuse;
    TDirtyContext<float(&)[4],float[4], decltype(glLightfv), glLightfv, lightID, GL_SPECULAR> m_specular;
    TDirtyContext<float(&)[4],float[4], decltype(glLightfv), glLightfv, lightID, GL_POSITION> m_position;

  public:
    void Apply()
    {
      m_ambient.Apply();
      m_diffuse.Apply();
      m_specular.Apply();
      m_position.Apply();
    }
  };
  
  class CLightingContext
  {
    CLightContext<GL_LIGHT0> m_lightContext0;
    CLightContext<GL_LIGHT1> m_lightContext1;
    CLightContext<GL_LIGHT2> m_lightContext2;
    CLightContext<GL_LIGHT3> m_lightContext3;
  
  public:
    void Apply()
    {
      m_lightContext0.Apply();
      m_lightContext1.Apply();
      m_lightContext2.Apply();
      m_lightContext3.Apply();
    }
  };
  
  class RenderContext
  {
    CModelViewContext m_modelView;
    CProjectionContext m_projection;
    CLightingContext m_lighting;
    
    TDirtyContext<GLuint, GLuint, decltype(glUseProgram), glUseProgram> m_program;
    
    void Apply()
    {
      m_modelView.Apply();
      m_projection.Apply();
      m_lighting.Apply();
      m_program.Apply();
    }
  };
  
  //*/
  
  CGLRenderContext::CGLRenderContext()
  {
      glewInit();
  }
  
  CGLRenderContext::~CGLRenderContext()
  {
  }
  
  void CGLRenderContext::FlushContext()
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float ambient []{ 0.2, 0.2, 0.2, 1.0};
    float diffuse[] {1.0, 1.0, 1.0, 1.0};
    float specular[] {1.0, 1.0, 1.0, 1.0};
    float position[] {m_vLightPosition.x, m_vLightPosition.y, m_vLightPosition.z, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
 
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((float*) &m_projection);
    
    glMatrixMode(GL_MODELVIEW);
    Matrix4 m = Matrix4::Transform(m_view, m_model); 
    glLoadMatrixf((float*)&m);
    
    glUseProgram(m_nProgram);
  }
}