/*
 *  Matrix.h
 *  GameEngine
 *
 *  Created by Phillip Voyle on 18/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MATRIX_H
#define __MATRIX_H
namespace E4Gamma
{
  struct Quaternion;
  struct Vector;
  
  struct Matrix4
  {
    float _rx, _ry, _rz, _rw; //right
    float _ux, _uy, _uz, _uw; //up
    float _fx, _fy, _fz, _fw; //forward
    float _tx, _ty, _tz, _tw; //translate

    Matrix4();
    Matrix4(
    float rx, float ry, float rz, float rw,
    float ux, float uy, float uz, float uw,
    float fx, float fy, float fz, float fw,
    float tx, float ty, float tz, float tw);
    
    Matrix4(const Vector& position, const Quaternion& orientation);
    Matrix4(const Matrix4& matrix);
    
      
    Vector GetPosition() const;
    void SetPosition(const Vector& vPosition);
    void TranslateWorld(const Vector& vDisplacement);
    void TranslateLocal(const Vector& vDisplacement);
    
    Quaternion GetOrientation() const;
    void SetOrientation(const Quaternion&q);
    
    Matrix4 Inverse() const;
    
    static Matrix4 Transform(const Matrix4& world, const Matrix4& local);
    static Vector Transform(const Matrix4& w, const Vector& v);
    
    void GetUpVector(const Vector&up) const;
    void GetDownVector(const Vector&down) const;
    void GetLeftVector(const Vector&left) const;
    void GetRightVector(const Vector&right) const;
    void GetForwardVector(const Vector& forward) const;
    void GetBackVector(const Vector&back) const;
  };
}
#endif//__MATRIX_H
