#ifndef _E4Gamma_IDATASTORE_H
#define _E4Gamma_IDATASTORE_H

#include <string>
using namespace std;

namespace E4Gamma {
  
  class ITableReader;
  class ISequenceReader;

  class IDataStore
  {
  public:
    virtual ~IDataStore() {}
    
    virtual ITableReader* OpenTable(const string& sName) = 0;
    virtual ISequenceReader* OpenSequence(const string& sName) = 0;
    virtual bool ReadString(const string& sName, string& sValue) = 0;
  };

}

#endif//_E4Gamma_IDATASTORE_H
