//
//  ICTransaction.h
//  iSMP Library
//
//  Created by Christophe Fontaine on 21/06/10.
//  Copyright 2010 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ICISMPDeviceExtension.h"

@interface ICTransaction : ICISMPDeviceExtension {
	NSMutableSet	*streamObjects;                             /**< Delegates of ICTransaction (not used anymore since the class supports only one delegate now) */
}

@property (nonatomic, assign) id<ICISMPDeviceDelegate, ICISMPDeviceExtensionDelegate> delegate;

+(id) sharedChannel;

-(id)init;

-(void)forwardStreamEvents:(BOOL)enabled to:(id<NSStreamDelegate>)anObject;

@property (nonatomic, readonly) id streamEventDelegate;

@end
