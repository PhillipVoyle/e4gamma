//
//  IFunction.h
//  E4Gamma
//
//  Created by Stacey Voyle on 28/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_IFunction_h
#define E4Gamma_IFunction_h

#include <Interfaces/Foundation/IUnknown.h>
#include <utility>
namespace E4Gamma
{
  template<typename TResult, typename...TParms>
  class IFunction: public IUnknown
  {
  public:
    virtual ~IFunction() {}
    virtual TResult Execute(TParms...) = 0;
    
  };



  template<typename TResult, typename...TParms>
  class FunctionPtr: public SharedPtr<IFunction<TParms...>>
  {
    TResult operator()(TParms&&...parms)
    {
      return (*this)->Execute(std::forward(parms)...);
    }
  };

  template <typename...TParms>
  class FunctionPtr<void, TParms...>: public SharedPtr<IFunction<TParms...>>
  {
    void operator()(TParms&&...parms)
    {
      (*this)->Execute(std::forward(parms)...);
    }
  };
}

#endif
