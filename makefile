
GLDIR := GL
stdcppdir = stdcpp

OBJS_GL := $(addprefix Object/$(GLDIR)/, \
	GLMaterial.o \
	GLRenderer.o \
	GLTexture.o \
	GLShader.o \
	GLModel.o \
	GLMesh.o \
) 
OBJS_stdcpp := $(addprefix Object/$(stdcppdir)/, \
 	FileSystemDataStore.o \
	FlatFile.o \
)

all:	Lib/libE4GGL.a Lib/libE4cpp.a

Lib/libE4GGL.a: $(OBJS_GL) Lib
	ar -rvs	Lib/libE4GGL.a \
		$(OBJS_GL)

Lib/libE4cpp.a: Object/stdcpp $(OBJS_stdcpp)
	ar -rvs	Lib/libE4cpp.a \
		$(OBJS_stdcpp)

Object/GL/%.o: Source/GL/%.cpp Object/GL
	g++ -c $< -o $@ \
	-IInclude \
	-framework OpenGL

Object/stdcpp/%.o: Source/stdcpp/%.cpp Object/stdcpp
	g++ -c $< -o $@ \
	-IInclude

Lib:
	mkdir Lib


Object/GL:
	mkdir -p Object/GL

Object/stdcpp:
	mkdir -p Object/stdcpp

clean:
	rm -rf Lib
	rm -rf Object
