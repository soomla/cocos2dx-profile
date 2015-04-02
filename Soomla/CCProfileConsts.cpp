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

#include "CCProfileConsts.h"

namespace soomla {
    char const *CCProfileConsts::JSON_PROVIDER = "provider";
    char const *CCProfileConsts::JSON_PROFILE_ID = "profileId";
    char const *CCProfileConsts::JSON_USERNAME = "username";
    char const *CCProfileConsts::JSON_EMAIL = "email";
    char const *CCProfileConsts::JSON_FIRST_NAME = "firstName";
    char const *CCProfileConsts::JSON_LAST_NAME = "lastName";
    char const *CCProfileConsts::JSON_AVATAR_LINK = "avatarLink";
    char const *CCProfileConsts::JSON_LOCATION = "location";
    char const *CCProfileConsts::JSON_GENDER = "gender";
    char const *CCProfileConsts::JSON_LANGUAGE = "language";
    char const *CCProfileConsts::JSON_BIRTHDAY = "birthday";

    char const *CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE = "UserProfile";
    
    
    char const *CCProfileConsts::DICT_ELEMENT_USER_PROFILE = "userProfile";
    char const *CCProfileConsts::DICT_ELEMENT_PROVIDER = "provider";
    char const *CCProfileConsts::DICT_ELEMENT_PAYLOAD = "payload";
    char const *CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE = "socialActiontype";
    char const *CCProfileConsts::DICT_ELEMENT_MESSAGE = "message";
    char const *CCProfileConsts::DICT_ELEMENT_CONTACTS = "contacts";
    char const *CCProfileConsts::DICT_ELEMENT_FEEDS = "feeds";
    char const *CCProfileConsts::DICT_ELEMENT_REWARD = "reward";

    char const *CCProfileConsts::EVENT_PROFILE_INITIALIZED = "com.soomla.profile.events.ProfileInitializedEvent";
    char const *CCProfileConsts::EVENT_USER_RATING = "com.soomla.profile.events.UserRatingEvent";

    char const *CCProfileConsts::EVENT_LOGIN_CANCELLED = "com.soomla.profile.events.auth.LoginCancelledEvent";
    char const *CCProfileConsts::EVENT_LOGIN_FAILED = "com.soomla.profile.events.auth.LoginFailedEvent";
    char const *CCProfileConsts::EVENT_LOGIN_FINISHED = "com.soomla.profile.events.auth.LoginFinishedEvent";
    char const *CCProfileConsts::EVENT_LOGIN_STARTED = "com.soomla.profile.events.auth.LoginStartedEvent";

    char const *CCProfileConsts::EVENT_LOGOUT_FAILED = "com.soomla.profile.events.auth.LogoutFailedEvent";
    char const *CCProfileConsts::EVENT_LOGOUT_FINISHED = "com.soomla.profile.events.auth.LogoutFinishedEvent";
    char const *CCProfileConsts::EVENT_LOGOUT_STARTED = "com.soomla.profile.events.auth.LogoutStartedEvent";

    char const *CCProfileConsts::EVENT_GET_CONTACTS_FAILED = "com.soomla.profile.events.social.GetContactsFailedEvent";
    char const *CCProfileConsts::EVENT_GET_CONTACTS_FINISHED = "com.soomla.profile.events.social.GetContactsFinishedEvent";
    char const *CCProfileConsts::EVENT_GET_CONTACTS_STARTED = "com.soomla.profile.events.social.GetContactsStartedEvent";
    
    char const *CCProfileConsts::EVENT_GET_FEED_FAILED = "com.soomla.profile.events.social.GetFeedFailedEvent";
    char const *CCProfileConsts::EVENT_GET_FEED_FINISHED = "com.soomla.profile.events.social.GetFeedFinishedEvent";
    char const *CCProfileConsts::EVENT_GET_FEED_STARTED = "com.soomla.profile.events.social.GetFeedStartedEvent";

    char const *CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED = "com.soomla.profile.events.social.SocialActionFailedEvent";
    char const *CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED = "com.soomla.profile.events.social.SocialActionFinishedEvent";
    char const *CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED = "com.soomla.profile.events.social.SocialActionStartedEvent";

    char const *CCProfileConsts::EVENT_USER_PROFILE_UPDATED = "com.soomla.profile.events.UserProfileUpdatedEvent";

}