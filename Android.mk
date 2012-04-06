LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS = \
	-O3 -Wreturn-type -Wunused -Wuninitialized \
	-Wall -Wno-psabi -funroll-all-loops  -funroll-loops \
	-DCHECKOPTS -DNDEBUG -DHAVE_CONFIG_H -DSTRESSAPPTEST_CPU_ARMV7A

LOCAL_C_INCLUDES = \
	bionic \
	external/stlport/stlport

LOCAL_SRC_FILES:= \
	src/adler32memcpy.cpp \
	src/disk_blocks.cpp \
	src/error_diag.cpp \
	src/finelock_queue.cpp \
	src/logger.cpp \
	src/main.cpp \
	src/os.cpp \
	src/os_factory.cpp \
	src/pattern.cpp \
	src/queue.cpp \
	src/sat.cpp \
	src/sat_factory.cpp \
	src/worker.cpp

LOCAL_SHARED_LIBRARIES := libstlport
LOCAL_MODULE_TAGS := optional

LOCAL_MODULE:= stressapptest

include $(BUILD_EXECUTABLE)
