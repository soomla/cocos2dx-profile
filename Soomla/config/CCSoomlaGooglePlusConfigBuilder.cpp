//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaGooglePlusConfigBuilder.h"

using namespace soomla;

CCProvider CCSoomlaGooglePlusConfigBuilder::getProvider() {
    return CCProvider::GOOGLE;
}

CCSoomlaGooglePlusConfigBuilder::CCSoomlaGooglePlusConfigBuilder()
        : CCSoomlaProfileSNConfigBuilder() {
}

CCSoomlaGooglePlusConfigBuilder *CCSoomlaGooglePlusConfigBuilder::create() {
    return new CCSoomlaGooglePlusConfigBuilder();
}

CCSoomlaGooglePlusConfigBuilder *CCSoomlaGooglePlusConfigBuilder::setClientId(const char *clientId) {
    return this->appendConfigParameter("clientId", cocos2d::__String::create(clientId)) ? this : NULL;
}