
#include <GL/GLRenderer.h>
#include <Interfaces/Renderer/ITexture.h>
#include <stdcpp/FileSystemDataStore.h>
#include <iostream>
using namespace std;
using namespace E4Gamma;

#include <GLUT/glut.h>


CFileSystemDataStore g_fileSystemDataStore;
CGLRenderer* g_pRenderer = NULL;
ITexture *g_pTexture = NULL;

void init()
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  
  g_pRenderer = new CGLRenderer(&g_fileSystemDataStore);
  g_pTexture = g_pRenderer->LoadTexture("../Data/Textures/White.rgba");
}

void display()
{
  g_pRenderer->BeginScene();
  g_pTexture->RenderSet(0);
  
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
  delete g_pTexture;
  delete g_pRenderer;
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);//initialize GLUT.
  
	glutInitWindowSize(800,600);//define the window size as 800 pixels wide and 600 pixels high
  glutInitWindowPosition(10,50);//Set the window position at (10,50)
  
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//Set the initial display mode
  
	glutCreateWindow("Lesson 1");//Create our window
  
	init();//call init()
  
	glutDisplayFunc(display);//tell GLUT what our display function is
  
	glutMainLoop();//Tell the program we are not done yet

  cleanup();
  
  return 0;
}
