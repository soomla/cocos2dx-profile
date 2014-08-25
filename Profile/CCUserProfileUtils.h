//
//  CCUserProfileUtils.h
//
//  Created by Simon Grinberg on 8/25/14.
//  Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCUserProfileUtils_H_
#define __CCUserProfileUtils_H_

#include "cocos2d.h"

namespace soomla {
    
    USING_NS_CC;
    
    enum CCProvider {
        FACEBOOK,
        FOURSQUARE,
        GOOGLE,
        LINKEDIN,
        MYSPACE,
        TWITTER,
        YAHOO,
        SALESFORCE,
        YAMMER,
        RUNKEEPER,
        INSTAGRAM,
        FLICKR
    };
    
    class CCUserProfileUtils
    {
    public:
        static __String *providerEnumToString(CCProvider actionType);
        static CCProvider providerStringToEnum(__String* actionTypeString);
    };
};


#endif
