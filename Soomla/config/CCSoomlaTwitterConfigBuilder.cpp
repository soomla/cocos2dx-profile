//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaTwitterConfigBuilder.h"

using namespace soomla;

CCSoomlaTwitterConfigBuilder *CCSoomlaTwitterConfigBuilder::setConsumerKey(const char *consumerKey) {
    return this->appendConfigParameter("consumerKey", cocos2d::__String::create(consumerKey)) ? this : NULL;
}

CCSoomlaTwitterConfigBuilder *CCSoomlaTwitterConfigBuilder::setConsumerSecret(const char *consumerSecret) {
    return this->appendConfigParameter("consumerSecret", cocos2d::__String::create(consumerSecret)) ? this : NULL;
}