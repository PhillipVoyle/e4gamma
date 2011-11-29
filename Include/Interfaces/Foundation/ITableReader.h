#ifndef _E4Gamma_ITABLEREADER_H
#define _E4Gamma_ITABLEREADER_H

#include <string>
using namespace std;

#include <Interfaces/Foundation/IDataStore.h>

namespace E4Gamma {
  
  class ITableReader;
  class ISequenceReader;
  
  class ITableReader: public IDataStore
  {
  public:
    virtual ~ITableReader() {}
    
    virtual bool ReadU8(const string& sName, unsigned char&u8) = 0;
    virtual bool ReadI8(const string& sName, char&i8) = 0;
    virtual bool ReadU16(const string& sName, unsigned short&u16) = 0;
    virtual bool ReadI16(const string& sName, short&i16) = 0;
    virtual bool ReadU32(const string& sName, unsigned int&u32) = 0;
    virtual bool ReadI32(const string& sName, int&i32) = 0;
    
    virtual bool Close() = 0;
  };
  
}

#endif//_E4Gamma_ITABLEREADER_H