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
             case FOURSQUARE:
                 return CCString::create("foursquare");
                 break;
             case GOOGLE:
                 return CCString::create("google");
                 break;
             case LINKEDIN:
                 return CCString::create("linkedin");
                 break;
             case MYSPACE:
                 return CCString::create("myspace");
                 break;
             case TWITTER:
                 return CCString::create("twitter");
                 break;
             case YAHOO:
                 return CCString::create("yahoo");
                 break;
             case SALESFORCE:
                 return CCString::create("salesforce");
                 break;
             case YAMMER:
                 return CCString::create("yammer");
                 break;
             case RUNKEEPER:
                 return CCString::create("runkeeper");
                 break;
             case INSTAGRAM:
                 return CCString::create("instagram");
                 break;
             case FLICKR:
                 return CCString::create("flickr");
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
        else if (actionTypeString->compare("foursquare")) {
            return FOURSQUARE;
        }
        else if (actionTypeString->compare("google")) {
            return GOOGLE;
        }
        else if (actionTypeString->compare("linkedin")) {
            return LINKEDIN;
        }
        else if (actionTypeString->compare("myspace")) {
            return LINKEDIN;
        }
        else if (actionTypeString->compare("twitter")) {
            return TWITTER;
        }
        else if (actionTypeString->compare("yahoo")) {
            return YAHOO;
        }
        else if (actionTypeString->compare("salesforce")) {
            return SALESFORCE;
        }
        else if (actionTypeString->compare("yammer")) {
            return YAMMER;
        }
        else if (actionTypeString->compare("runkeeper")) {
            return RUNKEEPER;
        }
        else if (actionTypeString->compare("instagram")) {
            return INSTAGRAM;
        }
        else if (actionTypeString->compare("flickr")) {
            return FLICKR;
        }
        
        return (CCProvider)-1;
    }
    
};
