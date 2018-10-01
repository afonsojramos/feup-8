LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

SRC_PATH := ../..

LOCAL_ARM_MODE := arm
LOCAL_CFLAGS    := -O3 -D__ANDROID__
LOCAL_MODULE    := libgif
LOCAL_SRC_FILES := \
	$(SRC_PATH)/egif_lib.c \
	$(SRC_PATH)/dgif_lib.c \
	$(SRC_PATH)/gifalloc.c \
	$(SRC_PATH)/gif_font.c \
	$(SRC_PATH)/gif_hash.c \
	$(SRC_PATH)/gif_err.c \
	$(SRC_PATH)/quantize.c \
	$(SRC_PATH)/openbsd-reallocarray.c
	 
include $(BUILD_SHARED_LIBRARY)