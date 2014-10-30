
#ifndef __CCSimpleProfileEventHandler_H_
#define __CCSimpleProfileEventHandler_H_

#include "CCProfileEventHandler.h"

namespace soomla {

    class CCSimpleProfileEventHandler: public CCProfileEventHandler {

    public:

        virtual void onProfileInitialized();

        virtual void onUserRatingEvent();

        virtual void onLoginFailed(CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload);

        virtual void onLoginFinished(CCUserProfile *userProfile, cocos2d::__String *payload);

        virtual void onLoginStarted(CCProvider provider, cocos2d::__String *payload);

        virtual void onLogoutFailed(CCProvider provider, cocos2d::__String *errorDescription);

        virtual void onLogoutFinished(CCProvider provider);

        virtual void onLogoutStarted(CCProvider provider);

        virtual void onGetContactsFailed(CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload);

        virtual void onGetContactsFinished(CCProvider provider, cocos2d::__Array *contactsDict, cocos2d::__String *payload);

        virtual void onGetContactsStarted(CCProvider provider, cocos2d::__String *payload);

        virtual void onGetFeedFailed(CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload);

        virtual void onGetFeedFinished(CCProvider provider, cocos2d::__Array *feedList, cocos2d::__String *payload);

        virtual void onGetFeedStarted(CCProvider provider, cocos2d::__String *payload);

        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *errorDescription, cocos2d::__String *payload);

        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *payload);

        virtual void onLoginCancelledEvent(CCProvider provider, cocos2d::__String *payload);

        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);
    };
}

#endif //__CCSimpleProfileEventHandler_H_
