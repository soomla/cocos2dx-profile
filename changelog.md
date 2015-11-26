### v1.7.0 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.6.0...v1.7.0)

* New Features
  * Added Leaderboards to GameCenter

### v1.6.0 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.5.1...v1.6.0)

* New Features
  * Added Game Center as a social provider

### v1.5.1 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.5.0...v1.5.1)

* Features
  * Add `logoutFromAllProviders` method to `SoomlaProfile`

### v1.5.0 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.4.0...v1.5.0)

* Changes
  * Added builder classes for initialization params

### v1.4.0 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.3.3...v1.4.0)

* New Features
  * Implemented uploadCurrentScreenshot and invite

* Fixes
  * Crash when calling SoomlaProfile.login from within OnSoomlaProfileInitialized

### v1.3.3 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.3.2...v1.3.3)

* Changes
  * Removed binaries and improved build scripts
  * Added gson jar to android libs

### v1.3.2 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.3.1...v1.3.2)

* Changes
  * Updated submodules

### v1.3.1 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.3.0...v1.3.1)

* New Features
  * Support extra params in UserProfile
  * Support auto login

* Changes
  * Upgraded simple-facebook version

* Fixes
  * Add "autoLogin" field to LoginFinishedEvent

### v1.3.0 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.2.0...v1.3.0)

* New Features
  * Implemented Pagination for getContacts and getFeed
  * Implemented multi-sharing (sharing with the native functionality of your target platform)
  * Implemented methods to show confirmation dialog before some actions
  * Supporting permissions param in FB

### v1.2.0 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.1.1...v1.2.0)

**BREAKING API VERSION**

* Features
  * Replacing event handlers with custom events dispatched through Cocos2d-x facilities

### v1.1.1 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.1.0...v1.1.1)

* Changes
  * Changing iOS bridge compilation and resulting header location

### v1.1.0 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.0.3...v1.1.0)

**BREAKING API VERSION**

* Features
  * Better integration process for Profile module (see README for instructions)

### v1.0.3 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.0.2...v1.0.3)

* Fixes
  * Login cancelled will fire when back is clicked while logging in (Twitter Android)

### v1.0.2 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.0.1...v1.0.2)

* Fixes
  * Upload image now works in Google+

* Changes
  * Updating to new native submodules

### v1.0.1 [view commit logs](https://github.com/soomla/cocos2dx-profile/compare/v1.0.0...v1.0.1)

* Changes
  * Updating to new native submodules

### v1.0.0
* Features
  * The module is integrated with Facebook, Google Plus and Twitter
  * Ability to preform following actions on multiple social networks (parallel):
    * Login/Logout
    * Update status
    * Update Story (supported fully in Facebook only)
    * Upload image
    * Get user profile + store it on the device
    * Get user's contacts (not all social networks provide all information)
    * Get user's most recent feed (not supported in Google Plus)
