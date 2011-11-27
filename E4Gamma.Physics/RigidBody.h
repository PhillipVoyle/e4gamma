#ifndef __RIGIDBODY_H
#define __RIGIDBODY_H

#include <E4Gamma/Vector.h>
#include <E4Gamma/Matrix.h>
#include <E4Gamma/Quaternion.h>

namespace E4Gamma
{
  namespace Physics
  {
    struct LinearBody
    {
      unsigned cookie;
      
      // primary
      Vector position;
      Vector momentum;
      
      // secondary
      Vector velocity;
      
      // constant
      //float mass;
      float inverseMass;
      
      void recalculate()
      {
        velocity = momentum * inverseMass;
      }
      
      LinearBody(unsigned c):cookie(c), inverseMass(0.0f), position(Vector::Origin), momentum(Vector::Origin)
      {
        recalculate();
      }
      
      LinearBody(unsigned c, float invMass):cookie(c), inverseMass(invMass), position(Vector::Origin), momentum(Vector::Origin)
      {
        recalculate();
      }
      
      LinearBody(unsigned c, float invMass,const Vector& pos, const Vector& mom):cookie(c), inverseMass(invMass), position(pos), momentum(mom)
      {
        
      }
      
      LinearBody(const LinearBody& l):cookie(l.cookie), inverseMass(l.inverseMass), position(l.position), momentum(l.momentum)
      {
        recalculate();
      }
      
      struct Derivative
      {
        Vector velocity;
        Vector force;
        
        Derivative():velocity(Vector::Origin), force(Vector::Origin)
        {
        }
        Derivative(const Derivative&d):velocity(d.velocity),force(d.force)
        {
        }
        Derivative(const Vector&v, const Vector&f):velocity(v), force(f)
        {
        }
        
        Derivative operator*(float h) const
        {
          return Derivative(velocity * h, force * h);
        }
        Derivative operator+(const Derivative& d) const
        {
          return Derivative(velocity + d.velocity, force + d.force);
        }
      };
      
      LinearBody operator+(const Derivative& d) const 
      {
        return LinearBody(cookie, inverseMass, position + d.velocity, momentum + d.force);
      }
    };

    struct AngularBody
    {
      // primary
      Quaternion orientation;
      Vector angularMomentum;
      
      // secondary
      Quaternion spin;
      Vector angularVelocity;
      
      // constant
      //float inertia;
      float inverseInertia;
      
      void recalculate()
      {
        angularVelocity = angularMomentum * inverseInertia;
        
        orientation.normalize();
        
        spin = 0.5f * Quaternion(0, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
      }
      
      AngularBody():orientation(Quaternion::Identity), angularMomentum(Vector::Origin)
      {
        inverseInertia = 0.0f; //massive, stationary
        recalculate();
      }
      
      AngularBody(float invInertia,const Quaternion& orient, const Vector& angMom):inverseInertia(invInertia), orientation(orient), angularMomentum(angMom)
      {
        recalculate();
      }
      
      AngularBody(const AngularBody& a):inverseInertia(a.inverseInertia), orientation(a.orientation), angularMomentum(a.angularMomentum)
      {
        recalculate();
      }
      
      struct Derivative
      {
        Quaternion spin;
        Vector torque;
        
        Derivative():spin(Quaternion::Identity),torque(Vector::Origin)
        {
        }
        Derivative(const Derivative&d):spin(d.spin),torque(d.torque)
        {
        }
        Derivative(const Quaternion& s, const Vector& t):spin(s),torque(t)
        {
        }
        
        Derivative operator*(float h) const
        {
          return Derivative(spin * h, torque * h);
        }
        
        Derivative operator+(const Derivative &d) const
        {
          return Derivative(spin + d.spin, torque + d.torque);
        }
      };
      
      AngularBody operator+(const Derivative& d) const
      {
        return AngularBody(inverseInertia, orientation + d.spin, angularMomentum + d.torque);
      }
    };

    struct RigidBody
    {
      LinearBody linear;
      AngularBody angular;
      
      RigidBody(unsigned cookie):linear(cookie), angular()
      {
      }
      
      RigidBody(const LinearBody& l, const AngularBody& a):linear(l), angular(a)
      {
      }
      
      RigidBody(const RigidBody& rb):linear(rb.linear), angular(rb.angular)
      {
      }
      
      struct Derivative
      {
        LinearBody::Derivative linear;
        AngularBody::Derivative angular;
        Derivative():linear(),angular()
        {
        }
        
        Derivative(const Derivative& d)
        {
          linear = d.linear;
          angular = d.angular;
        }
        
        Derivative(const LinearBody::Derivative& l, const AngularBody::Derivative& a)
        {
          linear = l;
          angular = a;
        }
        
        Derivative operator*(float h) const
        {
          return Derivative(linear * h, angular * h);
        }
        
        Derivative operator+(const Derivative& d) const 
        {
          return Derivative(linear + d.linear, angular + d.angular);
        }
      };
      
      RigidBody operator+(const Derivative &d) const
      {
        return RigidBody(linear + d.linear, angular + d.angular);
      }
    };
  }
}

#endif//__RIGIDBODY_H
