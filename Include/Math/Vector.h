/*
 *  Vector.h
 *  GameEngine
 *
 *  Created by Phillip Voyle on 18/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __VECTOR_H
#define __VECTOR_H

#include <float.h>
#include <math.h>

struct Vector
{
  float x,y,z;
  
  Vector()
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }
  
  Vector(float a_x, float a_y, float a_z)
  {
    x = a_x;
    y = a_y;
    z = a_z;
  }
  
  Vector(const Vector&v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }
  
  void operator=(const Vector&v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }
  
  Vector operator-() const
  {
    return Vector(-x, -y, -z);
  }
  
  Vector normalize()
  {
    float fLength = sqrtf(x * x + y * y + z * z);
    
    if(fLength > FLT_EPSILON)
    {
      return Vector(x / fLength, y / fLength, z / fLength);
    }
    else
    {
      return Vector(0.0f, 0.0f, 0.0f); // should this be a unit vector?
    }
  }
  
  static const Vector Origin;
  static const Vector I;
  static const Vector J;
  static const Vector K;
};

Vector Cross(const Vector& v1, const Vector& v2);
float Dot(const Vector& v1, const Vector& v2);
Vector operator+(const Vector& v1, const Vector &v2);
Vector operator-(const Vector& v1, const Vector &v2);
Vector operator*(const Vector& v, float scalar);
Vector operator*(float scalar, const Vector& v);

#endif//__VECTOR_H
