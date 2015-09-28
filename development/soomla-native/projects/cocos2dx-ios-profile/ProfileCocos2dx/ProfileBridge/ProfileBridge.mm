
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
        NSDictionary *providerParams = parameters[@"params"];
        if (providerParams) {
            NSMutableDictionary *parsedParams = [NSMutableDictionary dictionary];
            for (NSString* key in providerParams) {
                id value = providerParams[key];
                parsedParams[@([UserProfileUtils providerStringToEnum:key])] = value;
            }

            BOOL res = [[SoomlaProfile getInstance] initialize:parsedParams];
            retParameters[@"return"] = @(res);
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
        NSString *provider = parameters[@"provider"];
        NSString *status = parameters[@"status"];
        NSString *payload = parameters[@"payload"];
        NSDictionary *rewardDict = parameters[@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStatusWithProvider:[UserProfileUtils providerStringToEnum:provider] andStatus:status andPayload:payload andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::updateStatusWithConfirmation" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = parameters[@"provider"];
        NSString *status = parameters[@"status"];
        NSString *payload = parameters[@"payload"];
        NSDictionary *rewardDict = parameters[@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        NSString *customMessage = parameters[@"customMessage"];
        if (customMessage.length == 0) {
            customMessage = nil;
        }
        [[SoomlaProfile getInstance] updateStatusWithProvider:[UserProfileUtils providerStringToEnum:provider] andStatus:status andPayload:payload andReward:reward andConfirmation:true andCustomMessage:customMessage];
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
        NSString *provider = parameters[@"provider"];
        NSString *message = parameters[@"message"];
        NSString *name = parameters[@"name"];
        NSString *caption = parameters[@"caption"];
        NSString *description = parameters[@"description"];
        NSString *link = parameters[@"link"];
        NSString *picture = parameters[@"picture"];
        NSString *payload = parameters[@"payload"];
        NSDictionary *rewardDict = parameters[@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStoryWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                  andMessage:message
                                                     andName:name
                                                  andCaption:caption
                                              andDescription:description
                                                     andLink:link
                                                  andPicture:picture
                                                  andPayload:payload
                                                   andReward:reward
                                         andShowConfirmation:false
                                            andCustomMessage:nil];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::updateStoryWithConfirmation" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = parameters[@"provider"];
        NSString *message = parameters[@"message"];
        NSString *name = parameters[@"name"];
        NSString *caption = parameters[@"caption"];
        NSString *description = parameters[@"description"];
        NSString *link = parameters[@"link"];
        NSString *picture = parameters[@"picture"];
        NSString *payload = parameters[@"payload"];
        NSDictionary *rewardDict = parameters[@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        NSString *customMessage = parameters[@"customMessage"];
        if (customMessage.length == 0) {
            customMessage = nil;
        }
        [[SoomlaProfile getInstance] updateStoryWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                  andMessage:message
                                                     andName:name
                                                  andCaption:caption
                                              andDescription:description
                                                     andLink:link
                                                  andPicture:picture
                                                  andPayload:payload
                                                   andReward:reward
                                         andShowConfirmation:true
                                            andCustomMessage:customMessage];
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
        NSString *provider = parameters[@"provider"];
        NSString *message = parameters[@"message"];
        NSString *filePath = parameters[@"filePath"];
        NSString *payload = parameters[@"payload"];
        NSDictionary *rewardDict = parameters[@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] uploadImageWithProvider:[UserProfileUtils providerStringToEnum:provider] andMessage:message andFilePath:filePath andPayload:payload andReward:reward andConfirmation:false andCustomMessage:nil];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::uploadImageWithConfirmation" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = parameters[@"provider"];
        NSString *message = parameters[@"message"];
        NSString *filePath = parameters[@"filePath"];
        NSString *payload = parameters[@"payload"];
        NSDictionary *rewardDict = parameters[@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        NSString *customMessage = parameters[@"customMessage"];
        if (customMessage.length == 0) {
            customMessage = nil;
        }
        [[SoomlaProfile getInstance] uploadImageWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                  andMessage:message
                                                 andFilePath:filePath
                                                  andPayload:payload
                                                   andReward:reward
                                             andConfirmation:true
                                            andCustomMessage:customMessage];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::getContacts" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSNumber *fromStart = [parameters objectForKey:@"fromStart"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] getContactsWithProvider:[UserProfileUtils providerStringToEnum:provider] andFromStart:[fromStart boolValue] andPayload:payload andReward:reward];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::getFeed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSNumber *fromStart = [parameters objectForKey:@"fromStart"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] getFeedWithProvider:[UserProfileUtils providerStringToEnum:provider] andFromStart:[fromStart boolValue] andPayload:payload andReward:reward];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::invite" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSNumber *inviteMessage = [parameters objectForKey:@"inviteMessage"];
        NSNumber *dialogTitle = [parameters objectForKey:@"dialogTitle"];
        NSString *payload = [parameters objectForKey:@"payload"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] inviteWithProvider:[UserProfileUtils providerStringToEnum:provider] inviteMessage:inviteMessage
                                            dialogTitle:dialogTitle payload:payload andReward:reward];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::isLoggedIn" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        BOOL result = [[SoomlaProfile getInstance] isLoggedInWithProvider:[UserProfileUtils providerStringToEnum:provider]];
        [retParameters setObject:@(result) forKey:@"return"];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::like" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *pageId = [parameters objectForKey:@"pageId"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] like:[UserProfileUtils providerStringToEnum:provider] andPageId:pageId andReward:reward];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::openAppRatingPage" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [[SoomlaProfile getInstance] openAppRatingPage];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::multiShare" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *text = parameters[@"text"];
        NSString *imageFilePath = parameters[@"imageFilePath"];
        [[SoomlaProfile getInstance] multiShareWithText:text andImageFilePath:imageFilePath];
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
        parameters[@"method"] = @"com.soomla.profile.events.auth.LoginCancelledEvent";
        parameters[@"provider"] = notification.userInfo[DICT_ELEMENT_PROVIDER];
        parameters[DICT_ELEMENT_AUTO_LOGIN] = notification.userInfo[DICT_ELEMENT_AUTO_LOGIN];
        parameters[@"payload"] = notification.userInfo[DICT_ELEMENT_PAYLOAD];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.profile.events.auth.LoginFailedEvent";
        parameters[@"provider"] = notification.userInfo[DICT_ELEMENT_PROVIDER];
        parameters[@"errorDescription"] = notification.userInfo[DICT_ELEMENT_MESSAGE];
        parameters[DICT_ELEMENT_AUTO_LOGIN] = notification.userInfo[DICT_ELEMENT_AUTO_LOGIN];
        parameters[@"payload"] = notification.userInfo[DICT_ELEMENT_PAYLOAD];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.profile.events.auth.LoginFinishedEvent";
        id userProfile = notification.userInfo[DICT_ELEMENT_USER_PROFILE];
        parameters[@"userProfile"] = [userProfile toDictionary];
        parameters[DICT_ELEMENT_AUTO_LOGIN] = notification.userInfo[DICT_ELEMENT_AUTO_LOGIN];
        parameters[@"payload"] = notification.userInfo[DICT_ELEMENT_PAYLOAD];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.profile.events.auth.LoginStartedEvent";
        parameters[@"provider"] = notification.userInfo[DICT_ELEMENT_PROVIDER];
        parameters[DICT_ELEMENT_AUTO_LOGIN] = notification.userInfo[DICT_ELEMENT_AUTO_LOGIN];
        parameters[@"payload"] = notification.userInfo[DICT_ELEMENT_PAYLOAD];
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
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_FROM_START] forKey:@"fromStart"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_CONTACTS_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        id contacts = [notification.userInfo objectForKey:DICT_ELEMENT_CONTACTS];
        [parameters setObject:[[DomainHelper sharedDomainHelper] getDictListFromDomains:contacts] forKey:@"contacts"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_HAS_MORE] forKey:@"hasMore"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_CONTACTS_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_FROM_START] forKey:@"fromStart"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];

    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_FROM_START] forKey:@"fromStart"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_FEEDS] forKey:@"feed"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_HAS_MORE] forKey:@"hasMore"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_FROM_START] forKey:@"fromStart"];
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

    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_INVITE_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.InviteStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_INVITE_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.InviteFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_REQUEST_ID] forKey:@"requestId"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_INVITED_LIST] forKey:@"invitedIds"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_INVITE_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.InviteFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_INVITE_CANCELLED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.InviteCancelledEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PAYLOAD] forKey:@"payload"];
    }];
}

@end
