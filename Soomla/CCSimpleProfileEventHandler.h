//
// Created by Shubin Fedor on 08/09/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCSimpleProfileEventHandler_H_
#define __CCSimpleProfileEventHandler_H_

#include "CCProfileEventHandler.h"

namespace soomla {

    class CCSimpleProfileEventHandler: public CCProfileEventHandler {

    public:

        virtual void onProfileInitialized();
        
        virtual void onUserRatingEvent();

        virtual void onLoginFailed(CCProvider provider, cocos2d::__String *errorDescription);

        virtual void onLoginFinished(CCUserProfile *userProfile);

        virtual void onLoginStarted(CCProvider provider);

        virtual void onLogoutFailed(CCProvider provider, cocos2d::CCString *errorDescription);

        virtual void onLogoutFinished(CCProvider provider);

        virtual void onLogoutStarted(CCProvider provider);

        virtual void onGetContactsFailed(CCProvider provider, cocos2d::CCString *errorDescription);

        virtual void onGetContactsFinished(CCProvider provider, cocos2d::CCArray *contactsDict);

        virtual void onGetContactsStarted(CCProvider provider);

        virtual void onGetFeedFailed(CCProvider provider, cocos2d::CCString *errorDescription);

        virtual void onGetFeedFinished(CCProvider provider, cocos2d::CCArray *feedList);

        virtual void onGetFeedStarted(CCProvider provider);

        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *errorDescription);

        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType);

        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType);

        virtual void onLoginCancelledEvent(CCProvider provider);

        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);
    };
}

#endif //__CCSimpleProfileEventHandler_H_
