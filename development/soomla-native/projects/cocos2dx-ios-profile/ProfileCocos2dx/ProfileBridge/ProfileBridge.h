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

#import <Foundation/Foundation.h>

/**
 Profile defines all the glue between Cocos2dx-Profile and iOS Profile

 ProfileBridge signs up to all Profile events which are received from native
 and passed to Cocos2dx and the other way around.
 */
@interface ProfileBridge : NSObject
/**
 Retrieves the singleton instance of the service

 @return Singleton instance of ProfileBridge
 */
+ (id)sharedProfileBridge;
@end
