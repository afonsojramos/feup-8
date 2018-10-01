CC=emcc
OPT=-Os -DSDL_GPU_DISABLE_GLES_1 -DSDL_GPU_DISABLE_GLES_3 -DSDL_GPU_DISABLE_OPENGL

AR= emar rcu
RANLIB= emranlib

INCLUDES = \
	-I../../include \
	-I../../src/externals/glew/GL \
	-I../../src/externals/stb_image \
	-I../../src/externals/stb_image_write \
	-I../../../SDL2-2.0.7/include

renderer_GLES_1.o: ../../src/renderer_GLES_1.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

renderer_GLES_2.o: ../../src/renderer_GLES_2.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

renderer_GLES_3.o: ../../src/renderer_GLES_3.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

renderer_OpenGL_1.o: ../../src/renderer_OpenGL_1.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

renderer_OpenGL_1_BASE.o: ../../src/renderer_OpenGL_1_BASE.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

renderer_OpenGL_2.o: ../../src/renderer_OpenGL_2.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

renderer_OpenGL_3.o: ../../src/renderer_OpenGL_3.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

renderer_OpenGL_4.o: ../../src/renderer_OpenGL_4.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

SDL_gpu.o: ../../src/SDL_gpu.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

SDL_gpu_matrix.o: ../../src/SDL_gpu_matrix.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

SDL_gpu_renderer.o: ../../src/SDL_gpu_renderer.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

SDL_gpu_shapes.o: ../../src/SDL_gpu_shapes.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

glew.o: ../../src/externals/glew/glew.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

stb_image.o: ../../src/externals/stb_image/stb_image.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

stb_image_write.o: ../../src/externals/stb_image_write/stb_image_write.c
	$(CC) $< $(OPT) $(INCLUDES) -c -o $@

OBJS = \
	renderer_GLES_2.o \
	SDL_gpu.o \
	SDL_gpu_matrix.o \
	SDL_gpu_renderer.o \
	stb_image.o \
	stb_image_write.o

SDL2_GPU_A = libsdlgpu.a

$(SDL2_GPU_A): $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

