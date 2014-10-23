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



#ifndef __CCUserProfile_H_
#define __CCUserProfile_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCProfileConsts.h"
#include "CCDomain.h"

namespace soomla {
    /**
     @class CCUserProfile
     @brief Represents a profile of a user from a social network (provider)

     The class contains all provided information from the user to the
     application

     Inheritance CCUserProfile > CCDomain > cocos2d::Ref
     */
    class CCUserProfile : public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mProvider, Provider, CCProfileConsts::JSON_PROVIDER);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mProfileId, ProfileId, CCProfileConsts::JSON_PROFILE_ID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mEmail, Email, CCProfileConsts::JSON_EMAIL);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mUsername, Username, CCProfileConsts::JSON_USERNAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mFirstName, FirstName, CCProfileConsts::JSON_FIRST_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mLastName, LastName, CCProfileConsts::JSON_LAST_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAvatarLink, AvatarLink, CCProfileConsts::JSON_AVATAR_LINK);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mLocation, Location, CCProfileConsts::JSON_LOCATION);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mGender, Gender, CCProfileConsts::JSON_GENDER);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mLanguage, Language, CCProfileConsts::JSON_LANGUAGE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mBirthday, Birthday, CCProfileConsts::JSON_BIRTHDAY);
    public:
        /**
         Constructor

         Main constructor for the user profile which nullifies all information
         in the class
         */
        CCUserProfile() : CCDomain(), mProvider(NULL), mProfileId(NULL), mEmail(NULL) , mUsername(NULL),
                          mFirstName(NULL), mLastName(NULL), mAvatarLink(NULL), mLocation(NULL) ,
                          mGender(NULL), mLanguage(NULL), mBirthday(NULL) {};

        /**
         Creates an instance of CCUserProfile according to the information
         provided

         @param provider The origin of this profile, meaning the originating
         social network (defined in CCProvider)
         @param profileId The ID of the profile in the social network
         @param email The email of the user
         @param username The user-name of the user in the social network
         @param firstName The user's first name
         @param lastName The user's last name
         @param avatarLink The user's avatar link
         @param location The user's location
         @param gender The user's gender
         @param language The user's language
         @param birthday The user's birth date
         */
        static CCUserProfile *create(
                cocos2d::CCString *provider,
                cocos2d::CCString *profileId,
                cocos2d::CCString *email,
                cocos2d::CCString *username,
                cocos2d::CCString *firstName,
                cocos2d::CCString *lastName,
                cocos2d::CCString *avatarLink,
                cocos2d::CCString *location,
                cocos2d::CCString *gender,
                cocos2d::CCString *language,
                cocos2d::CCString *birthday);

        SL_CREATE_WITH_DICTIONARY(CCUserProfile);

        /**
         Initializes the class instance with the provided information

         @param provider The origin of this profile, meaning the originating
         social network (defined in CCProvider)
         @param profileId The ID of the profile in the social network
         @param email The email of the user
         @param username The user-name of the user in the social network
         @param firstName The user's first name
         @param lastName The user's last name
         @param avatarLink The user's avatar link
         @param location The user's location
         @param gender The user's gender
         @param language The user's language
         @param birthday The user's birth date
         */
        virtual bool init(
                cocos2d::CCString *provider,
                cocos2d::CCString *profileId,
                cocos2d::CCString *email,
                cocos2d::CCString *username,
                cocos2d::CCString *firstName,
                cocos2d::CCString *lastName,
                cocos2d::CCString *avatarLink,
                cocos2d::CCString *location,
                cocos2d::CCString *gender,
                cocos2d::CCString *language,
                cocos2d::CCString *birthday);

        /**
         Initializes the class instance with information provided in a
         dictionary format with keys corresponding to fields JSON constants
         (see SL_SYNTHESIZE_RETAIN_WITH_DICT macros above)
         */
        virtual bool initWithDictionary(cocos2d::CCDictionary *dict);

        /**
         Convers the profile instance into a dictionary using the fields'
         JSON constants as keys
         (see SL_SYNTHESIZE_RETAIN_WITH_DICT macros above)
         */
        virtual cocos2d::CCDictionary *toDictionary();

        /**
         Destructor for the user profile
         */
        virtual ~CCUserProfile();
    };
}

#endif //__CCUserProfile_H_
