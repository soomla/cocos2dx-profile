/*
 Copyright (C) 2012-2015 Soomla Inc.

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

#include "CCSoomlaTwitterConfigBuilder.h"

using namespace soomla;

CCProvider CCSoomlaTwitterConfigBuilder::getProvider() {
    return CCProvider::TWITTER;
}

CCSoomlaTwitterConfigBuilder::CCSoomlaTwitterConfigBuilder()
        : CCSoomlaProfileSNConfigBuilder() {
}

CCSoomlaTwitterConfigBuilder *CCSoomlaTwitterConfigBuilder::create() {
    return new CCSoomlaTwitterConfigBuilder();
}

CCSoomlaTwitterConfigBuilder *CCSoomlaTwitterConfigBuilder::setConsumerKey(const char *consumerKey) {
    return this->appendConfigParameter("consumerKey", cocos2d::__String::create(consumerKey)) ? this : NULL;
}

CCSoomlaTwitterConfigBuilder *CCSoomlaTwitterConfigBuilder::setConsumerSecret(const char *consumerSecret) {
    return this->appendConfigParameter("consumerSecret", cocos2d::__String::create(consumerSecret)) ? this : NULL;
}