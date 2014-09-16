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

//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCProfileService_H_
#define __CCProfileService_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"
#include "CCUserProfile.h"

namespace soomla {

    /**
     @class CCProfileService
     @brief Provides an interface to the native ProfileService
     
     Allows the cocos2dx project to call native functions on ProfileService
     in the Cocos2dx Profile bridge.
     */
    class CCProfileService: public cocos2d::CCObject {
    public:
		/**
         This class is singleton, use this function to access it.
		*/
        static CCProfileService* getInstance();

        /**
         Initializes the singleto instance of the service
         
         @param profileParams The parameters which are used to initialize
         the native ProfileService
         */
        static void initShared(cocos2d::CCDictionary *profileParams);

        /**
         Constructor
         
         The main constructor for CCProfileService
         */
        CCProfileService();

        /**
         Initializes an instance of CCProfileService with the profile parameters
         needed by the native platform
         
         @param profileParams The parameters which are used to initialize
         the native ProfileService
         */
        virtual bool init(cocos2d::CCDictionary *profileParams);
    };
};

#endif // !__CCSoomlaProfile_H_
