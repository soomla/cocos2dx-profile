//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXPROFILE_CCSOOMLAPROFILECONFIGBUILDER_H
#define COCOS2DXPROFILE_CCSOOMLAPROFILECONFIGBUILDER_H

#include "CCSoomlaConfigBuilder.h"
#include "CCSoomlaProfileSNConfigBuilder.h"

namespace soomla {
    class CCSoomlaProfileConfigBuilder : public CCSoomlaConfigBuilder {
    public:
        CCSoomlaProfileConfigBuilder();
        static CCSoomlaProfileConfigBuilder *create();
        CCSoomlaProfileConfigBuilder *setSocialProviderConfiguration(CCSoomlaProfileSNConfigBuilder *snConfig);
    };
}




#endif //COCOS2DXPROFILE_CCSOOMLAPROFILECONFIGBUILDER_H
