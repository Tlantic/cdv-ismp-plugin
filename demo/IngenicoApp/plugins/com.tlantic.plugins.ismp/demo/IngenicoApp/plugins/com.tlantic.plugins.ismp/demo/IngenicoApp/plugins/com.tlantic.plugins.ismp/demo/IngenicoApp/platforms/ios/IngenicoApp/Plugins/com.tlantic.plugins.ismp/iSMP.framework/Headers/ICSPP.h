//
//  ICSPP.h
//  iSMP Library
//
//  Created by Hichem Boussetta on 24/05/12.
//  Copyright (c) 2012 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ICISMPDeviceExtension.h"

@interface ICSPP : ICISMPDeviceExtension

+(ICSPP *)sharedChannel;

@property (nonatomic, assign) id<ICISMPDeviceDelegate, ICISMPDeviceExtensionDelegate> delegate;

@end
