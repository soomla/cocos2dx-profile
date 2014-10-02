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

//  Created by Simon Grinberg on 8/25/14.

#ifndef __CCSocialActionUtils_H_
#define __CCSocialActionUtils_H_

#include "cocos2d.h"

namespace soomla {
    
    USING_NS_CC;
    
    /**
     Lists all the social actions supported by social providers in Profile
     */
    enum CCSocialActionType {
        UPDATE_STATUS,
        UPDATE_STORY,
        UPLOAD_IMAGE,
        GET_CONTACTS,
        GET_FEED
    };
    
    /**
     @class CCSocialActionUtil
     @brief a Utility class which helps convert CCSocialActionType from/to 
     CCString
    
     Currently the class' soul purpose is to convert CCProvider from/to CCString
     */
    class CCSocialActionUtils
    {
    public:
        /**
         Converts the supplied enum CCSocialActionType to CCString
         
         @param actionType The value of provider to convert
         @return The provided value represented by a CCString
         */
        static CCString *actionEnumToString(CCSocialActionType actionType);
        
        /*
         Converts the supplied CCString to CCSocialActionType if possible
         
         @param actionTypeString The string to convert to CCSocialActionType
         @return The CCSocialActionType value corresponding to the supplied 
         string, or -1 if there is none
         */
        static CCSocialActionType actionStringToEnum(CCString* actionTypeString);
    };
};


#endif
