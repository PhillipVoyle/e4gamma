#include <GL/GLModel.h>

namespace E4Gamma
{
  CGLModel::CGLModel(CGLRenderer* pRenderer, SharedPtr<IDataStore> pDataStore, const std::string& sModel)
  {
    //pDataStore->OpenSequence(szModel);
    
  }
  
  CGLModel::~CGLModel()
  {
  }
  
  void CGLModel::RenderPose(IPose* pPose)
  {
  }
}