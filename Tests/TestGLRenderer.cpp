
#include <GL/GLRenderer.h>
#include <stdcpp/FileSystemDataStore.h>
#include <iostream>
using namespace std;
using namespace E4Gamma;

#include <GLUT/glut.h>


CFileSystemDataStore g_fileSystemDataStore;
CGLRenderer* g_pRenderer = NULL;

void init()
{
  g_pRenderer = new CGLRenderer(&g_fileSystemDataStore);
}

void display()
{
  g_pRenderer->BeginScene();
  
  g_pRenderer->Present();
  
	glutPostRedisplay();//Tell the program to refresh
}

void cleanup()
{
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
