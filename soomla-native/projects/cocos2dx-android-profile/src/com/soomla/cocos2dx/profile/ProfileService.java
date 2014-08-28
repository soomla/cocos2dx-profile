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
 * @author vedi
 *         date 6/10/14
 *         time 11:08 AM
 */
public class ProfileService extends AbstractSoomlaService {

    private static ProfileService INSTANCE = null;

    private boolean inited = false;

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

        ndkGlue.registerCallHandler("CCProfileController::login", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().login(ndkGlue.getActivityRef().get(), IProvider.Provider.getEnum(provider), reward);
            }
        });

        ndkGlue.registerCallHandler("CCProfileController::logout", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                SoomlaProfile.getInstance().logout(IProvider.Provider.getEnum(provider));
            }
        });

        ndkGlue.registerCallHandler("CCProfileController::getStoredUserProfile", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                UserProfile userProfile = SoomlaProfile.getInstance().getStoredUserProfile(IProvider.Provider.getEnum(provider));
                if (userProfile != null) {
                    retParams.put("return", userProfile.toJSONObject());
                }
            }
        });

        ndkGlue.registerCallHandler("CCProfileController::updateStatus", new NdkGlue.CallHandler() {
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

        ndkGlue.registerCallHandler("CCProfileController::updateStory", new NdkGlue.CallHandler() {
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

        ndkGlue.registerCallHandler("CCProfileController::uploadImage", new NdkGlue.CallHandler() {
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

        ndkGlue.registerCallHandler("CCProfileController::getContacts", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().getContacts(IProvider.Provider.getEnum(provider), reward);
            }
        });

        ndkGlue.registerCallHandler("CCProfileController::getFeed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String provider = params.getString("provider");
                JSONObject rewardJson = params.optJSONObject("reward");
                Reward reward = (rewardJson != null) ?
                        domainFactory.<Reward>createWithJsonObject(rewardJson) : null;
                SoomlaProfile.getInstance().getFeed(IProvider.Provider.getEnum(provider), reward);
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

    public void init() {
        final GLSurfaceView glSurfaceView = glSurfaceViewRef.get();
        if (glSurfaceView != null) {
            profileEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }

        inited = true;
    }

    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        if (inited) {
            profileEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        } else {
            glSurfaceViewRef = new WeakReference<GLSurfaceView>(glSurfaceView);
        }
    }
}
