/*
 *  RK4.h
 *  GameEngine
 *
 *  Created by Phillip Voyle on 19/06/11.
 *  Copyright 2011 Phillip Voyle. All rights reserved.
 *
 */

#ifndef __RK4_H
#define __RK4_H

namespace E4Gamma
{
  namespace Physics
  {
    //
    // this template function implements the Runge Kutta integration method
    //

    //using the accumulation method (+=)
    //note the void return type
    template<typename TState, typename TDerivative, typename TFunctor>
    void IntegrateRK4_Accumulate(TState& q, TFunctor f, float h)
    {
      TDerivative k1 = f(q) * h;
      TDerivative k2 = f(q + k1 * 0.5f) * h;
      TDerivative k3 = f(q + k2 * 0.5f) * h;
      TDerivative k4 = f(q + k3) * h;
      
      q += (k1 + (k2 + k3) * 2.0f + k4) * (1.0f / 6.0f);
    }

    //offloading accumulation to the caller (note that q is const)
    //note the const TState argument and result type
    template<typename TState, typename TDerivative, typename TFunctor>
    TState IntegrateRK4(const TState& q, TFunctor f, float h)
    {
      TDerivative k1 = f(q) * h;
      TDerivative k2 = f(q + k1 * 0.5f) * h;
      TDerivative k3 = f(q + k2 * 0.5f) * h;
      TDerivative k4 = f(q + k3) * h;
      
      return q + (k1 + (k2 + k3) * 2.0f + k4) * (1.0f / 6.0f);
    }
  }
}

#endif//__RK4_H
