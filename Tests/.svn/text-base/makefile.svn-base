all: TestGLRenderer

TestGLRenderer: TestGLRenderer.cpp makefile
	g++ TestGLRenderer.cpp -o TestGLRenderer \
	-framework GLUT \
	-framework OpenGL \
	-I../Include \
        -L../Lib \
	-lE4cpp \
	-lE4GGL

clean:
	rm TestGLRenderer
