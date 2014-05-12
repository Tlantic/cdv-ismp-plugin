//
//  ICAdministration.h
//  iSMP Library
//
//  Created by Hichem Boussetta on 19/07/10.
//  Copyright 2010 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ICISMPDevice.h"

typedef struct {
	NSInteger		serialNumber;                       /**< The device's serial number */
	NSInteger		reference;                          /**< The device's software reference number */
	char			protocol[20];                       /**< The payment protocol used by the device */
} ICDeviceInformation;

enum eICDeviceKeys {
	ICNum0			= '0',                              /**< Numeric Key 0 */
	ICNum1			= '1',                              /**< Numeric Key 1 */
	ICNum2			= '2',                              /**< Numeric Key 2 */
	ICNum3			= '3',                              /**< Numeric Key 3 */
	ICNum4			= '4',                              /**< Numeric Key 4 */
	ICNum5			= '5',                              /**< Numeric Key 5 */
	ICNum6			= '6',                              /**< Numeric Key 6 */
	ICNum7			= '7',                              /**< Numeric Key 7 */
	ICNum8			= '8',                              /**< Numeric Key 8 */
	ICNum9			= '9',                              /**< Numeric Key 9 */
	ICKeyDot		= '.',                              /**< Dot Key */
	ICKeyPaperFeed	= 0x07,                             /**< Paper Feed Key */
	ICKeyGreen		= 0x16,                             /**< Green Key */
	ICKeyRed		= 0x17,                             /**< Red Key */
	ICKeyYellow		= 0x18,                             /**< Yellow Key */
	ICKeyF1			= 0x19,                             /**< F1 Key */
	ICKeyF2			= 0x20,                             /**< F2 Key */
	ICKeyF3			= 0x21,                             /**< F3 Key */
	ICKeyF4			= 0x22,                             /**< F4 Key */
	ICKeyUp			= 0x23,                             /**< UP Key */
	ICKeyDown		= 0x24,                             /**< Down Key */
	ICKeyOK			= 0x25,                             /**< OK Key */
	ICKeyC			= 0x26,                             /**< C Key */
	ICKeyF			= 0x28,                             /**< F Key */
};

enum eICDeviceSoftwareComponentType {
	ICDeviceApplication = 0,                            /**< Application */
	ICDeviceLibrary,                                    /**< Library */
	ICDeviceDriver,                                     /**< Driver */
	ICDeviceParameter                                   /**< Parameter File */
};

typedef enum {
    ISMP_Result_SUCCESS = 0,                                   /**< The call succeeded */
    ISMP_Result_ISMP_NOT_CONNECTED,                            /**< The call failed because the iSMP is not connected */
    ISMP_Result_Failure,                                       /**< The call failed for an unknown reason */
    ISMP_Result_TIMEOUT,                                       /**< The call failed because the timeout was reached. No response was received from the iSMP */

    //Key Injection Error Codes
    ISMP_Result_KEY_INJECTION_ABORTED,                         /**< Key Injection Aborted */
    ISMP_Result_KEY_INJECTION_KEY_NOT_FOUND,                   /**< Key Injection failed because no key was found on the server */
    ISMP_Result_KEY_INJECTION_INVALID_HTTP_FILE,               /**< Key Injection failed because the returned HTTP file is invalid */
    ISMP_Result_KEY_INJECTION_INVALID_HTTP_RESPONSE,           /**< Key Injection failed because the returned HTTP response is not 200 OK */
    ISMP_Result_KEY_INJECTION_INVALID_HTTP_HEADER,             /**< Key Injection failed because the returned HTTP header is invalid */
    ISMP_Result_KEY_INJECTION_SSL_NEW_ERROR,                   /**< Key Injection failed because of an SSL initialization failure */
    ISMP_Result_KEY_INJECTION_SSL_CONNECT_ERROR,               /**< Key Injection failed because the connection to the server can not be established */
    ISMP_Result_KEY_INJECTION_SSL_READ_ERROR,                  /**< Key Injection failed because of an SSL reading error */
    ISMP_Result_KEY_INJECTION_SSL_WRITE_ERROR,                 /**< Key Injection failed because of an SSL writing error */
    ISMP_Result_KEY_INJECTION_SSL_PROFILE_ERROR,               /**< Key Injection failed because of an SSL profile error */
    ISMP_Result_KEY_INJECTION_INTERNAL_ERROR,                  /**< Key Injection failed because of an internal error */

    ISMP_Result_ENCRYPTION_KEY_NOT_FOUND,                      /**< The encryption key does not exist within the iSMP */
    ISMP_Result_ENCRYPTION_KEY_INVALID,                        /**< The encryption key is not valid */
    ISMP_Result_ENCRYPTION_DLL_MISSING                         /**< The encryption DLL is missing within the iSMP */
} iSMPResult;

@interface ICSoftwareComponent : NSObject

@property (nonatomic, readonly) NSString * name;

@property (nonatomic, readonly) NSString * version;

@property (nonatomic, readonly) NSString * crc;

@property (nonatomic, readonly) NSUInteger type;

@end

@protocol ICAdministrationDelegate;

@interface ICAdministration : ICISMPDevice {
	
	NSMutableArray				* _printerJobs;                             /**< List of in progress printer jobs */

	BOOL						  _isWaitingForSignature;                   /**< Boolean value indicating whether ICAdministration is waiting for a signature to be returned by the application*/
	
	NSDictionary				* _fontTable;                               /**< Table of fonts used for printing */
	
	BOOL						_shouldUpdatePowerManagementSettings;       /**< Boolean value indicating whether the power management settings should be updated */

    NSUInteger                  _doTransactionTimeout;                      /**< Timeout value used for @ref doTransaction */
}

+(id) sharedChannel;

@property (nonatomic, assign) id<ICISMPDeviceDelegate,ICAdministrationDelegate> delegate;

-(iSMPResult)open;

-(void)close;

#pragma mark Power Management

@property (nonatomic, readonly) NSInteger backlightTimeout;

@property (nonatomic, readonly) NSInteger suspendTimeout;

@property (nonatomic, readonly) NSInteger batteryLevel;

-(BOOL)setBacklightTimeout:(NSUInteger)backlightTimeout andSuspendTimeout:(NSUInteger)suspendTimeout;

#pragma mark -
#pragma mark iSMP Management

-(BOOL)setDate;

-(NSDate *)getDate;

-(BOOL)isIdle;

-(ICDeviceInformation)getInformation;

-(void)reset:(NSUInteger)resetInfo;

-(BOOL)simulateKey:(NSUInteger)key;

-(NSArray *)getSoftwareComponents;

-(BOOL)startRemoteDownload;

-(BOOL)updateKeyWithServerIP:(NSString *)ip andPort:(NSUInteger)port __attribute__((deprecated));

-(iSMPResult)updateEncryptionKeyWithServerIP:(NSString *)ip andPort:(NSUInteger)port;

-(iSMPResult)validateEncryptionKey;

-(iSMPResult)eraseEncryptionKey;

-(BOOL)setServerConnectionState:(BOOL)connectionState;

#pragma mark -

@end

#pragma mark ICAdministrationDelegate

@protocol ICAdministrationDelegate
@optional

-(void)shouldScheduleWakeUpNotification:(id)wakeUpNotification;

-(void)confLogEntry:(NSString*)message withSeverity:(int)severity;

-(void)confSerialData:(NSData*)data incoming:(BOOL)isIncoming;

@end

#pragma mark -
