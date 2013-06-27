//
//  Frame.cpp
//  E4Gamma
//
//  Created by Phillip Voyle on 29/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <stdcpp/Frame.h>
#include <Math/Quaternion.h>

namespace E4Gamma {
    
    Vector CMatrix4Frame::GetPosition()
    {
      return m_transform.GetPosition();
    }
    UnitQuaternion CMatrix4Frame::GetOrientation()
    {
      return m_transform.GetOrientation();
    }
    Matrix4 CMatrix4Frame::GetTransform()
    {
      return m_transform;
    }
    
    void CMatrix4Frame::SetPosition(const Vector& vPosition)
    {
      m_transform.SetPosition(vPosition);
    }
    void CMatrix4Frame::SetOrientation(const UnitQuaternion& qOrientation)
    {
      m_transform.SetOrientation(qOrientation);
    }
    void CMatrix4Frame::SetTransform(const Matrix4& mTransform)
    {
      m_transform = mTransform;
    }
    
    void CMatrix4Frame::TranslateWorld(const Vector& vDisplacement)
    {
      m_transform.TranslateWorld(vDisplacement);
    }
    void CMatrix4Frame::RotateWorld(const UnitQuaternion& qRotation)
    {
      Matrix4 mRotation(Vector::Origin, qRotation);
      TransformWorld(mRotation);
    }
    void CMatrix4Frame::TransformWorld(const Matrix4& mTransformWorld)
    {
      m_transform = Matrix4::Transform(mTransformWorld, m_transform);
    }
    
    void CMatrix4Frame::TranslateLocal(const Vector& vDisplacement)
    {
      m_transform.TranslateLocal(vDisplacement);
    }
    void CMatrix4Frame::RotateLocal(const UnitQuaternion& qRotation)
    {
      Matrix4 mRotation(Vector::Origin, qRotation);
      TransformLocal(mRotation);
    }
    void CMatrix4Frame::TransformLocal(const Matrix4& mTransformLocal)
    {
      m_transform = Matrix4::Transform(m_transform, mTransformLocal);
    }
    
    Vector CRotPosFrame::GetPosition()
    {
      return m_position;
    }
    UnitQuaternion CRotPosFrame::GetOrientation()
    {
      return m_orientation;
    }
    Matrix4 CRotPosFrame::GetTransform()
    {
      return Matrix4(m_position, m_orientation);
    }
    
    void CRotPosFrame::SetPosition(const Vector& vPosition)
    {
      m_position = vPosition;
    }
    void CRotPosFrame::SetOrientation(const UnitQuaternion& qOrientation)
    {
      m_orientation = qOrientation;
    }
    void CRotPosFrame::SetTransform(const Matrix4& mTransform)
    {
      m_position = mTransform.GetPosition();
      m_orientation = mTransform.GetOrientation();
    }  
    
    void CRotPosFrame::TranslateWorld(const Vector& vDisplacement)
    {
      m_position += vDisplacement;
    }
    
    void CRotPosFrame::RotateWorld(const UnitQuaternion& qRotation)
    {
      m_position = Quaternion::Transform(qRotation, m_position);
      m_orientation = Quaternion::Transform(qRotation, m_orientation).normalize();
    }
    void CRotPosFrame::TransformWorld(const Matrix4& mTransform)
    {
      RotateWorld(mTransform.GetOrientation());
      TranslateWorld(mTransform.GetPosition());
    }
    
    void CRotPosFrame::TranslateLocal(const Vector& vDisplacement)
    {
      Vector vTranslate = Quaternion::Transform(m_orientation, vDisplacement);
      m_position += vTranslate;
    }
    
    void CRotPosFrame::RotateLocal(const UnitQuaternion& qRotation)
    {
      m_orientation = Quaternion::Transform(m_orientation, qRotation).normalize();
    }
    
    void CRotPosFrame::TransformLocal(const Matrix4& mTransform)
    {  
      Vector vTranslateWorld = Quaternion::Transform(m_orientation, mTransform.GetPosition());
      RotateLocal(mTransform.GetOrientation());
      m_position += vTranslateWorld;
    }
    
    
    Vector CPositionFrame::GetPosition()
    {
      return m_position;
    }
    UnitQuaternion CPositionFrame::GetOrientation()
    {
      return Quaternion::Identity;
    }
    Matrix4 CPositionFrame::GetTransform()
    {
      return Matrix4(m_position, Quaternion::Identity);
    }
    
    void CPositionFrame::SetPosition(const Vector& vPosition)
    {
      m_position = vPosition;
    }
    void CPositionFrame::SetOrientation(const UnitQuaternion& qOrientation)
    {
    }
    void CPositionFrame::SetTransform(const Matrix4& mTransform)
    {
      m_position = mTransform.GetPosition();
    }  
    
    void CPositionFrame::TranslateWorld(const Vector& vDisplacement)
    {
      m_position += vDisplacement;
    }
    
    void CPositionFrame::RotateWorld(const UnitQuaternion& qRotation)
    {
      m_position = Quaternion::Transform(qRotation, m_position);
    }
    void CPositionFrame::TransformWorld(const Matrix4& mTransform)
    {
      TranslateWorld(mTransform.GetPosition());
    }
    
    void CPositionFrame::TranslateLocal(const Vector& vDisplacement)
    {
      m_position += vDisplacement;
    }
    
    void CPositionFrame::RotateLocal(const UnitQuaternion& qRotation)
    {
    }
    
    void CPositionFrame::TransformLocal(const Matrix4& mTransform)
    {  
      m_position += mTransform.GetPosition();
    }
    
}
