//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaProfileConfigBuilder.h"

using namespace soomla;

CCSoomlaProfileConfigBuilder::CCSoomlaProfileConfigBuilder()
        : CCSoomlaConfigBuilder() {
}

CCSoomlaProfileConfigBuilder *CCSoomlaProfileConfigBuilder::create() {
    return new CCSoomlaProfileConfigBuilder();
}

CCSoomlaProfileConfigBuilder* CCSoomlaProfileConfigBuilder::addSocialProviderConfiguration(CCSoomlaProfileSNConfigBuilder *snConfig) {
    return this->appendConfigParameter(CCUserProfileUtils::providerEnumToString(snConfig->getProvider())->getCString(), snConfig->build()) ? this : NULL;
}