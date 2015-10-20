//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCSOOMLATWITTERCONFIGBUILDER_H
#define COCOS2DXPROFILE_CCSOOMLATWITTERCONFIGBUILDER_H

#include "CCSoomlaProfileSNConfigBuilder.h"

namespace soomla {
    class CCSoomlaTwitterConfigBuilder : public CCSoomlaProfileSNConfigBuilder {
    public:
        static const CCProvider provider = CCProvider::TWITTER;
        CCSoomlaTwitterConfigBuilder *setConsumerKey(const char *consumerKey);
        CCSoomlaTwitterConfigBuilder *setConsumerSecret(const char *setConsumerSecret);
    };
}

#endif //COCOS2DXPROFILE_CCSOOMLATWITTERCONFIGBUILDER_H
