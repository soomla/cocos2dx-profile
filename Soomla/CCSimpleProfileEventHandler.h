
#ifndef __CCSimpleProfileEventHandler_H_
#define __CCSimpleProfileEventHandler_H_

#include "CCProfileEventHandler.h"

namespace soomla {

    class CCSimpleProfileEventHandler: public CCProfileEventHandler {

    public:

        virtual void onProfileInitialized();

        virtual void onUserRatingEvent();

        virtual void onLoginFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        virtual void onLoginFinished(CCUserProfile *userProfile, cocos2d::CCString *payload);

        virtual void onLoginStarted(CCProvider provider, cocos2d::CCString *payload);

        virtual void onLogoutFailed(CCProvider provider, cocos2d::CCString *errorDescription);

        virtual void onLogoutFinished(CCProvider provider);

        virtual void onLogoutStarted(CCProvider provider);

        virtual void onGetContactsFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        virtual void onGetContactsFinished(CCProvider provider, cocos2d::CCArray *contactsDict, cocos2d::CCString *payload);

        virtual void onGetContactsStarted(CCProvider provider, cocos2d::CCString *payload);

        virtual void onGetFeedFailed(CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        virtual void onGetFeedFinished(CCProvider provider, cocos2d::CCArray *feedList, cocos2d::CCString *payload);

        virtual void onGetFeedStarted(CCProvider provider, cocos2d::CCString *payload);

        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *errorDescription, cocos2d::CCString *payload);

        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload);

        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::CCString *payload);

        virtual void onLoginCancelledEvent(CCProvider provider, cocos2d::CCString *payload);

        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);
    };
}

#endif //__CCSimpleProfileEventHandler_H_
