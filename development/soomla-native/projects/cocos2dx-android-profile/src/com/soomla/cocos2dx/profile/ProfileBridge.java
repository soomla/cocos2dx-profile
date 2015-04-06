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

import com.soomla.SoomlaUtils;
import com.soomla.cocos2dx.common.DomainFactory;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.profile.SoomlaProfile;
import com.soomla.profile.domain.IProvider;
import com.soomla.profile.domain.UserProfile;
import com.soomla.profile.exceptions.ProviderNotFoundException;
import com.soomla.profile.exceptions.UserProfileNotFoundException;
import com.soomla.rewards.Reward;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Iterator;

/**
 * Profile defines all the glue between Cocos2dx-Profile and iOS Profile
 *
 * ProfileBridge signs up to all Profile events which are received from native
 * and passed to Cocos2dx and the other way around.
 *
 */
public class ProfileBridge {

    private static ProfileBridge INSTANCE = null;

    /**
     * Retrieves the singleton instance of the bridge
     *
     * @return The singleton instance of the bridge
     */
    public static ProfileBridge getInstance() {
        if (INSTANCE == null) {
            synchronized (ProfileBridge.class) {
                if (INSTANCE == null) {
                    INSTANCE = new ProfileBridge();
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
     * The main constructor for the bridge.
     * Registers all glue between native and Cocos2dx
     */
    public ProfileBridge() {
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

        ndkGlue.registerCallHandler("CCProfileBridge::init", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                HashMap<IProvider.Provider, HashMap<String, String>> providerParams = parseProviderParams(params.optJSONObject("params"));
                SoomlaUtils.LogDebug("SOOMLA", "initialize is called from java!");
                SoomlaProfile.getInstance().initialize(providerParams);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::login", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().login(ndkGlue.getActivityRef().get(), IProvider.Provider.getEnum(provider), payload, reward);
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
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStatus(IProvider.Provider.getEnum(provider), status, payload, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::updateStatusDialog", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String link = params.optString("link");
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStatusDialog(IProvider.Provider.getEnum(provider), link, payload, reward);
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
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStory(IProvider.Provider.getEnum(provider), message, name, caption,
                        description, link, picture, payload, reward);
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
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().updateStoryDialog(IProvider.Provider.getEnum(provider), name, caption,
                        description, link, picture, payload, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::uploadImage", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String message = params.getString("message");
                String filePath = params.getString("filePath");
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().uploadImage(IProvider.Provider.getEnum(provider), message, filePath,
                        payload, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::getContacts", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().getContacts(IProvider.Provider.getEnum(provider), payload, reward);
            }
        });

        ndkGlue.registerCallHandler("CCSoomlaProfile::getFeed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                String payload = params.getString("payload");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().getFeed(IProvider.Provider.getEnum(provider), payload, reward);
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
                String pageId = params.getString("pageId");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().like(ndkGlue.getActivityRef().get(), IProvider.Provider.getEnum(provider),
                pageId, reward);
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

    private HashMap<IProvider.Provider, HashMap<String, String>> parseProviderParams(JSONObject sentParams) {
        if (sentParams == null) {
            SoomlaUtils.LogDebug("SOOMLA", "no provider params were sent");
            return null;
        }

        HashMap<IProvider.Provider, HashMap<String, String>> result = new HashMap<IProvider.Provider, HashMap<String, String>>();
        Iterator keysIterator = sentParams.keys();
        while (keysIterator.hasNext()) {
            String providerStr = (String)keysIterator.next();
            JSONObject paramsEntry = sentParams.optJSONObject(providerStr);

            if (paramsEntry != null) {
                HashMap<String, String> currentProviderParams = new HashMap<String, String>();
                Iterator innerKeysIterator = paramsEntry.keys();
                while (innerKeysIterator.hasNext()) {
                    String innerKey = (String)innerKeysIterator.next();
                    String innerValue = paramsEntry.optString(innerKey);
                    currentProviderParams.put(innerKey, innerValue);
                }

                result.put(IProvider.Provider.getEnum(providerStr), currentProviderParams);
            }
        }

        return result;
    }

    /**
     * Initializes the bridge for further use
     *
     * NOTE: Called through the Cocos side
     */
    public void init() {
        final GLSurfaceView glSurfaceView = NdkGlue.getInstance().getGlSurfaceRef().get();
        if (glSurfaceView != null) {
            profileEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }
    }
}
