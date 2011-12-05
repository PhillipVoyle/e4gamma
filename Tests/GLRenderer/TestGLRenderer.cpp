
#include <GL/GLRenderer.h>
#include <GL/GLShader.h>
#include <GL/GLTexture.h>
#include <stdcpp/FileSystemDataStore.h>
#include <iostream>
using namespace std;
using namespace E4Gamma;

#include <GLUT/glut.h>


CFileSystemDataStore g_fileSystemDataStore;
CGLRenderer* g_pRenderer = NULL;
CGLShader* g_pVertexShader = NULL;
CGLShader* g_pFragmentShader = NULL;

CGLTexture *g_pTexture = NULL;
int g_nProgram = 0;
int g_nVertexShader = 0;
int g_nFragmentShader = 0;


void init()
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  
  g_pRenderer = new IUnknownImpl<CGLRenderer>(&g_fileSystemDataStore);
  g_pTexture = g_pRenderer->LoadTexture("Data/Textures/White.rgba");
  g_pVertexShader = g_pRenderer->LoadShader("Data/Shaders/test.vsh", GL_VERTEX_SHADER);
  g_pFragmentShader = g_pRenderer->LoadShader("Data/Shaders/test.fsh", GL_FRAGMENT_SHADER);
  
  g_nProgram = glCreateProgram();
  g_nVertexShader = g_pVertexShader->GetShader();
  g_nFragmentShader = g_pFragmentShader->GetShader();
  
  glAttachShader(g_nProgram, g_nVertexShader);
  glAttachShader(g_nProgram, g_nFragmentShader);

  int nStatus = 0;
  glLinkProgram(g_nProgram);
  glGetProgramiv(g_nProgram, GL_LINK_STATUS, &nStatus);
  if(!nStatus) {
    int loglen;
    glGetProgramiv(g_nProgram, GL_INFO_LOG_LENGTH, &loglen);
    if(loglen > 1) {
      char *infolog = new char[loglen];
      int written;
      glGetProgramInfoLog(g_nProgram, loglen, &written, infolog);
      cout << "engine: error linking shader program: " << infolog << endl;
      delete infolog;
    }
    glDeleteProgram(g_nProgram);
  }
}

void display()
{
  g_pRenderer->BeginScene();
  g_pTexture->RenderSet(0);

  glUseProgram(g_nProgram);
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
  delete g_pVertexShader;
  glDeleteProgram(g_nProgram);
  delete g_pVertexShader;
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