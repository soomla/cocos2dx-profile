/*
 Copyright (C) 2012-2015 Soomla Inc.

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

#ifndef COCOS2DXPROFILE_CCLEADERBOARD_H
#define COCOS2DXPROFILE_CCLEADERBOARD_H

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCProfileConsts.h"
#include "CCCoreConsts.h"
#include "CCDomain.h"

namespace soomla {
    class CCLeaderboard : public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mId, Id, CCProfileConsts::JSON_IDENTIFIER);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mProvider, Provider, CCProfileConsts::JSON_PROVIDER);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mName, Name, CCProfileConsts::JSON_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mIconUrl, IconUrl, CCProfileConsts::JSON_ICON_URL);

    public:
        /**
         Constructor

         Main constructor for the leaderboard which nullifies all information
         in the class
         */
        CCLeaderboard() : CCDomain(), mId(), mProvider(NULL), mName(NULL), mIconUrl(NULL) {};

        /**
         Creates an instance of CCLeaderboard according to the information
         provided

         @param provider The origin of this CCLeaderboard, meaning the originating
         social network (defined in CCProvider)
         @param name The name of this leaderboard
         @param iconUrl URL to image that represents by this leaderboard
         */
        static CCLeaderboard *create(cocos2d::__String *id, cocos2d::__String *provider, cocos2d::__String *name, cocos2d::__String *iconUrl);

        SL_CREATE_WITH_DICTIONARY(CCLeaderboard);

        /**
         Initializes the class instance with the provided information

         @param provider The origin of this CCLeaderboard, meaning the originating
         social network (defined in CCProvider)
         @param name The name of this leaderboard
         @param iconUrl URL to image that represents by this leaderboard
         */
        virtual bool init(cocos2d::__String *id, cocos2d::__String *provider, cocos2d::__String *name, cocos2d::__String *iconUrl);

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
         Destructor for the leaderboard
         */
        virtual ~CCLeaderboard();
    };
}


#endif //COCOS2DXPROFILE_CCLEADERBOARD_H
