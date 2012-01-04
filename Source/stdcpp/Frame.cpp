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
    
    void CMatrix4Frame::GetPosition(Vector& vPosition)
    {
      vPosition = m_transform.GetPosition();
    }
    void CMatrix4Frame::GetOrientation(Quaternion& qOrientation)
    {
      qOrientation = m_transform.GetOrientation();
    }
    void CMatrix4Frame::GetTransform(Matrix4& mTransform)
    {
      mTransform = m_transform;
    }
    
    void CMatrix4Frame::SetPosition(const Vector& vPosition)
    {
      m_transform.SetPosition(vPosition);
    }
    void CMatrix4Frame::SetOrientation(const Quaternion& qOrientation)
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
    void CMatrix4Frame::RotateWorld(const Quaternion& qRotation)
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
    void CMatrix4Frame::RotateLocal(const Quaternion& qRotation)
    {
      Matrix4 mRotation(Vector::Origin, qRotation);
      TransformLocal(mRotation);
    }
    void CMatrix4Frame::TransformLocal(const Matrix4& mTransformLocal)
    {
      m_transform = Matrix4::Transform(m_transform, mTransformLocal);
    }
    
    void CRotPosFrame::GetPosition(Vector& vPosition)
    {
      vPosition = m_position;
    }
    void CRotPosFrame::GetOrientation(Quaternion& qOrientation)
    {
      qOrientation = m_orientation;
    }
    void CRotPosFrame::GetTransform(Matrix4& mTransform)
    {
      mTransform = Matrix4(m_position, m_orientation);
    }
    
    void CRotPosFrame::SetPosition(const Vector& vPosition)
    {
      m_position = vPosition;
    }
    void CRotPosFrame::SetOrientation(const Quaternion& qOrientation)
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
    
    void CRotPosFrame::RotateWorld(const Quaternion& qRotation)
    {
      m_position = Quaternion::Transform(qRotation, m_position);
      m_orientation = Quaternion::Transform(qRotation, m_orientation);
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
    
    void CRotPosFrame::RotateLocal(const Quaternion& qRotation)
    {
      m_orientation = Quaternion::Transform(m_orientation, qRotation);
    }
    
    void CRotPosFrame::TransformLocal(const Matrix4& mTransform)
    {  
      Vector vTranslateWorld = Quaternion::Transform(m_orientation, mTransform.GetPosition());
      RotateLocal(mTransform.GetOrientation());
      m_position += vTranslateWorld;
    }
}
