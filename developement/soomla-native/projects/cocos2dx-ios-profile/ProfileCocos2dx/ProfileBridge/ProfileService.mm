//
// Created by Fedor Shubin on 6/12/14.
//

#import "ProfileService.h"
#import "NdkGlue.h"
#import "Reward.h"
#import "DomainFactory.h"
#import "SoomlaProfile.h"
#import "UserProfileEventHandling.h"
#import "ProviderNotFoundException.h"
#import "UserProfile.h"
#import "DomainHelper.h"
#import "UserProfileNotFoundException.h"

@interface ProfileService ()
@end

@implementation ProfileService {

}

+ (id)sharedProfileService {
    static ProfileService *sharedProfileService = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedProfileService = [self alloc];
    });
    return sharedProfileService;
}

+ (void)initialize {
    [super initialize];
    [self initGlue];
    [self initDomainHelper];
}


- (id)init {
    self = [super init];
    if (self) {
        [UserProfileEventHandling observeAllEventsWithObserver:[NdkGlue sharedInstance]
                                                  withSelector:@selector(dispatchNdkCallback:)];
        [[SoomlaProfile getInstance] initialize];
    }

    return self;
}

+ (void)initDomainHelper {
    [[DomainHelper sharedDomainHelper] registerType:@"userProfile"
                                      withClassName:NSStringFromClass([UserProfile class])];
}

+ (void)initGlue {
    NdkGlue *ndkGlue = [NdkGlue sharedInstance];

    /* -= Call handlers =- */
    [ndkGlue registerCallHandlerForKey:@"CCProfileService::init" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [[ProfileService sharedProfileService] init];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::login" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        if (reward != nil) {
            [[SoomlaProfile getInstance] loginWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                 andReward:reward];
        } else {
            [[SoomlaProfile getInstance] loginWithProvider:[UserProfileUtils providerStringToEnum:provider]];
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
        if (userProfile != nil) {
            [retParameters setObject:[userProfile toDictionary] forKey:@"return"];
        }
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::updateStatus" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *status = [parameters objectForKey:@"status"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStatusWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                    andStatus:status
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
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] updateStoryWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                  andMessage:message
                                                     andName:name
                                                  andCaption:caption
                                              andDescription:description
                                                     andLink:link
                                                  andPicture:picture
                                                   andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::uploadImage" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSString *message = [parameters objectForKey:@"message"];
        NSString *filePath = [parameters objectForKey:@"filePath"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] uploadImageWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                  andMessage:message
                                                 andFilePath:filePath
                                                   andReward:reward];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::getContacts" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] getContactsWithProvider:[UserProfileUtils providerStringToEnum:provider] andReward:reward];
    }];
    
    [ndkGlue registerCallHandlerForKey:@"CCSoomlaProfile::getFeed" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *provider = [parameters objectForKey:@"provider"];
        NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
        Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
        [[SoomlaProfile getInstance] getFeedWithProvider:[UserProfileUtils providerStringToEnum:provider] andReward:reward];
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
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginFinishedEvent" forKey:@"method"];
        id userProfile = [notification.userInfo objectForKey:DICT_ELEMENT_USER_PROFILE];
        [parameters setObject:[userProfile toDictionary] forKey:@"userProfile"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_LOGIN_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
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
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_CONTACTS_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        id contacts = [notification.userInfo objectForKey:DICT_ELEMENT_CONTACTS];
        [parameters setObject:[[DomainHelper sharedDomainHelper] getDictListFromDomains:contacts] forKey:@"contacts"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_CONTACTS_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
    }];
    
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_FEEDS] forKey:@"feed"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_GET_FEED_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.GetFeedStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
    }];
    
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_SOCIAL_ACTION_FAILED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_SOCIAL_ACTION_FINISHED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_SOCIAL_ACTION_STARTED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
    }];
    
    [ndkGlue registerCallbackHandlerForKey:EVENT_UP_USER_PROFILE_UPDATED withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        [parameters setObject:@"com.soomla.profile.events.UserProfileUpdatedEvent" forKey:@"method"];
        UserProfile *userProfile = [notification.userInfo objectForKey:DICT_ELEMENT_USER_PROFILE];
        [parameters setObject:[userProfile toDictionary] forKey:@"userProfile"];
    }];
}

@end