//
// Created by Eugene Butusov on 23/11/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCSCORE_H
#define COCOS2DXPROFILE_CCSCORE_H

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCProfileConsts.h"
#include "CCSoomlaEntity.h"
#include "CCLeaderboard.h"
#include "CCUserProfile.h"

namespace soomla {
    class CCScore : public CCSoomlaEntity {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(soomla::CCLeaderboard *, mLeaderboard, Leaderboard, CCProfileConsts::JSON_LEADERBOARD);

        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Integer *, mRank, Rank, CCProfileConsts::JSON_SCORE_RANK);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(soomla::CCUserProfile *, mPlayer, Player, CCProfileConsts::JSON_USER_PROFILE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Integer *, mValue, Value, CCProfileConsts::JSON_SCORE_VALUE);
    public:
        /**
         Constructor

         Main constructor for the leaderboard which nullifies all information
         in the class
         */
        CCScore() : CCSoomlaEntity(), mLeaderboard(NULL), mRank(NULL), mPlayer(NULL), mValue(NULL) {};

        /**
         Creates an instance of CCScore according to the information
         provided

         @param provider The origin of this CCLeaderboard, meaning the originating
         social network (defined in CCProvider)
         */
        static CCScore *create(
                soomla::CCLeaderboard *leaderboard,
                cocos2d::__Integer *rank,
                soomla::CCUserProfile *player,
                cocos2d::__Integer *value);

        SL_CREATE_WITH_DICTIONARY(CCScore);

        /**
         Initializes the class instance with the provided information

         @param provider The origin of this CCLeaderboard, meaning the originating
         social network (defined in CCProvider)
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
        
        virtual char const * getType() const;

        /**
         Destructor for the score
         */
        virtual ~CCScore();
    };
}


#endif //COCOS2DXPROFILE_CCSCORE_H
