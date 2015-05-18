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

#include "CCSoomlaProfile.h"
#include "CCNdkBridge.h"
#include "CCSoomlaMacros.h"
#include "CCDomainFactory.h"
#include "CCProfileBridge.h"
#include "CCSoomlaUtils.h"

using namespace cocos2d;
typedef DictElement CCDictElement;

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

    void CCSoomlaProfile::initialize(cocos2d::__Dictionary *profileParams) {

        if (CCSoomlaProfile::getInstance()->mInited) {
            CCSoomlaUtils::logError(TAG, "SoomlaProfile is already initialized. You can't initialize it twice!");
            return;
        }

        CCProfileBridge::initShared(profileParams);

        CCSoomlaProfile::getInstance()->mInited = true;
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    void CCSoomlaProfile::login(CCProvider provider, CCReward *reward, CCError **soomlaError) {
        this->login(provider, "", reward, soomlaError);
    }

    void CCSoomlaProfile::login(CCProvider provider, const char *payload, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::login"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(payload), "payload");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    void CCSoomlaProfile::login(CCProvider provider, CCError **soomlaError) {
        this->login(provider, "", NULL, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    void CCSoomlaProfile::logout(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::logout"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        CCNdkBridge::callNative(params, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    /// Missing user info for Twitter: email, gender, birthday.
    ///
    CCUserProfile *CCSoomlaProfile::getStoredUserProfile(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::getStoredUserProfile"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative(params, NULL);
        SL_SAFE_CREATE_FROM_RETURN(CCUserProfile *, retValue, retParams);
        return retValue;
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    void CCSoomlaProfile::updateStatus(CCProvider provider, const char *status, const char *payload, CCReward *reward, CCError **soomlaError) {
        this->updateStatus(provider, status, "", reward, false, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    void CCSoomlaProfile::updateStatus(CCProvider provider, const char *status, const char *payload, CCReward *reward, bool showConfirmation, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::updateStatus"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(status), "status");
        params->setObject(__String::create(payload), "payload");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        params->setObject(__Bool::create(showConfirmation), "showConfirmation");
        CCNdkBridge::callNative(params, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    void CCSoomlaProfile::updateStatus(CCProvider provider, const char *status, CCReward *reward, CCError **soomlaError) {
        this->updateStatus(provider, status, "", reward, false, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Google+
    /// NOTE:
    /// 1. Twitter does NOT support dialogs.
    /// 2. Google+ uses dialogs by default.
    ///
    void CCSoomlaProfile::updateStatusDialog(CCProvider provider, const char *link, const char *payload, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::updateStatusDialog"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(payload), "payload");
        if (link) {
            params->setObject(__String::create(link), "link");
        }
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::updateStatusDialog(CCProvider provider, const char *link, CCReward *reward, CCError **soomlaError) {
        this->updateStatusDialog(provider, link, "", reward, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    /// NOTE:
    /// Partial support for Twitter and Google+ - only message and link
    ///
    void CCSoomlaProfile::updateStory(CCProvider provider, const char *message, const char *name,
            const char *caption, const char *description, const char *link, const char *picture,
            const char *payload, CCReward *reward, CCError **soomlaError) {

        this->updateStory(provider, message, name, caption, description, link, picture, payload, reward, false, soomlaError);
    }

    void CCSoomlaProfile::updateStory(CCProvider provider, const char *message, const char *name,
                                      const char *caption, const char *description, const char *link, const char *picture,
                                      CCReward *reward, CCError **soomlaError) {
        this->updateStory(provider, message, name, caption, description, link, picture, "", reward, soomlaError);
    }



    void CCSoomlaProfile::updateStory(CCProvider provider, const char *message, const char *name, const char *caption, const char *description, const char *link, const char *picture, const char *payload, CCReward *reward, bool showConfirmation, CCError **soomlaError) {

        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::updateStory"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(message), "message");
        params->setObject(__String::create(name), "name");
        params->setObject(__String::create(caption), "caption");
        params->setObject(__String::create(description), "description");
        params->setObject(__String::create(link), "link");
        params->setObject(__String::create(picture), "picture");
        params->setObject(__String::create(payload), "payload");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        params->setObject(__Bool::create(showConfirmation), "showConfirmation");
        CCNdkBridge::callNative(params, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Google+.
    /// Note:
    /// 1. Twitter does NOT support dialogs.
    /// 2. Google+ uses dialogs by default.
    /// 3. Partial support for Google+ - only message and link
    ///
    void CCSoomlaProfile::updateStoryDialog(CCProvider provider, const char *name,
                                      const char *caption, const char *description, const char *link, const char *picture,
                                      const char *payload, CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::updateStoryDialog"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(payload), "payload");
        if (name) {
            params->setObject(__String::create(name), "name");
        }
        if (caption) {
            params->setObject(__String::create(caption), "caption");
        }
        if (description) {
            params->setObject(__String::create(description), "description");
        }
        if (link) {
            params->setObject(__String::create(link), "link");
        }
        if (picture) {
            params->setObject(__String::create(picture), "picture");
        }
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::updateStoryDialog(CCProvider provider, const char *name,
                                            const char *caption, const char *description, const char *link, const char *picture,
                                            CCReward *reward, CCError **soomlaError) {

        this->updateStoryDialog(provider, name, caption, description, link, picture, "", reward, soomlaError);
    }

    void CCSoomlaProfile::uploadImage(CCProvider provider, const char *message, const char *filePath,
            const char *payload, CCReward *reward, CCError **soomlaError) {
        this->uploadImage(provider, message, filePath, payload, reward, false, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+.
    /// Note:
    /// Google+ - not supported targetting Android.
    ///
    void CCSoomlaProfile::uploadImage(CCProvider provider, const char *message, const char *filePath,
            const char *payload, CCReward *reward, bool showConfirmation, CCError **soomlaError) {

        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::uploadImage"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__String::create(message), "message");
        params->setObject(__String::create(filePath), "filePath");
        params->setObject(__String::create(payload), "payload");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        params->setObject(__Bool::create(showConfirmation), "showConfirmation");
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::uploadImage(CCProvider provider, const char *message, const char *filePath,
                                      CCReward *reward, CCError **soomlaError) {

        this->uploadImage(provider, message, filePath, "", reward, false, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    /// Note:
    /// 1. Twitter - missing contact info: email, gender, birthday.
    /// 2. Google+ - missing contact info: username, email, gender, bithday
    ///
    void CCSoomlaProfile::getContacts(CCProvider provider, bool fromStart, const char *payload, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::getContacts"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__Bool::create(fromStart), "fromStart");
        params->setObject(__String::create(payload), "payload");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::getContacts(CCProvider provider, CCReward *reward, CCError **soomlaError) {

        this->getContacts(provider, false, "", reward, soomlaError);
    }

    void CCSoomlaProfile::getContacts(CCProvider provider, bool fromStart, CCReward *reward, CCError **soomlaError) {
        this->getContacts(provider, fromStart, "", reward, soomlaError);
    }

    ///
    /// Supported platforms: Facebook.
    ///
    void CCSoomlaProfile::getFeed(CCProvider provider, bool fromStart, const char *payload, CCReward *reward, CCError **soomlaError) {

        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::getFeed"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        params->setObject(__Bool::create(fromStart), "fromStart");
        params->setObject(__String::create(payload), "payload");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::getFeed(CCProvider provider, CCReward *reward, CCError **soomlaError) {

        this->getFeed(provider, false, "", reward, soomlaError);
    }


    void CCSoomlaProfile::getFeed(CCProvider provider, bool fromStart, CCReward *reward, CCError **soomlaError) {

        this->getFeed(provider, fromStart, "", reward, soomlaError);
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    bool CCSoomlaProfile::isLoggedIn(CCProvider provider, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::isLoggedIn"), "method");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, soomlaError);
        __Bool *retValue = (__Bool *) retParams->objectForKey("return");

        if (retValue != NULL) {
            return retValue->getValue();
        }

        return false;
    }

    ///
    /// Supported platforms: Facebook, Twitter, Google+
    ///
    void CCSoomlaProfile::like(CCProvider provider, const char *pageId, CCReward *reward, CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::like"), "method");
        params->setObject(__String::create(pageId), "pageId");
        params->setObject(CCUserProfileUtils::providerEnumToString(provider), "provider");
        if (reward) {
            params->setObject(reward->toDictionary(), "reward");
        }
        CCNdkBridge::callNative(params, soomlaError);
    }

    void CCSoomlaProfile::openAppRatingPage(CCError **soomlaError) {
        CC_ASSERT(mInited);
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCSoomlaProfile::openAppRatingPage"), "method");
        CCNdkBridge::callNative(params, soomlaError);
    }
}
