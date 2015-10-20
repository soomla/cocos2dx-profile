//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaFacebookConfigBuilder.h"

using namespace soomla;

CCProvider CCSoomlaFacebookConfigBuilder::getProvider() {
    return CCProvider::FACEBOOK;
}

CCSoomlaFacebookConfigBuilder::CCSoomlaFacebookConfigBuilder()
        : CCSoomlaProfileSNConfigBuilder() {
}

CCSoomlaFacebookConfigBuilder *CCSoomlaFacebookConfigBuilder::create() {
    return new CCSoomlaFacebookConfigBuilder();
}

CCSoomlaFacebookConfigBuilder *CCSoomlaFacebookConfigBuilder::setPermissions(const char *permissions) {
    return this->appendConfigParameter("permissions", cocos2d::__String::create(permissions)) ? this : NULL;
}