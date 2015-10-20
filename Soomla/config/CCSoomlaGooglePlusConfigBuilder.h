//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCSOOMLAGOOGLEPLUSCONFIGBUILDER_H
#define COCOS2DXPROFILE_CCSOOMLAGOOGLEPLUSCONFIGBUILDER_H

#include "CCSoomlaProfileSNConfigBuilder.h"

namespace soomla {
    class CCSoomlaGooglePlusConfigBuilder : public CCSoomlaProfileSNConfigBuilder {
    public:
        static const CCProvider provider = CCProvider::GOOGLE;
        static CCSoomlaGooglePlusConfigBuilder *create();
        CCSoomlaGooglePlusConfigBuilder *setClientId(const char *clientId);
    };
}


#endif //COCOS2DXPROFILE_CCSOOMLAGOOGLEPLUSCONFIGBUILDER_H
