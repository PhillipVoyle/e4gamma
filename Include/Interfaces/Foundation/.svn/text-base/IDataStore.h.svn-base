#ifndef _E4Gamma_IDATASTORE_H
#define _E4Gamma_IDATASTORE_H

#include <string>
using namespace std;

#include <Interfaces/Foundation/IUnknown.h>

namespace E4Gamma {
  
  class ITableReader;
  class ISequenceReader;

  class IDataStore: public IUnknown
  {
  public:
    virtual ~IDataStore() {}
    
    virtual SharedPtr<ITableReader> OpenTable(const string& sName) = 0;
    virtual SharedPtr<ISequenceReader> OpenSequence(const string& sName) = 0;
    virtual bool ReadString(const string& sName, string& sValue) = 0;
  };

}

#endif//_E4Gamma_IDATASTORE_H
