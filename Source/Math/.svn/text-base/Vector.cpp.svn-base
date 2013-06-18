/*
 *  Vector.cpp
 *  GameEngine
 *
 *  Created by Phillip Voyle on 18/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.h"

namespace E4Gamma {

  const Vector Vector::Origin(0.0f, 0.0f, 0.0f);
  const Vector Vector::I(1.0f, 0.0f, 0.0f);
  const Vector Vector::J(0.0f, 1.0f, 0.0f);
  const Vector Vector::K(0.0f, 0.0f, 1.0f);

  Vector Cross(const Vector& v1, const Vector& v2)
  {
    return Vector(v1.y * v2.z - v1.z * v2.y,
                  v1.z * v2.x - v1.x * v2.z,
                  v1.x * v2.y - v1.y * v2.x);
  }

  float Dot(const Vector& v1, const Vector& v2)
  {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  Vector operator+(const Vector& v1, const Vector &v2)
  {
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
  }

  Vector operator-(const Vector& v1, const Vector &v2)
  {
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
  }

  Vector operator*(const Vector& v, float scalar)
  {
    return Vector(v.x * scalar,v.y * scalar,v.z * scalar);
  }

  Vector operator*(float scalar, const Vector& v)
  {
    return Vector(v.x * scalar,v.y * scalar,v.z * scalar);
  }

}