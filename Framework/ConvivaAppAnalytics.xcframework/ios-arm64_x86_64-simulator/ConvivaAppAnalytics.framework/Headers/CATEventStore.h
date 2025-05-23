//
//  CATEventStore.h
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

#import "CATPayload.h"
#import "CATEmitterEvent.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATEventStore)
@protocol CATEventStore <NSObject>

/**
 * Adds an event to the store.
 * @param payload the payload to be added
 */
- (void)addEvent:(CATPayload *)payload;

/**
 * Removes an event from the store.
 * @param storeId the identifier of the event in the store.
 * @return a boolean of success to remove.
 */
- (BOOL)removeEventWithId:(long long int)storeId;

/**
 * Removes a range of events from the store.
 * @param storeIds the events' identifiers in the store.
 * @return a boolean of success to remove.
 */
- (BOOL)removeEventsWithIds:(NSArray<NSNumber *> *)storeIds;

/**
 * Empties the store of all the events.
 * @return a boolean of success to remove.
 */
- (BOOL)removeAllEvents;

/**
 * Returns amount of events currently in the store.
 * @return the count of events in the store.
 */
- (NSUInteger)count;

/**
 * Returns a list of EmitterEvent objects which contains events and related ids.
 * @param queryLimit is the maximum number of events returned.
 * @return EmitterEvent objects containing storeIds and event payloads.
 */
- (NSArray<CATEmitterEvent *> *)emittableEventsWithQueryLimit:(NSUInteger)queryLimit;

/**
 * Returns a list of EmitterEvent objects which contains events and related ids.
 * @param size is the size limit of events returned.
 * @return EmitterEvent objects containing storeIds and event payloads.
 */

- (NSArray<CATEmitterEvent *> *)getEventsBySizeLimit:(NSUInteger)size;


- (NSUInteger)getAllEventsSize;

/**
 * Returns last inserted event row id.
 * @return last inserted event row id.
 */

- (long long int) getLastInsertedRowId;

@end

NS_ASSUME_NONNULL_END
