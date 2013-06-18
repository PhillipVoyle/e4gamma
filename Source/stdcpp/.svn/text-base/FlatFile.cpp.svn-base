#include <Interfaces/Foundation/ITableReader.h>
#include <stdcpp/FlatFile.h>

#include <iostream>
using namespace std;

namespace E4Gamma {
  
  CFlatFile::CFlatFile(const string& sFilename): m_fStream(sFilename.c_str(), std::ios::in | std::ios::binary)
  {
    if(m_fStream.fail())
    {
      cout << "error loading " << sFilename << endl;
    }
  }
  
  CFlatFile::~CFlatFile() {}
  
  bool CFlatFile::ReadU8(unsigned char&u8)
  {
    if(m_fStream.fail())
    {
      return false;
    }
    else
    {
      m_fStream.read((char*)&u8, (std::streamsize)1);
      return !m_fStream.fail();
    }
  }
  
  bool CFlatFile::ReadI8(char&i8)
  {
    return ReadU8((unsigned char&)i8);
  }
  
  bool CFlatFile::ReadU16(unsigned short&u16)
  {
    unsigned short u16Result;
    for(int nBytes = 0; nBytes < 2; nBytes ++)
    {
      unsigned char u8 = 0;
      if(!ReadU8(u8))
      {
        return false;
      }
      u16Result = (u16Result << 8)|(unsigned short)u8;
    }
    u16 = u16Result;
    return true;
  }
  
  bool CFlatFile::ReadI16(short&i16)
  {
    return ReadU16((unsigned short&) i16);
  }
  
  bool CFlatFile::ReadU32(unsigned&u32)
  {
    unsigned u32Result;
    for(int nBytes = 0; nBytes < 2; nBytes ++)
    {
      unsigned char u8 = 0;
      if(!ReadU8(u8))
      {
        return false;
      }
      u32Result = (u32Result << 8)|(unsigned)u8;
    }
    u32 = u32Result;
    return true;
  }
  
  bool CFlatFile::ReadI32(int&i32)
  {
    return ReadU32((unsigned&)i32);
  }
  
  bool CFlatFile::ReadString(string& sValue)
  {
    int nStringLength = 0;
    if(!ReadI32(nStringLength))
    {
      return false;
    }
    
    sValue.reserve(nStringLength);
    
    for(int n = 0; n < nStringLength; n++)
    {
      char cChar = '\0';
      if(!ReadI8(cChar))
      {
        return false;
      }
      sValue += cChar;
    }
    return true;
  }
  
  SharedPtr<ITableReader> CFlatFile::OpenTable()
  {
    return nullptr;
  }
  
  SharedPtr<ISequenceReader> CFlatFile::OpenSequence()
  {
    return nullptr;
  }
  
  bool CFlatFile::ReadFloat(float& fValue)
  {
    return false;
  }
  bool CFlatFile::ReadDouble(double& lfValue)
  {
    return false;
  }
  
  bool CFlatFile::Close()
  {
    return true;
  }
}