/*
 *  Quaternion.cpp
 *  GameEngine
 *
 *  Created by Phillip Voyle on 18/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Quaternion.h"

namespace E4Gamma {

  Quaternion Quaternion::Identity(1.0f, Vector::Origin);

  Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
  {
    return Quaternion(
                      q1.s * q2.s - Dot(q1.v, q2.v),
                      q1.s * q2.v + q2.s * q1.v + Cross(q1.v, q2.v)
                      );
  }

  Quaternion operator*(const Quaternion& q, float f)
  {
    return Quaternion(q.s * f, q.v * f);
  }

  Quaternion operator*(float f, const Quaternion& q)
  {
    return Quaternion(q.s * f, q.v * f);
  }

  Quaternion operator+(const Quaternion&q1, const Quaternion& q2)
  {
    return Quaternion(q1.s + q2.s, q1.v + q2.v);
  }

  Quaternion operator-(const Quaternion&q1, const Quaternion& q2)
  {
    return Quaternion(q1.s - q2.s, q1.v - q2.v);
  }

  Quaternion operator*(const Quaternion& q, const Vector& v)
  {
    return Quaternion(
      -(q.v.x * v.x + q.v.y * v.y +q.v.z * v.z),
      q.s * v.x + q.v.y * v.z - q.v.z * v.y,
      q.s * v.y + q.v.z * v.x - q.v.x * v.z,
      q.s * v.z + q.v.x * v.y - q.v.y * v.x);
  }

  Quaternion operator*(const Vector& v, const Quaternion& q)
  {
    return Quaternion(
      -(q.v.x * v.x + q.v.y * v.y +q.v.z * v.z),
      q.s * v.x + q.v.x * v.y - q.v.y * v.z,
      q.s * v.y + q.v.x * v.z - q.v.z * v.x,
      q.s * v.z + q.v.y * v.x - q.v.x * v.y);
  }
  
  Quaternion Quaternion::Rotate(const Quaternion& qWorld, const Quaternion& qLocal)
  {
    Quaternion opFirst = qWorld * qLocal;
    Quaternion opSecond = ~(qWorld);
    Quaternion opThird = opFirst * opSecond;
  
    return opFirst;
  }
  
  Quaternion Quaternion::FromAxisAngle(const Vector& vAxis, float fAngle)
  {
  }
}