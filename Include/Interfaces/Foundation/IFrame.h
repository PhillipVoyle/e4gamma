//
//  IFrame.h
//  E4Gamma
//
//  Created by Phillip Voyle on 23/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_IFrame_h
#define E4Gamma_IFrame_h

#include <Interfaces/Foundation/IUnknown.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>
#include <Math/Vector.h>

namespace E4Gamma
{
  class IFrame: public IUnknown
  {
  public:
    virtual Vector GetPosition() = 0;
    virtual Quaternion GetOrientation() = 0;
    virtual Matrix4 GetTransform() = 0;
    
    virtual void SetPosition(const Vector& vPosition) = 0;
    virtual void SetOrientation(const Quaternion& qOrientation) = 0;
    virtual void SetTransform(const Matrix4& mTransform) = 0;    
    
    virtual void TranslateWorld(const Vector& vDisplacement) = 0;
    virtual void RotateWorld(const Quaternion& qRotation) = 0;
    virtual void TransformWorld(const Matrix4& mTransform) = 0;
    
    virtual void TranslateLocal(const Vector& vDisplacement) = 0;
    virtual void RotateLocal(const Quaternion& qRotation) = 0;
    virtual void TransformLocal(const Matrix4& mTransform) = 0;
  };
}

#endif
