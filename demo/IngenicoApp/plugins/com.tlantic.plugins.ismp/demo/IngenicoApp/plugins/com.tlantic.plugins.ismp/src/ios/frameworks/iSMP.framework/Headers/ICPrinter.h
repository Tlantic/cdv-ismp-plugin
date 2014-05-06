//
//  ICPrinter.h
//  iSMP Library
//
//  Created by Christophe Fontaine on 22/06/10.
//  Copyright 2010 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>
#import "ICISMPDevice.h"

@protocol ICPrinterDelegate;

@interface ICPrinter : ICISMPDevice {
	
	NSUInteger			  _microlineCount;                      /**< The number of received microlines during a print session */
	
	NSUInteger			  _microlineNumber;                     /**< The microline number sent by the SPM (contains the microline number in the first 3 bytes, and the printing session in the last byte) */
}

+(id)sharedPrinter;

@property(nonatomic, assign) id<ICISMPDeviceDelegate,ICPrinterDelegate> delegate;

@end

#pragma mark ICPrinterDelegate protocol

@protocol ICPrinterDelegate

@optional

-(void)receivedPrinterData:(NSData *)data;

-(void)receivedPrinterData:(NSData *)data numberOfLines:(NSInteger)count;

-(void)printingDidEndWithRowNumber:(NSUInteger)count;

@end

#pragma mark -
