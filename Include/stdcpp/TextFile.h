//
//  TextFile.h
//  E4Gamma
//
//  Created by Phillip Voyle on 18/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef E4Gamma_TextFile_h
#define E4Gamma_TextFile_h

#include <string>
#include <fstream>
#include <Interfaces/Foundation/ISequenceReader.h>

namespace E4Gamma {
  class CTextFile: public ISequenceReader
  {
    std::fstream m_fStream;
  public:
    CTextFile(const std::string& sTextFile);
    virtual ~CTextFile();
    
    bool ReadU8(unsigned char&u8);
    bool ReadI8(char&i8);
    bool ReadU16(unsigned short&u16);
    bool ReadI16(short&i16);
    bool ReadU32(unsigned int&u32);
    bool ReadI32(int&i32);
    bool ReadString(string& sValue);
    bool ReadFloat(float& fValue);
    bool ReadDouble(double& lfValue);
    
    SharedPtr<ITableReader> OpenTable();
    SharedPtr<ISequenceReader> OpenSequence();
    bool Close();    
  };
}

#endif
