#ifndef __CCProfileEventDispatcher_H_
#define __CCProfileEventDispatcher_H_

#include "cocos2d.h"
#include "CCProfileEventHandler.h"
#include "CCAbstractAggregatedEventHandler.h"
#include "CCSocialActionUtils.h"
#include "CCUserProfileUtils.h"

namespace soomla {

	/** \class CCProfileEventDispatcher
		\brief Calls event handler functions when events are fired, also contains settings for StoreController.

		This class calls event handler functions when events are fired, to tie
		it to your event handler call addEventHandler(). You also set parameters
		for StoreController through this class.
	 */
    class CCProfileEventDispatcher : public CCAbstractAggregatedEventHandler<CCProfileEventHandler>, public CCProfileEventHandler {
    public:
		/**
		   This class is singleton, access it with this function.
		 */
        static CCProfileEventDispatcher *getInstance();

        bool init();

        virtual void onLoginFailed(CCProvider provider, cocos2d::__String *errorDescription);

        virtual void onLoginFinished(CCUserProfile *userProfile);

        virtual void onLoginStarted(CCProvider provider);

        virtual void onLogoutFailed(CCProvider provider, cocos2d::__String *errorDescription);

        virtual void onLogoutFinished(CCProvider provider);

        virtual void onLogoutStarted(CCProvider provider);

        virtual void onGetContactsFailed(CCProvider provider, cocos2d::__String *errorDescription);

        virtual void onGetContactsFinished(CCProvider provider, cocos2d::__Array *contactsDict);

        virtual void onGetContactsStarted(CCProvider provider);
        
        virtual void onGetFeedFailed(CCProvider provider, cocos2d::__String *errorDescription);
        
        virtual void onGetFeedFinished(CCProvider provider, cocos2d::__Array *feedList);
        
        virtual void onGetFeedStarted(CCProvider provider);

        virtual void onSocialActionFailedEvent(CCProvider provider, CCSocialActionType socialActionType, cocos2d::__String *errorDescription);

        virtual void onSocialActionFinishedEvent(CCProvider provider, CCSocialActionType socialActionType);

        virtual void onSocialActionStartedEvent(CCProvider provider, CCSocialActionType socialActionType);

        virtual void onLoginCancelledEvent(CCProvider provider);

        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);
        
        virtual void onRewardGivenEvent(CCReward *reward);

    private:
        CCUserProfile *extractUserProfile(Ref *userProfileRef);
        cocos2d::__Array *extractUserProfileArray(Ref *userProfileDictArray);
    };
};

#endif //__CCProfileEventDispatcher_H_
