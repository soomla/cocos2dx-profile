/**
 * Created by vedi on 15/04/15.
 */
(function () {

  /**
   * UserProfile
   */
  var UserProfile = Soomla.Models.UserProfile = Soomla.declareClass("UserProfile", {
    provider: null,
    profileId: null,
    email: null,
    firstName: null,
    lastName: null,
    avatarLink: null,
    location: null,
    gender: null,
    language: null,
    birthday: null
  }, Soomla.Domain);

  var Provider = Soomla.Models.Provider = {
    FACEBOOK: {id: 0, key: 'facebook'},
    GOOGLE: {id: 2, key: 'google'},
    TWITTER: {id: 5, key: 'twitter'}
  };

  Provider.findById = function (id) {
    return _.find(Soomla.Models.Provider, function (provider) {
      return !_.isFunction(provider) && provider.id == id;
    })
  };
  Provider.findByKey = function (key) {
    return _.find(Soomla.Models.Provider, function (provider) {
      return !_.isFunction(provider) && provider.key == key;
    });
  };

  Soomla.Models.SocialActionType = {
    UPDATE_STATUS: 0,
    UPDATE_STORY: 1,
    UPLOAD_IMAGE: 2,
    GET_CONTACTS: 3,
    GET_FEED: 4
  };

  /**
   * ProfileConsts
   */
  var ProfileConsts = Soomla.Models.ProfileConsts = {
    EVENT_PROFILE_INITIALIZED: "com.soomla.profile.events.ProfileInitializedEvent",
    EVENT_USER_RATING: "com.soomla.profile.events.UserRatingEvent",
    EVENT_LOGIN_CANCELLED: "com.soomla.profile.events.auth.LoginCancelledEvent",
    EVENT_LOGIN_FAILED: "com.soomla.profile.events.auth.LoginFailedEvent",
    EVENT_LOGIN_FINISHED: "com.soomla.profile.events.auth.LoginFinishedEvent",
    EVENT_LOGIN_STARTED: "com.soomla.profile.events.auth.LoginStartedEvent",
    EVENT_LOGOUT_FAILED: "com.soomla.profile.events.auth.LogoutFailedEvent",
    EVENT_LOGOUT_FINISHED: "com.soomla.profile.events.auth.LogoutFinishedEvent",
    EVENT_LOGOUT_STARTED: "com.soomla.profile.events.auth.LogoutStartedEvent",
    EVENT_GET_CONTACTS_FAILED: "com.soomla.profile.events.social.GetContactsFailedEvent",
    EVENT_GET_CONTACTS_FINISHED: "com.soomla.profile.events.social.GetContactsFinishedEvent",
    EVENT_GET_CONTACTS_STARTED: "com.soomla.profile.events.social.GetContactsStartedEvent",
    EVENT_GET_FEED_FAILED: "com.soomla.profile.events.social.GetFeedFailedEvent",
    EVENT_GET_FEED_FINISHED: "com.soomla.profile.events.social.GetFeedFinishedEvent",
    EVENT_GET_FEED_STARTED: "com.soomla.profile.events.social.GetFeedStartedEvent",
    EVENT_SOCIAL_ACTION_FAILED: "com.soomla.profile.events.social.SocialActionFailedEvent",
    EVENT_SOCIAL_ACTION_FINISHED: "com.soomla.profile.events.social.SocialActionFinishedEvent",
    EVENT_SOCIAL_ACTION_STARTED: "com.soomla.profile.events.social.SocialActionStartedEvent",
    EVENT_USER_PROFILE_UPDATED: "com.soomla.profile.events.UserProfileUpdatedEvent"
  };

  /**
   * HighwayHandler
   * Here for documentation reasons only, shows signatures for event handlers
   */
  var ProfileEventHandler = Soomla.ProfileEventHandler = function () {
    return Soomla.declareClass("ProfileEventHandler", {
      /**
       * Called after the service has been initialized
       */
      onProfileInitialized: function () {
      },
      /**
       Called when the market page for the app is opened
       */
      onUserRatingEvent: function () {
      },

      /**
       Called when the login process to a provider has failed
       @param provider The provider on which the login has failed
       @param errorDescription a Description of the reason for failure
       @param payload an identification String sent from the caller of the action
       */
      onLoginFailed: function (provider, errorDescription, payload) {
      },

      /**
       Called when the login process finishes successfully
       @param userProfile The user's profile from the logged in provider
       @param payload an identification String sent from the caller of the action
       */
      onLoginFinished: function (userProfile, payload) {
      },

      /**
       Called when the login process to a provider has started
       @param provider The provider on where the login has started
       @param payload an identification String sent from the caller of the action
       */
      onLoginStarted: function (provider, payload) {
      },

      /**
       Called when the logout process from a provider has failed
       @param provider The provider on which the logout has failed
       @param errorDescription a Description of the reason for failure
       */
      onLogoutFailed: function (provider, errorDescription) {
      },

      /**
       Called when the logout process from a provider has finished
       @param provider The provider on which the logout has finished
       */
      onLogoutFinished: function (provider) {
      },

      /**
       Called when the logout process from a provider has started
       @param provider The provider on which the login has started
       */
      onLogoutStarted: function (provider) {
      },

      /**
       Called when the get contacts process from a provider has failed
       @param provider The provider on which the get contacts process has
       failed
       @param errorDescription a Description of the reason for failure
       @param fromFirst Should we reset pagination or request the next page
       @param payload an identification String sent from the caller of the action
       */
      onGetContactsFailed: function (provider, errorDescription, fromFirst, payload) {
      },

      /**
       Called when the get contacts process from a provider has finished
       @param provider The provider on which the get contacts process finished
       @param contactsDict an Array of contacts represented by CCUserProfile
       @param payload an identification String sent from the caller of the action
       @param hasMore if it has more in pagination
       */
      onGetContactsFinished: function (provider, contactsDict, payload, hasMore) {
      },

      /**
       Called when the get contacts process from a provider has started
       @param provider The provider on which the get contacts process started
       @param fromFirst Should we reset pagination or request the next page
       @param payload an identification String sent from the caller of the action
       */
      onGetContactsStarted: function (provider, fromFirst, payload) {
      },

      /**
       Called when the get feed process from a provider has failed
       @param provider The provider on which the get feed process has
       failed
       @param errorDescription a Description of the reason for failure
       @param fromFirst Should we reset pagination or request the next page
       @param payload an identification String sent from the caller of the action
       */
      onGetFeedFailed: function (provider, errorDescription, fromFirst, payload) {
      },

      /**
       Called when the get feed process from a provider has finished
       @param provider The provider on which the get feed process finished
       @param feedList an Array of feed entries represented by __String
       @param payload an identification String sent from the caller of the action
       @param hasMore if it has more in pagination
       */
      onGetFeedFinished: function (provider, feedList, payload, hasMore) {
      },

      /**
       Called when the get feed process from a provider has started
       @param provider The provider on which the get feed process started
       @param fromFirst Should we reset pagination or request the next page
       @param payload an identification String sent from the caller of the action
       */
      onGetFeedStarted: function (provider, fromFirst, payload) {
      },

      /**
       Called when a generic social action on a provider has failed
       @param provider The provider on which the social action has failed
       @param socialActionType The social action which failed
       @param errorDescription a Description of the reason for failure
       @param payload an identification String sent from the caller of the action
       */
      onSocialActionFailedEvent: function (provider, socialActionType, errorDescription, payload) {
      },

      /**
       Called when a generic social action on a provider has finished
       @param provider The provider on which the social action has finished
       @param socialActionType The social action which finished
       @param payload an identification String sent from the caller of the action
       */
      onSocialActionFinishedEvent: function (provider, socialActionType, payload) {
      },

      /**
       Called when a generic social action on a provider has started
       @param provider The provider on which the social action has started
       @param socialActionType The social action which started
       @param payload an identification String sent from the caller of the action
       */
      onSocialActionStartedEvent: function (provider, socialActionType, payload) {
      },

      /**
       Called the login process to a provider has been cancelled
       @param provider The provider on which the login has failed
       @param payload an identification String sent from the caller of the action
       */
      onLoginCancelledEvent: function (provider, payload) {
      },

      /**
       Called when a user profile from a provider has been retrieved
       @param userProfile The user's profile which was updated
       */
      onUserProfileUpdatedEvent: function (userProfile) {
      }
    });
  }();

  var ProfileEventDispatcher = Soomla.ProfileEventDispatcher = function () {

    /**
     @class CCProfileEventDispatcher
     @brief Fires event when received from the native implementation.

     Signs up to native Profile events through CCSoomlaEventDispatcher.
     When the events arrive this class fires the repective event through
     the Cocos2dx Event Dispatcher.
     */
    var ProfileEventDispatcher = Soomla.declareClass('ProfileEventDispatcher', {
      init: function () {
        var eventDispatcher = Soomla.soomlaEventDispatcher;

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_PROFILE_INITIALIZED, _.bind(function (parameters) {
          Soomla.fireSoomlaEvent(parameters.method);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_USER_RATING, _.bind(function (parameters) {
          Soomla.fireSoomlaEvent(parameters.method);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_LOGIN_CANCELLED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_LOGIN_FAILED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var errorDescription = parameters.errorDescription;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, errorDescription, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_LOGIN_FINISHED, _.bind(function (parameters) {
          var userProfile = parameters.userProfile;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [userProfile, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_LOGIN_STARTED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_LOGOUT_FAILED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var errorDescription = parameters.errorDescription;
          Soomla.fireSoomlaEvent(parameters.method, [provider, errorDescription]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_LOGOUT_FINISHED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          Soomla.fireSoomlaEvent(parameters.method, [provider]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_LOGOUT_STARTED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          Soomla.fireSoomlaEvent(parameters.method, [provider]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_GET_CONTACTS_FAILED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var errorDescription = parameters.errorDescription;
          var fromStart = parameters.fromStart;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, errorDescription, fromStart, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_GET_CONTACTS_FINISHED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var contacts = parameters.contacts;
          var payload = parameters.payload;
          var hasMore = parameters.hasMore;
          Soomla.fireSoomlaEvent(parameters.method, [provider, contacts, payload, hasMore]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_GET_CONTACTS_STARTED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var fromStart = parameters.fromStart;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, fromStart, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_GET_FEED_FAILED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var errorDescription = parameters.errorDescription;
          var fromStart = parameters.fromStart;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, errorDescription, fromStart, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_GET_FEED_FINISHED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var feed = parameters.feed;
          var payload = parameters.payload;
          var hasMore = parameters.hasMore;
          Soomla.fireSoomlaEvent(parameters.method, [provider, feed, payload, hasMore]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_GET_FEED_STARTED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var fromStart = parameters.fromStart;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, fromStart, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_SOCIAL_ACTION_FAILED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var socialActionType = parameters.socialActionType;
          var errorDescription = parameters.errorDescription;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, socialActionType, errorDescription, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var socialActionType = parameters.socialActionType;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, socialActionType, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_SOCIAL_ACTION_STARTED, _.bind(function (parameters) {
          var providerId = parameters.provider;
          var provider = Provider.findById(providerId);
          var socialActionType = parameters.socialActionType;
          var payload = parameters.payload;
          Soomla.fireSoomlaEvent(parameters.method, [provider, socialActionType, payload]);
        }, this));

        eventDispatcher.registerEventHandler(ProfileConsts.EVENT_USER_PROFILE_UPDATED, _.bind(function (parameters) {
          var userProfile = parameters.userProfile;
          Soomla.fireSoomlaEvent(parameters.method, [userProfile]);
        }, this));

        return true;
      }
    });

    ProfileEventDispatcher.initShared = function () {
      var ret = ProfileEventDispatcher.create();
      if (ret.init()) {
        Soomla.profileEventDispatcher = ret;
      } else {
        Soomla.profileEventDispatcher = null;
      }
    };

    return ProfileEventDispatcher;
  }();


  /**
   * SoomlaProfile
   */
  var SoomlaProfile = Soomla.SoomlaProfile = Soomla.declareClass("SoomlaProfile", {
    inited: false,
    init: function (customParams) {
      ProfileEventDispatcher.initShared();

      Soomla.callNative({
        method: "CCProfileBridge::init",
        params: customParams
      });

      this.inited = true;
      return true;
    },
    login: function (provider, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::login",
        provider: provider.key
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    logout: function (provider) {
      Soomla.callNative({
        method: "CCSoomlaProfile::logout",
        provider: provider.key
      });
    },
    getStoredUserProfile: function (provider) {
      var retParams = Soomla.callNative({
        method: "CCSoomlaProfile::getStoredUserProfile",
        provider: provider.key
      });
      return retParams.return;
    },
    updateStatus: function (provider, status, payload, reward) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStatus",
        provider: provider.key,
        status: status
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    updateStatusDialog: function (provider, link, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStatusDialog",
        provider: provider.key,
        link: link
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    updateStory: function (provider, message, name, caption, description, link, picture, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStory",
        provider: provider.key,
        message: message,
        name: name,
        caption: caption,
        description: description,
        link: link,
        picture: picture
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    updateStoryDialog: function (provider, name, caption, description, link, picture, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStoryDialog",
        provider: provider.key,
        name: name,
        caption: caption,
        description: description,
        link: link,
        picture: picture
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    uploadImage: function (provider, message, filePath, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::uploadImage",
        provider: provider.key,
        message: message,
        filePath: filePath
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    getContacts: function (provider, reward, fromFirst, payload) {
      fromFirst = (fromFirst !== undefined ? fromFirst : false);
      var toPassData = {
        method: "CCSoomlaProfile::getContacts",
        provider: provider.key,
        reward: reward
        fromFirst: fromFirst
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    getFeed: function (provider, reward, fromFirst, payload) {
      fromFirst = (fromFirst !== undefined ? fromFirst : false);
      var toPassData = {
        method: "CCSoomlaProfile::getFeed",
        provider: provider.key,
        fromFirst: fromFirst
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    isLoggedIn: function (provider) {
      var retParams = Soomla.callNative({
        method: "CCSoomlaProfile::isLoggedIn",
        provider: provider.key
      });
      return retParams.return;
    },
    like: function (provider, pageId, reward) {
      var toPassData = {
        method: "CCSoomlaProfile::like",
        provider: provider.key,
        pageId: pageId
      };

      if (reward) {
        toPassData.reward = reward;
      }

      Soomla.callNative(toPassData, true);
    },
    openAppRatingPage: function () {
      Soomla.callNative({
        method: "CCSoomlaProfile::openAppRatingPage"
      });
    }
  });

  SoomlaProfile.createShared = function (customParams) {
    var ret = new SoomlaProfile();
    if (ret.init(customParams)) {
      Soomla.soomlaProfile = ret;
    } else {
      Soomla.soomlaProfile = null;
    }
  };

})();