#ifndef _E4Gamma_FLATFILE_H
#define _E4Gamma_FLATFILE_H

#include <string>
#include <fstream>
#include <Interfaces/Foundation/ISequenceReader.h>

namespace E4Gamma {
  class CFlatFile: public ISequenceReader
  {
    std::fstream m_fStream;
  public:
    CFlatFile(const std::string& sFlatFile);
    virtual ~CFlatFile();
    
    bool ReadU8(unsigned char&u8);
    bool ReadI8(char&i8);
    bool ReadU16(unsigned short&u16);
    bool ReadI16(short&i16);
    bool ReadU32(unsigned int&u32);
    bool ReadI32(int&i32);
    bool ReadString(string& sValue);
    
    ITableReader* OpenTable();
    ISequenceReader* OpenSequence();
    bool Close();    
  };
}

#endif//_E4Gamma_FLATFILE_H
