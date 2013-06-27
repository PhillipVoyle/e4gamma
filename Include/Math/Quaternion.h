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
namespace E4Gamma
{
  struct Matrix4;
  struct UnitQuaternion;

  struct Quaternion
  {
    float s;   //scalar component
    Vector v;  //vector component
    
    Quaternion()
    {
      s = 1.0f;
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
    
    Quaternion(const Quaternion& q)
    {
      s = q.s;
      v = q.v;
    }
    
    void operator=(const Quaternion& q)
    {
      s = q.s;
      v = q.v;
    }
    
    UnitQuaternion normalize() const;
    
    Quaternion operator~()const
    {
      return Quaternion(s, -v);
    }
    
    static Quaternion Transform(const Quaternion& qWorld, const Quaternion& qLocal);
    static Vector Transform(const Quaternion& qWorld, const Vector& vLocal);
    
    void ToMatrix4(Matrix4& matrix);
    
    static UnitQuaternion Identity;
    
    static UnitQuaternion FromAxisAngle(const Vector& vAxis, float fAngle);
  };
  
  struct UnitQuaternion:public Quaternion
  {
    friend UnitQuaternion Quaternion::normalize() const;
  private:
    UnitQuaternion(const Quaternion& q):Quaternion(q)
    {
    }
  public:
    UnitQuaternion():Quaternion(Quaternion::Identity)
    {
    }
  };


  Quaternion operator*(const Quaternion& q, const Vector& v);
  Quaternion operator*(const Vector& v, const Quaternion& q);
  Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

  Quaternion operator*(const Quaternion& q, float f);
  Quaternion operator*(float f, const Quaternion& q);
  Quaternion operator+(const Quaternion&q1, const Quaternion& q2);
  Quaternion operator-(const Quaternion&q1, const Quaternion& q2);

}
#endif//__QUATERNION_H
