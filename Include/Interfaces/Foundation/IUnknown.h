
#ifndef _E4Gamma_ROOTOBJECT_H
#define _E4Gamma_ROOTOBJECT_H

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
  class SharedPtr
  {
  protected:
    T* m_ptr;
    
  public:
    
    SharedPtr()
    {
      m_ptr = nullptr;
    }
    SharedPtr(const T* ptr)
    {
      m_ptr = const_cast<T*>(ptr);
      m_ptr->AddRef();
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
    
    operator T* () const
    {
      return const_cast<T*>(m_ptr);
    }
    
    void operator=(const T* ptr)
    {
      if(ptr != nullptr)
      {
        const_cast<T*>(ptr)->AddRef(); //in case the pointers are related somehow
      }
      if(m_ptr != nullptr)
      {
        m_ptr->Release();
      }
      m_ptr = const_cast<T*>(ptr);
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

