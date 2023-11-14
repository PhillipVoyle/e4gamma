
#include <GL/GLIncludes.h>


#include <GL/GLRenderer.h>
#include <GL/GLRenderContext.h>
#include <GL/GLMesh.h>
#include <Interfaces/Renderer/IModel.h>
#include <Interfaces/Renderer/ICamera.h>
#include <Interfaces/Foundation/IFrame.h>
#include <Interfaces/Renderer/ILight.h>
#include <stdcpp/Frame.h>

#include <Interfaces/Renderer/IMaterial.h>
#include <Interfaces/Renderer/IMesh.h>

#include <Interfaces/Foundation/ISequenceReader.h>
#include <Physics/PhysicsFrame.h>
#include <Physics/RK4.h>
//#include <Physics/Euler.h>

#include <stdcpp/FileSystemDataStore.h>
#include <iostream>

#include <vector>
#include <cmath>

using namespace std;
using namespace E4Gamma;
using namespace E4Gamma::Physics;

//tell g++ not to warn me
void init();
void display();
void cleanup();
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);

SharedPtr<CGLRenderer> g_pRenderer = nullptr;
SharedPtr<IMaterial> g_pDepthMaterial = nullptr;

SharedPtr<ICamera> g_pCamera = nullptr;

std::vector<SharedPtr<IMesh>> g_meshes;
std::vector<SharedPtr<CRigidBodyFrame>> g_bodies;

SharedPtr<CRotPosFrame> g_frame = new IUnknownImpl<CRotPosFrame>();

CGLMesh::TexturedVertex CreateTexturedVert(Vector pos, Vector normal, Vector binormal, Vector tangent, float u, float v)
{
  CGLMesh::TexturedVertex result;
  result.binormal = binormal;
  result.tangent = tangent;
  result.normal = normal;
  result.position = pos;
  result.u = u;
  result.v = v;
  return result;
}

SharedPtr<IMesh> CreateBoxMesh(double fWidth, double fHeight, double fDepth)
{
  std::vector<Vector> geometryVerts;
  std::vector<CGLMesh::Triangle> triangles;
  std::vector<CGLMesh::Edge> edges;
  std::vector<CGLMesh::TexturedVertex> texturedVerts;
  
  //front face
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector( 1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector( 1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector( 1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1), 1.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector( 1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector( 1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1), 0.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector( 1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1), 0.0, 1.0));
  
  //back face
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(-1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(-1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(-1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(-1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(-1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(-1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 0.0));
  
  //bottom face (ha ha)
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 0.0));
  
  //top face
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 0.0));
  
  //left face
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector(-fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 0.0));

  //right face
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0, fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 1.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0,-fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 1.0, 0.0));
  texturedVerts.push_back(CreateTexturedVert(Vector( fWidth/2.0, fHeight/2.0,-fDepth/2.0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 0.0, 0.0));
  
  return SharedPtr<IMesh>(new IUnknownImpl<CGLMesh>(g_pRenderer->GetRenderContext(), geometryVerts, triangles, edges, texturedVerts));
}

void init()
{
  glClearColor(0.6,0.6,0.6,1.0);
  
  glEnable(GL_TEXTURE_2D);
  //glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glDepthFunc(GL_LEQUAL);
  
  glClearStencil(0x00);
  g_pRenderer = new IUnknownImpl<CGLRenderer>();
  
  //g_pMesh = g_pRenderer->LoadMesh("Data/Meshes/shadowtest.mesh");
  //g_pPhongMaterial = g_pRenderer->LoadMaterial("Data/Materials/shadowtest.material");

  //g_meshes.push_back(g_pRenderer->LoadMesh("Data/Meshes/level.mesh"));
  g_meshes.push_back(CreateBoxMesh(0.2, 0.2, 1.0));
  g_bodies.push_back(new IUnknownImpl<CRigidBodyFrame>());
  g_bodies[0].m_ptr->GetBody().linear.inverseMass = 1;
  g_bodies[0].m_ptr->GetBody().angular.inverseInertia = 1;
  g_bodies[0].m_ptr->SetOrientation(Quaternion::FromAxisAngle(Vector(0.0, 0.0, 1.0), 0.5));

  g_pDepthMaterial = g_pRenderer->LoadMaterial("Data/Materials/depthonly.material");
  
  float fovy = 30.0;
  float zfar = 1000.f;
  float znear = 0.1f;
  float aspect = 800.0f / 600.0f;
  
  g_pCamera = g_pRenderer->CreateCamera(aspect, znear, zfar, fovy);
  SharedPtr<IFrame> pFrame = g_pCamera->GetFrame();
  pFrame->SetPosition(Vector(0.0f, 0.0f, -10.0f));

  pFrame = nullptr;
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
int nPhysics = 0;

bool bSimulate = false;

const int kPhysicsDurnMs = 1000/60;
const double milliSecondsToSeconds = 0.001;

RigidBody::Derivative Simulate(const RigidBody& rigidBody)
{
  RigidBody::Derivative result;
  result.angular.spin = rigidBody.angular.spin;
  result.angular.torque = Vector(0, 0.1, 0);
  //*
  result.linear.force = Vector(0, -100 / rigidBody.linear.inverseMass, 0)  //gravity
       -rigidBody.linear.velocity * 0.4;                    //friction
  
  
  if(rigidBody.linear.position.y < 0)
  {
    result.linear.force = result.linear.force - rigidBody.linear.position * 100; //spring
  }
  //*/
  
  result.linear.velocity = rigidBody.linear.velocity;// copy velocity from body
  return result;
}

void display()
{
  int nTimeElapsed = glutGet(GLUT_ELAPSED_TIME);
  float fFrameTime = ((float)(nTimeElapsed - nPreviousTime))/1000.0f;
  
  if(bSimulate)
  {
    nPhysics += nTimeElapsed - nPreviousTime;
    while (nPhysics > kPhysicsDurnMs) {
      nPhysics -= kPhysicsDurnMs;
      g_bodies[0]->GetBody() = IntegrateRK4<RigidBody, RigidBody::Derivative, RigidBody::Derivative (&)(const RigidBody& rigidBody)>(g_bodies[0]->GetBody(), Simulate, ((double)kPhysicsDurnMs) * milliSecondsToSeconds);
      g_bodies[0]->GetBody().recalculate();
    }
  }
  nPreviousTime = nTimeElapsed;

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
  
  g_pCamera->Select();  
  
  glClearDepth(1.0);
  g_pRenderer->BeginScene();
  glClear(GL_DEPTH_BUFFER_BIT);
  glClear(GL_STENCIL_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LESS);

  glColorMask(1, 1, 1, 1);
  glEnable(GL_LIGHTING);

  g_frame->SetPosition(Vector(1.0, 0.0, 0.0));
  g_frame->SetOrientation(Quaternion::FromAxisAngle(Vector(1.0, 0.0, 0.0), 0.1));
  for(int i = 0; i < g_meshes.size(); i++)
  {
    if(i < g_bodies.size())
    {
      g_meshes[i]->RenderPose(g_bodies[i]);
    }
    else
    {
      g_meshes[i]->RenderPose(nullptr);
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
  g_pCamera = nullptr;
  
  g_meshes.clear();
  
  g_pDepthMaterial = nullptr;
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
  else if((char)key == 'p')
  {
    bSimulate = !bSimulate;
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
    fTurnRight = 0.7f;
  }
  else if(key == GLUT_KEY_LEFT)
  {
    fTurnLeft = 0.7f;
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
  glutCreateWindow("Physics Test");//Create our window

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