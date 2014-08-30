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
    
     __String* CCUserProfileUtils::providerEnumToString(CCProvider actionType) {
         switch (actionType) {
             case FACEBOOK:
                 return __String::create("facebook");
                 break;
             case FOURSQUARE:
                 return __String::create("foursquare");
                 break;
             case GOOGLE:
                 return __String::create("google");
                 break;
             case LINKEDIN:
                 return __String::create("linkedin");
                 break;
             case MYSPACE:
                 return __String::create("myspace");
                 break;
             case TWITTER:
                 return __String::create("twitter");
                 break;
             case YAHOO:
                 return __String::create("yahoo");
                 break;
             case SALESFORCE:
                 return __String::create("salesforce");
                 break;
             case YAMMER:
                 return __String::create("yammer");
                 break;
             case RUNKEEPER:
                 return __String::create("runkeeper");
                 break;
             case INSTAGRAM:
                 return __String::create("instagram");
                 break;
             case FLICKR:
                 return __String::create("flickr");
                 break;
             default:
                 break;
         }
         
         return NULL;
    }
    
    CCProvider CCUserProfileUtils::providerStringToEnum(__String* actionTypeString) {
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
