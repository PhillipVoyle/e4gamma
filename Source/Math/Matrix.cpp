/*
 *  Matrix.cpp
 *  GameEngine
 *
 *  Created by Phillip Voyle on 18/06/11.
 *  Copyright 2011 Phillip Voyle. All rights reserved.
 *
 */

#include "Math/Matrix.h"
#include "Math/Quaternion.h"

namespace E4Gamma {

  Matrix4::Matrix4()
  {
    _rx = 1.0f;
    _ry = 0.0f;
    _rz = 0.0f;
    _rw = 0.0f;
    
    _ux = 0.0f;
    _uy = 1.0f;
    _uz = 0.0f;
    _uw = 0.0f;
    
    _fx = 0.0f;
    _fy = 0.0f;
    _fz = 1.0f;
    _fw = 0.0f;
    
    _tx = 0.0f;
    _ty = 0.0f;
    _tz = 0.0f;
    _tw = 1.0f;
  }
  
  Matrix4::Matrix4(
    float rx,float ry,float rz,float rw,
    float ux,float uy,float uz,float uw,
    float fx,float fy,float fz,float fw,
    float tx,float ty,float tz,float tw)
  {
    _rx = rx;
    _ry = ry;
    _rz = rz;
    _rw = rw;
    
    _ux = ux;
    _uy = uy;
    _uz = uz;
    _uw = uw;
    
    _fx = fx;
    _fy = fy;
    _fz = fz;
    _fw = fw;
    
    _tx = tx;
    _ty = ty;
    _tz = tz;
    _tw = tw;
  }
  
    Matrix4::Matrix4(const Matrix4& m4)
  {
    _rx = m4._rx;
    _ry = m4._ry;
    _rz = m4._rz;
    _rw = m4._rw;
    
    _ux = m4._ux;
    _uy = m4._uy;
    _uz = m4._uz;
    _uw = m4._uw;
    
    _fx = m4._fx;
    _fy = m4._fy;
    _fz = m4._fz;
    _fw = m4._fw;
    
    _tx = m4._tx;
    _ty = m4._ty;
    _tz = m4._tz;
    _tw = m4._tw;
  }
  
  Matrix4::Matrix4(const Vector &v, const UnitQuaternion& q)
  {
    _rx = 1.0f - 2.0f * q.v.y * q.v.y - 2.0f * q.v.z * q.v.z;
    _ry = 2.0f * q.v.x * q.v.y - 2.0f * q.v.z * q.s;
    _rz = 2.0f * q.v.x * q.v.z + 2.0f * q.v.y * q.s;
    _rw = 0.0f;
    
    _ux = 2.0f * q.v.x * q.v.y + 2.0f * q.v.z * q.s;
    _uy = 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.z * q.v.z;
    _uz = 2.0f * q.v.y * q.v.z - 2.0f * q.v.x * q.s;
    _uw = 0.0f;
    
    _fx = 2.0f * q.v.x * q.v.z - 2.0f * q.v.y * q.s;
    _fy = 2.0f * q.v.y * q.v.z + 2.0f * q.v.x * q.s;
    _fz = 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.y * q.v.y;
    _fw = 0.0f;
    
    _tx = v.x;
    _ty = v.y;
    _tz = v.z;
    _tw = 1.0f;
  }
  
  Vector Matrix4::GetPosition() const
  {
    return Vector(_tx, _ty, _tz);
  }
  
  void Matrix4::SetPosition(const Vector& vPosition)
  {
    _tx = vPosition.x;
    _ty = vPosition.y;
    _tz = vPosition.z;
    _tw = 1.0f;
  }
  
  UnitQuaternion Matrix4::GetOrientation() const
  {
    float qw = sqrtf(1.0f + _rx + _uy + _fz) * 0.5;
    float invqw4 = 1.0f / (4.0f * qw);
    return Quaternion(
      qw,
      (_fy - _uz) * invqw4,
      (_rz - _fx) * invqw4,
      (_ux - _ry) * invqw4).normalize(); //todo: prove already normalized
  }
  
  void Matrix4::SetOrientation(const UnitQuaternion& q)
  {
    _rx = 1.0f - 2.0f * q.v.y * q.v.y - 2.0f * q.v.z * q.v.z;
    _ry = 2.0f * q.v.x * q.v.y - 2.0f * q.v.z * q.s;
    _rz = 2.0f * q.v.x * q.v.z + 2.0f * q.v.y * q.s;
    
    _ux = 2.0f * q.v.x * q.v.y + 2.0f * q.v.z * q.s;
    _uy = 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.z * q.v.z;
    _uz = 2.0f * q.v.y * q.v.z - 2.0f * q.v.x * q.s;
    
    _fx = 2.0f * q.v.x * q.v.z - 2.0f * q.v.y * q.s;
    _fy = 2.0f * q.v.y * q.v.z + 2.0f * q.v.x * q.s;
    _fz = 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.y * q.v.y; 
  }
  
  Vector Matrix4::Transform(const Matrix4& w, const Vector& v)
  {
    return Vector(
      w._rx * v.x + w._ux * v.y + w._fx * v.z + w._tx,
      w._ry * v.x + w._uy * v.y + w._fy * v.z + w._ty,
      w._rz * v.x + w._uz * v.y + w._fz * v.z + w._tz);
  }
  
  Matrix4 Matrix4::Transform(const Matrix4& w /*world*/, const Matrix4& l /*local*/)
  {
    Matrix4 r; //result
    //transform local right vector by world matrix
    r._rx = w._rx * l._rx + w._ux * l._ry + w._fx * l._rz + w._tx * l._rw;
    r._ry = w._ry * l._rx + w._uy * l._ry + w._fy * l._rz + w._ty * l._rw;
    r._rz = w._rz * l._rx + w._uz * l._ry + w._fz * l._rz + w._tz * l._rw;
    r._rw = w._rw * l._rx + w._uw * l._ry + w._fw * l._rz + w._tw * l._rw;
    
    //transform local up vector by world matrix
    r._ux = w._rx * l._ux + w._ux * l._uy + w._fx * l._uz + w._tx * l._uw;
    r._uy = w._ry * l._ux + w._uy * l._uy + w._fy * l._uz + w._ty * l._uw;
    r._uz = w._rz * l._ux + w._uz * l._uy + w._fz * l._uz + w._tz * l._uw;
    r._uw = w._rw * l._ux + w._uw * l._uy + w._fw * l._uz + w._tw * l._uw;
    
    //transform local fwd vector by world matrix
    r._fx = w._rx * l._fx + w._ux * l._fy + w._fx * l._fz + w._tx * l._fw;
    r._fy = w._ry * l._fx + w._uy * l._fy + w._fy * l._fz + w._ty * l._fw;
    r._fz = w._rz * l._fx + w._uz * l._fy + w._fz * l._fz + w._tz * l._fw;
    r._fw = w._rw * l._fx + w._uw * l._fy + w._fw * l._fz + w._tw * l._fw;
    
    //transform local translation vector by world matrix
    r._tx = w._rx * l._tx + w._ux * l._ty + w._fx * l._tz + w._tx * l._tw;
    r._ty = w._ry * l._tx + w._uy * l._ty + w._fy * l._tz + w._ty * l._tw;
    r._tz = w._rz * l._tx + w._uz * l._ty + w._fz * l._tz + w._tz * l._tw;
    r._tw = w._rw * l._tx + w._uw * l._ty + w._fw * l._tz + w._tw * l._tw;
    
    return r;
  }
  
  void Matrix4::TranslateWorld(const Vector& vDisplacement)
  {
    _tx += vDisplacement.x;
    _ty += vDisplacement.y;
    _tz += vDisplacement.z;
  }
  
  void Matrix4::TranslateLocal(const Vector& vDisplacement)
  {
    float dtx = vDisplacement.x * _rx + vDisplacement.y * _ux + vDisplacement.z * _fx + _tx;
    float dty = vDisplacement.y * _ry + vDisplacement.y * _uy + vDisplacement.z * _fy + _ty;
    float dtz = vDisplacement.z * _rz + vDisplacement.y * _uz + vDisplacement.z * _fz + _tz;
    
    _tx += dtx;
    _ty += dty;
    _tz += dtz;
  }
  
  Matrix4 Matrix4::Inverse() const
  {
    float a0 = _rx*_uy - _ry*_ux;
    float a1 = _rx*_uz - _rz*_ux;
    float a2 = _rx*_uw - _rw*_ux;
    float a3 = _ry*_uz - _rz*_uy;
    float a4 = _ry*_uw - _rw*_uy;
    float a5 = _rz*_uw - _rw*_uz;
    float b0 = _fx*_ty - _fy*_tx;
    float b1 = _fx*_tz - _fz*_tx;
    float b2 = _fx*_tw - _fw*_tx;
    float b3 = _fy*_tz - _fz*_ty;
    float b4 = _fy*_tw - _fw*_ty;
    float b5 = _fz*_tw - _fw*_tz;

    float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    if (det > FLT_EPSILON || det < -FLT_EPSILON)
    {
        float invDet = 1.0f/det;
        return Matrix4(
          invDet * (+ _uy*b5 - _uz*b4 + _uw*b3),
          invDet * (- _ry*b5 + _rz*b4 - _rw*b3),
          invDet * (+ _ty*a5 - _tz*a4 + _tw*a3),
          invDet * (- _fy*a5 + _fz*a4 - _fw*a3),
          invDet * (- _ux*b5 + _uz*b2 - _uw*b1),
          invDet * (+ _rx*b5 - _rz*b2 + _rw*b1),
          invDet * (- _tx*a5 + _tz*a2 - _tw*a1),
          invDet * (+ _fx*a5 - _fz*a2 + _fw*a1),
          invDet * (+ _ux*b4 - _uy*b2 + _uw*b0),
          invDet * (- _rx*b4 + _ry*b2 - _rw*b0),
          invDet * (+ _tx*a4 - _ty*a2 + _tw*a0),
          invDet * (- _fx*a4 + _fy*a2 - _fw*a0),
          invDet * (- _ux*b3 + _uy*b1 - _uz*b0),
          invDet * (+ _rx*b3 - _ry*b1 + _rz*b0),
          invDet * (- _tx*a3 + _ty*a1 - _tz*a0),
          invDet * (+ _fx*a3 - _fy*a1 + _fz*a0));
    }
    else
    {
      return Matrix4(); //otherwise just use identity.
    }
  }
}
