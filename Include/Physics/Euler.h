//
//  Euler.h
//  E4Gamma
//
//  Created by Phillip Voyle on 26/06/13.
//
//

#ifndef E4Gamma_Euler_h
#define E4Gamma_Euler_h

namespace E4Gamma
{
  namespace Physics
  {
    //
    // this template function implements the euler integration method
    //

    //using the accumulation method (+=)
    //note the void return type
    template<typename TState, typename TDerivative, typename TFunctor>
    void IntegrateEuler_Accumulate(TState& q, TFunctor f, float h)
    {
      q += f(q) * h;
    }

    //offloading accumulation to the caller (note that q is const)
    //note the const TState argument and result type
    template<typename TState, typename TDerivative, typename TFunctor>
    TState IntegrateEuler(const TState& q, TFunctor f, float h)
    {
      return q + f(q) * h;
    }
  }
}

#endif
