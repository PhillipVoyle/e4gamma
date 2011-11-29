#ifndef _E4Gamma_ISEQUENCEREADER_H
#define _E4Gamma_ISEQUENCEREADER_H

#include <string>
using namespace std;

namespace E4Gamma
{
  class ITableReader;
  
  class ISequenceReader
  {
  public:
    virtual ~ISequenceReader() {}
    
    virtual bool ReadU8(unsigned char&u8) = 0;
    virtual bool ReadI8(char&i8) = 0;
    virtual bool ReadU16(unsigned short&u16) = 0;
    virtual bool ReadI16(short&i16) = 0;
    virtual bool ReadU32(unsigned int&u32) = 0;
    virtual bool ReadI32(int&i32) = 0;
    virtual bool ReadString(string& sValue) = 0;
    
    virtual ITableReader* OpenTable() = 0;
    virtual ISequenceReader* OpenSequence() = 0;
    virtual bool Close() = 0;
  };
}
#endif//_E4Gamma_ISEQUENCEREADER_H
