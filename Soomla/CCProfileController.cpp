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

#include "CCProfileController.h"
#include "CCNdkBridge.h"

using namespace cocos2d;
typedef CCDictElement CCDictElement;

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCProfileController *sInstance = NULL;

    CCProfileController *CCProfileController::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCProfileController();
            sInstance->retain();
        }
        return sInstance;
    }

    CCProfileController::CCProfileController() {
        mInited = false;
    }

    bool CCProfileController::init() {
        mInited = true;
        return true;
    }

    void CCProfileController::login(CCProvider provider, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::login"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::login(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::login"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::logout(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::logout"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCNdkBridge::callNative(params, soomlaError);
    }

    CCUserProfile *CCProfileController::getStoredUserProfile(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::getStoredUserProfile"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative(params, NULL);
        CCUserProfile *retValue = (CCUserProfile *) retParams->objectForKey("return");
        return retValue;
    }

    void CCProfileController::updateStatus(CCProvider provider, const char *status, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::updateStatus"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(CCString::create(status), "status");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::updateStory(CCProvider provider, const char *message, const char *name,
            const char *caption, const char *description, const char *link, const char *picture,
            CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::updateStory"), "method");
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

    void CCProfileController::uploadImage(CCProvider provider, const char *message, const char *filePath,
            CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::uploadImage"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(CCString::create(message), "message");
        params->setObject(CCString::create(filePath), "filePath");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::getContacts(CCProvider provider, CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::getContacts"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    void CCProfileController::getFeed(CCProvider provider, CCReward *reward, CCError **soomlaError) {
        
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::getFeed"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    bool CCProfileController::isLoggedIn(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::isLoggedIn"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, soomlaError);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        
        return retValue->getValue();
    }
    
    void CCProfileController::like(CCProvider provider, const char *pageName, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::like"), "method");
        params->setObject(CCString::create(pageName), "pageName");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    void CCProfileController::openAppRatingPage(CCError **soomlaError) {
        CC_ASSERT(mInited);
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCProfileController::openAppRatingPage"), "method");
        CCNdkBridge::callNative(params, soomlaError);
    }
}
