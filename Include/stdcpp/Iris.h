#ifndef _E4Gamma_IRIS_H
#define _E4Gamma_IRIS_H

#include <Interfaces/Foundation/IUnknown.h>
#include <string>

namespace E4Gamma {
    
  class IDataStore;

  class CIrisFile
  {
  private:
    int m_nWidth;
    int m_nHeight;
    unsigned char* m_pPixels;
  public:
    CIrisFile(const std::string& szFilename, SharedPtr<IDataStore> pDataStore);
    ~CIrisFile();
    
    int   GetWidth() {return m_nWidth;}
    int   GetHeight(){return m_nHeight;}
    void* GetPixels(){return m_pPixels;}
  };
};

#endif//_E4Gamma_IRIS_H
