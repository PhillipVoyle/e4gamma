
#ifndef _E4Gamma_ROOTOBJECT_H
#define _E4Gamma_ROOTOBJECT_H

#include <cstddef>

namespace E4Gamma
{
  class IUnknown
  {
  protected:
    virtual ~IUnknown() {}
    
  public:
    virtual unsigned Release() = 0;
    virtual void AddRef() = 0;
  };

  template<class T>
  class IUnknownImpl: public T
  {
  protected:
    int m_nRefCount;
    
  public:
    virtual ~IUnknownImpl()
    {
    }
    
    template<class... A>
    IUnknownImpl(A... a):T(a...)
    {
      m_nRefCount = 0;
    }
    
    IUnknownImpl(): T()
    {
      m_nRefCount = 0;
    }
    
    unsigned Release()
    {
      int nResult = --m_nRefCount;
      if(nResult == 0)
      {
        delete this;
      }
      return nResult;
    }
    
    void AddRef()
    {
      m_nRefCount++;
    }
  };
  
  template<class T>
  class IUnknownNull: public T
  {
  public:
    virtual ~IUnknownNull() {}
    unsigned Release() {return 0;}
    void AddRef(){}
  };
  
  template<class T>
  class SharedPtr
  {
  public:
    T* m_ptr;
    
    SharedPtr()
    {
      m_ptr = nullptr;
    }
    
    SharedPtr(std::nullptr_t ptr)
    {
      m_ptr = nullptr;
    }
    
    template<class TSuper>
    SharedPtr(const TSuper* ptr)
    {
      m_ptr = const_cast<TSuper*>(ptr);
      if(m_ptr != nullptr)
      {
        m_ptr->AddRef();
      }
    }
    
    template<class TSuper>
    SharedPtr(const SharedPtr<TSuper>& ptr)
    {
      m_ptr = const_cast<TSuper*>(ptr.m_ptr);
      if(m_ptr != nullptr)
      {
        m_ptr->AddRef();
      }
    }
    
    SharedPtr(const SharedPtr<T>& ptr)
    {
      m_ptr = const_cast<T*>(ptr.m_ptr);
      if(m_ptr != nullptr)
      {
        m_ptr->AddRef();
      }
    }
    
    T& operator* () const
    {
      return *const_cast<T*>(m_ptr);
    }
    
    T* operator-> () const
    {    
      return const_cast<T*>(m_ptr);
    }
    
    
    void operator=(const std::nullptr_t ptr)
    {
      if(m_ptr != nullptr)
      {
        m_ptr->Release();
      }
      m_ptr = ptr;
    }
    
    template<class TSuper>
    operator TSuper* () const
    {
      return const_cast<TSuper*>(m_ptr);
    }
    
    template<class TSuper>
    void operator=(const TSuper* ptr)
    {
      if(ptr != nullptr)
      {
        const_cast<TSuper*>(ptr)->AddRef(); //in case the pointers are related somehow
      }
      if(m_ptr != nullptr)
      {
        m_ptr->Release();
      }
      m_ptr = const_cast<TSuper*>(ptr);
    }

    template<class TSuper>
    void operator=(const SharedPtr<TSuper> &ptr)
    {
      if(ptr.m_ptr != nullptr)
      {
        const_cast<TSuper*>(ptr.m_ptr)->AddRef();
      }
      if(m_ptr != nullptr)
      {
        m_ptr->Release();
      }
      m_ptr = const_cast<TSuper*>(ptr.m_ptr);
    }

    void operator=(const SharedPtr<T> &ptr)
    {
      if(ptr.m_ptr != nullptr)
      {
        const_cast<T*>(ptr.m_ptr)->AddRef();
      }
      if(m_ptr != nullptr)
      {
        m_ptr->Release();
      }
      m_ptr = const_cast<T*>(ptr.m_ptr);
    }
    
    ~SharedPtr()
    {
      if(m_ptr != nullptr)
      {
        m_ptr->Release();
      }
      m_ptr = nullptr;
    }
  };
};

    



#endif//_E4Gamma_ROOTOBJECT_H

