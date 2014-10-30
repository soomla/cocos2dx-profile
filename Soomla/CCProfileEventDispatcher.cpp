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
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginCancelledEvent(CCProvider(provider->getValue()), payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FAILED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginFailed(CCProvider(provider->getValue()), errorDescription, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FINISHED,
                [this](__Dictionary *parameters) {
                    CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginFinished(userProfile, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onLoginStarted(CCProvider(provider->getValue()), payload);
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
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetContactsFailed(CCProvider(provider->getValue()), errorDescription, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_FINISHED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __Array *contacts = this->extractUserProfileArray(parameters->objectForKey("contacts"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetContactsFinished(CCProvider(provider->getValue()), contacts, payload);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_STARTED,
                [this](__Dictionary *parameters) {
                    __Integer* provider = dynamic_cast<__Integer *>(parameters->objectForKey("provider"));
                    __String *payload = dynamic_cast<__String *>(parameters->objectForKey("payload"));
                    this->onGetContactsStarted(CCProvider(provider->getValue()), payload);
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
                    this->onGetFeedFinished(CCProvider(provider->getValue()), feed, payload);
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

    void CCProfileEventDispatcher::onLoginFailed(CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginFailed(provider, errorDescription, payload);
        }
    }

    void CCProfileEventDispatcher::onLoginFinished(CCUserProfile *userProfile, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginFinished(userProfile, payload);
        }
    }

    void CCProfileEventDispatcher::onLoginStarted(CCProvider provider, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginStarted(provider, payload);
        }
    }

    void CCProfileEventDispatcher::onLogoutFailed(CCProvider provider, cocos2d::__String *errorDescription) {
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

    void CCProfileEventDispatcher::onGetContactsFailed(CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsFailed(provider, errorDescription, payload);
        }
    }

    void CCProfileEventDispatcher::onGetContactsFinished(CCProvider provider, cocos2d::__Array *contactsDict, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsFinished(provider, contactsDict, payload);
        }
    }

    void CCProfileEventDispatcher::onGetContactsStarted(CCProvider provider, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsStarted(provider, payload);
        }
    }

    void CCProfileEventDispatcher::onGetFeedFailed(CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload){
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetFeedFailed(provider, errorDescription, payload);
        }
    }

    void CCProfileEventDispatcher::onGetFeedFinished(CCProvider provider, cocos2d::__Array *feedList, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetFeedFinished(provider, feedList, payload);
        }
    }

    void CCProfileEventDispatcher::onGetFeedStarted(CCProvider provider, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetFeedStarted(provider, payload);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFailedEvent(CCProvider provider, CCSocialActionType  socialActionType,
                                                             cocos2d::__String *errorDescription, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionFailedEvent(provider, socialActionType, errorDescription, payload);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionFinishedEvent(provider, socialActionType, payload);
        }
    }

    void CCProfileEventDispatcher::onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionStartedEvent(provider, socialActionType, payload);
        }
    }

    void CCProfileEventDispatcher::onLoginCancelledEvent(CCProvider provider, cocos2d::__String *payload) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginCancelledEvent(provider, payload);
        }
    }

    void CCProfileEventDispatcher::onUserProfileUpdatedEvent(CCUserProfile *userProfile) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onUserProfileUpdatedEvent(userProfile);
        }
    }
}
