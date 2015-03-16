
#import "ProfileBridge.h"
#import "NdkGlue.h"
#import "Reward.h"
#import "DomainFactory.h"
#import "SoomlaProfile.h"
#import "ProfileEventHandling.h"
#import "ProviderNotFoundException.h"
#import "UserProfile.h"
#import "DomainHelper.h"
#import "UserProfileNotFoundException.h"

@interface ProfileBridge ()
@end

@implementation ProfileBridge {

}

+ (id)sharedProfileBridge {
    static ProfileBridge *sharedProfileBridge = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedProfileBridge = [self alloc];
    });
    return sharedProfileBridge;
}

+ (void)initialize {
    [super initialize];
    [self initGlue];
    [self initDomainHelper];
}


- (id)init {
    self = [super init];
    if (self) {
        [ProfileEventHandling observeAllEventsWithObserver:[NdkGlue sharedInstance]
                                                  withSelector:@selector(dispatchNdkCallback:)];
    }

    return self;
}

+ (void)initDomainHelper {

    [[DomainHelper sharedDomainHelper] registerType:(NSString *)@"UserProfile"
                                      withClassName:NSStringFromClass([UserProfile class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[UserProfile alloc] initWithDictionary:dict];
                                           }];
}

+ (void)initGlue {
    NdkGlue *ndkGlue = [NdkGlue sharedInstance];

    /* -= Call handlers =- */
    [ndkGlue registerCallHandlerForKey:@"CCProfileBridge::init" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSDictionary *providerParams = [parameters objectForKey:@"params"];
        if (providerParams) {
            NSMutableDictionary *parsedParams = [NSMutableDictionary dictionary];
            for (NSString* key in providerParams) {
                id value = providerParams[key];
                [parsedParams setObject:value forKey:@([UserProfileUtils providerStringToEnum:key])];
            }
            
            [[SoomlaProfile getInstance] initialize:parsedParams];
        }
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::login" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        NSString *payload = [parameters objectForKey:@"payload"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        if (reward != nil) {
            [[SoomlaProfile getInstance] loginWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                 andPayload:payload andReward:reward];
        } else {
            [[SoomlaProfile getInstance] loginWithProvider:[UserProfileUtils providerStringToEnum:provider] andPayload:payload andReward:nil];
        }
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::logout" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        [[SoomlaProfile getInstance] logoutWithProvider:[UserProfileUtils providerStringToEnum:provider]];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::getStoredUserProfile" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        UserProfile *userProfile = [[SoomlaProfile getInstance] getStoredUserProfileWithProvider:
                [UserProfileUtils providerStringToEnum:provider]];
        NSDictionary *retObj = [[DomainHelper sharedDomainHelper] domainToDict:userProfile];
        if (userProfile != nil) {
            [retParameters setObject:retObj forKey:@"return"];
        }
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::updateStatus" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *status = [parameters objectForKey:@"status"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStatusWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                    andStatus:status
                                                    andPayload:payload
                                                    andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::updateStatusDialog" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *link = [parameters objectForKey:@"link"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStatusWithProviderDialog:[UserProfileUtils providerStringToEnum:provider]
                                                    andLink:link
                                                    andPayload:payload
                                                    andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::updateStory" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *message = [parameters objectForKey:@"message"];
        NSString *name = [parameters objectForKey:@"name"];
        NSString *caption = [parameters objectForKey:@"caption"];
        NSString *description = [parameters objectForKey:@"description"];
        NSString *link = [parameters objectForKey:@"link"];
        NSString *picture = [parameters objectForKey:@"picture"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStoryWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                  andMessage:message
                                                     andName:name
                                                  andCaption:caption
                                              andDescription:description
                                                     andLink:link
                                                  andPicture:picture
                                                  andPayload:payload
                                                   andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::updateStoryDialog" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *name = [parameters objectForKey:@"name"];
        NSString *caption = [parameters objectForKey:@"caption"];
        NSString *description = [parameters objectForKey:@"description"];
        NSString *link = [parameters objectForKey:@"link"];
        NSString *picture = [parameters objectForKey:@"picture"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStoryWithProviderDialog:[UserProfileUtils providerStringToEnum:provider]
                                                     andName:name
                                                  andCaption:caption
                                              andDescription:description
                                                     andLink:link
                                                  andPicture:picture
                                                  andPayload:payload
                                                   andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::uploadImage" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *message = [parameters objectForKey:@"message"];
        NSString *filePath = [parameters objectForKey:@"filePath"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] uploadImageWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                  andMessage:message
                                                 andFilePath:filePath
                                                  andPayload:payload
                                                   andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::getContacts" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] getContactsWithProvider:[UserProfileUtils providerStringToEnum:provider] andPayload:payload andReward:reward];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::getFeed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] getFeedWithProvider:[UserProfileUtils providerStringToEnum:provider] andPayload:payload andReward:reward];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::isLoggedIn" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        BOOL result = [[SoomlaProfile getInstance] isLoggedInWithProvider:[UserProfileUtils providerStringToEnum:provider]];
        [retParameters setObject:@(result) forKey:@"return"];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::like" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *pageName = [parameters objectForKey:@"pageName"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] like:[UserProfileUtils providerStringToEnum:provider] andPageName:pageName andReward:reward];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::openAppRatingPage" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [[SoomlaProfile getInstance] openAppRatingPage];
    }];

    /* -= Exception handlers =- */
    void (^exceptionHandler)(NSException *, NSDictionary *, NSMutableDictionary *) = ^(NSException *exception, NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [retParameters setObject: NSStringFromClass([exception class]) forKey: @"errorInfo"];
    };
    [ndkGlue registerExceptionHandlerForKey:NSStringFromClass([ProviderNotFoundException class]) withBlock:exceptionHandler];
    [ndkGlue registerExceptionHandlerForKey:NSStringFromClass([UserProfileNotFoundException class]) withBlock:exceptionHandler];

    /* -= Callback handlers =- */
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_PROFILE_INITIALIZED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.profile.events.ProfileInitializedEvent";
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_USER_RATING withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.profile.events.UserRatingEvent";
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_CANCELLED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginCancelledEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginFinishedEvent" forKey:@"method"];
        id userProfile = [notification.userInfo objectForKey:DICT_ELEMENT_USER_PROFILE];
        [parameters setObject:[userProfile toDictionary] forKey:@"userProfile"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGOUT_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LogoutFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGOUT_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LogoutFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGOUT_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LogoutStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_CONTACTS_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_CONTACTS_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        id contacts = [notification.userInfo objectForKey:DICT_ELEMENT_CONTACTS];
        [parameters setObject:[[DomainHelper sharedDomainHelper] getDictListFromDomains:contacts] forKey:@"contacts"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_CONTACTS_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_FEEDS] forKey:@"feed"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_SOCIAL_ACTION_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_SOCIAL_ACTION_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_SOCIAL_ACTION_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_USER_PROFILE_UPDATED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.UserProfileUpdatedEvent" forKey:@"method"];
        UserProfile *userProfile = [notification.userInfo objectForKey:DICT_ELEMENT_USER_PROFILE];
        [parameters setObject:[userProfile toDictionary] forKey:@"userProfile"];
    }];
}

@end
