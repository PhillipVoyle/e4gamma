#include <stdcpp/FileSystemDataStore.h>
#include <stdcpp/FlatFile.h>
#include <fstream>
using namespace std;

namespace E4Gamma {
  
  CFileSystemDataStore::CFileSystemDataStore()
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
    return new IUnknownImpl<CFlatFile>(sName);
  }
   
  bool CFileSystemDataStore::ReadString(const string& sName, string& sValue)
  {
    fstream file(sName.c_str());
    sValue = string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return true;
  }
}
