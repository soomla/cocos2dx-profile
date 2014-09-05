*This project is a part of [The SOOMLA Project](http://project.soom.la) which is a series of open source initiatives with a joint goal to help mobile game developers get better stores and more in-app purchases.*

Haven't you ever wanted a status sharing one liner that looks like this ?!

C++
```cpp
soomla::CCProfileController::getInstance()->updateStatus(soomla::FACEBOOK, "I love this game !", soomla::CCVirtualItemReward::create( ... ), ...);
```

cocos2dx-profile
---

*SOOMLA's Profile Module for Cocos2d-x*

* More documentation and information in SOOMLA's [Knowledge Base](http://know.soom.la/docs/platforms/cocos2dx/)  
* For issues you can use the [issues](https://github.com/soomla/cocos2dx-profile/issues) section or SOOMLA's [Answers Website](http://answers.soom.la).  cocos2dx-profile currently supports all Cocos2d-x 3.x versions. cocos2dx-profile currently supports Facebook only.

cocos2dx-profile is the Cocos2d-x flavour of SOOMLA's Profile Module. This project uses [android-profile](https://github.com/soomla/android-profile) and [ios-profile](https://github.com/soomla/ios-profile) in order to provide game developers with social network connectivity for their **cocos2d-x** projects.

cocos2dx-profile easily connects to SOOMLA's virtual economy model ([cocos2dx-store](https://github.com/soomla/cocos2dx-store)), thus you can reward players for performing social interactions with virtual rewards (`CCVirtualItemReward`, etc). That said this integration is completely optional.
![SOOMLA's Profile Module](http://know.soom.la/img/tutorial_img/soomla_diagrams/Profile.png)

## Example Project

There is an example project that show how to use cocos2dx-profile:

C++: https://github.com/soomla/cocos2dx-profile-example

The example project is still under development but it already has some important aspects of the framework that you can learn and implement in your application.

## Getting Started (With pre-built libraries)

*If you want to develop with sources, refer to the [Working with sources](https://github.com/soomla/cocos2dx-profile#working-with-sources) section below*

> If you didn't do that already, clone the Cocos2d-x framework from [here](https://github.com/cocos2d/cocos2d-x) or download it from the [Cocos2d-x website](http://www.cocos2d-x.org/download). Make sure the version you clone is supported by cocos2dx-profile (the tag is the version).

##### C++

1. Clone [soomla-cocos2dx-core](https://github.com/soomla/soomla-cocos2dx-core) and **cocos2dx-profile** into the `extensions` directory located at the root of your Cocos2d-x framework.
    ```
    $ git clone git@github.com:soomla/soomla-cocos2dx-core.git extensions/soomla-cocos2dx-core

    $ git clone git@github.com:soomla/cocos2dx-profile.git extensions/cocos2dx-profile
    ```

1. We use a [fork](https://github.com/vedi/jansson) of the jansson library for json parsing, clone our fork into the `external` directory at the root of your framework.
    ```
    $ git clone git@github.com:vedi/jansson.git external/jansson
    ```

1. Implement your `CCProfileEventHandler` in order to be notified about social network related events. Refer to the [Event Handling](https://github.com/soomla/cocos2dx-profile#event-handling) section for more information.

1. Initialize `CCServiceManager` and `CCProfileService` with the class you just created, a `customSecret` and other params:

    ```cpp
    __Dictionary *commonParams = __Dictionary::create();
    commonParams->setObject(__String::create("ExampleCustomSecret"), "customSecret");
    soomla::CCServiceManager::getInstance()->setCommonParams(commonParams);
    ```

    ```cpp
    __Dictionary *profileParams = __Dictionary::create();
    soomla::CCProfileService::initShared(profileParams);
    ```
    - *Custom Secret* - is an encryption secret you provide that will be used to secure your data.
    **Choose the secret wisely. You can't change it after you launch your game!**

    > Initialize `CCProfileService` ONLY ONCE when your application loads.

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
 - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/build/ios/headers/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/Profile/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/build/ios/headers/**`

1. Register the native `StoreService` by adding:

    ```cpp
    [[ServiceManager sharedServiceManager] registerService:[ProfileService sharedProfileService]];
    ```
at the begining of the method `application: didFinishLaunchingWithOptions:` of `AppController`.

1. Make sure you have these 3 Frameworks linked to your XCode project: **Security, libsqlite3.0.dylib, StoreKit**.

1. The following steps should be done according to the target social network:

  ##### Facebook

  1. Add the Facebook SDK for iOS to the project's Frameworks and make sure your project links to the project

    1. Refer to [Getting Started with the Facebook iOS SDK](https://developers.facebook.com/docs/ios/getting-started/) for more information

> To see a working Facebook example, try our [cocos2dx-profile-example](https://github.com/soomla/cocos2dx-profile-example) project

That's it! Now all you have to do is build your XCode project and run your game with cocos2dx-profile.

#### Instructions for Android

1. Import the cocos2dx-profile module into your project's Android.mk by adding the following:
    ```
    LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_profile_static        # add this line along with your other LOCAL_WHOLE_STATIC_LIBRARIES

    $(call import-module, extensions/cocos2dx-profile) # add this line at the end of the file, along with the other import-module calls
    ```

1. Add the following jars to your android project's classpath:
    - from `extensions/soomla-cocos2dx-core/build/android`
        1. SoomlaAndroidCore.jar
        1. Cocos2dxAndroidCore.jar

    - from `extensions/cocos2dx-profile/build/android`
        1. SoomlaAndroidStore.jar
        1. Cocos2dxAndroidStore.jar

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

  ##### Facebook

  1. Import the Facebook SDK for Android into your project

    1. For more information regarding this refer to [Facebook SDK for Android](https://developers.facebook.com/docs/android)

    1. SOOMLA uses [Android Studio](https://developer.android.com/sdk/installing/studio.html), in this case you can extract the Facebook SDK into your `proj.android` folder and then it's simply a case of importing the `.iml` file in the Facebook SDK folder into your project

  1. Update your AndroidManifest.xml:

      ```xml
      ...

      <application ...
          <activity android:name="com.soomla.profile.social.facebook.SoomlaFacebook$SoomlaFBActivity" android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen">
        </activity>
      </application>
      ```

> To see a working Facebook example, try our [cocos2dx-profile-example](https://github.com/soomla/cocos2dx-profile-example) project

That's it! Don't forget to run the **build_native.sh** script so cocos2dx-profile sources will be built with cocos2d-x.

## What's next? Social Actions.

The Profile module is young and only a few social actions are provided. We're always working on extending the social capabilities and hope the community will "jump" on the chance to create them and even connect them with SOOMLA's modules (Store and LevelUp).

Here is an example of sharing a story on the user's feed:

After you initialized `CCProfileService` and logged the user in:

```cpp
  soomla::CCProfileController::getInstance()->updateStory(
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
soomla::CCUserProfile *userProfile = soomla::CCProfileController::getInstance()->getStoredUserProfile(
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

## Error Handling

Since Cocos2d-x doesn't support exceptions, we use a different method to catch and work with exceptions on the native side. All functions that raise an exception on the native side have an additional `CCError*` parameter to them. In order to know if an exception was raised, send a reference to `CCError*` to the function, and inspect it after running.

For example, if I want to log a user into my game and later see if all went through ok, I will call `login` like this:

```cpp
soomla::CCError *profileError = nullptr;
soomla::CCProfileController::getInstance()->login(soomla::FACEBOOK, nullptr, &profileError);

if (profileError != NULL) {
     MessageBox(profileError->getInfo(), "Error");
}
```

You can choose to handle each exception on its own, handle all three at once, or not handle the exceptions at all. The `CCError` parameter is entirely optional, you can pass NULL instead if you do not wish to handle errors, but remember, error handling is *your* responsibility. cocos2dx-profile doesn't do any external error handling (i.e. error handling that uses `CCError`) for you.

## Debugging

You can enable debug logging in cocos2dx-profile by setting `SOOMLA_DEBUG` in `CCSoomlaUtils.h` (which is located in `soomla-cocos2dx-core` submodule) to `true`. Debug logging can also be enabled at build time by adding `-DSOOMLA_DEBUG=1` to `APP_CPPFLAGS` in your `Application.mk` on Android, or by setting `SOOMLA_DEBUG=1` in your Build Settings' `Preprocessor Macros` on iOS.

If you want to see debug messages from _android-profile_, set the `logDebug` variable in `com.soomla.store.StoreConfig` to `true`.

To see debug messages on iOS, make sure you have also `DEBUG=1` in your Build Settings' `Preprocessor Macros` (for Debug only).


## Working with sources

We try to do all our best to make your contributions as easy as possible. We prepared a "sourced" environment for you if you wish to contribute to SOOMLA projects. In order to get it you should:

1. Fetch submodules of repositories, you can do it recursively cloning them:
    ```
    $ git clone --recursive git@github.com:soomla/soomla-cocos2dx-core.git extensions/soomla-cocos2dx-core
    $ git clone --recursive git@github.com:soomla/cocos2dx-store.git extensions/cocos2dx-profile
    ```
or, if you have repositories already cloned, fetch the submodules with this command:
    ```
    $ git submodule update --init --recursive
    ```
> You should run this command in every repository.

1. For iOS: Use a sourced versions of linked projects (`extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.xcodeproj`, `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.xcodeproj`)

1. For Android: You can use our "sourced" modules for Android Studio (or IntelliJ IDEA) (`extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.iml`, `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.iml`), just including them to your project.

## Contribution

We want you!

Fork -> Clone -> Implement -> Insert Comments -> Test -> Pull-Request.

We have great RESPECT for contributors.

## Code Documentation

cocos2dx-profile follows strict code documentation conventions. If you would like to contribute please read our [Documentation Guidelines](https://github.com/soomla/cocos2dx-profile/blob/master/documentation.md) and follow them. Clear, consistent  comments will make our code easy to understand.


## SOOMLA, Elsewhere ...

+ [Framework Website](http://www.soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376).
+ [On AngelList](https://angel.co/the-soomla-project)


## License

Apache License. Copyright (c) 2012-2014 SOOMLA. http://www.soom.la
+ http://opensource.org/licenses/Apache-2.0
