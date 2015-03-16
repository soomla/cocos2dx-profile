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

#ifndef __CCProfileBridge_H_
#define __CCProfileBridge_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"
#include "CCUserProfile.h"

namespace soomla {

    /**
     @class CCProfileBridge
     @brief Provides an interface to the native ProfileBridge

     Allows the cocos2dx project to call native functions on ProfileBridge
     in the Cocos2dx Profile bridge.
     */
    class CCProfileBridge: public cocos2d::CCObject {
    public:
		/**
         This class is singleton, use this function to access it.
		*/
        static CCProfileBridge* getInstance();

        /**
         Initializes the singleto instance of the service

         @param profileParams The parameters which are used to initialize
         the native ProfileBridge
         */
        static void initShared(cocos2d::CCDictionary *profileParams);

        /**
         Constructor

         The main constructor for CCProfileBridge
         */
        CCProfileBridge();

        /**
         Initializes an instance of CCProfileBridge with the profile parameters
         needed by the native platform

         @param profileParams The parameters which are used to initialize
         the native ProfileService
         */
        virtual bool init(cocos2d::CCDictionary *profileParams);
        
    private:
        void bindNative();

    };
};

#endif // !__CCProfileBridge_H_
