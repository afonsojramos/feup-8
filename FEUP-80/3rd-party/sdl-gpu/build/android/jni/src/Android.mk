LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

SRC_PATH := ../../../../src
INCLUDES = \
	-I../../include \
	-I../../src/externals/glew/GL \
	-I../../src/externals/stb_image \
	-I../../src/externals/stb_image_write \
	-I../../../SDL2-2.0.7/include

LOCAL_ARM_MODE := arm
LOCAL_CFLAGS    := -O3 $(INCLUDES) -DSDL_GPU_DISABLE_GLES_1 -DSDL_GPU_DISABLE_GLES_3 -DSDL_GPU_DISABLE_OPENGL
LOCAL_MODULE    := libsdlgpu
LOCAL_SRC_FILES := \
	$(SRC_PATH)/renderer_GLES_2.c \
	$(SRC_PATH)/SDL_gpu.c \
	$(SRC_PATH)/SDL_gpu_matrix.c \
	$(SRC_PATH)/SDL_gpu_renderer.c \
	$(SRC_PATH)/externals/stb_image/stb_image.c \
	$(SRC_PATH)/externals/stb_image_write/stb_image_write.c

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -llog -lGLESv1_CM -lGLESv2

include $(BUILD_SHARED_LIBRARY)