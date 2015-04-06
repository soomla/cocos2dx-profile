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
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_PROFILE_INITIALIZED);
    }

    void CCProfileEventDispatcher::onUserRatingEvent() {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_USER_RATING);
    }

    void CCProfileEventDispatcher::onLoginFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(errorDescription, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_LOGIN_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onLoginFinished(CCUserProfile *userProfile, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(userProfile, CCProfileConsts::DICT_ELEMENT_USER_PROFILE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_LOGIN_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onLoginStarted(CCProvider provider, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_LOGIN_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onLogoutFailed(CCProvider provider, cocos2d::CCString *message) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_LOGOUT_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onLogoutFinished(CCProvider provider) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_LOGOUT_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onLogoutStarted(CCProvider provider) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_LOGOUT_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onGetContactsFailed(CCProvider provider, cocos2d::CCString *message, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_GET_CONTACTS_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onGetContactsFinished(CCProvider provider, cocos2d::CCArray *contactsDict, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(contactsDict, CCProfileConsts::DICT_ELEMENT_CONTACTS);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_GET_CONTACTS_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onGetContactsStarted(CCProvider provider, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_GET_CONTACTS_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onGetFeedFailed(CCProvider provider, cocos2d::CCString *message, cocos2d::CCString *payload){
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_GET_FEED_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onGetFeedFinished(CCProvider provider, cocos2d::CCArray *feedList, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(feedList, CCProfileConsts::DICT_ELEMENT_FEEDS);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_GET_FEED_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onGetFeedStarted(CCProvider provider, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_GET_FEED_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onSocialActionFailedEvent(CCProvider provider, CCSocialActionType  socialActionType,
                                                             cocos2d::CCString *message, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(CCInteger::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(CCInteger::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(CCInteger::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onLoginCancelledEvent(CCProvider provider, cocos2d::CCString *payload) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(CCInteger::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_LOGIN_CANCELLED, eventData);
    }

    void CCProfileEventDispatcher::onUserProfileUpdatedEvent(CCUserProfile *userProfile) {
        CCDictionary *eventData = CCDictionary::create();
        eventData->setObject(userProfile, CCProfileConsts::DICT_ELEMENT_USER_PROFILE);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CCProfileConsts::EVENT_USER_PROFILE_UPDATED, eventData);
    }

    void CCProfileEventDispatcher::handle__EVENT_PROFILE_INITIALIZED(cocos2d::CCDictionary *parameters) {
        this->onProfileInitialized();
    }

    void CCProfileEventDispatcher::handle__EVENT_USER_RATING(cocos2d::CCDictionary *parameters) {
        this->onUserRatingEvent();
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_CANCELLED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onLoginCancelledEvent(CCProvider(provider->getValue()), payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onLoginFailed(CCProvider(provider->getValue()), errorDescription, payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_FINISHED(cocos2d::CCDictionary *parameters) {
        CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onLoginFinished(userProfile, payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_LOGIN_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onLoginStarted(CCProvider(provider->getValue()), payload);
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
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onGetContactsFailed(CCProvider(provider->getValue()), errorDescription, payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_FINISHED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCArray *contacts = this->extractUserProfileArray(parameters->objectForKey("contacts"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onGetContactsFinished(CCProvider(provider->getValue()), contacts, payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_CONTACTS_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onGetContactsStarted(CCProvider(provider->getValue()), payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_FEED_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onGetFeedFailed(CCProvider(provider->getValue()), errorDescription, payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_FEED_FINISHED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCArray *feed = dynamic_cast<CCArray *>(parameters->objectForKey("feed"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onGetFeedFinished(CCProvider(provider->getValue()), feed, payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_GET_FEED_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onGetFeedStarted(CCProvider(provider->getValue()), payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_FAILED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCInteger *socialActionType = dynamic_cast<CCInteger *>(parameters->objectForKey("socialActionType"));
        CCString *errorDescription = dynamic_cast<CCString *>(parameters->objectForKey("errorDescription"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onSocialActionFailedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), errorDescription, payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_FINISHED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCInteger *socialActionType = dynamic_cast<CCInteger *>(parameters->objectForKey("socialActionType"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onSocialActionFinishedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_SOCIAL_ACTION_STARTED(cocos2d::CCDictionary *parameters) {
        CCInteger* provider = dynamic_cast<CCInteger *>(parameters->objectForKey("provider"));
        CCInteger *socialActionType = dynamic_cast<CCInteger *>(parameters->objectForKey("socialActionType"));
        CCString *payload = dynamic_cast<CCString *>(parameters->objectForKey("payload"));
        this->onSocialActionStartedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), payload);
    }

    void CCProfileEventDispatcher::handle__EVENT_USER_PROFILE_UPDATED(cocos2d::CCDictionary *parameters) {
        CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
        this->onUserProfileUpdatedEvent(userProfile);
    }
}
