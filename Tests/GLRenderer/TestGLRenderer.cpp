
#include <GL/GLRenderer.h>
#include <Interfaces/Renderer/IModel.h>
#include <Interfaces/Renderer/ICamera.h>
#include <Interfaces/Foundation/IFrame.h>
#include <Interfaces/Renderer/ILight.h>

#include <Interfaces/Renderer/IMaterial.h>
#include <Interfaces/Renderer/IMesh.h>

#include <Interfaces/Foundation/ISequenceReader.h>

#include <stdcpp/FileSystemDataStore.h>
#include <Math/Quaternion.h>

#include <iostream>
#include <cmath>
using namespace std;
using namespace E4Gamma;


//tell g++ not to warn me
void init();
void display();
void cleanup();
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);

SharedPtr<CGLRenderer> g_pRenderer = nullptr;
//SharedPtr<IModel> g_pModel = nullptr;
SharedPtr<IMesh> g_pMesh = nullptr;
SharedPtr<IMesh> g_pOccluder = nullptr;
SharedPtr<IMaterial> g_ambientMaterial = nullptr;
SharedPtr<IMaterial> g_pPhongMaterial = nullptr;
SharedPtr<IMaterial> g_depthMaterial = nullptr;

SharedPtr<ICamera> g_pCamera = nullptr;
SharedPtr<ILight> g_pLight = nullptr;
SharedPtr<ILight> g_pLight2 = nullptr;

void init()
{
  glClearColor(0.3,0.3,0.3,1.0);
  
  glEnable(GL_TEXTURE_2D);
  //glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glDepthFunc(GL_LEQUAL);
  
  glClearStencil(0x00);
  g_pRenderer = new IUnknownImpl<CGLRenderer>();
  
  //g_pMesh = g_pRenderer->LoadMesh("Data/Meshes/shadowtest.mesh");
  //g_pPhongMaterial = g_pRenderer->LoadMaterial("Data/Materials/shadowtest.material");

  g_pMesh = g_pRenderer->LoadMesh("Data/Meshes/level.mesh");
  g_pPhongMaterial = g_pRenderer->LoadMaterial("Data/Materials/phong.material");
  g_ambientMaterial = g_pRenderer->LoadMaterial("Data/Materials/ambientonly.material");
  g_depthMaterial = g_pRenderer->LoadMaterial("Data/Materials/depthonly.material");
  
  float fovy = 30.0;
  float zfar = 1000.f;
  float znear = 0.1f;
  float aspect = 800.0f / 600.0f;
  
  g_pCamera = g_pRenderer->CreateCamera(aspect, znear, zfar, fovy);
  SharedPtr<IFrame> pFrame = g_pCamera->GetFrame();
  pFrame->SetPosition(Vector(0.0f, 0.0f, 0.0f));
  pFrame = nullptr;
  
  g_pLight = g_pRenderer->CreateLight();
  g_pLight2 = g_pRenderer->CreateLight();
  auto frame = g_pLight2->GetFrame();
  frame->SetPosition(Vector(0.0f, 0.0f, 8.0f));
}

int nLastX = 0;
int nLastY = 0;

float fFwd = 0;
float fBack = 0;
float fStrafeLeft = 0;
float fStrafeRight = 0;

float fTurnLeft = 0;
float fTurnRight = 0;

float fPitchUp = 0;
float fPitchDown = 0;

Quaternion qYaw;

float fActualPitch = 0;

int nPreviousTime = 0;

void display()
{
  int nTimeElapsed = glutGet(GLUT_ELAPSED_TIME);
  float fFrameTime = ((float)(nTimeElapsed - nPreviousTime))/1000.0f;
  nPreviousTime = nTimeElapsed;
  
  static float fF = 1.0f;
  static float dF = 5;
  
  if(fFrameTime > 0.0f)
  {
    SharedPtr<IFrame> pFrame = g_pCamera->GetFrame();
    
    qYaw = Quaternion::Transform(Quaternion::FromAxisAngle(Vector::J, (fTurnLeft - fTurnRight) * fFrameTime), qYaw);
    fActualPitch += (fPitchUp - fPitchDown) * fFrameTime;
    
    const float fLimitPitch = 90.0f * M_PI / 180.0f;
    
    if(fActualPitch > fLimitPitch)
    {
      fActualPitch = fLimitPitch;
    }
    else if(fActualPitch < -fLimitPitch)
    {
      fActualPitch = -fLimitPitch;
    }
    
    pFrame->SetOrientation(Quaternion::Transform(Quaternion::FromAxisAngle(Vector::I, fActualPitch), qYaw).normalize());
    pFrame->TranslateWorld(Quaternion::Transform(qYaw, Vector(fFrameTime * (fStrafeRight - fStrafeLeft), 0, fFrameTime * (fFwd - fBack))));
    
    Matrix4 mFrame = pFrame->GetTransform();
    
    fF += dF * fFrameTime;
    
    if(fF > 11.0f)
    {
      dF = -5;
    }
    
    if(fF < -0.0f)
    {
      dF = 5; 
    }
    
    pFrame = g_pLight->GetFrame();
    pFrame->SetPosition(Vector(0.0f, -0.3f, fF));

    auto frame = g_pLight2->GetFrame();
    frame->SetPosition(g_pCamera->GetFrame()->GetPosition());

  }
  
  g_pCamera->Select();  
  
  glClearDepth(1.0);
  g_pRenderer->BeginScene();
  glClear(GL_DEPTH_BUFFER_BIT);

//* 
  bool bRenderDepth = true;
  if(bRenderDepth)
  {
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_ONE);

    //Render depth-only geometry
    g_ambientMaterial->RenderSet();
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    //glColorMask(0, 0, 0, 0);
    glDisable(GL_STENCIL_TEST);
    g_pMesh->RenderPose(nullptr);
  }

  SharedPtr<ILight> lights[] = {g_pLight, g_pLight2};
  for(auto light:lights)
  {
    bool bRenderStencils = true;
    light->Select();
    auto shadowMesh = g_pMesh->CreateShadowVolume();

    if(bRenderStencils)
    {
      glClear(GL_STENCIL_BUFFER_BIT);
      glEnable(GL_STENCIL_TEST);

      glDepthFunc(GL_LESS);  
      glDepthMask(GL_FALSE);
      glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
      glDisable(GL_LIGHTING);
      
      glEnable(GL_DEPTH_CLAMP);
      
      glStencilFuncSeparate(GL_BACK, GL_ALWAYS, 0x00, 0xff);
      glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_INCR_WRAP);
      glStencilFuncSeparate(GL_FRONT, GL_ALWAYS, 0x00, 0xff);
      glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_DECR_WRAP);
      
      glDisable(GL_DEPTH_TEST);
      glDepthMask(GL_FALSE);  
      
      
      glCullFace(GL_NONE);
      
      glEnable(GL_DEPTH_TEST);
      
      g_depthMaterial->RenderSet();
      shadowMesh->RenderPose(nullptr);
      
      glStencilFuncSeparate(GL_BACK, GL_EQUAL, 0x00, 0xff);
      glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_KEEP);
      glStencilFuncSeparate(GL_FRONT, GL_EQUAL, 0x00, 0xff);
      glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_KEEP); 
      
      glDisable(GL_DEPTH_CLAMP);
      
      glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    
    }
    
    bool bRenderLitGeometry = true;
    if(bRenderLitGeometry)
    {
      light->Select();  
      g_pPhongMaterial->RenderSet();
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_COLOR, GL_ONE);

      glEnable(GL_DEPTH_TEST);
      if(bRenderDepth)
      {
        glDepthMask(GL_FALSE); 
        glDepthFunc(GL_EQUAL);
      }
      else
      {
        glDepthMask(GL_TRUE); 
        glDepthFunc(GL_LESS);
      }
      glColorMask(1, 1, 1, 1);
      glEnable(GL_LIGHTING);
    
      g_pMesh->RenderPose(nullptr);
    }
    
    if(!bRenderStencils)
    {
      glDepthFunc(GL_LESS);
      g_depthMaterial->RenderSet();
      glDisable(GL_STENCIL_TEST);
      glCullFace(GL_NONE);
      
      glEnable(GL_DEPTH_CLAMP);
      glEnable(GL_DEPTH_TEST);
      glDepthMask(GL_FALSE);
      glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
      
      shadowMesh->RenderPose(nullptr);
      
      glDisable(GL_DEPTH_CLAMP);
      glDisable(GL_BLEND);
    }
  }

  g_pRenderer->Present();
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);  
  glDisable(GL_STENCIL_TEST);
  glColorMask(1, 1, 1, 1);
  
	glutPostRedisplay();//Tell the program to refresh
}

void cleanup()
{
  g_pLight = nullptr;
  g_pCamera = nullptr;
  
  //g_pModel = nullptr;
  
  g_pMesh = nullptr;
  g_pOccluder = nullptr;
  
  g_ambientMaterial = nullptr;
  g_pPhongMaterial = nullptr;
  g_pRenderer = nullptr;
}

void keyDown(unsigned char key, int x, int y)
{
  if((char)key == 'w')
  {
    fFwd = 5.0f;
  }
  else if((char)key == 's')
  {
    fBack = 1.0f;
  }
  else if((char)key == 'a')
  {
    fStrafeLeft = 2.0f;
  }
  else if((char)key == 'd')
  {
    fStrafeRight = 2.0f;
  }
  else if((char)key == 27)
  {
    throw(0);
  }
}

void keyUp(unsigned char key, int x, int y)
{
  if((char)key == 'w')
  {
    fFwd = 0.0f;
  }
  else if((char)key == 's')
  {
    fBack = 0.0f;
  }
  else if((char)key == 'a')
  {
    fStrafeLeft = 0.0f;
  }
  else if((char)key == 'd')
  {
    fStrafeRight = 0.0f;
  }
}

void specialDown(int key, int x, int y)
{
  if(key == GLUT_KEY_UP)
  {
    fPitchUp = 1.0f;
  }
  else if(key == GLUT_KEY_DOWN)
  {
    fPitchDown = 1.0f;
  }
  else if(key == GLUT_KEY_RIGHT)
  {
    fTurnRight = 2.0f;
  }
  else if(key == GLUT_KEY_LEFT)
  {
    fTurnLeft = 2.0f;
  }
}

void specialUp(int key, int x, int y)
{
  if(key == GLUT_KEY_UP)
  {
    fPitchUp = 0.0f;
  }
  else if(key == GLUT_KEY_DOWN)
  {
    fPitchDown = 0.0f;
  }
  else if(key == GLUT_KEY_RIGHT)
  {
    fTurnRight = 0.0f;
  }
  else if(key == GLUT_KEY_LEFT)
  {
    fTurnLeft = 0.0f;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);//initialize GLUT.
  
	glutInitWindowSize(800,600);//define the window size as 800 pixels wide and 600 pixels high
  glutInitWindowPosition(0,0);//Set the window position at (10,50)
  
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH|GLUT_STENCIL);//Set the initial display mode
  glutCreateWindow("TestGLRenderer");//Create our window

	init();//call init()
  
  glutDisplayFunc(display);//tell GLUT what our display function is
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutSpecialFunc(specialDown);
  glutSpecialUpFunc(specialUp);
  
  try
  {
    glutMainLoop();//Tell the program we are not done yet
  }
  catch(...)
  {
  }
  cleanup();
  
  return 0;
}
