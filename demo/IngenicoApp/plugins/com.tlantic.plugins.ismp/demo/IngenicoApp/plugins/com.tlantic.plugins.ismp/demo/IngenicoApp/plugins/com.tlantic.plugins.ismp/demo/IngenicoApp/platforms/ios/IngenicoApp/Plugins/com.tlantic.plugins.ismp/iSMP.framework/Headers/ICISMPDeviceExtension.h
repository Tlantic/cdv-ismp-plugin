//
//  ICISMPDeviceExtension.h
//  iSMP Library
//
//  Created by Boris LECLERE on 7/18/12.
//  Copyright (c) 2012 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ICISMPDevice.h"

@protocol ICISMPDeviceExtensionDelegate;

@interface ICISMPDeviceExtension : ICISMPDevice
{
	NSMutableArray * m_SendList;
}

@property(nonatomic, assign) id<ICISMPDeviceDelegate, ICISMPDeviceExtensionDelegate> delegate;

-(unsigned int)SendData:(NSData *)Data;

-(bool)SendDataAsync:(NSData *)Data;

-(unsigned int)SendString:(NSString *)String;

-(bool)SendStringAsync:(NSString *)String;

// Reception
@property(getter = TotalNbFrameReceived) unsigned int m_TotalNbFrameReceived;

// Reception Property
@property(getter = ReceiveBufferSize, setter = SetReceiveBufferSize:) unsigned int m_ReceiveBufferSize;

// Sent
@property(getter = TotalNbFrameSent) unsigned int m_TotalNbFrameSent;

@end

@protocol ICISMPDeviceExtensionDelegate <ICISMPDeviceDelegate>

//@required

-(void)didReceiveData:(NSData *)Data fromICISMPDevice:(ICISMPDevice *)Sender;

@optional

-(void)willReceiveData:(ICISMPDevice *)Sender;

-(void)willSendData:(ICISMPDevice *)Sender;

-(void)didSendData:(NSData *)Data withNumberOfBytesSent:(unsigned int) NbBytesSent fromICISMPDevice:(ICISMPDevice *)Sender;

@end
