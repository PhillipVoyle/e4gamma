project (E4Gamma)

cmake_minimum_required(VERSION 3.1)

include_directories(Include)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

# add_library(Collision Source/
add_library(E4GGL
    Source/GL/GLCamera.cpp
    Source/GL/GLFrameBuffer.cpp
    Source/GL/GLLight.cpp
    Source/GL/GLMaterial.cpp
    Source/GL/GLMesh.cpp
    Source/GL/GLModel.cpp
    Source/GL/GLRenderContext.cpp
    Source/GL/GLRenderer.cpp
    Source/GL/GLShader.cpp
    Source/GL/GLShaderProgram.cpp
    Source/GL/GLTexture.cpp)

add_library(E4GMath
    Source/Math/Matrix.cpp
    Source/Math/Quaternion.cpp
    Source/Math/Vector.cpp)

add_library(E4Gcpp
    Source/stdcpp/FileSystemDataStore.cpp
    Source/stdcpp/FlatFile.cpp
    Source/stdcpp/Frame.cpp
    Source/stdcpp/Iris.cpp
    Source/stdcpp/TextFile.cpp)

add_library(E4GPhysics
    Source/Physics/PhysicsFrame.cpp)


add_executable(TestGLRenderer
    Tests/GLRenderer/TestGLRenderer.cpp)

target_link_libraries(TestGLRenderer E4GGL E4GMath E4Gcpp ${OPENGL_LIBRARY} glut)

add_executable(MathTest
    Tests/Math/MathTest.cpp)

target_link_libraries(MathTest E4GMath E4Gcpp)

add_executable(PhysicsTest
    Tests/PhysicsTest/PhysicsTest.cpp)

target_link_libraries(PhysicsTest E4GGL E4GMath E4GPhysics E4Gcpp ${OPENGL_LIBRARY} glut)
