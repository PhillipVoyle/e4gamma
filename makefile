
GLDIR := GL
stdcppdir := stdcpp
Math := Math

OBJS_GL := $(addprefix Object/$(GLDIR)/, \
	GLCamera.o \
	GLFrameBuffer.o \
	GLLight.o \
	GLMaterial.o \
	GLMesh.o \
	GLModel.o \
	GLRenderContext.o \
	GLRenderer.o \
	GLShaderProgram.o \
	GLShader.o \
	GLTexture.o \
) 
OBJS_stdcpp := $(addprefix Object/$(stdcppdir)/, \
 	FileSystemDataStore.o \
	Frame.o \
	FlatFile.o \
	TextFile.o \
	Iris.o \
)

OBJS_Math :=  $(addprefix Object/$(Math)/, \
 	Matrix.o \
	Quaternion.o \
	Vector.o \
)

all:	Lib/libE4GGL.a Lib/libE4cpp.a Lib/libE4Math.a

Lib/libE4GGL.a: $(OBJS_GL) Lib
	ar -rvs	Lib/libE4GGL.a \
		$(OBJS_GL)

Lib/libE4cpp.a: Object/stdcpp $(OBJS_stdcpp)
	ar -rvs	Lib/libE4cpp.a \
		$(OBJS_stdcpp)

Lib/libE4Math.a: Object/Math $(OBJS_Math)
	ar -rvs	Lib/libE4Math.a \
		$(OBJS_Math)

Object/GL/%.o: Source/GL/%.cpp Object/GL
	g++ -c $< -o $@ \
	-IInclude 
	

Object/stdcpp/%.o: Source/stdcpp/%.cpp Object/stdcpp
	g++ -c $< -o $@ \
	-IInclude

Object/Math/%.o: Source/Math/%.cpp Object/Math
	g++ -c $< -o $@ \
	-IInclude


Lib:
	mkdir Lib

Object/GL:
	mkdir -p Object/GL

Object/stdcpp:
	mkdir -p Object/stdcpp

Object/Math:
	mkdir -p Object/Math

clean:
	rm -rf Lib
	rm -rf Object
	rm -rf Math

