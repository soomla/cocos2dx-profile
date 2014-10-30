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

#ifndef __CCProfileEventDispatcher_H_
#define __CCProfileEventDispatcher_H_

#include "cocos2d.h"
#include "CCProfileEventHandler.h"
#include "CCAbstractAggregatedEventHandler.h"
#include "CCSocialActionUtils.h"
#include "CCUserProfileUtils.h"

namespace soomla {

	/** 
     @class CCProfileEventDispatcher
     @brief Calls event handler functions when events are fired
     
     Signs up to native Profile events through CCSoomlaEventDispatcher.
     When the events arrive this class calls event handler functions, to tie
     it to your event handler call addEventHandler().
     */
    class CCProfileEventDispatcher : public CCAbstractAggregatedEventHandler<CCProfileEventHandler>, public CCProfileEventHandler {
    public:
		/**
		   This class is singleton, access it with this function.
		 */
        static CCProfileEventDispatcher *getInstance();

        /**
         Initializes the event dispatcher after construction
         */
        bool init();

        /**
        see parent
        */
        virtual void onProfileInitialized();
        
        /**
         see parent
         */
        virtual void onUserRatingEvent();

        /**
         see parent
         */
        virtual void onLoginFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onLoginFinished(CCUserProfile *userProfile, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onLoginStarted(CCProvider provider, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onLogoutFailed(CCProvider provider, cocos2d::CCString *errorDescription);

        /**
         see parent
         */
        virtual void onLogoutFinished(CCProvider provider);
        
        /**
         see parent
         */
        virtual void onLogoutStarted(CCProvider provider);

        /**
         see parent
         */
        virtual void onGetContactsFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onGetContactsFinished(CCProvider provider, cocos2d::CCArray *contactsDict, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onGetContactsStarted(CCProvider provider, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onGetFeedFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onGetFeedFinished(CCProvider provider, cocos2d::CCArray *feedList, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onGetFeedStarted(CCProvider provider, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload);

        /**
         see parent
         */
        virtual void onLoginCancelledEvent(CCProvider provider, cocos2d::CCString *payload);
        
        /**
         see parent
         */
        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);
        
        void handle__EVENT_PROFILE_INITIALIZED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_USER_RATING(cocos2d::CCDictionary *parameters);
        
        void handle__EVENT_LOGIN_CANCELLED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LOGIN_FAILED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LOGIN_FINISHED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LOGIN_STARTED(cocos2d::CCDictionary *parameters);
        
        void handle__EVENT_LOGOUT_FAILED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LOGOUT_FINISHED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_LOGOUT_STARTED(cocos2d::CCDictionary *parameters);
        
        void handle__EVENT_GET_CONTACTS_FAILED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_GET_CONTACTS_FINISHED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_GET_CONTACTS_STARTED(cocos2d::CCDictionary *parameters);
        
        void handle__EVENT_GET_FEED_FAILED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_GET_FEED_FINISHED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_GET_FEED_STARTED(cocos2d::CCDictionary *parameters);
        
        void handle__EVENT_SOCIAL_ACTION_FAILED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_SOCIAL_ACTION_FINISHED(cocos2d::CCDictionary *parameters);
        void handle__EVENT_SOCIAL_ACTION_STARTED(cocos2d::CCDictionary *parameters);
        
        void handle__EVENT_USER_PROFILE_UPDATED(cocos2d::CCDictionary *parameters);

    private:
        CCUserProfile *extractUserProfile(CCObject *userProfileRef);
        cocos2d::CCArray *extractUserProfileArray(CCObject *userProfileDictArray);
    };
};

#endif //__CCProfileEventDispatcher_H_
