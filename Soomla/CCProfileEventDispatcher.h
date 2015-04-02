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
#include "CCUserProfile.h"
#include "CCSocialActionUtils.h"
#include "CCUserProfileUtils.h"

namespace soomla {

	/** 
     @class CCProfileEventDispatcher
     @brief Fires event when received from the native implementation.
     
     Signs up to native Profile events through CCSoomlaEventDispatcher.
     When the events arrive this class fires the repective event through
     the Cocos2dx Event Dispatcher.
     */
    class CCProfileEventDispatcher : public cocos2d::CCObject {
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
         Fired after Profile has been initialized.
         
         Event Name - CCProfileConsts::EVENT_PROFILE_INITIALIZED
         */
        virtual void onProfileInitialized();
        
        /**
         Fired when the market page for the app is opened.
         
         Event Name - CCProfileConsts::EVENT_USER_RATING
         */
        virtual void onUserRatingEvent();

        /**
         Fired when the login process to a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_LOGIN_FAILED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the login has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - CCString - a Description of the 
         reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginFailed(CCProvider provider, cocos2d::CCString *message, cocos2d::CCString *payload);

        /**
         Fired when the login process finishes successfully.
         
         Event Name - CCProfileConsts::EVENT_LOGIN_FINISHED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's 
         profile from the logged in provider.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginFinished(CCUserProfile *userProfile, cocos2d::CCString *payload);

        /**
         Fired when the login process to a provider has started.
         
         Event Name - CCProfileConsts::EVENT_LOGIN_STARTED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         where the login has started.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginStarted(CCProvider provider, cocos2d::CCString *payload);

        /**
         Fired when the logout process from a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_LOGOUT_FAILED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the logout has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - CCString - a Description of the 
         reason for failure.
         */
        virtual void onLogoutFailed(CCProvider provider, cocos2d::CCString *message);

        /**
         Fired when the logout process from a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_LOGOUT_FINISHED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the logout has finished.
         */
        virtual void onLogoutFinished(CCProvider provider);
        
        /**
         Fired when the logout process from a provider has started.
         
         Event Name - CCProfileConsts::EVENT_LOGOUT_STARTED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the login has started.
         */
        virtual void onLogoutStarted(CCProvider provider);

        /**
         Fired when the get contacts process from a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_GET_CONTACTS_FAILED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the get contacts process has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - CCString - a Description of the 
         reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsFailed(CCProvider provider, cocos2d::CCString *message, cocos2d::CCString *payload);

        /**
         Fired when the get contacts process from a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_GET_CONTACTS_FINISHED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the get contacts process finished.
         CCProfileConsts::DICT_ELEMENT_CONTACTS - CCArray - an Array of contacts 
         represented by CCUserProfile.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsFinished(CCProvider provider, cocos2d::CCArray *contactsDict, cocos2d::CCString *payload);

        /**
         Fired when the get contacts process from a provider has started.
         
         Event Name - CCProfileConsts::EVENT_GET_CONTACTS_STARTED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the get contacts process started.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsStarted(CCProvider provider, cocos2d::CCString *payload);

        /**
         Fired when the get feed process from a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_GET_FEED_FAILED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the get feed process has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - CCString - a Description of 
         the reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedFailed(CCProvider provider, cocos2d::CCString *message, cocos2d::CCString *payload);

        /**
         Fired when the get feed process from a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_GET_FEED_FINISHED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the get feed process finished.
         CCProfileConsts::DICT_ELEMENT_FEEDS - CCArray - an Array of feed entries 
         represented by CCString.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedFinished(CCProvider provider, cocos2d::CCArray *feedList, cocos2d::CCString *payload);

        /**
         Fired when the get feed process from a provider has started.
         
         Event Name - CCProfileConsts::EVENT_GET_FEED_STARTED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the get feed process started
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedStarted(CCProvider provider, cocos2d::CCString *payload);

        /**
         Fired when a generic social action on a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the social action has failed.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - CCInteger - The social 
         action which failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - CCString - a Description of 
         the reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *message, cocos2d::CCString *payload);

        /**
         Fired when a generic social action on a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the social action has finished.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - CCInteger - The social 
         action which finished.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload);

        /**
         Fired when a generic social action on a provider has started.
         
         Event Name - CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the social action has started.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - CCInteger - The social 
         action which started.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload);

        /**
         Fired when the login process to a provider has been cancelled.
         
         Event Name - CCProfileConsts::EVENT_LOGIN_CANCELLED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - CCInteger - The provider on 
         which the login has cancelled.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - CCString - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginCancelledEvent(CCProvider provider, cocos2d::CCString *payload);
        
        /**
         Fired when a user profile from a provider has been retrieved.
         
         Event Name - CCProfileConsts::EVENT_USER_PROFILE_UPDATED
         Event Data (CCDictionary):
         CCProfileConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's 
         profile which was updated.
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
