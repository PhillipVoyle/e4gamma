//
//  GLRenderContext.h
//  E4Gamma
//
//  Created by Phillip Voyle on 5/01/12.
//  Copyright (c) 2012 Phillip Voyle. All rights reserved.
//

#ifndef E4Gamma_GLRenderContext_h
#define E4Gamma_GLRenderContext_h

#include <Math/Matrix.h>
#include <Math/Vector.h>
#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma
{
  class IMesh;
  class IMaterial;
  class IModel;
  
  class CGLRenderContext: public IUnknown
  {
  public:
    ~CGLRenderContext();
    CGLRenderContext();
    
    Matrix4 m_model;
    Matrix4 m_view;
    Matrix4 m_projection;
    
    float m_fLightRadius;
    Vector m_vLightPosition;
    
    int m_nProgram;
    
    void FlushContext();
  };
}

#endif
