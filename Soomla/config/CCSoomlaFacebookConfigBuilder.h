//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCSOOMLAFACEBOOKCONFIGBUILDER_H
#define COCOS2DXPROFILE_CCSOOMLAFACEBOOKCONFIGBUILDER_H

#include "CCSoomlaProfileSNConfigBuilder.h"

namespace soomla {
    class CCSoomlaFacebookConfigBuilder : public CCSoomlaProfileSNConfigBuilder {
    public:
        static const CCProvider provider = CCProvider::FACEBOOK;
        static CCSoomlaFacebookConfigBuilder *create();
        CCSoomlaFacebookConfigBuilder *setPermissions(const char *permissions);
    };
}


#endif //COCOS2DXPROFILE_CCSOOMLAFACEBOOKCONFIGBUILDER_H
