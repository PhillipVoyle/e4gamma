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
      m_transform.GetPosition(vPosition);
    }
    void CMatrix4Frame::GetOrientation(Quaternion& qOrientation)
    {
      m_transform.GetOrientation(qOrientation);
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
      mTransform.GetPosition(m_position);
      mTransform.GetOrientation(m_orientation);
    }  
    
    void CRotPosFrame::TranslateWorld(const Vector& vDisplacement)
    {
      m_position += vDisplacement;
    }
    
    void CRotPosFrame::RotateWorld(const Quaternion& qRotation)
    {
      m_position = RotateV(m_position, qRotation);
      m_orientation = Quaternion::Rotate(qRotation, m_orientation);
    }
    void CRotPosFrame::TransformWorld(const Matrix4& mTransform)
    {
      Vector vTranslate;
      Quaternion qOrient;
      mTransform.GetPosition(vTranslate);
      mTransform.GetOrientation(qOrient);
      
      m_position += vTranslate;
      m_orientation = Quaternion::Rotate(qOrient, m_orientation);
    }
    
    void CRotPosFrame::TranslateLocal(const Vector& vDisplacement)
    {
      Vector vTranslate = RotateV(vDisplacement, m_orientation);
      m_position += vTranslate;
    }
    
    void CRotPosFrame::RotateLocal(const Quaternion& qRotation)
    {
      m_orientation = Quaternion::Rotate(m_orientation, qRotation);
    }
    
    void CRotPosFrame::TransformLocal(const Matrix4& mTransform)
    {
      Vector vTranslateLocal;
      Quaternion qOrientLocal;
      mTransform.GetPosition(vTranslateLocal);
      mTransform.GetOrientation(qOrientLocal);
      
      Vector vTranslateWorld = RotateV(vTranslateLocal, m_orientation);
      m_position += vTranslateWorld;
      m_orientation = Quaternion::Rotate(m_orientation, qOrientLocal);
    }
}
