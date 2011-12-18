#include <Interfaces/Foundation/ITableReader.h>
#include <stdcpp/TextFile.h>

#include <iostream>
using namespace std;

namespace E4Gamma {
  
  CTextFile::CTextFile(const string& sFilename): m_fStream(sFilename.c_str(), std::ios::in )
  {
    if(m_fStream.fail())
    {
      cout << "error loading " << sFilename << endl;
    }
  }
  
  CTextFile::~CTextFile() {}
  
  bool CTextFile::ReadU8(unsigned char&u8)
  {
    m_fStream >> u8;
    return !m_fStream.fail();
  }
  
  bool CTextFile::ReadI8(char&i8)
  {
    m_fStream >> i8;
    return !m_fStream.fail();
  }
  
  bool CTextFile::ReadU16(unsigned short&u16)
  {
    m_fStream >> u16;
    return !m_fStream.fail();
  }
  
  bool CTextFile::ReadI16(short&i16)
  {
    m_fStream >> i16;
    return !m_fStream.fail();
  }
  
  bool CTextFile::ReadU32(unsigned&u32)
  {
    m_fStream >> u32;
    return !m_fStream.fail();
  }
  
  bool CTextFile::ReadI32(int&i32)
  {
    m_fStream >> i32;
    return !m_fStream.fail();
  }
  
  bool CTextFile::ReadString(string& sValue)
  {
    m_fStream >> sValue;
    return !m_fStream.fail();
  }
  
  SharedPtr<ITableReader> CTextFile::OpenTable()
  {
    return nullptr;
  }
  
  SharedPtr<ISequenceReader> CTextFile::OpenSequence()
  {
    return nullptr;
  }
  
  bool CTextFile::ReadFloat(float& fValue)
  {
    m_fStream >> fValue;
    return !m_fStream.fail();
  }
  
  bool CTextFile::ReadDouble(double& lfValue)
  {
    m_fStream >> lfValue;
    return !m_fStream.fail();
  }
  
  bool CTextFile::Close()
  {
    return true;
  }
  
  
  
  
}