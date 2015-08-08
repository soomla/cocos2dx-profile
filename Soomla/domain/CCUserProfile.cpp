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
        cocos2d::__String *provider,
        cocos2d::__String *profileId,
        cocos2d::__String *email,
        cocos2d::__String *username,
        cocos2d::__String *firstName,
        cocos2d::__String *lastName,
        cocos2d::__String *avatarLink,
        cocos2d::__String *location,
        cocos2d::__String *gender,
        cocos2d::__String *language,
        cocos2d::__String *birthday,
        cocos2d::__Dictionary *extra) {

    CCUserProfile *ret = new CCUserProfile();
    if (ret->init(provider, profileId, email, username,
            firstName, lastName,
            avatarLink, location, gender, language, birthday, extra)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCUserProfile::init(
        cocos2d::__String *provider,
        cocos2d::__String *profileId,
        cocos2d::__String *email,
        cocos2d::__String *username,
        cocos2d::__String *firstName,
        cocos2d::__String *lastName,
        cocos2d::__String *avatarLink,
        cocos2d::__String *location,
        cocos2d::__String *gender,
        cocos2d::__String *language,
        cocos2d::__String *birthday,
        cocos2d::__Dictionary *extra) {

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
    setExtra(extra);

    return true;
}

bool soomla::CCUserProfile::initWithDictionary(cocos2d::__Dictionary *dict) {
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
    fillExtraFromDict(dict);

    return true;
}

cocos2d::__Dictionary *soomla::CCUserProfile::toDictionary() {
    cocos2d::__Dictionary* dict = cocos2d::__Dictionary::create();

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
    putExtraToDict(dict);

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
    CC_SAFE_RELEASE(mExtra);
}
