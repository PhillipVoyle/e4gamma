//
//  MathTest.cpp
//  E4Gamma
//
//  Created by Stacey Voyle on 4/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include <Math/Vector.h>
#include <Math/Quaternion.h>
#include <Math/Matrix.h>

using namespace E4Gamma;

void check_rot(Matrix4 mat1, Matrix4 mat2);
void check_pos(Matrix4 mat1, Vector v);

void check_rot(Matrix4 mat1, Matrix4 mat2)
{
  Matrix4 mat3 = Matrix4::Transform(mat1, mat2);
  Quaternion qOut1 = mat3.GetOrientation();
  Vector vOut1 = mat3.GetPosition();
  
  Quaternion qOut2 = Quaternion::Transform(mat1.GetOrientation(), mat2.GetOrientation());
  Vector vOut2 = Quaternion::Transform(mat1.GetOrientation(), mat2.GetPosition()) + mat1.GetPosition();
  
  Matrix4 matQ(vOut1, qOut1.normalize());
}

void check_pos(Matrix4 mat1, Vector v)
{
  Vector vOut1 = Matrix4::Transform(mat1, v);
  Vector vOut2 = Quaternion::Transform(mat1.GetOrientation(), v) + mat1.GetPosition();
}


int main(int argc, char**argv)
{
  
  float theta1 = 0.5;
  float theta2 = 1.3;
  
  float fcostheta1 = cosf(theta1);
  float fsintheta1 = sinf(theta1);
  
  float fcostheta2 = cosf(theta2);
  float fsintheta2 = sinf(theta2);

  check_rot(
    Matrix4(
      fcostheta1, 0, fsintheta1, 0,
      0, 1, 0, 0,
      -fsintheta1, 0, fcostheta1, 0,
      0, 0, 10, 1),
     Matrix4(
      fcostheta2, fsintheta2, 0, 0,
      -fsintheta2, fcostheta2, 0, 0,
      0, 0, 1, 0,
      0, 0, 10,1) 
  );
  
  check_pos(
    Matrix4(
      fcostheta1, 0, fsintheta1, 0,
      0, 1, 0, 0,
      -fsintheta1, 0, fcostheta1, 0,
      0, 0, 10, 1),
     Vector(0, 0, 10)
  );
  return 0;
}
