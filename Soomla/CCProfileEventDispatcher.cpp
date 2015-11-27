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
                [this](__Dictionary *parameters) {
                    this->onProfileInitialized();
                });
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_USER_RATING,
                [this](__Dictionary *parameters) {
                    this->onUserRatingEvent();
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_CANCELLED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Bool *autoLogin = dynamic_cast<__Bool *>(parameters->objectForKey(CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginCancelled(CCProvider(provider->getValue()), autoLogin, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __Bool *autoLogin = dynamic_cast<__Bool *>(parameters->objectForKey(CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginFailed(CCProvider(provider->getValue()), errorDescription, autoLogin, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FINISHED,
                [this](__Dictionary *parameters) {
                    CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
                    __Bool *autoLogin = dynamic_cast<__Bool *>(parameters->objectForKey(CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginFinished(userProfile, autoLogin, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Bool *autoLogin = dynamic_cast<__Bool *>(parameters->objectForKey(CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginStarted(CCProvider(provider->getValue()), autoLogin, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    this->onLogoutFailed(CCProvider(provider->getValue()), errorDescription);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    this->onLogoutFinished(CCProvider(provider->getValue()));
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    this->onLogoutStarted(CCProvider(provider->getValue()));
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __Bool *fromStart = dynamic_cast<__Bool *>(parameters->objectForKey("fromStart"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetContactsFailed(CCProvider(provider->getValue()), errorDescription, fromStart, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Array *contacts = this->extractUserProfileArray(parameters->objectForKey("contacts"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    __Bool *hasMore = dynamic_cast<__Bool *>(parameters->objectForKey("hasMore"));
                    this->onGetContactsFinished(CCProvider(provider->getValue()), contacts, payload, hasMore);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Bool *fromStart = dynamic_cast<__Bool *>(parameters->objectForKey("fromStart"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetContactsStarted(CCProvider(provider->getValue()), fromStart, payload);
                });
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_FEED_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetFeedFailed(CCProvider(provider->getValue()), errorDescription, payload);
                });
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_FEED_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Array *feed = dynamic_cast<__Array *>(parameters->objectForKey("feed"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    __Bool *hasMore = dynamic_cast<__Bool *>(parameters->objectForKey("hasMore"));
                    this->onGetFeedFinished(CCProvider(provider->getValue()), feed, payload, hasMore);
                });
        
        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_FEED_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetFeedStarted(CCProvider(provider->getValue()), payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Integer *socialActionType = dynamic_cast<__Integer *>(parameters->objectForKey("socialActionType"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onSocialActionFailedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), errorDescription, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Integer *socialActionType = dynamic_cast<__Integer *>(parameters->objectForKey("socialActionType"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onSocialActionFinishedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Integer *socialActionType = dynamic_cast<__Integer *>(parameters->objectForKey("socialActionType"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onSocialActionStartedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_USER_PROFILE_UPDATED,
                [this](__Dictionary *parameters) {
                    CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
                    this->onUserProfileUpdatedEvent(userProfile);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_INVITE_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Integer *socialActionType = dynamic_cast<__Integer *>(parameters->objectForKey("socialActionType"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onInviteStartedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_INVITE_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Integer *socialActionType = dynamic_cast<__Integer *>(parameters->objectForKey("socialActionType"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    __String *requestId = dynamic_cast<__String *>(parameters->objectForKey("requestId"));;
                    __Array *invitedIds = dynamic_cast<__Array *>(parameters->objectForKey("invitedIds"));
                    this->onInviteFinishedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), requestId, invitedIds, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_INVITE_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Integer *socialActionType = dynamic_cast<__Integer *>(parameters->objectForKey("socialActionType"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onInviteFailedEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), errorDescription, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_INVITE_CANCELLED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Integer *socialActionType = dynamic_cast<__Integer *>(parameters->objectForKey("socialActionType"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onInviteCancelledEvent(CCProvider(provider->getValue()), CCSocialActionType(socialActionType->getValue()), payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_GET_LEADERBOARDS_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetLeaderboardsStartedEvent(CCProvider(provider->getValue()), payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_GET_LEADERBOARDS_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Array *leaderboards = this->extractLeaderboardArray(parameters->objectForKey("leaderboards"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetLeaderboardsFinishedEvent(CCProvider(provider->getValue()), leaderboards, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_GET_LEADERBOARDS_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetLeaderboardsFailedEvent(CCProvider(provider->getValue()), errorDescription, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_GET_SCORES_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    CCLeaderboard *leaderboard = new CCLeaderboard();
                    leaderboard->initWithDictionary(dynamic_cast<__Dictionary *>(parameters->objectForKey("leaderboard")));
                    __Bool *fromStart = dynamic_cast<__Bool *>(parameters->objectForKey("fromStart"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetScoresStartedEvent(CCProvider(provider->getValue()), leaderboard, fromStart, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_GET_SCORES_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    CCLeaderboard *leaderboard = new CCLeaderboard();
                    leaderboard->initWithDictionary(dynamic_cast<__Dictionary *>(parameters->objectForKey("leaderboard")));
                    __Array *scores = this->extractScoreArray(parameters->objectForKey("scores"));
                    __Bool *hasMore = dynamic_cast<__Bool *>(parameters->objectForKey("hasMore"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetScoresFinishedEvent(CCProvider(provider->getValue()), leaderboard, scores, hasMore, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_GET_SCORES_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    CCLeaderboard *leaderboard = new CCLeaderboard();
                    leaderboard->initWithDictionary(dynamic_cast<__Dictionary *>(parameters->objectForKey("leaderboard")));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __Bool *fromStart = dynamic_cast<__Bool *>(parameters->objectForKey("fromStart"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetScoresFailedEvent(CCProvider(provider->getValue()), leaderboard, fromStart, errorDescription, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_SUBMIT_SCORE_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    CCLeaderboard *leaderboard = new CCLeaderboard();
                    leaderboard->initWithDictionary(dynamic_cast<__Dictionary *>(parameters->objectForKey("leaderboard")));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onSubmitScoreStartedEvent(CCProvider(provider->getValue()), leaderboard, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_SUBMIT_SCORE_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    CCLeaderboard *leaderboard = new CCLeaderboard();
                    leaderboard->initWithDictionary(dynamic_cast<__Dictionary *>(parameters->objectForKey("leaderboard")));
                    CCScore *score = new CCScore();
                    score->initWithDictionary(dynamic_cast<__Dictionary *>(parameters->objectForKey("score")));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onSubmitScoreFinishedEvent(CCProvider(provider->getValue()), leaderboard, score, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_UP_SUBMIT_SCORE_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    CCLeaderboard *leaderboard = new CCLeaderboard();
                    leaderboard->initWithDictionary(dynamic_cast<__Dictionary *>(parameters->objectForKey("leaderboard")));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onSubmitScoreFailedEvent(CCProvider(provider->getValue()), leaderboard, errorDescription, payload);
                });

        return true;
    }

    CCUserProfile *CCProfileEventDispatcher::extractUserProfile(Ref *userProfileRef) {
        __Dictionary *userProfileDict = dynamic_cast<__Dictionary *>(userProfileRef);
        CC_ASSERT(userProfileDict);
        CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(
                CCDomainFactory::getInstance()->createWithDictionaryAndType(userProfileDict, CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE));
        CC_ASSERT(userProfile);
        return userProfile;
    }

    __Array *CCProfileEventDispatcher::extractUserProfileArray(Ref *userProfileDictArray) {
        __Array *contactsDict = dynamic_cast<__Array *>(userProfileDictArray);
        CC_ASSERT(contactsDict);
        return CCDomainHelper::getInstance()->getDomainsFromDictArray(contactsDict, CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE);
    }

    __Array *CCProfileEventDispatcher::extractLeaderboardArray(Ref *leaderboardDictArray) {
        __Array *leaderboardDict = dynamic_cast<__Array *>(leaderboardDictArray);
        CC_ASSERT(leaderboardDict);
        return CCDomainHelper::getInstance()->getDomainsFromDictArray(leaderboardDict, CCProfileConsts::JSON_JSON_TYPE_LEADERBOARD);
    }

    __Array *CCProfileEventDispatcher::extractScoreArray(Ref *scoreDictArray) {
        __Array *scoreDict = dynamic_cast<__Array *>(scoreDictArray);
        CC_ASSERT(scoreDict);
        return CCDomainHelper::getInstance()->getDomainsFromDictArray(scoreDict, CCProfileConsts::JSON_JSON_TYPE_SCORE);
    }

    void CCProfileEventDispatcher::onProfileInitialized() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_PROFILE_INITIALIZED);
    }

    void CCProfileEventDispatcher::onUserRatingEvent() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_USER_RATING);
    }

    void CCProfileEventDispatcher::onLoginFailed(CCProvider provider, cocos2d::__String *message, cocos2d::__Bool *autoLogin, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(autoLogin, CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_LOGIN_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onLoginFinished(CCUserProfile *userProfile, cocos2d::__Bool *autoLogin, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(userProfile, CCProfileConsts::DICT_ELEMENT_USER_PROFILE);
        eventData->setObject(autoLogin, CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_LOGIN_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onLoginStarted(CCProvider provider, cocos2d::__Bool *autoLogin, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(autoLogin, CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_LOGIN_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onLoginCancelled(CCProvider provider, cocos2d::__Bool *autoLogin, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(autoLogin, CCProfileConsts::DICT_ELEMENT_AUTO_LOGIN);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_LOGIN_CANCELLED, eventData);
    }

    void CCProfileEventDispatcher::onLogoutFailed(CCProvider provider, cocos2d::__String *message) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_LOGOUT_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onLogoutFinished(CCProvider provider) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_LOGOUT_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onLogoutStarted(CCProvider provider) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_LOGOUT_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onGetContactsFailed(CCProvider provider, __String *message, __Bool *fromStart, __String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(fromStart, CCProfileConsts::DICT_ELEMENT_FROM_START);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_GET_CONTACTS_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onGetContactsFinished(CCProvider provider, cocos2d::__Array *contactsDict, cocos2d::__String *payload, cocos2d::__Bool *hasMore) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(contactsDict, CCProfileConsts::DICT_ELEMENT_CONTACTS);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        eventData->setObject(hasMore, CCProfileConsts::DICT_ELEMENT_HAS_MORE);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_GET_CONTACTS_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onGetContactsStarted(CCProvider provider, cocos2d::__Bool *fromStart, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(fromStart, CCProfileConsts::DICT_ELEMENT_FROM_START);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_GET_CONTACTS_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onGetFeedFailed(CCProvider provider, cocos2d::__String *message, cocos2d::__String *payload){
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_GET_FEED_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onGetFeedFinished(CCProvider provider, cocos2d::__Array *feedList, cocos2d::__String *payload, cocos2d::__Bool *hasMore) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(feedList, CCProfileConsts::DICT_ELEMENT_FEEDS);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        eventData->setObject(hasMore, CCProfileConsts::DICT_ELEMENT_HAS_MORE);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_GET_FEED_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onGetFeedStarted(CCProvider provider, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_GET_FEED_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onSocialActionFailedEvent(CCProvider provider, CCSocialActionType  socialActionType,
                                                             cocos2d::__String *message, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(__Integer::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(__Integer::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(__Integer::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onUserProfileUpdatedEvent(CCUserProfile *userProfile) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(userProfile, CCProfileConsts::DICT_ELEMENT_USER_PROFILE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_USER_PROFILE_UPDATED, eventData);
    }

    void CCProfileEventDispatcher::onInviteStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(__Integer::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_INVITE_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onInviteFinishedEvent(CCProvider provider, CCSocialActionType socialActionType,
            cocos2d::__String *requestId, cocos2d::__Array *invitedIds, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(__Integer::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(requestId, CCProfileConsts::DICT_ELEMENT_REQUEST_ID);
        eventData->setObject(invitedIds, CCProfileConsts::DICT_ELEMENT_INVITED_IDS);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_INVITE_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onInviteFailedEvent(CCProvider provider, CCSocialActionType  socialActionType,
            cocos2d::__String *message, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(__Integer::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_INVITE_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onInviteCancelledEvent(CCProvider provider, CCSocialActionType  socialActionType, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(__Integer::create(socialActionType), CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_INVITE_CANCELLED, eventData);
    }

    void CCProfileEventDispatcher::onGetLeaderboardsStartedEvent(CCProvider provider, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_GET_LEADERBOARDS_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onGetLeaderboardsFinishedEvent(CCProvider provider, cocos2d::__Array *leaderboards, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(leaderboards, CCProfileConsts::DICT_ELEMENT_LEADERBOARDS);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_GET_LEADERBOARDS_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onGetLeaderboardsFailedEvent(CCProvider provider, cocos2d::__String *message, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_GET_LEADERBOARDS_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onGetScoresStartedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__Bool *fromStart, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(leaderboard, CCProfileConsts::DICT_ELEMENT_LEADERBOARD);
        eventData->setObject(fromStart, CCProfileConsts::DICT_ELEMENT_FROM_START);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_GET_SCORES_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onGetScoresFinishedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__Array *scores, cocos2d::__Bool *hasMore, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(leaderboard, CCProfileConsts::DICT_ELEMENT_LEADERBOARD);
        eventData->setObject(scores, CCProfileConsts::DICT_ELEMENT_SCORES);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);
        eventData->setObject(hasMore, CCProfileConsts::DICT_ELEMENT_HAS_MORE);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_GET_SCORES_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onGetScoresFailedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__Bool *fromStart, cocos2d::__String *message, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(leaderboard, CCProfileConsts::DICT_ELEMENT_LEADERBOARD);
        eventData->setObject(fromStart, CCProfileConsts::DICT_ELEMENT_FROM_START);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_GET_SCORES_FAILED, eventData);
    }

    void CCProfileEventDispatcher::onSubmitScoreStartedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(leaderboard, CCProfileConsts::DICT_ELEMENT_LEADERBOARD);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_SUBMIT_SCORE_STARTED, eventData);
    }

    void CCProfileEventDispatcher::onSubmitScoreFinishedEvent(CCProvider provider, CCLeaderboard *leaderboard, CCScore *score, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(leaderboard, CCProfileConsts::DICT_ELEMENT_LEADERBOARD);
        eventData->setObject(score, CCProfileConsts::DICT_ELEMENT_SCORE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_SUBMIT_SCORE_FINISHED, eventData);
    }

    void CCProfileEventDispatcher::onSubmitScoreFailedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__String *message, cocos2d::__String *payload) {
        __Dictionary *eventData = __Dictionary::create();
        eventData->setObject(__Integer::create(provider), CCProfileConsts::DICT_ELEMENT_PROVIDER);
        eventData->setObject(leaderboard, CCProfileConsts::DICT_ELEMENT_LEADERBOARD);
        eventData->setObject(message, CCProfileConsts::DICT_ELEMENT_MESSAGE);
        eventData->setObject(payload, CCProfileConsts::DICT_ELEMENT_PAYLOAD);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCProfileConsts::EVENT_UP_SUBMIT_SCORE_FAILED, eventData);
    }
}
