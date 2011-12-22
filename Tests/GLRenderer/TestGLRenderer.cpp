
#include <GL/GLRenderer.h>
#include <Interfaces/Renderer/IModel.h>

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

int g_nProgram = 0;
int g_nVertexShader = 0;
int g_nFragmentShader = 0;

GLuint g_vertices = 0;
GLuint g_texcoords = 0;

void init()
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  
  g_pRenderer = new IUnknownImpl<CGLRenderer>();
  g_pModel = g_pRenderer->LoadModel("Data/Models/test.model");
}

void display()
{
  g_pRenderer->BeginScene();
  g_pModel->RenderPose(nullptr);
  g_pRenderer->Present();
  
	glutPostRedisplay();//Tell the program to refresh
}

void cleanup()
{
  g_pModel = nullptr;
  g_pRenderer = nullptr;
  
  glDeleteBuffers(GL_ARRAY_BUFFER, &g_vertices);
  glDeleteBuffers(GL_ARRAY_BUFFER, &g_texcoords);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);//initialize GLUT.
  
	glutInitWindowSize(800,600);//define the window size as 800 pixels wide and 600 pixels high
  glutInitWindowPosition(10,50);//Set the window position at (10,50)
  
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//Set the initial display mode
  
	glutCreateWindow("TestGLRenderer");//Create our window
  
	init();//call init()
  
	glutDisplayFunc(display);//tell GLUT what our display function is
  
	glutMainLoop();//Tell the program we are not done yet

  cleanup();
  
  return 0;
}
