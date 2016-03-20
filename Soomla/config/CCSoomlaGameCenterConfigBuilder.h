/*
 Copyright (C) 2012-2015 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef COCOS2DXPROFILE_CCSOOMLAGAMECENTERCONFIGBUILDER_H
#define COCOS2DXPROFILE_CCSOOMLAGAMECENTERCONFIGBUILDER_H


#import "CCSoomlaProfileSNConfigBuilder.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

namespace soomla {
    class CCSoomlaGameCenterConfigBuilder : public CCSoomlaProfileSNConfigBuilder {
    public:
        CCSoomlaGameCenterConfigBuilder();
        CCProvider getProvider();
        CCSoomlaGameCenterConfigBuilder *enableAutoLogin(bool enabled);
        static CCSoomlaGameCenterConfigBuilder *create();
    };
}
#endif

#endif //COCOS2DXPROFILE_CCSOOMLAGAMECENTERCONFIGBUILDER_H
