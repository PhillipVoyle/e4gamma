
#include <GL/GLRenderer.h>
#include <GL/GLShader.h>
#include <GL/GLTexture.h>
#include <GL/GLMaterial.h>
#include <GL/GLMesh.h>

#include <Interfaces/Foundation/ISequenceReader.h>

#include <stdcpp/FileSystemDataStore.h>
#include <iostream>
using namespace std;
using namespace E4Gamma;

#include <GLUT/glut.h>
#include <OpenGL/gl3.h>

//tell g++ not to warn me
void init();
void display();
void cleanup();

IUnknownNull<CFileSystemDataStore> g_fileSystemDataStore;
SharedPtr<CGLRenderer> g_pRenderer = nullptr;
SharedPtr<CGLMaterial> g_pMaterial = nullptr;
SharedPtr<CGLMesh> g_pMesh = nullptr;

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
  g_pMaterial = new IUnknownImpl<CGLMaterial>(g_pRenderer);
  g_pMaterial->SetTexture(GL_TEXTURE0, g_fileSystemDataStore.OpenSequence("Data/Textures/White.rgba"));
  string vshSource, fshSource;
  g_fileSystemDataStore.ReadString("Data/Shaders/test.vsh", vshSource);
  g_fileSystemDataStore.ReadString("Data/Shaders/test.fsh", fshSource);
  g_pMaterial->SetShader(GL_VERTEX_SHADER, vshSource);
  g_pMaterial->SetShader(GL_FRAGMENT_SHADER, fshSource);
  g_pMesh = new IUnknownImpl<CGLMesh>(g_fileSystemDataStore.OpenTextSequence("Data/Meshes/TestMesh.mesh"));
}

void display()
{
  g_pRenderer->BeginScene();
  g_pMaterial->RenderSet();
  g_pMesh->RenderPose(nullptr);
  g_pRenderer->Present();
  
	glutPostRedisplay();//Tell the program to refresh
}

void cleanup()
{
  g_pMaterial = nullptr;
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
  
  if (gl3wInit()) {
    fprintf(stderr, "failed to initialize OpenGL\n");
    return -1;
  }
  if (!gl3wIsSupported(3, 2)) {
    fprintf(stderr, "OpenGL 3.2 not supported\n");
    return -1;
  }
  
	glutCreateWindow("TestGLRenderer");//Create our window
  
	init();//call init()
  
	glutDisplayFunc(display);//tell GLUT what our display function is
  
	glutMainLoop();//Tell the program we are not done yet

  cleanup();
  
  return 0;
}
