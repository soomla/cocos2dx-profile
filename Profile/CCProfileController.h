//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCProfileController_H_
#define __CCProfileController_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"
#include "CCUserProfile.h"
#include "CCSocialActionUtils.h"
#include "CCUserProfileUtils.h"

namespace soomla {
	/** \class CCProfileController
		\brief An interface to the native StoreController class.

		An interface to the native StoreController class, use this class to
		access the native StoreController functionality.
	 */
    class CCProfileController: public cocos2d::Ref {
    private:
        bool mInited;
    public:
		/**
		   This class is singleton, use this function to access it.
		*/
        static CCProfileController* getInstance();

        CCProfileController();
        virtual bool init();

        void login(CCProvider provider, CCReward *reward, CCError **soomlaError);

        void login(CCProvider provider, CCError **soomlaError);

        void logout(CCProvider provider, CCError **soomlaError);

        CCUserProfile *getStoredUserProfile(CCProvider provider, CCError **soomlaError);

        void updateStatus(CCProvider provider, const char *status, CCReward *reward, CCError **soomlaError);

        void updateStory(CCProvider provider, const char *message, const char *name, const char *caption,
                const char *description, const char *link, const char *picture,
                CCReward *reward, CCError **soomlaError);

        void uploadImage(CCProvider provider, const char *message, const char *filePath,
                CCReward *reward, CCError **soomlaError);

        void getContacts(CCProvider provider, CCReward *reward, CCError **soomlaError);
        
        void getFeed(CCProvider provider, CCReward *reward, CCError **soomlaError);
        
        bool isLoggedIn(CCProvider provider, CCError **soomlaError);
        
        void like(CCProvider provider, const char *pageName, CCReward *reward, CCError **soomlaError);

    };
};

#endif // !__CCProfileController_H_
