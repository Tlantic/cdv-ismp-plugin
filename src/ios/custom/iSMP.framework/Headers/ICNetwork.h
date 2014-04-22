//
//  ICNetwork.h
//  iSMP Library
//
//  Created by Christophe Fontaine on 21/06/10.
//  Copyright 2010 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ICISMPDevice.h"

@protocol ICNetworkDelegate;

@interface ICNetwork : ICISMPDevice <NSStreamDelegate>
{
	NSMutableArray	* openConnections;                          /**< An array of all open connections */
	
	NSOperationQueue	* spmToHostWriteOperations;             /**< An operation queue on which the write operations are scheduled */
}

+(id) sharedChannel;

@property (nonatomic, assign) id<ICISMPDeviceDelegate,ICNetworkDelegate> delegate;

@end

@protocol ICNetworkDelegate
@optional

-(void)networkData:(NSData *)data incoming:(BOOL)isIncoming;

-(void)networkWillConnectToHost:(NSString *)host onPort:(NSUInteger)port;

-(void)networkDidConnectToHost:(NSString *)host onPort:(NSUInteger)port;

-(void)networkFailedToConnectToHost:(NSString *)host onPort:(NSUInteger)port;

-(void)networkDidDisconnectFromHost:(NSString *)host onPort:(NSUInteger)port;

-(void)networkDidReceiveErrorWithHost:(NSString *)host andPort:(NSUInteger)port;

@end

