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
     When the events arrive this class calls event handler functions, to tie
     it to your event handler call addEventHandler().
     */
    class CCProfileEventDispatcher : public cocos2d::Ref {
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
         
         Event Name - CCStoreConsts::EVENT_PROFILE_INITIALIZED
         */
        virtual void onProfileInitialized();
        
        /**
         Fired when the market page for the app is opened.
         
         Event Name - CCStoreConsts::EVENT_USER_RATING
         */
        virtual void onUserRatingEvent();

        /**
         Fired when the login process to a provider has failed.
         
         Event Name - CCStoreConsts::EVENT_LOGIN_FAILED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the login has failed.
         CCStoreConsts::DICT_ELEMENT_MESSAGE - __String - a Description of the 
         reason for failure.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginFailed(CCProvider provider, cocos2d::__String *message, cocos2d::__String *payload);

        /**
         Fired when the login process finishes successfully.
         
         Event Name - CCStoreConsts::EVENT_LOGIN_FINISHED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's 
         profile from the logged in provider.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginFinished(CCUserProfile *userProfile, cocos2d::__String *payload);

        /**
         Fired when the login process to a provider has started.
         
         Event Name - CCStoreConsts::EVENT_LOGIN_STARTED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         where the login has started.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginStarted(CCProvider provider, cocos2d::__String *payload);

        /**
         Fired when the logout process from a provider has failed.
         
         Event Name - CCStoreConsts::EVENT_LOGOUT_FAILED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the logout has failed.
         CCStoreConsts::DICT_ELEMENT_MESSAGE - __String - a Description of the 
         reason for failure.
         */
        virtual void onLogoutFailed(CCProvider provider, cocos2d::__String *message);

        /**
         Fired when the logout process from a provider has finished.
         
         Event Name - CCStoreConsts::EVENT_LOGOUT_FINISHED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the logout has finished.
         */
        virtual void onLogoutFinished(CCProvider provider);
        
        /**
         Fired when the logout process from a provider has started.
         
         Event Name - CCStoreConsts::EVENT_LOGOUT_STARTED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the login has started.
         */
        virtual void onLogoutStarted(CCProvider provider);

        /**
         Fired when the get contacts process from a provider has failed.
         
         Event Name - CCStoreConsts::EVENT_GET_CONTACTS_FAILED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get contacts process has failed.
         CCStoreConsts::DICT_ELEMENT_MESSAGE - __String - a Description of the 
         reason for failure.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsFailed(CCProvider provider, cocos2d::__String *message, cocos2d::__String *payload);

        /**
         Fired when the get contacts process from a provider has finished.
         
         Event Name - CCStoreConsts::EVENT_GET_CONTACTS_FINISHED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get contacts process finished.
         CCStoreConsts::DICT_ELEMENT_CONTACTS - __Array - an Array of contacts 
         represented by CCUserProfile.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsFinished(CCProvider provider, cocos2d::__Array *contactsDict, cocos2d::__String *payload);

        /**
         Fired when the get contacts process from a provider has started.
         
         Event Name - CCStoreConsts::EVENT_GET_CONTACTS_STARTED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get contacts process started.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsStarted(CCProvider provider, cocos2d::__String *payload);

        /**
         Fired when the get feed process from a provider has failed.
         
         Event Name - CCStoreConsts::EVENT_GET_FEED_FAILED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get feed process has failed.
         CCStoreConsts::DICT_ELEMENT_MESSAGE - __String - a Description of 
         the reason for failure.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedFailed(CCProvider provider, cocos2d::__String *message, cocos2d::__String *payload);

        /**
         Fired when the get feed process from a provider has finished.
         
         Event Name - CCStoreConsts::EVENT_GET_FEED_FINISHED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get feed process finished.
         CCStoreConsts::DICT_ELEMENT_FEEDS - __Array - an Array of feed entries 
         represented by __String.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedFinished(CCProvider provider, cocos2d::__Array *feedList, cocos2d::__String *payload);

        /**
         Fired when the get feed process from a provider has started.
         
         Event Name - CCStoreConsts::EVENT_GET_FEED_STARTED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get feed process started
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedStarted(CCProvider provider, cocos2d::__String *payload);

        /**
         Fired when a generic social action on a provider has failed.
         
         Event Name - CCStoreConsts::EVENT_SOCIAL_ACTION_FAILED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the social action has failed.
         CCStoreConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social 
         action which failed.
         CCStoreConsts::DICT_ELEMENT_MESSAGE - __String - a Description of 
         the reason for failure.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *message, cocos2d::__String *payload);

        /**
         Fired when a generic social action on a provider has finished.
         
         Event Name - CCStoreConsts::EVENT_SOCIAL_ACTION_FINISHED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the social action has finished.
         CCStoreConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social 
         action which finished.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        /**
         Fired when a generic social action on a provider has started.
         
         Event Name - CCStoreConsts::EVENT_SOCIAL_ACTION_STARTED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the social action has started.
         CCStoreConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social 
         action which started.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        /**
         Fired when the login process to a provider has been cancelled.
         
         Event Name - CCStoreConsts::EVENT_LOGIN_CANCELLED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the login has cancelled.
         CCStoreConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginCancelledEvent(CCProvider provider, cocos2d::__String *payload);
        
        /**
         Fired when a user profile from a provider has been retrieved.
         
         Event Name - CCStoreConsts::EVENT_USER_PROFILE_UPDATED
         Event Data (__Dictionary):
         CCStoreConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's 
         profile which was updated.
         */
        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);

    private:
        CCUserProfile *extractUserProfile(Ref *userProfileRef);
        cocos2d::__Array *extractUserProfileArray(Ref *userProfileDictArray);
    };
};

#endif //__CCProfileEventDispatcher_H_
