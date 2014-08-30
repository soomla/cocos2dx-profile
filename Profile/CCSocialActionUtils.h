//
//  CCSocialActionUtils.h
//
//  Created by Simon Grinberg on 8/25/14.
//  Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCSocialActionUtils_H_
#define __CCSocialActionUtils_H_

#include "cocos2d.h"

namespace soomla {
    
    USING_NS_CC;
    
    enum CCSocialActionType {
        UPDATE_STATUS,
        UPDATE_STORY,
        UPLOAD_IMAGE,
        GET_CONTACTS,
        GET_FEED
    };
    
    class CCSocialActionUtils
    {
    public:
        static __String *actionEnumToString(CCSocialActionType actionType);
        static CCSocialActionType actionStringToEnum(__String* actionTypeString);
    };
};


#endif
