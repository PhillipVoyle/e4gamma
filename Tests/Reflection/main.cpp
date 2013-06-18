//
//  main.cpp
//  E4Gamma
//
//  Created by Phillip Voyle on 9/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

/*
#include <iostream>
#include <unordered_map>
#include <array>

using namespace std;

class IReflectedMember;
class IReflectedClass;
class IBoundReflectedMember;

class IReflectedObject
{
public:
  virtual ~IReflectedObject() {}
  virtual IReflectedClass& GetClass() = 0;
};

class IReflectedClass
{
public:
  virtual ~IReflectedClass() {}
  
  virtual IReflectedMember& operator[](const std::string& sMember) = 0;
};

template<typename TResult, typename ... TArgs>
class IReflectedFunction
{
public:
  virtual ~IReflectedFunction() { }
  virtual TResult operator()(TArgs...args) = 0;
};

template<typename ...TArgs>
class IReflectedFunction<void, TArgs...>
{
public:
  virtual ~IReflectedFunction() { }
  virtual void operator()(TArgs...args) = 0;
};

template<typename T>
class IReflectedProperty
{
public:
  virtual ~IReflectedProperty() { }
  virtual void Set(T t) = 0;
  virtual T Get() = 0;
};

class IReflectedMember
{
public:
  virtual ~IReflectedMember() {}
  
  template<typename T>
  void operator=(T t){
    IReflectedProperty<T>*pProperty = dynamic_cast<IReflectedProperty<T>*>(this);
    if(pProperty){
      pProperty->Set(t);
    }
    else{
      throw std::runtime_error("type mismatch");
    }
  }
  
  template<typename T>
  operator T (){
    IReflectedProperty<T>*pProperty = dynamic_cast<IReflectedProperty<T>*>(this);
    if(pProperty){
      return pProperty->Get();
    }
    else{
      throw std::runtime_error("type mismatch");
    }
  }
  
  template<typename T, typename ... TArgs>
  T operator()(TArgs...args){
    IReflectedFunction<T, TArgs...>* pFunction = dynamic_cast<IReflectedFunction<T, TArgs...>*>(this);
    (*pFunction)(args...);
  }
};

class CTest:public IReflectedObject{
public:
  CTest(){
  }
  
  int AMethod(int argc, char** argv){
    return 12345;
  }
};


template<typename TResult, typename TType, typename ... TArgs>
class TReflectedMethod:virtual public IReflectedMember, public IReflectedFunction<TResult, IReflectedObject*, TArgs...>, public IReflectedFunction<TResult, TType*, TArgs...>
{
  TResult (TType::*m_member)(TArgs...);
public:
  virtual ~TReflectedMethod() {}
  TReflectedMethod(TResult (TType::*member)(TArgs...)):m_member(member){
  }
  virtual TResult operator()(IReflectedObject* pThis, TArgs...args){
    TType* pRealThis = dynamic_cast<TType*>(pThis);
    if(pRealThis != nullptr){
      return (operator())(pRealThis, args...);
    }
    throw std::runtime_error("wrong type");
  }
  virtual TResult operator()(TType* pThis, TArgs...args){
    return (pThis->*m_member)(args...);
  }
};

template<typename TType, typename ... TArgs>
class TReflectedMethod<void, TType, TArgs...>:virtual public IReflectedMember, public IReflectedFunction<void, IReflectedObject*, TArgs...>, public IReflectedFunction<void, TType*, TArgs...>
{
  void (TType::*m_member)(TArgs...);
public:
  virtual ~TReflectedMethod() {}
  TReflectedMethod(void (TType::*member)(TArgs...)):m_member(member){
  }
  virtual void operator()(IReflectedObject* pThis, TArgs...args){
    TType* pRealThis = dynamic_cast<TType*>(pThis);
    if(pRealThis != nullptr)
    {
      (operator())(args...);
    }
  }
  virtual void operator()(TType* pThis, TArgs...args){
    (pThis->*m_member)(args...);
  }
};



int main(int argc, char** argv)
{
  std::shared_ptr<IReflectedFunction<int, IReflectedObject*, int, char**>> fpAMethod(new TReflectedMethod<int, CTest, int, char**>(&CTest::AMethod));
  
  CTest test;
  IReflectedObject* pObject = &test;
  cout << (*fpAMethod)(pObject, 1, nullptr) << endl;
}*/

template<typename ... TVars> struct Vars;

template <>
struct Vars<>
{
};

template <typename T>
struct Vars<T> {
  T var;
};

template<typename T, typename ... TRest>
struct Vars<T, TRest ...>
{
  T var;
  Vars<TRest...> rest;
};

int main(int argc, char** argv)
{
}
