
#include <GL/GLRenderer.h>
#include <GL/GLShader.h>
#include <GL/GLTexture.h>
#include <GL/GLMaterial.h>

#include <stdcpp/FileSystemDataStore.h>
#include <iostream>
using namespace std;
using namespace E4Gamma;

#include <GLUT/glut.h>

//tell g++ not to warn me
void init();
void display();
void cleanup();

IUnknownNull<CFileSystemDataStore> g_fileSystemDataStore;
SharedPtr<CGLRenderer> g_pRenderer = nullptr;
SharedPtr<CGLMaterial> g_pMaterial = nullptr;

int g_nProgram = 0;
int g_nVertexShader = 0;
int g_nFragmentShader = 0;


void init()
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  
  g_pRenderer = new IUnknownImpl<CGLRenderer>(&g_fileSystemDataStore);
  g_pMaterial = new IUnknownImpl<CGLMaterial>(g_pRenderer);
  g_pMaterial->SetTexture(GL_TEXTURE0, "Data/Textures/White.rgba");
  g_pMaterial->SetShader(GL_VERTEX_SHADER, "Data/Shaders/test.vsh");
  g_pMaterial->SetShader(GL_FRAGMENT_SHADER,  "Data/Shaders/test.fsh");

}

void display()
{
  g_pRenderer->BeginScene();

  g_pMaterial->RenderSet();
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
  
  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1.0, 0.0, 0.0);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(0.0, 1.0, 0.0);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(0.0, 1.0, 0.0);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1.0, 0.0, 0.0);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1.0, 1.0, 0.0);
  glEnd();
  
  g_pRenderer->Present();
  
	glutPostRedisplay();//Tell the program to refresh
}

void cleanup()
{
  g_pMaterial = nullptr;
  g_pRenderer = nullptr;
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
