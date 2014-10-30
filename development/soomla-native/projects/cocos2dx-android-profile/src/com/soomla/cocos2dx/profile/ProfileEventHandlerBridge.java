/*
 * Copyright (C) 2012-2014 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.soomla.cocos2dx.profile;

import android.opengl.GLSurfaceView;
import com.soomla.BusProvider;
import com.soomla.SoomlaUtils;
import com.soomla.cocos2dx.common.DomainHelper;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.profile.events.ProfileInitializedEvent;
import com.soomla.profile.events.UserProfileUpdatedEvent;
import com.soomla.profile.events.UserRatingEvent;
import com.soomla.profile.events.auth.*;
import com.soomla.profile.events.social.*;
import com.squareup.otto.Subscribe;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * This bridge is used to populate events from the native profile to cocos2dx (through JNI).
 */
public class ProfileEventHandlerBridge {

    private GLSurfaceView mGLThread;

    /**
     * Constructor
     *
     * The main constructor of the event handling bridge.
     * Registers all event handling for native side.
     */
    public ProfileEventHandlerBridge() {
        BusProvider.getInstance().register(this);
    }

    /**
     * Called when the profile module has finished initializing
     *
     * @param profileInitializedEvent The event information
     */
    @Subscribe
    public void onProfileInitializedEvent(final ProfileInitializedEvent profileInitializedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_UP_PROFILE_INITIALIZED);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when the app's market rate page is opened
     *
     * @param userRatingEvent The event information
     */
    @Subscribe
    public void onProfileInitializedEvent(final UserRatingEvent userRatingEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_UP_USER_RATING);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a login process to a provider has failed
     *
     * @param loginFailedEvent The event information
     */
    @Subscribe
    public void onLoginFailedEvent(final LoginFailedEvent loginFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_FAILED);
                    parameters.put("provider", loginFailedEvent.Provider.getValue());
                    parameters.put("errorDescription", loginFailedEvent.ErrorDescription);
                    parameters.put("payload", loginFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a login process to a provider has finished
     *
     * @param loginFinishedEvent The event information
     */
    @Subscribe
    public void onLoginFinishedEvent(final LoginFinishedEvent loginFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_FINISHED);
                    parameters.put("userProfile", loginFinishedEvent.UserProfile.toJSONObject());
                    parameters.put("payload", loginFinishedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a login process to a provider has started
     *
     * @param loginStartedEvent The event information
     */
    @Subscribe
    public void onLoginStartedEvent(final LoginStartedEvent loginStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_STARTED);
                    parameters.put("provider", loginStartedEvent.Provider.getValue());
                    parameters.put("payload", loginStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a logout process from a provider has failed
     *
     * @param logoutFailedEvent The event information
     */
    @Subscribe
    public void onLogoutFailedEvent(final LogoutFailedEvent logoutFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGOUT_FAILED);
                    parameters.put("provider", logoutFailedEvent.Provider.getValue());
                    parameters.put("errorDescription", logoutFailedEvent.ErrorDescription);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a logout process from a provider has finished
     *
     * @param logoutFinishedEvent The event information
     */
    @Subscribe
    public void onLogoutFinishedEvent(final LogoutFinishedEvent logoutFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGOUT_FINISHED);
                    parameters.put("provider", logoutFinishedEvent.Provider.getValue());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a logout process from a provider has started
     *
     * @param logoutStartedEvent The event information
     */
    @Subscribe
    public void onLogoutStartedEvent(final LogoutStartedEvent logoutStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGOUT_STARTED);
                    parameters.put("provider", logoutStartedEvent.Provider.getValue());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a get contacts process from a provider has failed
     *
     * @param getContactsFailedEvent The event information
     */
    @Subscribe
    public void onGetContactsFailedEvent(final GetContactsFailedEvent getContactsFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_CONTACTS_FAILED);
                    parameters.put("provider", getContactsFailedEvent.Provider.getValue());
                    parameters.put("socialActionType", getContactsFailedEvent.SocialActionType.getValue());
                    parameters.put("errorDescription", getContactsFailedEvent.ErrorDescription);
                    parameters.put("payload", getContactsFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a get contacts process from a provider has finished
     *
     * @param getContactsFinishedEvent The event information
     */
    @Subscribe
    public void onGetContactsFinishedEvent(final GetContactsFinishedEvent getContactsFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_CONTACTS_FINISHED);
                    parameters.put("provider", getContactsFinishedEvent.Provider.getValue());
                    parameters.put("socialActionType", getContactsFinishedEvent.SocialActionType.getValue());
                    parameters.put("contacts", DomainHelper.getInstance().getJsonObjectListFromDomains(getContactsFinishedEvent.Contacts));
                    parameters.put("payload", getContactsFinishedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a get contacts process from a provider has started
     *
     * @param getContactsStartedEvent The event information
     */
    @Subscribe
    public void onGetContactsStartedEvent(final GetContactsStartedEvent getContactsStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_CONTACTS_STARTED);
                    parameters.put("provider", getContactsStartedEvent.Provider.getValue());
                    parameters.put("socialActionType", getContactsStartedEvent.SocialActionType.getValue());
                    parameters.put("payload", getContactsStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a get feed process from a provider has failed
     *
     * @param getFeedFailedEvent The event information
     */
    @Subscribe
    public void onGetFeedFailedEvent(final GetFeedFailedEvent getFeedFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_FEED_FAILED);
                    parameters.put("provider", getFeedFailedEvent.Provider.getValue());
                    parameters.put("socialActionType", getFeedFailedEvent.SocialActionType.getValue());
                    parameters.put("errorDescription", getFeedFailedEvent.ErrorDescription);
                    parameters.put("payload", getFeedFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a get feed process from a provider has finished
     *
     * @param getFeedFinishedEvent The event information
     */
    @Subscribe
    public void onGetFeedFinishedEvent(final GetFeedFinishedEvent getFeedFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_FEED_FINISHED);
                    parameters.put("provider", getFeedFinishedEvent.Provider.getValue());
                    parameters.put("socialActionType", getFeedFinishedEvent.SocialActionType.getValue());
                    parameters.put("feed", new JSONArray(getFeedFinishedEvent.Posts));
                    parameters.put("payload", getFeedFinishedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a get feed process from a provider has started
     *
     * @param getFeedStartedEvent The event information
     */
    @Subscribe
    public void onGetFeedStartedEvent(final GetFeedStartedEvent getFeedStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_FEED_STARTED);
                    parameters.put("provider", getFeedStartedEvent.Provider.getValue());
                    parameters.put("socialActionType", getFeedStartedEvent.SocialActionType.getValue());
                    parameters.put("payload", getFeedStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a generic social action on a provider has failed
     *
     * @param socialActionFailedEvent The event information
     */
    @Subscribe
    public void onSocialActionFailedEvent(final SocialActionFailedEvent socialActionFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SOCIAL_ACTION_FAILED);
                    parameters.put("provider", socialActionFailedEvent.Provider.getValue());
                    parameters.put("socialActionType", socialActionFailedEvent.SocialActionType.getValue());
                    parameters.put("errorDescription", socialActionFailedEvent.ErrorDescription);
                    parameters.put("payload", socialActionFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a generic social action on a provider has finished
     *
     * @param socialActionFinishedEvent The event information
     */
    @Subscribe
    public void onSocialActionFinishedEvent(final SocialActionFinishedEvent socialActionFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED);
                    parameters.put("provider", socialActionFinishedEvent.Provider.getValue());
                    parameters.put("socialActionType", socialActionFinishedEvent.SocialActionType.getValue());
                    parameters.put("payload", socialActionFinishedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a generic social action on a provider has started
     *
     * @param socialActionStartedEvent The event information
     */
    @Subscribe
    public void onSocialActionStartedEvent(final SocialActionStartedEvent socialActionStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SOCIAL_ACTION_STARTED);
                    parameters.put("provider", socialActionStartedEvent.Provider.getValue());
                    parameters.put("socialActionType", socialActionStartedEvent.SocialActionType.getValue());
                    parameters.put("payload", socialActionStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a login process has been cancelled
     *
     * @param loginCancelledEvent The event information
     */
    @SuppressWarnings("UnusedParameters")
    @Subscribe
    public void onLoginCancelledEvent(final LoginCancelledEvent loginCancelledEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_LOGIN_CANCELLED);
                    parameters.put("provider", loginCancelledEvent.Provider.getValue());
                    parameters.put("payload", loginCancelledEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when a user's profile from a social provider has been updated
     *
     * @param userProfileUpdatedEvent The event information
     */
    @Subscribe
    public void onUserProfileUpdatedEvent(final UserProfileUpdatedEvent userProfileUpdatedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_USER_PROFILE_UPDATED);
                    parameters.put("userProfile", userProfileUpdatedEvent.UserProfile.toJSONObject());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Sets the main GL surface of the application
     *
     * @param glSurfaceView The GL surface of the main activity
     */
    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        this.mGLThread = glSurfaceView;
    }
}
