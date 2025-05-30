//
//  SPSnowplow.h
//  Snowplow
//
//  Copyright (c) 2013-2021 Snowplow Analytics Ltd. All rights reserved.
//
//  This program is licensed to you under the Apache License Version 2.0,
//  and you may not use this file except in compliance with the Apache License
//  Version 2.0. You may obtain a copy of the Apache License Version 2.0 at
//  http://www.apache.org/licenses/LICENSE-2.0.
//
//  Unless required by applicable law or agreed to in writing,
//  software distributed under the Apache License Version 2.0 is distributed on
//  an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
//  express or implied. See the Apache License Version 2.0 for the specific
//  language governing permissions and limitations there under.
//
//  Authors: Alex Benini
//  Copyright: Copyright (c) 2013-2021 Snowplow Analytics Ltd
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>
#import "CATTrackerController.h"
#import "CATNetworkConfiguration.h"
#import "CATTrackerConfiguration.h"
#import "CATRemoteConfiguration.h"
#import "CATConfigurationBundle.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Entry point to instance a new CAT tracker.
 */
NS_SWIFT_NAME(CATAppAnalytics)
@interface CATAppAnalytics : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;


/// Remote Configuration

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 * @param customerKey Customer key provided by conviva.
 * @param appName Uniquely identifiable app name.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey appName:(NSString*)appName NS_SWIFT_NAME(createTracker(customerKey:appName:));

/**
 * The default tracker instance is the first created in the app, but that can be overridden programmatically
 * calling `setTrackerAsDefault(TrackerController)`.
 */
+ (nullable id<CATTrackerController>)defaultTracker;

/**
 * @return AppAnalytics instance.
 */
+ (nullable instancetype)sharedInstance;

/**
 *  Cleanup sdk.
 */
+ (void) cleanup;

/**
 * Once CATAppAnalytics object is created, initialization of object happens automatically.
 * After cleanup is called, wants to resue the object, reInitializeSDK shall be called.
 */
+ (void) reInitializeSDK;

@end

@interface CATAppAnalytics(Advanced)

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `defaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 * @param customerKey Customer key provided by conviva.
 * @param appName Uniquely identifiable app name.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey appName:(NSString*)appName namespace:(NSString *)namespace NS_SWIFT_NAME(createTracker(customerKey:appName:namespace:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param namespace The namespace used to identify the current tracker among the possible
 *                  multiple tracker instances.
 * @param customerKey Customer key provided by conviva.
 * @param endpoint The URL of the collector.
 * @param method The method for the requests to the collector (GET or POST).
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithNamespace:(NSString *)namespace customerKey:(NSString*)customerKey endpoint:(NSString *)endpoint method:(CATHttpMethod)method NS_SWIFT_NAME(createTracker(namespace:customerKey:endpoint:method:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param namespace The namespace used to identify the current tracker among the possible
 *                  multiple tracker instances.
 * @param customerKey Customer key provided by conviva.
 * @param networkConfiguration The NetworkConfiguration object with settings for the communication with the
 *                collector.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithNamespace:(NSString *)namespace
                                                    customerKey:(NSString*)customerKey
                                                        network:(CATNetworkConfiguration *)networkConfiguration NS_SWIFT_NAME(createTracker(namespace:customerKey:network:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param namespace The namespace used to identify the current tracker among the possible
 *                  multiple tracker instances.
 * @param customerKey Customer key provided by conviva.
 * @param networkConfiguration The NetworkConfiguration object with settings for the communication with the
 *                collector.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithNamespace:(NSString *)namespace
                                                    customerKey:(NSString*)customerKey
                                                        network:(CATNetworkConfiguration *)networkConfiguration
                                                 configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(namespace:customerKey:network:configurations:));

/**
  * Using the namespace identifier is possible to get the trackerController if already instanced.
  *
  * @param namespace The namespace that identifies the tracker.
  * @return The tracker if it exist with that namespace.
  */
 + (nullable id<CATTrackerController>)trackerByNamespace:(NSString *)namespace NS_SWIFT_NAME(tracker(namespace:));

/**
 * Remove all the trackers.
 * The removed tracker is always stopped.
 * See `removeTracker(TrackerController)`
 */
+ (void)removeAllTrackers NS_SWIFT_NAME(removeAllTrackers());

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `defaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey Customer key provided by conviva.
 * @param appName Uniquely identifiable app name.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey
                                                 appName:(NSString*)appName
                                          configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(customerKey:appName:configurations:));



/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey Customer key provided by conviva.
 * @param appName Uniquely identifiable app name.
 * @param networkConfiguration The NetworkConfiguration object with settings for the communication with the
 *                collector.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey
                                                 appName:(NSString*)appName
                                                 network:(CATNetworkConfiguration *)networkConfiguration
                                          configurations:(NSArray<CATConfiguration *> *)configurations;
/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey Customer key provided by conviva.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey
                                          configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(customerKey:configurations:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey Customer key provided by conviva.
 * @param networkConfiguration The NetworkConfiguration object with settings for the communication with the
 *                collector.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (nullable id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey
                                                 network:(CATNetworkConfiguration *)networkConfiguration
                                          configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(customerKey:network:configurations:));

/**
 * A tracker can be removed from the active trackers of the app.
 * Once it has been removed it can't be added again or set as default.
 * The unique way to resume a removed tracker is creating a new tracker with same namespace and
 * same configurations.
 * The removed tracker is always stopped.
 *
 * @param trackerController The tracker controller to remove.
 * @return Whether it has been able to remove it.
 */
+ (BOOL)removeTracker:(id<CATTrackerController>)trackerController NS_SWIFT_NAME(remove(tracker:));

/**
 * @return Client Id.
 */
- (nullable NSString*) getClientId;

/**
 *  Sets Client Id Event Index.
 */
- (BOOL) setClientId: (NSString *)newClientId;

/**
 * @return Client Id Event Index.
 */
- (NSInteger) getClientIdEventIndex;

/**
 *  Sets Client Id Event Index.
 *  @param index - Sets Client Id Event Index.
 */
- (void) setClientIdEventIndex:(NSInteger)index;

/**
 *  Gets config info for given target URL
 *
 *  @param targetUrl - target url.
 *  @returns Config info map
 */
- (NSDictionary *)getConfigInfoFor:(NSString *)targetUrl;


@end
NS_ASSUME_NONNULL_END
