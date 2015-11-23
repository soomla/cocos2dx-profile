//
// Created by Eugene Butusov on 23/11/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCLEADERBOARD_H
#define COCOS2DXPROFILE_CCLEADERBOARD_H

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCProfileConsts.h"
#include "CCSoomlaEntity.h"

namespace soomla {
    class CCLeaderboard : public CCSoomlaEntity {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mProvider, Provider, CCProfileConsts::JSON_PROVIDER);

    public:
        /**
         Constructor

         Main constructor for the leaderboard which nullifies all information
         in the class
         */
        CCLeaderboard() : CCSoomlaEntity(), mProvider(NULL) {};

        /**
         Creates an instance of CCLeaderboard according to the information
         provided

         @param provider The origin of this CCLeaderboard, meaning the originating
         social network (defined in CCProvider)
         */
        static CCLeaderboard *create(cocos2d::__String *id, cocos2d::__String *provider);

        SL_CREATE_WITH_DICTIONARY(CCLeaderboard);

        /**
         Initializes the class instance with the provided information

         @param provider The origin of this CCLeaderboard, meaning the originating
         social network (defined in CCProvider)
         */
        virtual bool init(cocos2d::__String *id, cocos2d::__String *provider);

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
         Destructor for the leaderboard
         */
        virtual ~CCLeaderboard();
    };
}


#endif //COCOS2DXPROFILE_CCLEADERBOARD_H
