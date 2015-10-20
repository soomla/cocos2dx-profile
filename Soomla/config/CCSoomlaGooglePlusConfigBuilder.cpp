//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaGooglePlusConfigBuilder.h"

using namespace soomla;

CCSoomlaGooglePlusConfigBuilder *CCSoomlaGooglePlusConfigBuilder::setClientId(const char *clientId) {
    return this->appendConfigParameter("clientId", cocos2d::__String::create(clientId)) ? this : NULL;
}