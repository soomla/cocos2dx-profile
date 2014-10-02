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

//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCSoomlaProfile.h"
#include "CCNdkBridge.h"
#include "CCSoomlaMacros.h"
#include "CCDomainFactory.h"

using namespace cocos2d;
typedef CCDictElement CCDictElement;

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCSoomlaProfile *sInstance = NULL;

    CCSoomlaProfile *CCSoomlaProfile::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCSoomlaProfile();
            sInstance->retain();
        }
        return sInstance;
    }

    CCSoomlaProfile::CCSoomlaProfile() {
        mInited = false;
    }

    bool CCSoomlaProfile::init() {
        mInited = true;
        return true;
    }

    void CCSoomlaProfile::login(CCProvider provider, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::login"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::login(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::login"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::logout(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::logout"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCNdkBridge::callNative(params, soomlaError);
    }

    CCUserProfile *CCSoomlaProfile::getStoredUserProfile(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::getStoredUserProfile"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative(params, NULL);
        SL_SAFE_CREATE_FROM_RETURN(CCUserProfile *, retValue, retParams);
        return retValue;
    }

    void CCSoomlaProfile::updateStatus(CCProvider provider, const char *status, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::updateStatus"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(CCString::create(status), "status");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::updateStory(CCProvider provider, const char *message, const char *name,
            const char *caption, const char *description, const char *link, const char *picture,
            CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::updateStory"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(CCString::create(message), "message");
        params->setObject(CCString::create(name), "name");
        params->setObject(CCString::create(caption), "caption");
        params->setObject(CCString::create(description), "description");
        params->setObject(CCString::create(link), "link");
        params->setObject(CCString::create(picture), "picture");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::uploadImage(CCProvider provider, const char *message, const char *filePath,
            CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::uploadImage"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(CCString::create(message), "message");
        params->setObject(CCString::create(filePath), "filePath");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::getContacts(CCProvider provider, CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::getContacts"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    void CCSoomlaProfile::getFeed(CCProvider provider, CCReward *reward, CCError **soomlaError) {
        
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::getFeed"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    bool CCSoomlaProfile::isLoggedIn(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::isLoggedIn"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, soomlaError);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        
        return retValue->getValue();
    }
    
    void CCSoomlaProfile::like(CCProvider provider, const char *pageName, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::like"), "method");
        params->setObject(CCString::create(pageName), "pageName");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    void CCSoomlaProfile::openAppRatingPage(CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCSoomlaProfile::openAppRatingPage"), "method");
        CCNdkBridge::callNative(params, soomlaError);
    }
}
