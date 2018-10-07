LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

VM_PATH := ../src/vm
OPT_PATH := ../src/optional

LOCAL_C_INCLUDES := src/include
LOCAL_C_INCLUDES += src/vm
LOCAL_C_INCLUDES += src/optional

LOCAL_ARM_MODE  := arm
LOCAL_CFLAGS    := -DWREN_OPT_META -DWREN_OPT_RANDOM
LOCAL_MODULE    := libwren
LOCAL_SRC_FILES := \
	$(VM_PATH)/wren_compiler.c \
	$(VM_PATH)/wren_core.c \
	$(VM_PATH)/wren_debug.c \
	$(VM_PATH)/wren_primitive.c \
	$(VM_PATH)/wren_utils.c \
	$(VM_PATH)/wren_value.c \
	$(VM_PATH)/wren_vm.c \
	$(OPT_PATH)/wren_opt_meta.c \
	$(OPT_PATH)/wren_opt_random.c
	 
include $(BUILD_SHARED_LIBRARY)