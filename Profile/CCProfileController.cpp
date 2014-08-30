//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCProfileController.h"
#include "CCNdkBridge.h"

using namespace cocos2d;
typedef DictElement CCDictElement;

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
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::login"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::login(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::login"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::logout(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::logout"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCNdkBridge::callNative(params, soomlaError);
    }

    CCUserProfile *CCProfileController::getStoredUserProfile(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::getStoredUserProfile"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative(params, NULL);
        CCUserProfile *retValue = (CCUserProfile *) retParams->objectForKey("return");
        return retValue;
    }

    void CCProfileController::updateStatus(CCProvider provider, const char *status, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::updateStatus"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(status), "status");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::updateStory(CCProvider provider, const char *message, const char *name,
            const char *caption, const char *description, const char *link, const char *picture,
            CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::updateStory"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(message), "message");
        params->setObject(__String::create(name), "name");
        params->setObject(__String::create(caption), "caption");
        params->setObject(__String::create(description), "description");
        params->setObject(__String::create(link), "link");
        params->setObject(__String::create(picture), "picture");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::uploadImage(CCProvider provider, const char *message, const char *filePath,
            CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::uploadImage"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(message), "message");
        params->setObject(__String::create(filePath), "filePath");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::getContacts(CCProvider provider, CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::getContacts"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    void CCProfileController::getFeed(CCProvider provider, CCReward *reward, CCError **soomlaError) {
        
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::getFeed"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
    
    bool CCProfileController::isLoggedIn(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::isLoggedIn"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, soomlaError);
        __Bool *retValue = (__Bool *) retParams->objectForKey("return");
        
        return retValue->getValue();
    }
    
    void CCProfileController::like(CCProvider provider, const char *pageName, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::like"), "method");
        params->setObject(__String::create(pageName), "pageName");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }
}
