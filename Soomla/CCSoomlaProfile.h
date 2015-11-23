/*
 Copyright (C) 2012-2014 Soomla Inc.

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


#ifndef __CCSoomlaProfile_H_
#define __CCSoomlaProfile_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"
#include "CCUserProfile.h"
#include "CCSocialActionUtils.h"
#include "CCUserProfileUtils.h"
#include "CCLeaderboard.h"

namespace soomla {
	/**
     @class CCSoomlaProfile
     @brief An interface to the native SoomlaProfile class.

     An interface to the native SoomlaProfile class, use this class to
     access the native SoomlaProfile functionality.
	 */
    class CCSoomlaProfile: public cocos2d::Ref {
    public:
		/**
         Retrieves the singleton instance of CCSoomlaProfile

         @return The singleton instance of CCSoomlaProfile
         */
        static CCSoomlaProfile* getInstance();

        /**
         Constructor

         The main constructor for CCSoomlaProfile
         */
        CCSoomlaProfile();

        /**
         Initializes the CCSoomlaProfile

         NOTE: must be called before any of its methods can be used

         @param profileParams The parameters which are used to initialize
         the native ProfileBridge
         */
        static void initialize(cocos2d::__Dictionary *profileParams);

        /**
         Logs a user into the given provider, upon successful login, the
         user will receive the supplied reward

         @param provider The provider to log the user into
         @param reward The reward which will be granted to the user upon a
         successful login
         @param soomlaError Any errors will be returned in this parameter
         */
        void login(CCProvider provider, CCReward *reward, CCError **soomlaError);

        /**
         Logs a user into the given provider, upon successful login, the
         user will receive the supplied reward

         @param provider The provider to log the user into
         @param reward The reward which will be granted to the user upon a
         successful login
         @param payload a String to receive when the function returns.
         @param soomlaError Any errors will be returned in this parameter
         */
        void login(CCProvider provider, const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Logs a user into the given provider, the user will not receive
         a reward for the login

         @param provider The provider to log the user into
         @param soomlaError Any errors will be returned in this parameter
         */
        void login(CCProvider provider, CCError **soomlaError);

        /**
         Logs the user out of the given provider

         @param provider The provider to log the user into
         @param soomlaError Any errors will be returned in this parameter
         */
        void logout(CCProvider provider, CCError **soomlaError);

        /**
         Logs the user out of all available providers.

         @param soomlaError Any errors will be returned in this parameter
         */
        void logoutFromAllProviders(CCError **soomlaError);

        /**
         Fetches the user's profile for the given provider from the local
         device storage

         @param provider The provider for which to get the user's stored profile
         @param soomlaError Any errors will be returned in this parameter
         */
        CCUserProfile *getStoredUserProfile(CCProvider provider, CCError **soomlaError);

        /**
         Updates the user's status on the provided provider. Upon a successful
         update, the user will receive the supplied reward.

         @param provider The provider on which to update user's status
         @param status The text to update the user's status with
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStatus(CCProvider provider, const char *status, CCReward *reward, CCError **soomlaError);

        /**
        Updates the user's status on the provided provider. Upon a successful
        update, the user will receive the supplied reward.

        @param provider The provider on which to update user's status
        @param status The text to update the user's status with
        @param reward The reward which will be granted to the user upon a successful update
        @param showConfirmation If true, shows confirmation dialog before the action
        @param soomlaError Any errors will be returned in this parameter
        @param customMessage the message to show in the dialog
        */
        void updateStatusWithConfirmation(CCProvider provider, const char *status, const char *payload, CCReward *reward, char const *customMessage, CCError **soomlaError);

        /**
         Updates the user's status on the provided provider. Upon a successful
         update, the user will receive the supplied reward.

         @param provider The provider on which to update user's status
         @param status The text to update the user's status with
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStatus(CCProvider provider, const char *status, const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Updates the user's status on the provided provider. Upon a successful
         update, the user will receive the supplied reward.
         Using provider's native dialogs (when available)

         @param provider The provider on which to update user's status
         @param link The link that is shared
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStatusDialog(CCProvider provider, const char *link, CCReward *reward, CCError **soomlaError);

        /**
         Updates the user's status on the provided provider. Upon a successful
         update, the user will receive the supplied reward.
         Using provider's native dialogs (when available)

         @param provider The provider on which to update user's status
         @param link The link that is shared
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStatusDialog(CCProvider provider, const char *link, const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Updates a user's story on the provided provider. a Story is a more
         detailed status (very Facebook oriented). Upon a successful
         update, the user will receive the supplied reward.

         @param provider The provider on which to update user's story
         @param message The main text which will appear in the story
         @param name The headline for the link which will be integrated in the
         story
         @param caption The sub-headline for the link which will be
         integrated in the story
         @param description The description for the link which will be
         integrated in the story
         @param link The link which will be integrated into the user's story
         @param picture a Link to a picture which will be featured in the link
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStory(CCProvider provider, const char *message, const char *name, const char *caption,
                const char *description, const char *link, const char *picture,
                CCReward *reward, CCError **soomlaError);

        /**
         Updates a user's story on the provided provider. a Story is a more
         detailed status (very Facebook oriented). Upon a successful
         update, the user will receive the supplied reward.

         @param provider The provider on which to update user's story
         @param message The main text which will appear in the story
         @param name The headline for the link which will be integrated in the
         story
         @param caption The sub-headline for the link which will be
         integrated in the story
         @param description The description for the link which will be
         integrated in the story
         @param link The link which will be integrated into the user's story
         @param picture a Link to a picture which will be featured in the link
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStory(CCProvider provider, const char *message, const char *name, const char *caption,
                         const char *description, const char *link, const char *picture,
                         const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Updates a user's story on the provided provider. a Story is a more
         detailed status (very Facebook oriented). Upon a successful
         update, the user will receive the supplied reward.

         @param provider The provider on which to update user's story
         @param message The main text which will appear in the story
         @param name The headline for the link which will be integrated in the
         story
         @param caption The sub-headline for the link which will be
         integrated in the story
         @param description The description for the link which will be
         integrated in the story
         @param link The link which will be integrated into the user's story
         @param picture a Link to a picture which will be featured in the link
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful update
         @param showConfirmation If true, shows confirmation dialog before the action
         @param customMessage the message to show in the dialog
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStoryWithConfirmation(CCProvider provider, const char *message, const char *name, const char *caption,
                const char *description, const char *link, const char *picture,
                const char *payload, CCReward *reward, char const *customMessage, CCError **soomlaError);

        /**
         Updates a user's story on the provided provider. a Story is a more
         detailed status (very Facebook oriented). Upon a successful
         update, the user will receive the supplied reward.
         Using provider's native dialogs (when available)

         @param provider The provider on which to update user's story
         @param name The headline for the link which will be integrated in the
         story
         @param caption The sub-headline for the link which will be
         integrated in the story
         @param description The description for the link which will be
         integrated in the story
         @param link The link which will be integrated into the user's story
         @param picture a Link to a picture which will be featured in the link
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStoryDialog(CCProvider provider, const char *name, const char *caption,
                         const char *description, const char *link, const char *picture,
                         CCReward *reward, CCError **soomlaError);

        /**
         Updates a user's story on the provided provider. a Story is a more
         detailed status (very Facebook oriented). Upon a successful
         update, the user will receive the supplied reward.
         Using provider's native dialogs (when available)

         @param provider The provider on which to update user's story
         @param name The headline for the link which will be integrated in the
         story
         @param caption The sub-headline for the link which will be
         integrated in the story
         @param description The description for the link which will be
         integrated in the story
         @param link The link which will be integrated into the user's story
         @param picture a Link to a picture which will be featured in the link
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful update
         @param soomlaError Any errors will be returned in this parameter
         */
        void updateStoryDialog(CCProvider provider, const char *name, const char *caption,
                               const char *description, const char *link, const char *picture,
                               const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Uploads an image to the user's profile in the supplied provider.
         Upon a successful upload, the user will receive the supplied reward.

         @param provider The provider on which to upload an image for the user
         @param filePath The full file-path to the image on the device which
         will be uploaded
         @param reward The reward which will be granted to the user upon a
         successful upload
         @param soomlaError Any errors will be returned in this parameter
         */
        void uploadImage(CCProvider provider, const char *message, const char *filePath,
                CCReward *reward, CCError **soomlaError);

        /**
         Uploads an image to the user's profile in the supplied provider.
         Upon a successful upload, the user will receive the supplied reward.

         @param provider The provider on which to upload an image for the user
         @param filePath The full file-path to the image on the device which
         will be uploaded
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful upload
         @param soomlaError Any errors will be returned in this parameter
         */
        void uploadImage(CCProvider provider, const char *message, const char *filePath,
                         const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Uploads an image to the user's profile in the supplied provider.
         Upon a successful upload, the user will receive the supplied reward.

         @param provider The provider on which to upload an image for the user
         @param filePath The full file-path to the image on the device which
         will be uploaded
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful upload
         @param showConfirmation If true, shows confirmation dialog before the action
         @param customMessage the message to show in the dialog
         @param soomlaError Any errors will be returned in this parameter
         */
        void uploadImageWithConfirmation(CCProvider provider, const char *message, const char *filePath,
                const char *payload, CCReward *reward, char const *customMessage, CCError **soomlaError);

        /**
         Shares a current screenshot to the user's feed and grants the user a reward.

         @param activity activity to use as context for the screenshot
         @param provider The provider to use
         @param message  A text that will accompany the image
         @param title  A title of post
        */
        void uploadCurrentScreenshot(CCProvider provider, const char * title, const char * message, CCError **soomlaError);

        /**
         Shares a current screenshot to the user's feed and grants the user a reward.

         @param activity activity to use as context for the screenshot
         @param provider The provider to use
         @param message  A text that will accompany the image
         @param title  A title of post
         @param payload  a String to receive when the function returns.
         @param reward   The reward to give the user
         @throws ProviderNotFoundException if the supplied provider is not
                                           supported by the framework
        */
        void uploadCurrentScreenshot(CCProvider provider, const char * title, const char * message, const char * payload, CCReward * reward, CCError **soomlaError);

        /**
         Retrieves a list of the user's contacts from the supplied provider,
         which also use this application. Upon a successful retrieval of
         contacts the user will be granted the supplied reward.

         @param provider The provider on which to retrieve a list of contacts from
         @param fromStart Should we reset pagination or request the next page
         @param reward The reward which will be granted to the user upon a successful retrieval of contacts
         @param soomlaError Any errors will be returned in this parameter
         */
        void getContacts(CCProvider provider, bool fromStart, CCReward *reward, CCError **soomlaError);

        /**
         Retrieves a list of the user's contacts from the supplied provider,
         which also use this application. Upon a successful retrieval of
         contacts the user will be granted the supplied reward.

         @param provider The provider on which to retrieve a list of contacts
         from
         @param reward The reward which will be granted to the user upon a
         successful retrieval of contacts
         @param soomlaError Any errors will be returned in this parameter
         */
        void getContacts(CCProvider provider, CCReward *reward, CCError **soomlaError);

        /**
         Retrieves a list of the user's contacts from the supplied provider,
         which also use this application. Upon a successful retrieval of
         contacts the user will be granted the supplied reward.

         @param provider The provider on which to retrieve a list of contacts from
         @param fromStart Should we reset pagination or request the next page
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful retrieval of contacts
         @param soomlaError Any errors will be returned in this parameter
         */
        void getContacts(CCProvider provider, bool fromStart, const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Retrieves a list of the user's feed entries from the supplied provider.
         Upon a successful retrieval of feed entries the user will be granted
         the supplied reward.

         @param provider The provider on which to retrieve a list of feed
         entries
         @param reward The reward which will be granted to the user upon a
         successful retrieval of feed
         @param soomlaError Any errors will be returned in this parameter
         */
        void getFeed(CCProvider provider, CCReward *reward, CCError **soomlaError);

        /**
         Retrieves a list of the user's feed entries from the supplied provider.
         Upon a successful retrieval of feed entries the user will be granted
         the supplied reward.

         @param provider The provider on which to retrieve a list of feed
         entries
         @param fromStart Should we reset pagination or request the next page
         @param reward The reward which will be granted to the user upon a
         successful retrieval of feed
         @param soomlaError Any errors will be returned in this parameter
         */
        void getFeed(CCProvider provider, bool fromStart, CCReward *reward, CCError **soomlaError);

        /**
         Retrieves a list of the user's feed entries from the supplied provider.
         Upon a successful retrieval of feed entries the user will be granted
         the supplied reward.

         @param provider The provider on which to retrieve a list of feed
         entries
         @param fromStart Should we reset pagination or request the next page
         @param payload a String to receive when the function returns.
         @param reward The reward which will be granted to the user upon a
         successful retrieval of feed
         @param soomlaError Any errors will be returned in this parameter
         */
        void getFeed(CCProvider provider, bool fromStart, const char *payload, CCReward *reward, CCError **soomlaError);

        /**
         Sends an invite.

         @param activity The parent activity
         @param provider The provider to use
         @param inviteMessage a message will send to recipients.
        */
        void invite(CCProvider provider, const char * inviteMessage, CCError **soomlaError);

        /**
         Sends an invite.

         @param activity The parent activity
         @param provider The provider to use
         @param inviteMessage a message will send to recipients.
         @param dialogTitle a title of app request dialog.
         @param payload  a String to receive when the function returns.
         @param reward The reward to grant
         */
        void invite(CCProvider provider, const char * inviteMessage, const char * dialogTitle, const char * payload, CCReward * reward, CCError **soomlaError);

        /**
         Checks if the user is logged into the supplied provider

         @param provider The provider on which to check if the user is logged in
         @param soomlaError Any errors will be returned in this parameter
         */
        bool isLoggedIn(CCProvider provider, CCError **soomlaError);

        /**
         Opens up a provider page to "like" (external), and grants the user
         the supplied reward

         @param provider The provider on which to open the like page
         @param pageId The id or name of the page to open (page id is recommended)
         @param reward The reward which will be granted to the user upon a
         successful opening of the page
         @param soomlaError Any errors will be returned in this parameter
         */
        void like(CCProvider provider, const char *pageId, CCReward *reward, CCError **soomlaError);

        /**
         Utility method to open up the market application rating page
         */
        void openAppRatingPage(CCError **soomlaError);

        /**
        * Shares text and/or image using native sharing functionality of your target platform.
        * @param text Text to share
        * @param imageFilePath Path to an image file to share
        * @param soomlaError Any errors will be returned in this parameter
        */
        void multiShare(const char *text, const char *imageFilePath, CCError **soomlaError);

        void getLeaderboards(CCProvider provider, const char *payload, CCReward *reward, CCError **soomlaError);

        void getScores(CCProvider provider, CCLeaderboard *leaderboard, bool fromStart, const char *payload, CCReward *reward, CCError **soomlaError);

        void getScores(CCProvider provider, CCLeaderboard *leaderboard, const char *payload, CCReward *reward, CCError **soomlaError);

        void reportScore(CCProvider provider, CCLeaderboard *leaderboard, unsigned int score, const char *payload, CCReward *reward, CCError **soomlaError);
    };
};

#endif // !__CCSoomlaProfile_H_
