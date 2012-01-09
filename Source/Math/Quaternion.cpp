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
      q1.s * q2.s - q1.v.x * q2.v.x - q1.v.y * q2.v.y - q1.v.z * q2.v.z,
      q1.s * q2.v.x + q1.v.x * q2.s + q1.v.y * q2.v.z - q1.v.z * q2.v.y,
      q1.s * q2.v.y + q1.v.y * q2.s + q1.v.z * q2.v.x - q1.v.x * q2.v.z,
      q1.s * q2.v.z + q1.v.z * q2.s + q1.v.x * q2.v.y - q1.v.y * q2.v.x);
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
  
  Quaternion Quaternion::Transform(const Quaternion& qWorld, const Quaternion& qLocal)
  {
    return qWorld * qLocal;
  }
  
  Vector Quaternion::Transform(const Quaternion& qWorld, const Vector& vLocal)
  {
    return (~qWorld * vLocal * qWorld).v;
  }
  
  Quaternion Quaternion::FromAxisAngle(const Vector& vAxis, float fAngle)
  {
    float fHalfAngle = fAngle * 0.5f;
    return Quaternion(cosf(fHalfAngle), vAxis * sinf(fHalfAngle));
  }
}