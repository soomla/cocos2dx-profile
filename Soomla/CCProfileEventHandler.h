/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CCUserProfile.h"
#include "CCReward.h"
#include "CCUserProfileUtils.h"
#include "CCSocialActionUtils.h"

#ifndef __CCProfileEventHandler__
#define __CCProfileEventHandler__

namespace soomla {
    
    /**
     @class CCProfileEventHandler
     @brief an Interface for all receivers of Profile events
     
     To receive events about any Profile-related actions a class must inherit
     from this class and sign up for events on CCProfileEventDispatcher
     */
    class CCProfileEventHandler : public cocos2d::CCObject {
    public:

        /**
        * Called after the service has been initialized
        */
        virtual void onProfileInitialized() = 0;
        
        /**
         Called when the market page for the app is opened
         */
        virtual void onUserRatingEvent() = 0;

        /**
         Called when the login process to a provider has failed
         
         @param provider The provider on which the login has failed
         @param errorDescription a Description of the reason for failure
         @param payload an identification String sent from the caller of the action
         */
        virtual void onLoginFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the login process finishes successfully
         
         @param userProfile The user's profile from the logged in provider
         @param payload an identification String sent from the caller of the action
         */
        virtual void onLoginFinished(CCUserProfile *userProfile, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the login process to a provider has started
         
         @param provider The provider on where the login has started
         @param payload an identification String sent from the caller of the action
         */
        virtual void onLoginStarted(CCProvider provider, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the logout process from a provider has failed
         
         @param provider The provider on which the logout has failed
         @param errorDescription a Description of the reason for failure
         */
        virtual void onLogoutFailed(CCProvider provider, cocos2d::CCString *errorDescription) = 0;
        
        /**
         Called when the logout process from a provider has finished
         
         @param provider The provider on which the logout has finished
         */
        virtual void onLogoutFinished(CCProvider provider) = 0;
        
        /**
         Called when the logout process from a provider has started
         
         @param provider The provider on which the login has started
         */
        virtual void onLogoutStarted(CCProvider provider) = 0;
        
        /**
         Called when the get contacts process from a provider has failed
         
         @param provider The provider on which the get contacts process has 
         failed
         @param errorDescription a Description of the reason for failure
         @param payload an identification String sent from the caller of the action
         */
        virtual void onGetContactsFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the get contacts process from a provider has finished
         
         @param provider The provider on which the get contacts process finished
         @param contactsDict an Array of contacts represented by CCUserProfile
         @param payload an identification String sent from the caller of the action
         */
        virtual void onGetContactsFinished(CCProvider provider, cocos2d::CCArray *contactsDict, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the get contacts process from a provider has started
         
         @param provider The provider on which the get contacts process started
         @param payload an identification String sent from the caller of the action
         */
        virtual void onGetContactsStarted(CCProvider provider, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the get feed process from a provider has failed
         
         @param provider The provider on which the get feed process has
         failed
         @param errorDescription a Description of the reason for failure
         @param payload an identification String sent from the caller of the action
         */
        virtual void onGetFeedFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the get feed process from a provider has finished
         
         @param provider The provider on which the get feed process finished
         @param feedList an Array of feed entries represented by CCString
         @param payload an identification String sent from the caller of the action
         */
        virtual void onGetFeedFinished(CCProvider provider, cocos2d::CCArray *feedList, cocos2d::CCString *payload) = 0;
        
        /**
         Called when the get feed process from a provider has started
         
         @param provider The provider on which the get feed process started
         @param payload an identification String sent from the caller of the action
         */
        virtual void onGetFeedStarted(CCProvider provider, cocos2d::CCString *payload) = 0;
        
        /**
         Called when a generic social action on a provider has failed
         
         @param provider The provider on which the social action has failed
         @param socialActionType The social action which failed
         @param errorDescription a Description of the reason for failure
         @param payload an identification String sent from the caller of the action
         */
        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) = 0;
        
        /**
         Called when a generic social action on a provider has finished
         
         @param provider The provider on which the social action has finished
         @param socialActionType The social action which finished
         @param payload an identification String sent from the caller of the action
         */
        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload) = 0;
        
        /**
         Called when a generic social action on a provider has started
         
         @param provider The provider on which the social action has started
         @param socialActionType The social action which started
         @param payload an identification String sent from the caller of the action
         */
        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload) = 0;
        
        /**
         Called the login process to a provider has been cancelled
         
         @param provider The provider on which the login has failed
         @param payload an identification String sent from the caller of the action
         */
        virtual void onLoginCancelledEvent(CCProvider provider, cocos2d::CCString *payload) = 0;
        
        /**
         Called when a user profile from a provider has been retrieved
         
         @param userProfile The user's profile which was updated
         */
        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile) = 0;
    };

};

#endif /* defined(__CCProfileEventHandler__) */

