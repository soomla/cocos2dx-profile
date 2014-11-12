LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_profile_static
LOCAL_MODULE_FILENAME := libcocos2dxprofile

PROFILE_SRC_LIST := $(wildcard $(LOCAL_PATH)/Soomla/*.cpp)
PROFILE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/domain/*.cpp)
LOCAL_SRC_FILES := $(PROFILE_SRC_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Soomla
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_soomla_common_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions/soomla-cocos2dx-core)
