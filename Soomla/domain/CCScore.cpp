//
// Created by Eugene Butusov on 23/11/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCScore.h"

soomla::CCScore *soomla::CCScore::create(soomla::CCLeaderboard *leaderboard, cocos2d::__Integer *rank, soomla::CCUserProfile *player, cocos2d::__Integer *value) {

    CCScore *ret = new CCScore();
    if (ret->init(leaderboard, rank, player, value)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCScore::init(soomla::CCLeaderboard *leaderboard, cocos2d::__Integer *rank, soomla::CCUserProfile *player, cocos2d::__Integer *value) {

    setLeaderboard(leaderboard);
    setRank(rank);
    setPlayer(player);
    setValue(value);

    return true;
}

bool soomla::CCScore::initWithDictionary(cocos2d::__Dictionary *dict) {
    fillLeaderboardFromDict(dict);
    fillRankFromDict(dict);
    fillPlayerFromDict(dict);
    fillValueFromDict(dict);

    return true;
}

cocos2d::__Dictionary *soomla::CCScore::toDictionary() {
    cocos2d::__Dictionary* dict = cocos2d::__Dictionary::create();

    putLeaderboardToDict(dict);
    putRankToDict(dict);
    putPlayerToDict(dict);
    putValueToDict(dict);

    return dict;
}

soomla::CCScore::~CCScore() {
    CC_SAFE_RELEASE(mLeaderboard);
    CC_SAFE_RELEASE(mRank);
    CC_SAFE_RELEASE(mPlayer);
    CC_SAFE_RELEASE(mValue);
}
