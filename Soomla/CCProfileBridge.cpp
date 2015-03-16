/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CCProfileBridge.h"
#include "CCNdkBridge.h"
#include "CCDomainFactory.h"
#include "CCProfileEventDispatcher.h"
#include "CCSoomlaUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <string>

#define CLASS_NAME "com/soomla/cocos2dx/profile/ProfileBridgeBinder"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "CCProfileBridgeBinderIos.h"

#endif

namespace soomla {

    USING_NS_CC;
    
    #define TAG "SOOMLA NativeCoreBridge"

    static CCProfileBridge *sInstance = NULL;

    CCProfileBridge *CCProfileBridge::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCProfileBridge();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCProfileBridge::initShared(CCDictionary *profileParams) {
        CCProfileBridge *profileBridge = CCProfileBridge::getInstance();
        if (!profileBridge->init(profileParams)) {
            exit(1);
        }
    }

    CCProfileBridge::CCProfileBridge() {
        // Just bind to native before initing
        this->bindNative();
    }

    bool CCProfileBridge::init(CCDictionary *profileParams) {

        CCProfileEventDispatcher::getInstance();    // to get sure it's inited

        CCDomainFactory::getInstance()->registerCreator(CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE,
                (SEL_DomainCreator)&CCUserProfile::createWithDictionary);
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileBridge::init"), "method");
        params->setObject(profileParams, "params");
        CCNdkBridge::callNative(params, NULL);

        return true;
    }
    
    void CCProfileBridge::bindNative() {
        CCSoomlaUtils::logDebug(TAG, "Binding to native platform Profile bridge...");
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo minfo;
        
        bool exists = JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "bind", "()V");
        
        if (exists)
        {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
        else {
            CCSoomlaUtils::logError(TAG, "Unable to bind native Profile bridge on Android");
        }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        soomla::CCProfileBridgeBinderIos::bind();
#endif
    }
}
