#include <stdcpp/FileSystemDataStore.h>
#include <stdcpp/FlatFile.h>
#include <stdcpp/TextFile.h>
#include <fstream>
#include <Interfaces/Foundation/ITableReader.h>

using namespace std;

namespace E4Gamma {
  
  CFileSystemDataStore::CFileSystemDataStore()
  {
  }

  CFileSystemDataStore::~CFileSystemDataStore()
  {
  }

  SharedPtr<ITableReader> CFileSystemDataStore::OpenTable(const string& sName)
  {
    return nullptr; //not implemented yet - use xml flat file maybe?
  }

  SharedPtr<ISequenceReader> CFileSystemDataStore::OpenSequence(const string& sName)
  {
    return new IUnknownImpl<CFlatFile>(sName);
  }
  
  SharedPtr<ISequenceReader> CFileSystemDataStore::OpenTextSequence(const string& sName)
  {
    return new IUnknownImpl<CTextFile>(sName);
  }
   
  bool CFileSystemDataStore::ReadString(const string& sName, string& sValue)
  {
    fstream file(sName.c_str());
    sValue = string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return true;
  }
}
