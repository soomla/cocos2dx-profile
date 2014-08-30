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

    char const *CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE = "userProfile";

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