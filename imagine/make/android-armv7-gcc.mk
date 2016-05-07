include $(IMAGINE_PATH)/make/config.mk
include $(buildSysPath)/setAndroidNDKPath.mk
SUBARCH := armv7
android_abi := armeabi-v7a
clangTarget := armv7-none-linux-androideabi
armv7CPUFlags ?= -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16
android_hardFP ?= 1
android_cpuFlags ?= $(armv7CPUFlags)
LDFLAGS_SYSTEM += -Wl,--fix-cortex-a8
android_armv7State ?= -mthumb
android_armState := $(android_armv7State)
android_cpuFlags += $(android_armv7State)

ifeq ($(android_hardFP),1)
 # NOTE: do not also link in -lm or strange runtime behavior can result, especially with LTO
 # imagineAppTarget.mk will strip any instances of -lm and append -lm_hard
 android_cpuFlags += -mhard-float
 CPPFLAGS += -D_NDK_MATH_NO_SOFTFP=1
 LDFLAGS_SYSTEM += -Wl,--no-warn-mismatch
 android_hardFPExt := -hard
endif

include $(buildSysPath)/android-arm.mk
