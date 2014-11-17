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

#ifndef __CCUserProfileUtils_H_
#define __CCUserProfileUtils_H_

#include "cocos2d.h"

namespace soomla {
    
    USING_NS_CC;
    
    /**
     Lists all the supported or to-be supported social platforms (providers)
     */
    enum CCProvider {
        FACEBOOK = 0,
        GOOGLE = 2,
        TWITTER = 5
    };
    
    /**
     @class CCUserProfileUtils
     @brief a Utility class which helps convert CCProvider from/to CCString
     
     Currently the class' soul purpose is to convert CCProvider from/to
     CCString
     */
    class CCUserProfileUtils
    {
    public:
        /**
         Converts the supplied enum CCProvider to CCString
         
         @param providerType The value of provider to convert
         @return The provided value represented by a CCString
         */
        static CCString *providerEnumToString(CCProvider providerType);
        
        /**
         Converts the supplied CCString to CCProvider if possible
         
         @param providerTypeString The string to convert to CCProvider
         @return The CCProvider value corresponding to the supplied string,
         or -1 if there is none
         */
        static CCProvider providerStringToEnum(CCString* providerTypeString);
    };
};


#endif
