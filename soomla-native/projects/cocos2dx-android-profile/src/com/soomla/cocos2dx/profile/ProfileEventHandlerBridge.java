package com.soomla.cocos2dx.profile;

import android.opengl.GLSurfaceView;
import com.soomla.BusProvider;
import com.soomla.SoomlaUtils;
import com.soomla.cocos2dx.common.DomainHelper;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.profile.events.UserProfileUpdatedEvent;
import com.soomla.profile.events.auth.*;
import com.soomla.profile.events.social.*;
import com.squareup.otto.Subscribe;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * This bridge is used to populate events from the store to cocos2dx (through JNI).
 */
public class ProfileEventHandlerBridge {

    private GLSurfaceView mGLThread;

    public ProfileEventHandlerBridge() {
        BusProvider.getInstance().register(this);
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLoginFinishedEvent(final LoginFinishedEvent loginFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_FINISHED);
                    parameters.put("userProfile", loginFinishedEvent.UserProfile.toJSONObject());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLoginStartedEvent(final LoginStartedEvent loginStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_STARTED);
                    parameters.put("provider", loginStartedEvent.Provider.getValue());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

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

    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        this.mGLThread = glSurfaceView;
    }
}
