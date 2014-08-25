//
//  CCSocialActionUtils.cpp
//  Cocos2dXProfile
//
//  Created by Simon Grinberg on 8/25/14.
//  Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialActionUtils.h"

namespace soomla {
    
     __String* CCSocialActionUtils::actionEnumToString(CCSocialActionType actionType) {
         switch (actionType) {
             case UPDATE_STATUS:
                 return __String::create("UPDATE_STATUS");
                 break;
             case UPDATE_STORY:
                 return __String::create("UPDATE_STORY");
             case UPLOAD_IMAGE:
                 return __String::create("UPLOAD_IMAGE");
             case GET_CONTACTS:
                 return __String::create("GET_CONTACTS");
             case GET_FEED:
                 return __String::create("GET_FEED");
             default:
                 break;
         }
         
         return NULL;
    }
    
    CCSocialActionType CCSocialActionUtils::actionStringToEnum(__String* actionTypeString) {
        if (actionTypeString->compare("UPDATE_STATUS")) {
            return UPDATE_STATUS;
        }
        else if (actionTypeString->compare("UPDATE_STORY")) {
            return UPDATE_STORY;
        }
        else if (actionTypeString->compare("UPLOAD_IMAGE")) {
            return UPLOAD_IMAGE;
        }
        else if (actionTypeString->compare("GET_CONTACTS")) {
            return GET_CONTACTS;
        }
        else if (actionTypeString->compare("GET_FEED")) {
            return GET_FEED;
        }
        
        return (CCSocialActionType)-1;
    }
    
};
