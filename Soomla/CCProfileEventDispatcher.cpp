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

#include "CCProfileEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCDomainHelper.h"
#include "CCSoomlaEventDispatcher.h"

namespace soomla {

    USING_NS_CC;

    static CCProfileEventDispatcher *s_SharedInstance = NULL;

    CCProfileEventDispatcher *CCProfileEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCProfileEventDispatcher();
            s_SharedInstance->init();
        }

        return s_SharedInstance;
    }

    bool CCProfileEventDispatcher::init() {

        if (!CCAbstractAggregatedEventHandler::init()) {
            return false;
        }
        
        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_PROFILE_INITIALIZED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_PROFILE_INITIALIZED);
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_USER_RATING,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_USER_RATING);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_CANCELLED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_LOGIN_CANCELLED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FAILED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_LOGIN_FAILED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FINISHED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_LOGIN_FINISHED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_STARTED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_LOGIN_STARTED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_FAILED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_LOGOUT_FAILED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_FINISHED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_LOGOUT_FINISHED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_STARTED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_LOGOUT_STARTED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_FAILED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_FAILED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_FINISHED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_FINISHED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_STARTED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_STARTED);
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_FEED_FAILED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_GET_FEED_FAILED);
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_FEED_FINISHED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_GET_FEED_FINISHED);
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_FEED_STARTED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_GET_FEED_STARTED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_FAILED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_FINISHED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_STARTED);

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_USER_PROFILE_UPDATED,
                                              this,
                                              (SEL_EventHandler) &CCProfileEventDispatcher::handle__EVENT_USER_PROFILE_UPDATED);

        return true;
    }

    CCUserProfile *CCProfileEventDispatcher::extractUserProfile(CCObject *userProfileRef) {
        CCDictionary *userProfileDict = dynamic_cast<CCDictionary *>(userProfileRef);
        CC_ASSERT(userProfileDict);
        CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(
                CCDomainFactory::getInstance()->createWithDictionaryAndType(userProfileDict, CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE));
        CC_ASSERT(userProfile);
        return userProfile;
    }

    CCArray *CCProfileEventDispatcher::extractUserProfileArray(CCObject *userProfileDictArray) {
        CCArray *contactsDict = dynamic_cast<CCArray *>(userProfileDictArray);
        CC_ASSERT(contactsDict);
        return CCDomainHelper::getInstance()->getDomainsFromDictArray(contactsDict, CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE);
    }

    void CCProfileEventDispatcher::onProfileInitialized() {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onProfileInitialized();
        }
    }

    void CCProfileEventDispatcher::onUserRatingEvent() {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onUserRatingEvent();
        }
    }

    void CCProfileEventDispatcher::onLoginFailed(CCProvider provider, cocos2d::CCString *errorDescription) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginFailed(provider, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onLoginFinished(CCUserProfile *userProfile) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginFinished(userProfile);
        }
    }

    void CCProfileEventDispatcher::onLoginStarted(CCProvider provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onLogoutFailed(CCProvider provider, cocos2d::CCString *errorDescription) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLogoutFailed(provider, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onLogoutFinished(CCProvider provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLogoutFinished(provider);
        }
    }

    void CCProfileEventDispatcher::onLogoutStarted(CCProvider provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLogoutStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onGetContactsFailed(CCProvider provider, cocos2d::CCString *errorDescription) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsFailed(provider, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onGetContactsFinished(CCProvider provider, cocos2d::CCArray *contactsDict) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsFinished(provider, contactsDict);
        }
    }

    void CCProfileEventDispatcher::onGetContactsStarted(CCProvider provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onGetFeedFailed(CCProvider provider, cocos2d::CCString *errorDescription){
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetFeedFailed(provider, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onGetFeedFinished(CCProvider provider, cocos2d::CCArray *feedList) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetFeedFinished(provider, feedList);
        }
    }

    void CCProfileEventDispatcher::onGetFeedStarted(CCProvider provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetFeedStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFailedEvent(CCProvider provider, CCSocialActionType  socialActionType, cocos2d::CCString *errorDescription) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionFailedEvent(provider, socialActionType, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionFinishedEvent(provider, socialActionType);
        }
    }

    void CCProfileEventDispatcher::onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionStartedEvent(provider, socialActionType);
        }
    }

    void CCProfileEventDispatcher::onLoginCancelledEvent(CCProvider provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginCancelledEvent(provider);
        }
    }

    void CCProfileEventDispatcher::onUserProfileUpdatedEvent(CCUserProfile *userProfile) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onUserProfileUpdatedEvent(userProfile);
        }
    }

    void CCProfileEventDispatcher::handle__EVENT_PROFILE_INITIALIZED(cocos2d::CCDictionary *parameters) {
        this->onProfileInitialized();
    }

    void CCProfileEventDispatcher::handle__EVENT_USER_RATING(cocos2d::CCDictionary *parameters) {
        this->onUserRatingEvent();
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_CANCELLED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        this->onLoginCancelledEvent(CCProvider(provider->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        this->onLoginFailed(CCProvider(provider->getValue()), errorDescription);
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_FINISHED(cocos2d::CCDictionary *parameters) {
        CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
        this->onLoginFinished(userProfile);
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        this->onLoginStarted(CCProvider(provider->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGOUT_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        this->onLogoutFailed(CCProvider(provider->getValue()), errorDescription);
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGOUT_FINISHED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        this->onLogoutFinished(CCProvider(provider->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGOUT_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        this->onLogoutStarted(CCProvider(provider->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        this->onGetContactsFailed(CCProvider(provider->getValue()), errorDescription);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_FINISHED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCArray *contacts = this->extractUserProfileArray(parameters->objectForKey("contacts"));
        this->onGetContactsFinished(CCProvider(provider->getValue()), contacts);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        this->onGetContactsStarted(CCProvider(provider->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_FEED_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        this->onGetFeedFailed(CCProvider(provider->getValue()), errorDescription);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_FEED_FINISHED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCArray *feed = dynamic_cast<CCArray *>(parameters->objectForKey("feed"));
        this->onGetFeedFinished(CCProvider(provider->getValue()), feed);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_FEED_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        this->onGetFeedStarted(CCProvider(provider->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCInteger *socialActionType = dynamic_cast<CCInteger *>(parameters->objectForKey("socialActionType"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        this->onSocialActionFailedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), errorDescription);
    }

    void CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_FINISHED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCInteger *socialActionType = dynamic_cast<CCInteger *>(parameters->objectForKey("socialActionType"));
        this->onSocialActionFinishedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCInteger *socialActionType = dynamic_cast<CCInteger *>(parameters->objectForKey("socialActionType"));
        this->onSocialActionStartedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()));
    }

    void CCProfileEventDispatcher::handle__EVENT_USER_PROFILE_UPDATED(cocos2d::CCDictionary *parameters) {
        CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
        this->onUserProfileUpdatedEvent(userProfile);
    }
}
