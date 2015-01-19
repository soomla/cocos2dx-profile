*This project is a part of The [SOOMLA](http://www.soom.la) Framework, which is a series of open source initiatives with a joint goal to help mobile game developers do more together. SOOMLA encourages better game design, economy modeling, social engagement, and faster development.*

Haven't you ever wanted a status sharing one liner that looks like this ?!

C++
```cpp
soomla::CCSoomlaProfile::getInstance()->updateStatus(soomla::FACEBOOK, "I love this game !", soomla::CCVirtualItemReward::create( ... ), ...);
```

cocos2dx-profile
---

*SOOMLA's Profile Module for Cocos2d-x*

**November 16th**: v1.0 **cocos2dx-profile** supports Facebook, Google+ and Twitter

* More documentation and information in SOOMLA's [Knowledge Base](http://know.soom.la/docs/platforms/cocos2dx/)  
* For issues you can use the [issues](https://github.com/soomla/cocos2dx-profile/issues) section or SOOMLA's [Answers Website](http://answers.soom.la).  cocos2dx-profile currently supports all Cocos2d-x 3.x versions.

cocos2dx-profile is the Cocos2d-x flavour of SOOMLA's Profile Module. This project uses [android-profile](https://github.com/soomla/android-profile) and [ios-profile](https://github.com/soomla/ios-profile) in order to provide game developers with social network connectivity for their **cocos2d-x** projects.

cocos2dx-profile easily connects to SOOMLA's virtual economy model ([cocos2dx-store](https://github.com/soomla/cocos2dx-store)), thus you can reward players for performing social interactions with virtual rewards (`CCVirtualItemReward`, etc). That said this integration is completely optional.
![SOOMLA's Profile Module](http://know.soom.la/img/tutorial_img/soomla_diagrams/profile.png)

## Example Project

There is an example project that shows how to use cocos2dx-profile:

C++: https://github.com/soomla/cocos2dx-profile-example

The example project is still under development but it already has some important aspects of the framework that you can learn and implement in your application.

## Download

####Pre baked zip:

- [soomla-cocos2dx-core 1.0.1](http://library.soom.la/fetch/cocos2dx-v2-core/1.0.1?cf=github)
- [cocos2dx-profile 1.0.2](http://library.soom.la/fetch/cocos2dx-v2-profile/1.0.2?cf=github)

## Getting Started (With pre-built libraries)

*If you want to develop with sources, refer to the [Working with sources](#working-with-sources) section below*

> If you didn't do that already, clone the Cocos2d-x framework from [here](https://github.com/cocos2d/cocos2d-x) or download it from the [Cocos2d-x website](http://www.cocos2d-x.org/download). Make sure the version you clone is supported by cocos2dx-profile (the tag is the version).

### C++

1. Clone [soomla-cocos2dx-core](https://github.com/soomla/soomla-cocos2dx-core) and **cocos2dx-profile** into the `extensions` directory located at the root of your Cocos2d-x framework.
    ```
    $ git clone git@github.com:soomla/soomla-cocos2dx-core.git extensions/soomla-cocos2dx-core

    $ git clone git@github.com:soomla/cocos2dx-profile.git extensions/cocos2dx-profile
    ```

1. We use a [fork](https://github.com/vedi/jansson) of the jansson library for json parsing, clone our fork into the `external` directory at the root of your framework.
    ```
    $ git clone git@github.com:vedi/jansson.git external/jansson
    ```

1. Implement your `CCProfileEventHandler` in order to be notified about social network related events. Refer to the [Event Handling](#event-handling) section for more information.

1. Initialize `CCServiceManager` and `CCProfileService` with the class you just created, a `customSecret` and other params:

    ```cpp
    CCDictionary *commonParams = CCDictionary::create();
    commonParams->setObject(CCString::create("ExampleCustomSecret"), "customSecret");
    soomla::CCServiceManager::getInstance()->setCommonParams(commonParams);
    ```

    ```cpp
    CCDictionary *profileParams = CCDictionary::create();
    soomla::CCProfileService::initShared(profileParams);
    ```
    - *Custom Secret* - is an encryption secret you provide that will be used to secure your data.
    **Choose the secret wisely. You can't change it after you launch your game!**

    > Initialize `CCProfileService` ONLY ONCE when your application loads.

1. Note that some social providers need special parameters to be passed in order for them to work:
  1. **Facebook** - No special parameters
  1. **Google+** - Please provide **Client ID** from the "API & Auth, credentials" section like so:
    ```cpp
    CCDictionary *googleParams = CCDictionary::create();
    googleParams->setObject(CCString::create("[YOUR CLIENT ID]"), "clientId");

    profileParams->setObject(googleParams, soomla::CCUserProfileUtils::providerEnumToString(soomla::GOOGLE)->getCString());
    ```
  1. **Twitter** - Please provide **Consumer Key** and **Consumer Secret** from the "Keys and Access Tokens" section in [Twitter Apps](https://apps.twitter.com/), like so:
    ```cpp
    CCDictionary *twitterParams = CCDictionary::create();
    twitterParams->setObject(CCString::create("[YOUR CONSUMER KEY]"), "consumerKey");
    twitterParams->setObject(CCString::create("[YOUR CONSUMER SECRET]"), "consumerSecret");

    profileParams->setObject(twitterParams, soomla::CCUserProfileUtils::providerEnumToString(soomla::TWITTER)->getCString());
    ```

1. Make sure to include the `Cocos2dxProfile.h` header whenever you use any of the **cocos2dx-profile** functions:
    ```cpp
    #include "Cocos2dxProfile.h"
    ```

1. Add an instance of your event handler to `CCProfileEventDispatcher` after `CCProfileService` initialization:

    ```cpp
    soomla::CCProfileEventDispatcher::getInstance()->addEventHandler(handler);
    ```

The next steps are different for the different platforms.

#### Instructions for iOS

In your XCode project, perform the following steps:

1. Add `jansson` (**external/jansson/**) to your project (just add it as a source folder).

1. For the following XCode projects:

 * `Cocos2dXCore.xcodeproj` (**extensions/soomla-cocos2dx-core/**).  
 * `Cocos2dXProfile.xcodeproj` (**extensions/cocos2dx-profile/**).

    1. Drag them to your project.
    1. Add their targets to your **Build Phases->Target Dependencies**.
    1. Add the Products (\*.a) of these projects to **Build Phases->Link Binary With Libraries**.

1. Add the following directories to **Build Settings->Header Search Paths** (with `recursive` option):
    > This article assumes you have a `cocos2d` folder under your project folder and which either contains the Cocos2d-x framework, or links to to its root folder

    - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/Soomla`
    - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/build/ios/headers`
    - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/Soomla`
    - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/build/ios/headers`

1. To register services on the native application (`AppController`):

    1. Import the following headers:
    ```objective-c
    #import "ServiceManager.h"
    #import "ProfileService.h"
    #import "SoomlaProfile.h"
    ```

    1. Register the native `ProfileService` by adding:
    ```objective-c
    [[ServiceManager sharedServiceManager] registerService:[ProfileService sharedProfileService]];
    ```
    at the beginning of the method `application: didFinishLaunchingWithOptions:` of `AppController`.

    1. To support browser-based authentication add the following method in your `AppController` (for more information see [ios-profile](https://github.com/soomla/ios-profile#browser-based-authentication)):
    ```objective-c
      - (BOOL)application:(UIApplication *)application
                  openURL:(NSURL *)url
        sourceApplication:(NSString *)sourceApplication
               annotation:(id)annotation
      {
          BOOL urlWasHandled = [[SoomlaProfile getInstance] tryHandleOpenURL:url sourceApplication:sourceApplication annotation:annotation];

          if (urlWasHandled) {
              return urlWasHandled;
          }

          // Profile was unable to handle callback, do some custom handling
          return NO;
      }
      ```

1. Make sure you have these 3 Frameworks linked to your XCode project: **Security, libsqlite3.0.dylib, StoreKit**.

1. Set your project's "Library Search Paths" to `extensions/cocos2dx-profile/build/ios` with `recursive` option.

1. The following steps should be done according to the target social network:

    - **Facebook** - Follow the integration steps in [ios-profile for Facebook](https://github.com/soomla/ios-profile#facebook)

    - **Google+** - Follow the integration steps in [ios-profile for Google+](https://github.com/soomla/ios-profile#google)

    - **Twitter** - Follow the integration steps in [ios-profile for Twitter](https://github.com/soomla/ios-profile#twitter)

> To see a working example, try our [cocos2dx-profile-example](https://github.com/soomla/cocos2dx-profile-example) project

That's it! Now all you have to do is build your XCode project and run your game with cocos2dx-profile.


#### Instructions for Android

1. Import the cocos2dx-profile module into your project's Android.mk by adding the following:
    ```
    LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_profile_static     # add this line along with your other LOCAL_WHOLE_STATIC_LIBRARIES

    $(call import-module, extensions/cocos2dx-profile)          # add this line at the end of the file, along with the other import-module calls
    ```

1. Add the following jars to your android project's classpath:
    - from `extensions/soomla-cocos2dx-core/build/android`
        1. SoomlaAndroidCore.jar
        2. Cocos2dxAndroidCore.jar
        3. square-otto-1.3.2.jar

    - from `extensions/cocos2dx-profile/build/android`
        1. AndroidProfile.jar
        2. Cocos2dxAndroidProfile.jar

1. In your game's main Cocos2dxActivity, call the following in the `onCreateView` method:
     ```java
    public Cocos2dxGLSurfaceView onCreateView() {

    // initialize services
    final ServiceManager serviceManager = ServiceManager.getInstance();
    serviceManager.setActivity(this);
    serviceManager.setGlSurfaceView(glSurfaceView);
    serviceManager.registerService(ProfileService.getInstance());
     ```

1. Override `onPause`, `onResume`:

    ```java
    @Override
    protected void onPause() {
        super.onPause();
        ServiceManager.getInstance().onPause();
    }

    @Override
    protected void onResume() {
        ServiceManager.getInstance().onResume();
        super.onResume();
    }
    ```

1. Update your AndroidManifest.xml to include permissions and the `SoomlaApp`:

    ```xml
    <uses-permission android:name="android.permission.INTERNET"/>
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />

    <!-- optional: required for uploadImage from SD card -->
    <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />

    <application ...
    	       android:name="com.soomla.SoomlaApp">
    	       ...
    </application>
    ```

1. The following steps should be done according to the target social network:

> NOTE: All jars for social providers are located at the following path: `extensions/cocos2dx-profile/build/android`

  - **Facebook** - Follow the integration steps in [android-profile for Facebook](https://github.com/soomla/android-profile#facebook)

  - **Google+** - Follow the integration steps in [android-profile for Google+](https://github.com/soomla/android-profile#google-plus)

  - **Twitter** - Follow the integration steps in [android-profile for Twitter](https://github.com/soomla/android-profile#twitter)

> To see a working example, try our [cocos2dx-profile-example](https://github.com/soomla/cocos2dx-profile-example) project

That's it! Don't forget to run the **build_native.sh** script so cocos2dx-profile sources will be built with cocos2d-x.

## What's next? Social Actions.

The Profile module is young and only a few social actions are provided. We're always working on extending the social capabilities and hope the community will "jump" on the chance to create them and even connect them with SOOMLA's modules (Store and LevelUp).

Here is an example of sharing a story on the user's feed:

After you initialized `CCProfileService` and logged the user in:

```cpp
  soomla::CCSoomlaProfile::getInstance()->updateStory(
        soomla::FACEBOOK,
        "Check out this great story by SOOMLA !",
        "SOOMLA is 2 years young!",
        "SOOMLA Story",
        "soomla_2_years",
        "http://blog.soom.la/2014/08/congratulations-soomla-is-2-years-young.html",
        "http://blog.soom.la/wp-content/uploads/2014/07/Birthday-bot-300x300.png",
        soomla::CCBadgeReward::create("sherriff", "Sheriff"),
        &profileError);
```

And that's it! cocos2dx-profile knows how to contact Facebook and share a story with the information you provided. It will also give the user the `CCBadgeReward` we configured in the function call.

Storage
---

**cocos2dx-profile** is caching user information on the device. You can access it through:

```cpp
soomla::CCUserProfile *userProfile = soomla::CCSoomlaProfile::getInstance()->getStoredUserProfile(
        soomla::FACEBOOK,
        &profileError);
```

The on-device storage is encrypted and kept in a SQLite database. SOOMLA is preparing a cloud-based storage service that will allow this SQLite to be synced to a cloud-based repository that you'll define.

## Event Handling

SOOMLA lets you subscribe to store events, get notified and implement your own application specific behaviour to them.

> Your behaviour is an addition to the default behaviour implemented by SOOMLA. You don't replace SOOMLA's behaviour.

The `CCProfileEventDispatcher` class is where all events go through. To handle various events, create your own event handler, a class that implements `CCProfileEventHandler`, and add it to the `CCProfileEventDispatcher` class:
```cpp
soomla::CCProfileEventDispatcher::getInstance()->addEventHandler(profileEventHandler);
```

Since Cocos2d-x doesn't support exceptions, we use a different method to catch and work with exceptions on the native side. All functions that raise an exception on the native side have an additional `CCError*` parameter to them. In order to know if an exception was raised, send a reference to `CCError*` to the function, and inspect it after running.

For example, if I want to log a user into my game and later see if all went through ok, I will call `login` like this:

```cpp
soomla::CCError *profileError = nullptr;
soomla::CCSoomlaProfile::getInstance()->login(soomla::FACEBOOK, nullptr, &profileError);

if (profileError != NULL) {
     MessageBox(profileError->getInfo(), "Error");
}
```

The `CCError` parameter is entirely optional, you can pass NULL instead if you do not wish to handle errors, but remember, error handling is *your* responsibility. cocos2dx-profile doesn't do any external error handling (i.e. error handling that uses `CCError`) for you.

## Debugging

You can enable debug logging in cocos2dx-profile by setting `SOOMLA_DEBUG` in `CCSoomlaUtils.h` (which is located in `soomla-cocos2dx-core` submodule) to `true`. Debug logging can also be enabled at build time by adding `-DSOOMLA_DEBUG=1` to `APP_CPPFLAGS` in your `Application.mk` on Android, or by setting `SOOMLA_DEBUG=1` in your Build Settings' `Preprocessor Macros` on iOS.

If you want to see debug messages from _android-profile_, set the `logDebug` variable in `com.soomla.store.StoreConfig` to `true`.

To see debug messages on iOS, make sure you have also `DEBUG=1` in your Build Settings' `Preprocessor Macros` (for Debug only).

## Facebook Caveats

1. See [iOS Facebook Caveats](https://github.com/soomla/ios-profile#facebook-caveats)
1. See [Android Facebook Caveats](https://github.com/soomla/android-profile#facebook-caveats)

## Google+ Caveats

1. See [iOS Google+ Caveats](https://github.com/soomla/ios-profile#google-plus-caveats)

## Twitter Caveats

1. See [iOS Twitter Caveats](https://github.com/soomla/ios-profile#twitter-caveats)
1. See [Android Twitter Caveats](https://github.com/soomla/android-profile#twitter-caveats)


## Working with sources

We try to do all our best to make your contributions as easy as possible. We prepared a "sourced" environment for you if you wish to contribute to SOOMLA projects. In order to get it you should:

1. Fetch submodules of repositories, you can do it recursively by cloning them:
    ```
    $ git clone --recursive git@github.com:soomla/soomla-cocos2dx-core.git extensions/soomla-cocos2dx-core
    $ git clone --recursive git@github.com:soomla/cocos2dx-profile.git extensions/cocos2dx-profile
    ```
or, if you have repositories already cloned, fetch the submodules with this command:
    ```
    $ git submodule update --init --recursive
    ```
> You should run this command in every repository.

1. For iOS: Use a sourced versions of linked projects (`extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.xcodeproj`, `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.xcodeproj`)

1. For Android: You can use our "sourced" modules for Android Studio (or IntelliJ IDEA) (`extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.iml`, `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.iml`), just include them to your project.

Contribution
---
SOOMLA appreciates code contributions! You are more than welcome to extend the capabilities of SOOMLA.

Fork -> Clone -> Implement -> Add documentation -> Test -> Pull-Request.

IMPORTANT: If you would like to contribute, please follow our [Documentation Guidelines](https://github.com/soomla/cocos2dx-store/blob/master/documentation.md
). Clear, consistent comments will make our code easy to understand.

## SOOMLA, Elsewhere ...

+ [Framework Website](http://www.soom.la/)
+ [Knowledge Base](http://know.soom.la/)


<a href="https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376"><img src="http://know.soom.la/img/tutorial_img/social/Facebook.png"></a><a href="https://twitter.com/Soomla"><img src="http://know.soom.la/img/tutorial_img/social/Twitter.png"></a><a href="https://plus.google.com/+SoomLa/posts"><img src="http://know.soom.la/img/tutorial_img/social/GoogleP.png"></a><a href ="https://www.youtube.com/channel/UCR1-D9GdSRRLD0fiEDkpeyg"><img src="http://know.soom.la/img/tutorial_img/social/Youtube.png"></a>

## License

Apache License. Copyright (c) 2012-2014 SOOMLA. http://www.soom.la
+ http://opensource.org/licenses/Apache-2.0
