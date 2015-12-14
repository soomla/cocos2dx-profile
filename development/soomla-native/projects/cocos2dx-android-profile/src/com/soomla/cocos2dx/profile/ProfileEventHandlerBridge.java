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
import com.soomla.profile.domain.gameservices.*;
import com.soomla.profile.events.auth.*;
import com.soomla.profile.events.social.*;
import com.soomla.profile.events.gameservices.*;
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
                    parameters.put("autoLogin", loginFailedEvent.AutoLogin);
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
                    parameters.put("autoLogin", loginFinishedEvent.AutoLogin);
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
                    parameters.put("autoLogin", loginStartedEvent.AutoLogin);
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
                    parameters.put("fromStart", getContactsFailedEvent.FromStart);
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
                    parameters.put("hasMore", getContactsFinishedEvent.HasMore);
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
                    parameters.put("fromStart", getContactsStartedEvent.FromStart);
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
                    parameters.put("fromStart", getFeedFailedEvent.FromStart);
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
                    parameters.put("hasMore", getFeedFinishedEvent.HasMore);
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
                    parameters.put("fromStart", getFeedStartedEvent.FromStart);
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
                    parameters.put("autoLogin", loginCancelledEvent.AutoLogin);
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
     * Called when an invitation on a provider has started
     *
     * @param inviteStartedEvent The event information
     */
    @Subscribe
    public void onInviteStartedEvent(final InviteStartedEvent inviteStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_INVITE_STARTED);
                    parameters.put("provider", inviteStartedEvent.Provider.getValue());
                    parameters.put("socialActionType", inviteStartedEvent.SocialActionType.getValue());
                    parameters.put("payload", inviteStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when an invitation on a provider has finished
     *
     * @param inviteFinishedEvent The event information
     */
    @Subscribe
    public void onInviteFinishedEvent(final InviteFinishedEvent inviteFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_INVITE_FINISHED);
                    parameters.put("provider", inviteFinishedEvent.Provider.getValue());
                    parameters.put("socialActionType", inviteFinishedEvent.SocialActionType.getValue());
                    parameters.put("requestId", inviteFinishedEvent.RequestId);
                    parameters.put("invitedIds", new JSONArray(inviteFinishedEvent.InvitedIds));
                    parameters.put("payload", inviteFinishedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when an invitation on a provider has failed
     *
     * @param inviteFailedEvent The event information
     */
    @Subscribe
    public void onInviteFailedEvent(final InviteFailedEvent inviteFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_INVITE_FAILED);
                    parameters.put("provider", inviteFailedEvent.Provider.getValue());
                    parameters.put("socialActionType", inviteFailedEvent.SocialActionType.getValue());
                    parameters.put("errorDescription", inviteFailedEvent.ErrorDescription);
                    parameters.put("payload", inviteFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    /**
     * Called when an invitation on a provider has cancelled
     *
     * @param inviteCancelledEvent The event information
     */
    @Subscribe
    public void onInviteCancelledEvent(final InviteCancelledEvent inviteCancelledEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_INVITE_CANCELLED);
                    parameters.put("provider", inviteCancelledEvent.Provider.getValue());
                    parameters.put("socialActionType", inviteCancelledEvent.SocialActionType.getValue());
                    parameters.put("payload", inviteCancelledEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetLeaderboardsStartedEvent(final GetLeaderboardsStartedEvent getLeaderboardsStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_LEADERBOARDS_STARTED);
                    parameters.put("provider", getLeaderboardsStartedEvent.Provider.getValue());
                    parameters.put("payload", getLeaderboardsStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetLeaderboardsFinishedEvent(final GetLeaderboardsFinishedEvent getLeaderboardsFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_LEADERBOARDS_FINISHED);
                    parameters.put("provider", getLeaderboardsFinishedEvent.Provider.getValue());
                    parameters.put("leaderboards", DomainHelper.getInstance().getJsonObjectListFromDomains(getLeaderboardsFinishedEvent.Leaderboards));
                    parameters.put("payload", getLeaderboardsFinishedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetLeaderboardsFailedEvent(final GetLeaderboardsFailedEvent getLeaderboardsFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_LEADERBOARDS_FAILED);
                    parameters.put("provider", getLeaderboardsFailedEvent.Provider.getValue());
                    parameters.put("errorDescription", getLeaderboardsFailedEvent.ErrorDescription);
                    parameters.put("payload", getLeaderboardsFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetScoresStartedEvent(final GetScoresStartedEvent getScoresStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_SCORES_STARTED);
                    parameters.put("provider", getScoresStartedEvent.Provider.getValue());
                    parameters.put("leaderboard", getScoresStartedEvent.Leaderboard.toJSONObject());
                    parameters.put("fromStart", getScoresStartedEvent.FromStart);
                    parameters.put("payload", getScoresStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetScoresFinishedEvent(final GetScoresFinishedEvent getScoresFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_SCORES_FINISHED);
                    parameters.put("provider", getScoresFinishedEvent.Provider.getValue());
                    parameters.put("leaderboard", getScoresFinishedEvent.Leaderboard.toJSONObject());
                    parameters.put("scores", DomainHelper.getInstance().getJsonObjectListFromDomains(getScoresFinishedEvent.Scores));
                    parameters.put("payload", getScoresFinishedEvent.Payload);
                    parameters.put("hasMore", getScoresFinishedEvent.HasMore);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetScoresFailedEvent(final GetScoresFailedEvent getScoresFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_SCORES_FAILED);
                    parameters.put("provider", getScoresFailedEvent.Provider.getValue());
                    parameters.put("leaderboard", getScoresFailedEvent.Leaderboard.toJSONObject());
                    parameters.put("fromStart", getScoresFailedEvent.FromStart);
                    parameters.put("errorDescription", getScoresFailedEvent.ErrorDescription);
                    parameters.put("payload", getScoresFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onSubmitScoreStartedEvent(final SubmitScoreStartedEvent submitScoreStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SUBMIT_SCORE_STARTED);
                    parameters.put("provider", submitScoreStartedEvent.Provider.getValue());
                    parameters.put("leaderboard", submitScoreStartedEvent.Leaderboard.toJSONObject());
                    parameters.put("payload", submitScoreStartedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onSubmitScoreFinishedEvent(final SubmitScoreFinishedEvent submitScoreFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SUBMIT_SCORE_FINISHED);
                    parameters.put("provider", submitScoreFinishedEvent.Provider.getValue());
                    parameters.put("leaderboard", submitScoreFinishedEvent.Leaderboard.toJSONObject());
                    parameters.put("score", submitScoreFinishedEvent.Score.toJSONObject());
                    parameters.put("payload", submitScoreFinishedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onSubmitScoreFailedEvent(final SubmitScoreFailedEvent submitScoreFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SUBMIT_SCORE_FAILED);
                    parameters.put("provider", submitScoreFailedEvent.Provider.getValue());
                    parameters.put("leaderboard", submitScoreFailedEvent.Leaderboard.toJSONObject());
                    parameters.put("errorDescription", submitScoreFailedEvent.ErrorDescription);
                    parameters.put("payload", submitScoreFailedEvent.Payload);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onShowLeaderboardsEvent(final ShowLeaderboardsEvent showLeaderboardsEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SHOW_LEADERBOARDS);
                    parameters.put("provider", showLeaderboardsEvent.Provider.getValue());
                    parameters.put("payload", showLeaderboardsEvent.Payload);
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
