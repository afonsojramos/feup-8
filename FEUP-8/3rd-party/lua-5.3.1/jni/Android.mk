LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

SRC_PATH := ../src

LOCAL_ARM_MODE := arm
LOCAL_CFLAGS    := -O3 -D"lua_getlocaledecpoint()='.'" -D"log2(x)=(log(x)/log(2))" -DLUA_COMPAT_5_2
LOCAL_MODULE    := liblua
LOCAL_SRC_FILES := \
	$(SRC_PATH)/lapi.c \
	$(SRC_PATH)/lauxlib.c \
	$(SRC_PATH)/lbaselib.c \
	$(SRC_PATH)/lbitlib.c \
	$(SRC_PATH)/lcode.c \
	$(SRC_PATH)/lcorolib.c \
	$(SRC_PATH)/lctype.c \
	$(SRC_PATH)/ldblib.c \
	$(SRC_PATH)/ldebug.c \
	$(SRC_PATH)/ldo.c \
	$(SRC_PATH)/ldump.c \
	$(SRC_PATH)/lfunc.c \
	$(SRC_PATH)/lgc.c \
	$(SRC_PATH)/linit.c \
	$(SRC_PATH)/liolib.c \
	$(SRC_PATH)/llex.c \
	$(SRC_PATH)/lmathlib.c \
	$(SRC_PATH)/lmem.c \
	$(SRC_PATH)/loadlib.c \
	$(SRC_PATH)/lobject.c \
	$(SRC_PATH)/lopcodes.c \
	$(SRC_PATH)/loslib.c \
	$(SRC_PATH)/lparser.c \
	$(SRC_PATH)/lstate.c \
	$(SRC_PATH)/lstring.c \
	$(SRC_PATH)/lstrlib.c \
	$(SRC_PATH)/ltable.c \
	$(SRC_PATH)/ltablib.c \
	$(SRC_PATH)/ltm.c \
	$(SRC_PATH)/lundump.c \
	$(SRC_PATH)/lutf8lib.c \
	$(SRC_PATH)/lvm.c \
	$(SRC_PATH)/lzio.c \
	$(SRC_PATH)/lpvm.c \
	$(SRC_PATH)/lpcap.c \
	$(SRC_PATH)/lptree.c \
	$(SRC_PATH)/lpcode.c \
	$(SRC_PATH)/lpprint.c
	 
include $(BUILD_SHARED_LIBRARY)