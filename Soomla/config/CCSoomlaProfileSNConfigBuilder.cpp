//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaProfileSNConfigBuilder.h"

using namespace soomla;

CCSoomlaProfileSNConfigBuilder *CCSoomlaProfileSNConfigBuilder::enableAutoLogin(bool enabled) {
    return this->appendConfigParameter("autoLogin", cocos2d::__Bool::create(enabled)) ? this : NULL;
}