
#include <GL/GLRenderer.h>
#include <Interfaces/Renderer/IModel.h>
#include <Interfaces/Renderer/ICamera.h>
#include <Interfaces/Foundation/IFrame.h>
#include <Interfaces/Renderer/ILight.h>

#include <Interfaces/Foundation/ISequenceReader.h>

#include <stdcpp/FileSystemDataStore.h>
#include <iostream>
using namespace std;
using namespace E4Gamma;

#include <GLUT/glut.h>

//tell g++ not to warn me
void init();
void display();
void cleanup();

SharedPtr<CGLRenderer> g_pRenderer = nullptr;
SharedPtr<IModel> g_pModel = nullptr;
SharedPtr<ICamera> g_pCamera = nullptr;
SharedPtr<ILight> g_pLight = nullptr;

void init()
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glDepthFunc(GL_LEQUAL);
  
  g_pRenderer = new IUnknownImpl<CGLRenderer>();
  g_pModel = g_pRenderer->LoadModel("Data/Models/test.model");
  
  float fovy = 30.0;
  float zfar = 10000.f;
  float znear = 0.1f;
  float aspect = 800.0f / 600.0f;
  
  g_pCamera = g_pRenderer->CreateCamera(aspect, znear, zfar, fovy);
  SharedPtr<IFrame> pFrame = g_pCamera->GetFrame();
  pFrame->SetPosition(Vector(0.0f, 0.0f, -10.0f));
  pFrame = nullptr;
  
  g_pLight = g_pRenderer->CreateLight();
  //pFrame = g_pLight->GetFrame();
  //pFrame = nullptr;
}

float g_theta = 0.0f;
float g_dTheta = 0.001;

void display()
{
  g_pRenderer->BeginScene();
  
  SharedPtr<IFrame> pFrame = g_pLight->GetFrame();
  
  g_theta += g_dTheta;
  
  float fsintheta = sinf(g_theta);
  float fcostheta = cosf(g_theta);
  
  pFrame->SetPosition(Vector(5.0f * fsintheta, 5.0f, 5.0f * fcostheta));
    
  g_pLight->Select();  
  g_pCamera->Select();
  
  g_pModel->RenderPose(nullptr);
  g_pRenderer->Present();
  
	glutPostRedisplay();//Tell the program to refresh
}

void cleanup()
{
  g_pLight = nullptr;
  g_pCamera = nullptr;
  g_pModel = nullptr;
  g_pRenderer = nullptr;
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);//initialize GLUT.
  
	glutInitWindowSize(800,600);//define the window size as 800 pixels wide and 600 pixels high
  glutInitWindowPosition(10,50);//Set the window position at (10,50)
  
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB| GLUT_DEPTH);//Set the initial display mode
  
	glutCreateWindow("TestGLRenderer");//Create our window
  
	init();//call init()
  
	glutDisplayFunc(display);//tell GLUT what our display function is
  
	glutMainLoop();//Tell the program we are not done yet

  cleanup();
  
  return 0;
}
