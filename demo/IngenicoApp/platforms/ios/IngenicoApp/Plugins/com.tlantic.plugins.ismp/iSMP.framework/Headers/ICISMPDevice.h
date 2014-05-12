//
//  ICISMPDevice.h
//  iSMP Library
//
//  Created by Christophe Fontaine on 21/06/10.
//  Copyright 2010 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>

@protocol ICISMPDeviceDelegate;

@interface ICISMPDevice : NSObject <NSStreamDelegate> {
	// external accessory management
	NSString				* protocolName;                             /**< IAP protocol name that the @ref ICISMPDevice use for communication with the SPM */
	EASession				* _cradleSession;                           /**< The IAP session opened by the @ref ICISMPDevice to the SPM */
	BOOL					  isAvailable;                              /**< SPM connection state */
	
	NSOutputStream			* outStream;                                /**< Serial output stream */
	NSInputStream			* inStream;                                 /**< Serial input stream */
	
	// iSMP Messages Processing
	NSRecursiveLock			* _inDataLock;                              /**< Used to synchronize access to received data buffer */
	NSMutableData			* _inStreamData;                            /**< Data received from SPM */
	NSMutableDictionary		* _actionLookupTable;                       /**< Map TLV tags to selectors */
	BOOL					  mustProcessReceivedDataOnCurrentThread;   /**< Indicates whether data should be processed in the communication thread (NO by default, messages are processed on the main thread) */
	NSArray					* _spmResponseTags;                         /**< List of all SPM's response Tags on a given channel */
	
	NSOperationQueue		* _requestOperationQueue;                   /**< This operation queue serializes the send operations to the SPM */
	
	id<ICISMPDeviceDelegate>	  _delegate;                                /**< Delegate of the @ref ICISMPDevice Class */
	
	NSCondition				* _waitingForResultCondition;               /**< Condition variable  used by subclassed of @ref ICISMPDevice to synchronize their calls */
	NSLock					* _waitingForResultLock;                    /**< Lock used to synchronize the methods of subclasses of @ref ICISMPDevice */
	id						 _requestResult;                            /**< Variable used to store the results of synchronous commands of subclasses of @ref ICISMPDevice. The _waitingForResultCondition should be signalled after this variable is set */
	NSMutableArray			* _pendingRequests;                         /**< Array of requests sent but that were not responded to by the terminal */
	
	SEL _processReceivedDataSEL;
	IMP _processReceivedDataIMP;
	SEL _simulateEventBytesAvailableforStreamSEL;	
}

@property (nonatomic, readonly) NSString    *protocolName;
@property (readonly) BOOL isAvailable;

@property (readonly) NSInputStream   *inStream;

@property (readonly) NSOutputStream  *outStream;

@property(nonatomic, assign) id<ICISMPDeviceDelegate> delegate;

//------------------------------------------------------------------------------

-(id)initWithProtocolString:(NSString*)protocolString;

-(id)initWithStreamIn:(NSInputStream*)inStream
		 andStreamOut:(NSOutputStream*)outStream;

// The following methods reads values returned in the authentication process
+(BOOL) isAvailable;

+(NSString *)getRevisionString;

+(NSString *)getVersionString;

+(NSString*) serialNumber;

+(NSString*) modelNumber;

+(NSString*) firmwareRevision;

+(NSString*) hardwareRevision;

+(NSString*) name;

enum SEVERITY_LOG_LEVELS {
	SEV_DEBUG=0,                                        /**< Debug Message */
	SEV_INFO,                                           /**< Information Message */
	SEV_TRACE,                                          /**< Trace Message */
	SEV_WARN,                                           /**< Warning Message */
	SEV_ERROR,                                          /**< Error Message */
	SEV_FATAL,                                          /**< Fatal Error Message */
	SEV_UNKOWN                                          /**< Unknown-Severity Message */
};

+(NSString*) severityLevelString:(int)level;

+(const char*) severityLevelStringA:(int)level;

@end

#pragma mark -
@protocol ICISMPDeviceDelegate
@optional

-(void)accessoryDidConnect:(ICISMPDevice*)sender;

-(void)accessoryDidDisconnect:(ICISMPDevice *)sender;

@optional

// log : you may implement either logEntry / logSerialData or implement the device specific --> only one call is made.

-(void) logEntry:(NSString*)message withSeverity:(int)severity;

-(void) logSerialData:(NSData*)data incomming:(BOOL)isIncoming;

@end
