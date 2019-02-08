#simo_src.c
LOCAL_PATH := $(call my-dir)
LOCAL_CPP_EXTENSION := .cpp
LOCAL_ARM_MODE := arm

include $(CLEAR_VARS)
LOCAL_MODULE    := TmcTunerDemo

MY_TMC_PATH := D:/Data_D/HSKOST/TMC/rel_sourceforge/tmc_src-1.02
MY_TMCLIB_PATH := $(MY_TMC_PATH)/src/tmcruntime/tmclib

MY_TMCLIB_SRC := $(MY_TMCLIB_PATH)/cmatrix.c \
$(MY_TMCLIB_PATH)/graphic_stubs.c \
$(MY_TMCLIB_PATH)/lapackutils.c \
$(MY_TMCLIB_PATH)/tmccell.c \
$(MY_TMCLIB_PATH)/tmcdebugger.c \
$(MY_TMCLIB_PATH)/tmcexcpt.c \
$(MY_TMCLIB_PATH)/tmcio.c \
$(MY_TMCLIB_PATH)/tmclib.c \
$(MY_TMCLIB_PATH)/tmcmath.c \
$(MY_TMCLIB_PATH)/tmcmstruct.c \
$(MY_TMCLIB_PATH)/tmcstringhash.c \
$(MY_TMCLIB_PATH)/tmc_unsupported.c \
$(MY_TMCLIB_PATH)/unicodeutils.c


MY_SIMOMEXLIB_PATH :=$(MY_TMC_PATH)/examples/Simo_ADT/MexSRC 
#MY_SIMOMEXLIB_SRC :=$(MY_SIMOMEXLIB_PATH)/ExMex1.c 
MY_SIMOMEXLIB_SRC := ExMex1.c

LOCAL_SRC_FILES :=  mainTunerDemoJni.c  tmcmodule1.c   tmc_jni_except.c
LOCAL_SRC_FILES += $(MY_TMCLIB_SRC) $(MY_SIMOMEXLIB_SRC)
LOCAL_SRC_FILES += TestO.globals.c TestO._init_hash_data.c TestO.c findcompensator.c getfrdRL.c


LOCAL_C_INCLUDES :=$(MY_TMCLIB_PATH)/  $(MY_TMC_PATH)/examples/Simo_ADT/Stubs/
LOCAL_STATIC_LIBRARIES := 
LOCAL_SHARED_LIBRARIES :=
LOCAL_LDLIBS :=    $(MY_TMC_PATH)/lib/arm/tmcruntime_mingw_armv7.a
LOCAL_CFLAGS :=-Wformat=0 -D true=1 -D false=0 -D bool=int -D MATLAB_MEX_FILE \
 -D TMC_NO_SEH -D TRY= -D CATCH= -D ENDCATCH= -D FINALLY= \
 -D ENDFINALLY= -fexceptions -D_TMC_SITARA_ -D _TMC_EMBEDDED_ \
 -D _TMC_ANDROID_ -D UNICODE -ftree-vectorize -unroll-loops \
 --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  \
 -D TMCMEX_DLL -D SIMOLIB_EXPORTS -DNO_BLAS_WRAP -DMSDOS \
 -DUSE_CLOCK -DNO_ONEXIT -I$(MY_TMCLIB_PATH)/ \
 -I$(MY_TMC_PATH)/examples/Simo_ADT/Stubs/
LOCAL_CPPFLAGS :=
LOCAL_LDFLAGS :=
include $(BUILD_SHARED_LIBRARY)
