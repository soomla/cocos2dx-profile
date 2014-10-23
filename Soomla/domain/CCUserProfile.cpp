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



#include "CCUserProfile.h"
#include "CCDomainFactory.h"

soomla::CCUserProfile *soomla::CCUserProfile::create(
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
        cocos2d::CCString *birthday) {

    CCUserProfile *ret = new CCUserProfile();
    if (ret->init(provider, profileId, email, username,
            firstName, lastName,
            avatarLink, location, gender, language, birthday)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCUserProfile::init(
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
        cocos2d::CCString *birthday) {

    setProvider(provider);
    setProfileId(profileId);
    setEmail(email);
    setUsername(username);
    setFirstName(firstName);
    setLastName(lastName);
    setAvatarLink(avatarLink);
    setLocation(location);
    setGender(gender);
    setLanguage(language);
    setBirthday(birthday);

    return true;
}

bool soomla::CCUserProfile::initWithDictionary(cocos2d::CCDictionary *dict) {
    fillProviderFromDict(dict);
    fillProfileIdFromDict(dict);
    fillEmailFromDict(dict);
    fillUsernameFromDict(dict);
    fillFirstNameFromDict(dict);
    fillLastNameFromDict(dict);
    fillAvatarLinkFromDict(dict);
    fillLocationFromDict(dict);
    fillGenderFromDict(dict);
    fillLanguageFromDict(dict);
    fillBirthdayFromDict(dict);

    return true;
}

cocos2d::CCDictionary *soomla::CCUserProfile::toDictionary() {
    cocos2d::CCDictionary* dict = cocos2d::CCDictionary::create();

    putProviderToDict(dict);
    putProfileIdToDict(dict);
    putEmailToDict(dict);
    putUsernameToDict(dict);
    putFirstNameToDict(dict);
    putLastNameToDict(dict);
    putAvatarLinkToDict(dict);
    putLocationToDict(dict);
    putGenderToDict(dict);
    putLanguageToDict(dict);
    putBirthdayToDict(dict);

    return dict;
}

soomla::CCUserProfile::~CCUserProfile() {
    CC_SAFE_RELEASE(mProvider);
    CC_SAFE_RELEASE(mProfileId);
    CC_SAFE_RELEASE(mEmail);
    CC_SAFE_RELEASE(mUsername);
    CC_SAFE_RELEASE(mFirstName);
    CC_SAFE_RELEASE(mLastName);
    CC_SAFE_RELEASE(mAvatarLink);
    CC_SAFE_RELEASE(mLocation);
    CC_SAFE_RELEASE(mGender);
    CC_SAFE_RELEASE(mLanguage);
    CC_SAFE_RELEASE(mBirthday);
}
