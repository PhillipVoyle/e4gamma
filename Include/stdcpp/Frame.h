//
//  Frame.h
//  E4Gamma
//
//  Created by Phillip Voyle on 23/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_Frame_h
#define E4Gamma_Frame_h

#include <Interfaces/Foundation/IFrame.h>
#include <Math/Matrix.h>
#include <Math/Vector.h>
#include <Math/Quaternion.h>

namespace E4Gamma {
  class CMatrix4Frame: public IFrame
  {
    Matrix4 m_transform;
  public:
    void GetPosition(Vector& vPosition);
    void GetOrientation(Quaternion& qOrientation);
    void GetTransform(Matrix4& mTransform);
    
    void SetPosition(const Vector& vPosition);
    void SetOrientation(const Quaternion& qOrientation);
    void SetTransform(const Matrix4& mTransform);    
    
    void TranslateWorld(const Vector& vDisplacement);
    void RotateWorld(const Quaternion& qRotation);
    void TransformWorld(const Matrix4& mTransform);
    
    void TranslateLocal(const Vector& vDisplacement);
    void RotateLocal(const Quaternion& qRotation);
    void TransformLocal(const Matrix4& mTransform);   
  };

  class CRotPosFrame: public IFrame
  {
    Quaternion m_orientation;
    Vector m_position;
  public:
    void GetPosition(Vector& vPosition);
    void GetOrientation(Quaternion& qOrientation);
    void GetTransform(Matrix4& mTransform);
    
    void SetPosition(const Vector& vPosition);
    void SetOrientation(const Quaternion& qOrientation);
    void SetTransform(const Matrix4& mTransform);    
    
    void TranslateWorld(const Vector& vDisplacement);
    void RotateWorld(const Quaternion& qRotation);
    void TransformWorld(const Matrix4& mTransform);
    
    void TranslateLocal(const Vector& vDisplacement);
    void RotateLocal(const Quaternion& qRotation);
    void TransformLocal(const Matrix4& mTransform);
  };
}

#endif