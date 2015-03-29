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

#ifndef __CCProfileConsts_H__
#define __CCProfileConsts_H__

namespace soomla {
    
    /**
     @class CCProfileConsts
     @brief Provides all the consts used by the Profile project
     
     The string consts defined here are used to define a common interface
     between string consts used in the native version of Profile and the 
     Cocos2dx one.
     This includes JSON field names and events published by native versions.
     */
    class CCProfileConsts {
    public:
        static char const *JSON_PROVIDER;
        static char const *JSON_PROFILE_ID;
        static char const *JSON_USERNAME;
        static char const *JSON_EMAIL;
        static char const *JSON_FIRST_NAME;
        static char const *JSON_LAST_NAME;
        static char const *JSON_AVATAR_LINK;
        static char const *JSON_LOCATION;
        static char const *JSON_GENDER;
        static char const *JSON_LANGUAGE;
        static char const *JSON_BIRTHDAY;

        static char const *JSON_JSON_TYPE_USER_PROFILE;
        
        /** Events **/
        
        static char const *DICT_ELEMENT_USER_PROFILE;
        static char const *DICT_ELEMENT_PROVIDER;
        static char const *DICT_ELEMENT_PAYLOAD;
        static char const *DICT_ELEMENT_SOCIAL_ACTION_TYPE;
        static char const *DICT_ELEMENT_MESSAGE;
        static char const *DICT_ELEMENT_CONTACTS;
        static char const *DICT_ELEMENT_FEEDS;
        static char const *DICT_ELEMENT_REWARD;

        static char const *EVENT_PROFILE_INITIALIZED;
        static char const *EVENT_USER_RATING;
        static char const *EVENT_LOGIN_CANCELLED;
        static char const *EVENT_LOGIN_FAILED;
        static char const *EVENT_LOGIN_FINISHED;
        static char const *EVENT_LOGIN_STARTED;

        static char const *EVENT_LOGOUT_FAILED;
        static char const *EVENT_LOGOUT_FINISHED;
        static char const *EVENT_LOGOUT_STARTED;

        static char const *EVENT_GET_CONTACTS_FAILED;
        static char const *EVENT_GET_CONTACTS_FINISHED;
        static char const *EVENT_GET_CONTACTS_STARTED;
        
        static char const *EVENT_GET_FEED_FAILED;
        static char const *EVENT_GET_FEED_FINISHED;
        static char const *EVENT_GET_FEED_STARTED;

        static char const *EVENT_SOCIAL_ACTION_FAILED;
        static char const *EVENT_SOCIAL_ACTION_FINISHED;
        static char const *EVENT_SOCIAL_ACTION_STARTED;

        static char const *EVENT_USER_PROFILE_UPDATED;
    };
}

#endif /* defined(__CCProfileConsts_H__) */
