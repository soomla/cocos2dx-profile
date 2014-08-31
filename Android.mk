LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_profile_static
LOCAL_MODULE_FILENAME := libcocos2dxprofile
LOCAL_SRC_FILES := Profile/CCProfileConsts.cpp \
	Profile/CCProfileController.cpp \
	Profile/CCProfileEventDispatcher.cpp \
	Profile/CCProfileService.cpp \
	Profile/CCSocialActionUtils.cpp \
	Profile/CCUserProfileUtils.cpp \
	Profile/domain/CCUserProfile.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Profile
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Profile/domain

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_soomla_common_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Profile
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Profile/domain

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions/soomla-cocos2dx-core)
