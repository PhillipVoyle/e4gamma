//
//  PhysicsFrame.h
//  E4Gamma
//
//  Created by Phillip Voyle on 22/06/13.
//
//

#ifndef E4Gamma_PhysicsFrame_h
#define E4Gamma_PhysicsFrame_h

#include <Physics/RigidBody.h>
#include <Interfaces/Foundation/IFrame.h>

namespace E4Gamma {
  namespace Physics
  {

    class CRigidBodyFrame: public IFrame
    {
      RigidBody m_body;
    public:
      CRigidBodyFrame()
      {
      }
      CRigidBodyFrame(RigidBody body):m_body(body)
      {
      }
      
      Vector GetPosition();
      UnitQuaternion GetOrientation();
      Matrix4 GetTransform();
      void SetPosition(const Vector& vPosition);
      void SetOrientation(const UnitQuaternion& qOrientation);
      void SetTransform(const Matrix4& mTransform);
      void TranslateWorld(const Vector& vDisplacement);
      void RotateWorld(const UnitQuaternion& qRotation);
      void TransformWorld(const Matrix4& mTransform);
      
      void TranslateLocal(const Vector& vDisplacement);
      void RotateLocal(const UnitQuaternion& qRotation);
      void TransformLocal(const Matrix4& mTransform);
      
      RigidBody& GetBody() {return m_body;}
    };
  }
}

#endif
