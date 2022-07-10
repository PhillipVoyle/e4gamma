all: TestGLRenderer

TestGLRenderer: TestGLRenderer.cpp makefile
	g++ TestGLRenderer.cpp \
	-I../../Include \
	-L../../Lib \
	-lE4GGL \
	-lE4Math \
	-lE4cpp \
	-lGL \
	-lglut \
	 -o TestGLRenderer

clean:
	rm TestGLRenderer
