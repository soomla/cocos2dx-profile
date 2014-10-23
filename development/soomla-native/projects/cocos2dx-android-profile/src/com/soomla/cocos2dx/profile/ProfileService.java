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

import com.soomla.Soomla;
import com.soomla.SoomlaUtils;
import com.soomla.cocos2dx.common.AbstractSoomlaService;
import com.soomla.cocos2dx.common.DomainFactory;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.cocos2dx.common.ParamsProvider;
import com.soomla.profile.SoomlaProfile;
import com.soomla.profile.domain.IProvider;
import com.soomla.profile.domain.UserProfile;
import com.soomla.profile.exceptions.ProviderNotFoundException;
import com.soomla.profile.exceptions.UserProfileNotFoundException;
import com.soomla.rewards.Reward;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.ref.WeakReference;

/**
 * Profile defines all the glue between Cocos2dx-Profile and iOS Profile
 *
 * ProfileService signs up to all Profile events which are received from native
 * and passed to Cocos2dx and the other way around.
 *
 * NOTE: This service should be registered in the ServiceManager in your
 * main app activity
 *
 */
public class ProfileService extends AbstractSoomlaService {

    private static ProfileService INSTANCE = null;

    private boolean inited = false;

    /**
     * Retrieves the singleton instance of the service
     *
     * @return The singleton instance of the service
     */
    public static ProfileService getInstance() {
        if (INSTANCE == null) {
            synchronized (ProfileService.class) {
                if (INSTANCE == null) {
                    INSTANCE = new ProfileService();
                }
            }
        }
        return INSTANCE;
    }

    @SuppressWarnings("FieldCanBeLocal")
    private ProfileEventHandlerBridge profileEventHandlerBridge;

    /**
     * Constructor
     *
     * The main constructor for the service.
     * Registers all glue between native and Cocos2dx
     */
    public ProfileService() {
        profileEventHandlerBridge = new ProfileEventHandlerBridge();

        final DomainFactory domainFactory = DomainFactory.getInstance();

        domainFactory.registerCreator(ProfileConsts.JSON_JSON_TYPE_USER_PROFILE, new DomainFactory.Creator<UserProfile>() {
            @Override
            public UserProfile create(JSONObject jsonObject) {
                try {
                    return new UserProfile(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });

        final NdkGlue ndkGlue = NdkGlue.getInstance();

        ndkGlue.registerCallHandler("CCProfileService::init", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                ProfileService.getInstance().init();

                String customSecret = ParamsProvider.getInstance().getParams("common").optString("customSecret");
                SoomlaUtils.LogDebug("SOOMLA", "initialize is called from java!");
                Soomla.initialize(customSecret);
                SoomlaProfile.getInstance().initialize();
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::login", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().login(ndkGlue.getActivityRef().get(), IProvider.Provider.getEnum(provider), reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::logout", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                SoomlaProfile.getInstance().logout(IProvider.Provider.getEnum(provider));
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::getStoredUserProfile", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                UserProfile userProfile = SoomlaProfile.getInstance().getStoredUserProfile(IProvider.Provider.getEnum(provider));
                if (userProfile != null) {
                    retParams.put("return", userProfile.toJSONObject());
                }
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::updateStatus", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String status = params.getString("status");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStatus(IProvider.Provider.getEnum(provider), status, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::updateStatusDialog", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String link = params.optString("link");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStatusDialog(IProvider.Provider.getEnum(provider), link, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::updateStory", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String message = params.getString("message");
                String name = params.getString("name");
                String caption = params.getString("caption");
                String description = params.getString("description");
                String link = params.getString("link");
                String picture = params.getString("picture");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStory(IProvider.Provider.getEnum(provider), message, name, caption,
                        description, link, picture, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::updateStoryDialog", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String name = params.optString("name");
                String caption = params.optString("caption");
                String description = params.optString("description");
                String link = params.optString("link");
                String picture = params.optString("picture");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStoryDialog(IProvider.Provider.getEnum(provider), name, caption,
                        description, link, picture, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::uploadImage", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String message = params.getString("message");
                String filePath = params.getString("filePath");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().uploadImage(IProvider.Provider.getEnum(provider), message, filePath,
                        reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::getContacts", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().getContacts(IProvider.Provider.getEnum(provider), reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::getFeed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().getFeed(IProvider.Provider.getEnum(provider), reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::isLoggedIn", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                boolean result = SoomlaProfile.getInstance().isLoggedIn(ndkGlue.getActivityRef().get(), IProvider.Provider.getEnum(provider));
                retParams.put("return", result);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::like", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String pageName = params.getString("pageName");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().like(ndkGlue.getActivityRef().get(), IProvider.Provider.getEnum(provider),
                        pageName, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::openAppRatingPage", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                SoomlaProfile.getInstance().openAppRatingPage(ndkGlue.getActivityRef().get().getApplicationContext());
            }
        });


        final NdkGlue.ExceptionHandler exceptionHandler = new NdkGlue.ExceptionHandler() {
            @Override
            public void handle(Exception exception, JSONObject params, JSONObject retParams) throws Exception {
                retParams.put("errorInfo", exception.getClass().getName());
            }
        };

        ndkGlue.registerExceptionHandler(ProviderNotFoundException.class.getName(), exceptionHandler);
        ndkGlue.registerExceptionHandler(UserProfileNotFoundException.class.getName(), exceptionHandler);
    }

    /**
     * Initializes the service for further use
     *
     * NOTE: Called through the Cocos side
     */
    public void init() {
        final GLSurfaceView glSurfaceView = glSurfaceViewRef.get();
        if (glSurfaceView != null) {
            profileEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }

        inited = true;
    }

    /**
     * Sets the main GL surface of the application
     *
     * @param glSurfaceView The GL surface of the main activity
     */
    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        if (inited) {
            profileEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        } else {
            glSurfaceViewRef = new WeakReference<GLSurfaceView>(glSurfaceView);
        }
    }
}
