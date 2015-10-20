//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCSOOMLAPROFILESNCONFIGBUILDER_H
#define COCOS2DXPROFILE_CCSOOMLAPROFILESNCONFIGBUILDER_H

#include "CCSoomlaConfigBuilder.h"
#include "CCUserProfileUtils.h"

namespace soomla {
    class CCSoomlaProfileSNConfigBuilder : public CCSoomlaConfigBuilder {
    public:
        CCSoomlaProfileSNConfigBuilder();
        virtual CCProvider getProvider() = 0;
        static CCSoomlaProfileSNConfigBuilder *create();
        CCSoomlaProfileSNConfigBuilder *enableAutoLogin(bool enabled);
    };
}


#endif //COCOS2DXPROFILE_CCSOOMLAPROFILESNCONFIGBUILDER_H
