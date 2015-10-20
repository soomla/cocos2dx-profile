//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaProfileConfigBuilder.h"

using namespace soomla;

CCSoomlaProfileConfigBuilder* CCSoomlaProfileConfigBuilder::setSocialProviderConfiguration(CCSoomlaProfileSNConfigBuilder *snConfig) {
    return this->appendConfigParameter(CCUserProfileUtils::providerEnumToString(snConfig->provider)->getCString(), snConfig->build()) ? this : NULL;
}