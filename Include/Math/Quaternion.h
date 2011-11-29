/*
 *  Quaternion.h
 *  GameEngine
 *
 *  Created by Phillip Voyle on 18/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __QUATERNION_H
#define __QUATERNION_H

#include "Vector.h"

struct Quaternion
{
  float s;   //scalar component
  Vector v;  //vector component
  
  Quaternion()
  {
    s = 0.0f;
    v = Vector(0.0f,0.0f,0.0f);
  }
  
  Quaternion(float a_s, const Vector& a_v)
  {
    s = a_s;
    v = a_v;
  }
  Quaternion(float a_s, float a_x, float a_y, float a_z)
  {
    s = a_s;
    v = Vector(a_x, a_y, a_z);
  }
  
  Quaternion normalize()const
  {
    float fLength = sqrtf(s * s + v.x * v.x + v.y * v.y + v.z * v.z);
    return Quaternion(s / fLength, v.x / fLength, v.y / fLength, v.z / fLength);
  }
  
  Quaternion operator~()const
  {
    return Quaternion(s, -v);
  }
  
  static Quaternion Identity;
};


Quaternion operator*(const Quaternion& q, const Vector& v);
Quaternion operator*(const Vector& v, const Quaternion& q);
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

Quaternion operator*(const Quaternion& q, float f);
Quaternion operator*(float f, const Quaternion& q);
Quaternion operator+(const Quaternion&q1, const Quaternion& q2);
Quaternion operator-(const Quaternion&q1, const Quaternion& q2);

inline Vector Rotate(const Vector& v, const Quaternion& q)
{
  return (q * v * ~q).v;
}


#endif//__QUATERNION_H