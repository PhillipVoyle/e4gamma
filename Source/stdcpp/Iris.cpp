#include <stdcpp/Iris.h>
#include <Interfaces/Foundation/IDataStore.h>
#include <Interfaces/Foundation/ISequenceReader.h>

#include <iostream>
using namespace std;

namespace E4Gamma {
    
  const short kMagic = 474;
  const char kStorageVERBATIM = 0;
  const char kStorageRLE = 1;

  const char kzsizeGreyscale = 1;
  const char kzsizeRGB = 3;
  const char kzsizeRGBA = 4;

  const char kColormapNormal = 0;
  const char kColormapDithered = 1;
  const char kColormapScreen = 2;
  const char kColormapColormap = 3;

  static unsigned short ReadShort(ISequenceReader* pSeqRead)
  {
    unsigned char buf[2] = {0, 0};
    pSeqRead->ReadU8(buf[0]);
    pSeqRead->ReadU8(buf[1]);
    
    return (buf[0]<<8)+(buf[1]<<0);
  }

  static long ReadLong(ISequenceReader* pSeqRead)
  {
    unsigned char buf[4] = {0, 0, 0, 0};
    pSeqRead->ReadU8(buf[0]);
    pSeqRead->ReadU8(buf[1]);
    pSeqRead->ReadU8(buf[2]);
    pSeqRead->ReadU8(buf[3]);
    
    return (buf[0]<<24)+(buf[1]<<16)+(buf[2]<<8)+(buf[3]<<0);
  }

  static unsigned char ReadChar(ISequenceReader* pSeqRead)
  {
    unsigned char buf = 0;
    pSeqRead->ReadU8(buf);
    return buf;
  }

  CIrisFile::CIrisFile(const char* szFilename, IDataStore* pDataStore)
  {
    ISequenceReader* pReader = pDataStore->OpenSequence(szFilename);
    if(pReader != NULL)
    {
      /*short magic =*/ ReadShort(pReader);
      /*char storage = (char)*/ ReadChar(pReader);
      /*char bpc = (char)*/ ReadChar(pReader);
      /*unsigned short dimension =*/ ReadShort(pReader);
      unsigned short xsize = ReadShort(pReader);
      unsigned short ysize = ReadShort(pReader);
      unsigned short zsize = ReadShort(pReader);
      /*long pixmin =*/ ReadLong(pReader);
      /*long pixmax =*/ ReadLong(pReader);
      /*long dummy1 =*/ ReadLong(pReader);
      char imagename[80];
      for(int nByte = 0; nByte < 80; nByte++)
      {
        pReader->ReadI8(imagename[nByte]);
      }
      /*long colormap =*/ ReadLong(pReader);
      char dummy2[404]; //expecting zeroes here
      
      for(int nByte = 0; nByte < 404; nByte++)
      {
        pReader->ReadI8(dummy2[nByte]);
      }
      
      long nSize =((long) xsize) * ((long) ysize) * ((long) zsize);
      m_pPixels = new unsigned char[nSize];
      m_nWidth = xsize;
      m_nHeight = ysize;
      
      for(int z = 0; (z < zsize) && (z < 4); z++)
      {
        for(int y = 0; y < ysize; y ++)
        {
          for(int x = 0; x < xsize; x++)
          {
            pReader->ReadU8(((unsigned char*)m_pPixels)[((x + (y * xsize)) * 4) + z]); 
          }
        }
      }
      
      delete pReader;
    }
  }
  
  CIrisFile::~CIrisFile()
  {
    delete[]m_pPixels;
  }
}
