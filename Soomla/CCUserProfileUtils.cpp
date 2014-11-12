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

#include "CCUserProfileUtils.h"

namespace soomla {
    
     CCString* CCUserProfileUtils::providerEnumToString(CCProvider actionType) {
         switch (actionType) {
             case FACEBOOK:
                 return CCString::create("facebook");
                 break;
             case GOOGLE:
                 return CCString::create("google");
                 break;
             case TWITTER:
                 return CCString::create("twitter");
                 break;
             default:
                 break;
         }
         
         return NULL;
    }
    
    CCProvider CCUserProfileUtils::providerStringToEnum(CCString* actionTypeString) {
        if (actionTypeString->compare("facebook")) {
            return FACEBOOK;
        }
        else if (actionTypeString->compare("google")) {
            return GOOGLE;
        }
        else if (actionTypeString->compare("twitter")) {
            return TWITTER;
        }
        
        return (CCProvider)-1;
    }
    
};
