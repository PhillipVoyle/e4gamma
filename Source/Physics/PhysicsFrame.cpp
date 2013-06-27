
#include <Physics/PhysicsFrame.h>

namespace E4Gamma
{
  namespace Physics
  {
    Vector CRigidBodyFrame::GetPosition()
    {
      return m_body.linear.position;
    }
    UnitQuaternion CRigidBodyFrame::GetOrientation()
    {
      return m_body.angular.orientation.normalize();
    }
    Matrix4 CRigidBodyFrame::GetTransform()
    {
      return Matrix4(m_body.linear.position, m_body.angular.orientation.normalize());
    }
    
    void CRigidBodyFrame::SetPosition(const Vector& vPosition)
    {
      m_body.linear.position = vPosition;
    }
    void CRigidBodyFrame::SetOrientation(const UnitQuaternion& qOrientation)
    {
      m_body.angular.orientation = qOrientation;
    }
    void CRigidBodyFrame::SetTransform(const Matrix4& mTransform)
    {
      m_body.linear.position = mTransform.GetPosition();
      m_body.angular.orientation = mTransform.GetOrientation();
    }  
    
    void CRigidBodyFrame::TranslateWorld(const Vector& vDisplacement)
    {
      m_body.linear.position += vDisplacement;
    }
    
    void CRigidBodyFrame::RotateWorld(const UnitQuaternion& qRotation)
    {
      m_body.linear.position = Quaternion::Transform(qRotation, m_body.linear.position);
      m_body.angular.orientation = Quaternion::Transform(qRotation, m_body.angular.orientation);
    }
    void CRigidBodyFrame::TransformWorld(const Matrix4& mTransform)
    {
      RotateWorld(mTransform.GetOrientation());
      TranslateWorld(mTransform.GetPosition());
    }
    
    void CRigidBodyFrame::TranslateLocal(const Vector& vDisplacement)
    {
      Vector vTranslate = Quaternion::Transform(m_body.angular.orientation, vDisplacement);
      m_body.linear.position += vTranslate;
    }
    
    void CRigidBodyFrame::RotateLocal(const UnitQuaternion& qRotation)
    {
      m_body.angular.orientation = Quaternion::Transform(m_body.angular.orientation, qRotation);
    }
    
    void CRigidBodyFrame::TransformLocal(const Matrix4& mTransform)
    {  
      Vector vTranslateWorld = Quaternion::Transform(m_body.angular.orientation, mTransform.GetPosition());
      RotateLocal(mTransform.GetOrientation());
      m_body.linear.position += vTranslateWorld;
    }
  }
}

