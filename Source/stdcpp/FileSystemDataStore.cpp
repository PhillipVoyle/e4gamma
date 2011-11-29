#include <stdcpp/FileSystemDataStore.h>
#include <stdcpp/FlatFile.h>

namespace E4Gamma {
  
  CFileSystemDataStore::CFileSystemDataStore(const string& sWorkingDir):
    m_sWorkingDir(sWorkingDir)
  {
  }

  CFileSystemDataStore::~CFileSystemDataStore()
  {
  }

  ITableReader* CFileSystemDataStore::OpenTable(const string& sName)
  {
    return NULL; //not implemented yet - use xml flat file maybe?
  }

  ISequenceReader* CFileSystemDataStore::OpenSequence(const string& sName)
  {
    return new CFlatFile(sName);
  }
    
}
