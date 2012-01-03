
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
    
    virtual void PostConstruct() {}
  };
  
  template<class T>
  class Shareable: public IUnknown, public T
  {
  public:
    
    template<class... A>
    Shareable(A... a):T(a...)
    {
    }
    
    Shareable():T()
    {
    }
    
    virtual ~Shareable() {}
  };

  template<class T>
  class AggregateImpl: public T
  {
    IUnknown* m_pEnclosing;
  public:
    
    virtual ~AggregateImpl() {}
    
    template<class... A>
    AggregateImpl(IUnknown* pEnclosing, A... a):m_pEnclosing(pEnclosing),T(a...)
    {
      T::PostConstruct();
    }
    
    AggregateImpl(IUnknown* pEnclosing):m_pEnclosing(pEnclosing), T()
    {
    }
    
    unsigned Release()
    {
      return m_pEnclosing->Release();
    }
    
    void AddRef()
    {
      m_pEnclosing->AddRef();
    }
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
      T::PostConstruct();
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
    
    SharedPtr(const T* ptr)
    {
      m_ptr = const_cast<T*>(ptr);
      if(m_ptr != nullptr)
      {
        IUnknown* pAdd = m_ptr;
        pAdd->AddRef();
      }
    }
    
    template<class TSuper>
    SharedPtr(const TSuper* ptr)
    {
      m_ptr = const_cast<TSuper*>(ptr);
      if(m_ptr != nullptr)
      {
        IUnknown* pAdd = m_ptr;
        pAdd->AddRef();
      }
    }
    
    template<class TSuper>
    SharedPtr(const SharedPtr<TSuper>& ptr)
    {
      m_ptr = const_cast<TSuper*>(ptr.m_ptr);
      if(m_ptr != nullptr)
      {
        IUnknown* pAdd = m_ptr;
        pAdd->AddRef();
      }
    }
    
    SharedPtr(const SharedPtr<T>& ptr)
    {
      m_ptr = const_cast<T*>(ptr.m_ptr);
      if(m_ptr != nullptr)
      {
        IUnknown* pAdd = m_ptr;
        pAdd->AddRef();
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
    
    template<class TSuper>
    bool operator != (const TSuper* ptr)
    {
      return m_ptr != ptr;
    }
    
    bool operator != (const T* ptr)
    {
      return m_ptr != ptr;
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
        ptr.m_ptr->AddRef();
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
        ptr.m_ptr->AddRef();
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
        IUnknown* pRelease = (IUnknown*)m_ptr; //we already know this is a safe type, so we can cast it and use the virtual method.
        pRelease->Release();
      }
      m_ptr = nullptr;
    }
  };
};

    



#endif//_E4Gamma_ROOTOBJECT_H

