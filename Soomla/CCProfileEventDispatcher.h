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
#include "CCLeaderboard.h"
#include "CCScore.h"

namespace soomla {

	/** 
     @class CCProfileEventDispatcher
     @brief Fires event when received from the native implementation.
     
     Signs up to native Profile events through CCSoomlaEventDispatcher.
     When the events arrive this class fires the repective event through
     the Cocos2dx Event Dispatcher.
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
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the login has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - __String - a Description of the 
         reason for failure.
         CCProfileConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's
         profile from the logged in provider.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification
         String sent from the caller of the action.
         */
        virtual void onLoginFailed(CCProvider provider, cocos2d::__String *message, cocos2d::__Bool *autoLogin, cocos2d::__String *payload);

        /**
         Fired when the login process finishes successfully.
         
         Event Name - CCProfileConsts::EVENT_LOGIN_FINISHED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's 
         profile from the logged in provider.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginFinished(CCUserProfile *userProfile, cocos2d::__Bool *autoLogin, cocos2d::__String *payload);

        /**
         Fired when the login process to a provider has started.
         
         Event Name - CCProfileConsts::EVENT_LOGIN_STARTED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         where the login has started.
         CCProfileConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's
         profile from the logged in provider.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification
         String sent from the caller of the action.
         */
        virtual void onLoginStarted(CCProvider provider, cocos2d::__Bool *autoLogin, cocos2d::__String *payload);

        /**
         Fired when the logout process from a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_LOGOUT_FAILED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the logout has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - __String - a Description of the 
         reason for failure.
         */
        virtual void onLogoutFailed(CCProvider provider, cocos2d::__String *message);

        /**
         Fired when the logout process from a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_LOGOUT_FINISHED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the logout has finished.
         */
        virtual void onLogoutFinished(CCProvider provider);
        
        /**
         Fired when the logout process from a provider has started.
         
         Event Name - CCProfileConsts::EVENT_LOGOUT_STARTED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the login has started.
         */
        virtual void onLogoutStarted(CCProvider provider);

        /**
         Fired when the get contacts process from a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_GET_CONTACTS_FAILED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get contacts process has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - __String - a Description of the 
         reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsFailed(CCProvider provider, __String *message, __Bool *payload, __String *pString);

        /**
         Fired when the get contacts process from a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_GET_CONTACTS_FINISHED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get contacts process finished.
         CCProfileConsts::DICT_ELEMENT_CONTACTS - __Array - an Array of contacts 
         represented by CCUserProfile.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsFinished(CCProvider provider, cocos2d::__Array *contactsDict, cocos2d::__String *payload, cocos2d::__Bool *hasMore);

        /**
         Fired when the get contacts process from a provider has started.
         
         Event Name - CCProfileConsts::EVENT_GET_CONTACTS_STARTED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get contacts process started.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetContactsStarted(CCProvider provider, cocos2d::__Bool *fromStart, cocos2d::__String *payload);

        /**
         Fired when the get feed process from a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_GET_FEED_FAILED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get feed process has failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - __String - a Description of 
         the reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedFailed(CCProvider provider, cocos2d::__String *message, cocos2d::__String *payload);

        /**
         Fired when the get feed process from a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_GET_FEED_FINISHED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get feed process finished.
         CCProfileConsts::DICT_ELEMENT_FEEDS - __Array - an Array of feed entries 
         represented by __String.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedFinished(CCProvider provider, cocos2d::__Array *feedList, cocos2d::__String *payload, cocos2d::__Bool *hasMore);

        /**
         Fired when the get feed process from a provider has started.
         
         Event Name - CCProfileConsts::EVENT_GET_FEED_STARTED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the get feed process started
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onGetFeedStarted(CCProvider provider, cocos2d::__String *payload);

        /**
         Fired when a generic social action on a provider has failed.
         
         Event Name - CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the social action has failed.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social 
         action which failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - __String - a Description of 
         the reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *message, cocos2d::__String *payload);

        /**
         Fired when a generic social action on a provider has finished.
         
         Event Name - CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the social action has finished.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social 
         action which finished.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        /**
         Fired when a generic social action on a provider has started.
         
         Event Name - CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the social action has started.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social 
         action which started.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        /**
         Fired when the login process to a provider has been cancelled.
         
         Event Name - CCProfileConsts::EVENT_LOGIN_CANCELLED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on 
         which the login has cancelled.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification 
         String sent from the caller of the action.
         */
        virtual void onLoginCancelled(CCProvider provider, cocos2d::__Bool *autoLogin, cocos2d::__String *payload);
        
        /**
         Fired when a user profile from a provider has been retrieved.
         
         Event Name - CCProfileConsts::EVENT_USER_PROFILE_UPDATED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_USER_PROFILE - CCUserProfile - The user's 
         profile which was updated.
         */
        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);

        /**
         Fired when a generic social action on a provider has started.

         Event Name - CCProfileConsts::EVENT_INVITE_STARTED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on
         which the invitation has started.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social
         action which started (INVITE in this case).
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification
         String sent from the caller of the action.
         */
        virtual void onInviteStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        /**
         Fired when an invitation on a provider has finished.

         Event Name - CCProfileConsts::EVENT_INVITE_FINISHED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on
         which the invite has finished.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social
         action which finished (INVITE in this case).
         CCProfileConsts::DICT_ELEMENT_REQUEST_ID - __String - identifier of created app request
         CCProfileConsts::DICT_ELEMENT_INVITED_IDS - __Array - list of recipients of this request
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification
         String sent from the caller of the action.
         */
        virtual void onInviteFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *requestId, cocos2d::__Array *invitedIds, cocos2d::__String *payload);

        /**
         Fired when an invitation on a provider has failed.

         Event Name - CCProfileConsts::EVENT_INVITE_FAILED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on
         which the social action has failed.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social
         action which failed.
         CCProfileConsts::DICT_ELEMENT_MESSAGE - __String - a Description of
         the reason for failure.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification
         String sent from the caller of the action.
         */
        virtual void onInviteFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *message, cocos2d::__String *payload);

        /**
         Fired when an invitation on a provider has cancelled.

         Event Name - CCProfileConsts::EVENT_INVITE_CANCELLED
         Event Data (__Dictionary):
         CCProfileConsts::DICT_ELEMENT_PROVIDER - __Integer - The provider on
         which the social action has failed.
         CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE - __Integer - The social
         action which failed.
         CCProfileConsts::DICT_ELEMENT_PAYLOAD - __String - an identification
         String sent from the caller of the action.
         */
        virtual void onInviteCancelledEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        virtual void onGetLeaderboardsStartedEvent(CCProvider provider, cocos2d::__Bool *fromStart, cocos2d::__String *payload);

        virtual void onGetLeaderboardsFinishedEvent(CCProvider provider, cocos2d::__Array *leaderboards, cocos2d::__Bool *hasMore, cocos2d::__String *payload);

        virtual void onGetLeaderboardsFailedEvent(CCProvider provider, cocos2d::__Bool *fromStart, cocos2d::__String *message, cocos2d::__String *payload);

        virtual void onGetScoresStartedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__Bool *fromStart, cocos2d::__String *payload);

        virtual void onGetScoresFinishedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__Array *scores, cocos2d::__Bool *hasMore, cocos2d::__String *payload);

        virtual void onGetScoresFailedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__Bool *fromStart, cocos2d::__String *message, cocos2d::__String *payload);

        virtual void onReportScoreStartedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__String *payload);

        virtual void onReportScoreFinishedEvent(CCProvider provider, CCLeaderboard *leaderboard, CCScore *score, cocos2d::__String *payload);

        virtual void onReportScoreFailedEvent(CCProvider provider, CCLeaderboard *leaderboard, cocos2d::__String *message, cocos2d::__String *payload);

    private:
        CCUserProfile *extractUserProfile(Ref *userProfileRef);
        cocos2d::__Array *extractUserProfileArray(Ref *userProfileDictArray);
        cocos2d::__Array *extractLeaderboardArray(Ref *leaderboardDictArray);
        cocos2d::__Array *extractScoreArray(Ref *scoreDictArray);
    };
};

#endif //__CCProfileEventDispatcher_H_
