#ifndef _E4Gamma_FILESYSTEMDATASTORE_H
#define _E4Gamma_FILESYSTEMDATASTORE_H

#include <Interfaces/Foundation/IDataStore.h>

namespace E4Gamma {
  class CFileSystemDataStore: public IDataStore
  {
  public:
    string m_sWorkingDir;
  public:
    CFileSystemDataStore(const string& sWorkingDir);
    virtual ~CFileSystemDataStore();
    
    ITableReader* OpenTable(const string& sName);
    ISequenceReader* OpenSequence(const string& sName);
    bool ReadString(const string& sName, string& sValue);
  };
}

#endif//_E4Gamma_FILESYSTEMDATASTORE_H
