//
//  main.cpp
//  Unk
//
//  Created by Phillip Voyle on 4/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <Interfaces/Foundation/IUnknown.h>
#include <iostream>
#include <string>

using namespace std;
using namespace E4Gamma;

class CTest: public IUnknown {
protected:
  string m_s;
  virtual ~CTest()
  {
    cout << "~CTest(" << m_s << ")" << endl;
  }
public:
  CTest(const string&s):m_s(s)
  {
    cout << "CTest(" << m_s <<")" << endl;
  }
};

class DTest: public CTest
{
public:
  virtual ~DTest()
  {
    cout << "~D" << endl;
  }
  
  DTest(const string& s):CTest(s)
  {
    cout << "D" << endl;
  }
};

int main(int argc, char** argv)
{
  SharedPtr<DTest> spTest = new IUnknownImpl<DTest>("A");
  cout << "test" << endl;
  SharedPtr<CTest> spTest2;
  spTest2 = spTest;
  cout << "test2" << endl;
  spTest = nullptr;
  cout << "test3" << endl;
  
  spTest2 = new IUnknownImpl<CTest>("B");
  
  spTest2 = spTest2;
  
  cout << "test4" << endl;
}

