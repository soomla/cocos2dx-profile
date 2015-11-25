//
// Created by Eugene Butusov on 23/11/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCSCORE_H
#define COCOS2DXPROFILE_CCSCORE_H

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCProfileConsts.h"
#include "CCDomain.h"
#include "CCLeaderboard.h"
#include "CCUserProfile.h"

namespace soomla {
    class CCScore : public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(soomla::CCLeaderboard *, mLeaderboard, Leaderboard, CCProfileConsts::JSON_LEADERBOARD);

        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Integer *, mRank, Rank, CCProfileConsts::JSON_SCORE_RANK);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(soomla::CCUserProfile *, mPlayer, Player, CCProfileConsts::JSON_USER_PROFILE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Integer *, mValue, Value, CCProfileConsts::JSON_SCORE_VALUE);
    public:
        /**
         Constructor

         Main constructor for the score which nullifies all information
         in the class
         */
        CCScore() : CCDomain(), mLeaderboard(NULL), mRank(NULL), mPlayer(NULL), mValue(NULL) {};

        /**
         Creates an instance of CCScore according to the information
         provided

         @param leaderboard A leaderboard containing this score
         @param rank Score position in the leaderboard
         @param player Owner of this score
         @param value Value of this score
         */
        static CCScore *create(
                soomla::CCLeaderboard *leaderboard,
                cocos2d::__Integer *rank,
                soomla::CCUserProfile *player,
                cocos2d::__Integer *value);

        SL_CREATE_WITH_DICTIONARY(CCScore);

        /**
         Initializes the class instance with the provided information

         @param leaderboard A leaderboard containing this score
         @param rank Score position in the leaderboard
         @param player Owner of this score
         @param value Value of this score
         */
        virtual bool init(
                soomla::CCLeaderboard *leaderboard,
                cocos2d::__Integer *rank,
                soomla::CCUserProfile *player,
                cocos2d::__Integer *value);

        /**
         Initializes the class instance with information provided in a
         dictionary format with keys corresponding to fields JSON constants
         (see SL_SYNTHESIZE_RETAIN_WITH_DICT macros above)
         */
        virtual bool initWithDictionary(cocos2d::__Dictionary *dict);

        /**
         Convers the profile instance into a dictionary using the fields'
         JSON constants as keys
         (see SL_SYNTHESIZE_RETAIN_WITH_DICT macros above)
         */
        virtual cocos2d::__Dictionary *toDictionary();

        /**
         Destructor for the score
         */
        virtual ~CCScore();
    };
}


#endif //COCOS2DXPROFILE_CCSCORE_H
