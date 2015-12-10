//
// Created by Eugene Butusov on 23/11/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCLeaderboard.h"

soomla::CCLeaderboard *soomla::CCLeaderboard::create(cocos2d::__String *id, cocos2d::__String *provider, cocos2d::__String *name, cocos2d::__String *iconUrl) {

    CCLeaderboard *ret = new CCLeaderboard();
    if (ret->init(id, provider, name, iconUrl)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCLeaderboard::init(cocos2d::__String *id, cocos2d::__String *provider, cocos2d::__String *name, cocos2d::__String *iconUrl) {
    
    setId(id);
    setProvider(provider);
    setName(name);
    setIconUrl(iconUrl);
    
    return true;
}


bool soomla::CCLeaderboard::initWithDictionary(cocos2d::__Dictionary *dict) {
    CCDomain::initWithDictionary(dict);
    fillProviderFromDict(dict);
    fillNameFromDict(dict);
    fillIconUrlFromDict(dict);

    return true;
}

cocos2d::__Dictionary *soomla::CCLeaderboard::toDictionary() {
    cocos2d::__Dictionary* dict = CCDomain::toDictionary();

    putProviderToDict(dict);
    putNameToDict(dict);
    putIconUrlToDict(dict);

    return dict;
}

soomla::CCLeaderboard::~CCLeaderboard() {
    CC_SAFE_RELEASE(mProvider);
    CC_SAFE_RELEASE(mName);
    CC_SAFE_RELEASE(mIconUrl);
}
