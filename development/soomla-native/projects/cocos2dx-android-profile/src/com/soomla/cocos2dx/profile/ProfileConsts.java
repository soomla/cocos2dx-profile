/*
 * Copyright (C) 2012-2014 Soomla Inc.
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

package com.soomla.cocos2dx.profile;


/**
 * Provides all the string consts to provide a common interface between native and
 * Cocos2dx. String consts represent events and JSON fields.
 */
public class ProfileConsts {
    public static final String JSON_JSON_TYPE_USER_PROFILE = "UserProfile";

    public static final String EVENT_UP_PROFILE_INITIALIZED = "com.soomla.profile.events.ProfileInitializedEvent";
    public static final String EVENT_UP_USER_RATING = "com.soomla.profile.events.UserRatingEvent";
    public static final String EVENT_AUTH_LOGIN_FAILED = "com.soomla.profile.events.auth.LoginFailedEvent";
    public static final String EVENT_AUTH_LOGIN_FINISHED = "com.soomla.profile.events.auth.LoginFinishedEvent";
    public static final String EVENT_AUTH_LOGIN_STARTED = "com.soomla.profile.events.auth.LoginStartedEvent";
    public static final String EVENT_AUTH_LOGOUT_FAILED = "com.soomla.profile.events.auth.LogoutFailedEvent";
    public static final String EVENT_AUTH_LOGOUT_FINISHED = "com.soomla.profile.events.auth.LogoutFinishedEvent";
    public static final String EVENT_AUTH_LOGOUT_STARTED = "com.soomla.profile.events.auth.LogoutStartedEvent";
    public static final String EVENT_GET_CONTACTS_FAILED = "com.soomla.profile.events.social.GetContactsFailedEvent";
    public static final String EVENT_GET_CONTACTS_FINISHED = "com.soomla.profile.events.social.GetContactsFinishedEvent";
    public static final String EVENT_GET_CONTACTS_STARTED = "com.soomla.profile.events.social.GetContactsStartedEvent";
    public static final String EVENT_GET_FEED_FAILED = "com.soomla.profile.events.social.GetFeedFailedEvent";
    public static final String EVENT_GET_FEED_FINISHED = "com.soomla.profile.events.social.GetFeedFinishedEvent";
    public static final String EVENT_GET_FEED_STARTED = "com.soomla.profile.events.social.GetFeedStartedEvent";
    public static final String EVENT_SOCIAL_ACTION_FAILED = "com.soomla.profile.events.social.SocialActionFailedEvent";
    public static final String EVENT_SOCIAL_ACTION_FINISHED = "com.soomla.profile.events.social.SocialActionFinishedEvent";
    public static final String EVENT_SOCIAL_ACTION_STARTED = "com.soomla.profile.events.social.SocialActionStartedEvent";
    public static final String EVENT_LOGIN_CANCELLED = "com.soomla.profile.events.auth.LoginCancelledEvent";
    public static final String EVENT_USER_PROFILE_UPDATED = "com.soomla.profile.events.UserProfileUpdatedEvent";
}
