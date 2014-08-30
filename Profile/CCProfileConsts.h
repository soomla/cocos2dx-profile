#ifndef __CCProfileConsts_H__
#define __CCProfileConsts_H__

namespace soomla {
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
