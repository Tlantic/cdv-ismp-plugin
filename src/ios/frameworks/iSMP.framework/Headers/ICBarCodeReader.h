//
//  ICBarCodeReader.h
//  iSMP Library
//
//  Created by Christophe Fontaine on 21/06/10.
//  Copyright 2010 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ICISMPDevice.h"

#pragma mark -
#pragma mark ICBarCodeReaderDelegate

@protocol ICBarCodeReaderDelegate
@required

-(void)barcodeData:(id)data ofType:(int)type; // data : NSString*, type: eICBarCodeSymbologies

-(void)configurationRequest;

@optional

-(void)unsuccessfulDecode;

-(void)triggerPulled;

-(void)triggerReleased;

-(void)onScanMiscEvent:(int)eventCode; // other scan events

-(void)onConfigurationApplied __attribute__((deprecated));

- (void)barcodeLogEntry:(NSString *)logEntry withSeverity:(int)severity;

- (void)barcodeSerialData:(NSData *)data incoming:(BOOL)isIncoming;

@end

#pragma mark -

@interface ICBarCodeReader : ICISMPDevice {
	NSMutableArray					*multiCodeStrings;
	
	NSCondition						*iscpResultReceived;
	NSCondition						*iscpReplyReceived;
	NSCondition						*scannerStartedCondition;
	
	NSData							*lastResultData;
	NSOperationQueue				*operationQueue;
	
	int								bufferingSetupWrites;
	NSMutableArray					*setupWriteList;
	
@private	
	// cached data
	NSInteger						currentScanMode;
	NSInteger						multiScan;	
	NSInteger						triggerEnabled;
	NSInteger						turboModeEnabled;
	NSInteger						currentImagerMode;
	NSString						*firmwareVersion;
    BOOL                            shouldRequestConfiguration;
}

#pragma mark BarcodeConstants

#pragma mark -

@property(nonatomic, assign) id<ICISMPDeviceDelegate, ICBarCodeReaderDelegate> delegate;

@property(nonatomic, assign) int iscpRetryCount;

+(id)sharedICBarCodeReader;

-(void)startScan;

-(void)stopScan;

#pragma mark Configuration related functions

-(void)bufferWriteCommands;

-(void)unbufferSetupCommands;

-(BOOL)shouldApplyDefaultConfiguration __attribute__((deprecated));     //NOT REQUIRED ANYMORE

-(void)applyDefaultConfiguration __attribute__((deprecated)); //NOT REQUIRED ANYMORE

-(void)configureBarCodeReaderMode:(int)mode; // for the mode, refers to eICBarCode_ScanMode

-(int)getBarCodeReaderMode; // see eICBarCode_ScanMode

+(BOOL)isSymbologySupported:(int)type; // type: eICBarCodeSymbologies

-(void)enableSymbologies:(int *)symbologies symbologyCount:(int)count; // symbologies: int[] containing eICBarCodeSymbologies

-(void)enableSymbology:(int)type enabled:(BOOL)enabled; // type: eICBarCodeSymbologies

-(BOOL)isSymbologyEnabled:(int)type; // type: eICBarCodeSymbologies

-(void)enableTransmitUPCABarcodesAsEAN13:(BOOL)enabled;

-(void)enableTransmitUPCEBarcodesAsUPCA:(BOOL)enabled;

-(void)enableTransmitEAN8BarcodesAsEAN13:(BOOL)enabled;

enum eICBarCodeSymbologies {
	ICBarCode_Unknown = -1,                     /**< Unknown Symbology */
	ICBarCode_AllSymbologies	= 0,            /**< All Symbologies */
	
	ICBarCode_EAN13,                            /**< EAN13 Barcode Type */
	ICBarCode_EAN8,                             /**< EAN8 Barcode Type */
	ICBarCode_UPCA,                             /**< UPCA Barcode Type */
	ICBarCode_UPCE,                             /**< UPCE Barcode Type */
	
	ICBarCode_EAN13_2,                          /**< EAN13_2 Barcode Type */
	ICBarCode_EAN8_2,                           /**< EAN8_2 Barcode Type */
	ICBarCode_UPCA_2,                           /**< UPCA_2 Barcode Type */
	ICBarCode_UPCE_2,                           /**< UPCE_2 Barcode Type */
	
	ICBarCode_EAN13_5,                          /**< EAN13_5 Barcode Type */
	ICBarCode_EAN8_5,                           /**< EAN8_5 Barcode Type */
	ICBarCode_UPCA_5,                           /**< UPCA_5 Barcode Type */
	ICBarCode_UPCE_5,                           /**< UPCE_5 Barcode Type */
	
	ICBarCode_Code39,                           /**< Code39 Barcode Type */
	// id 14 reserved
	ICBarCode_Interleaved2of5 = 15,             /**< Interleaved2of5 Barcode Type */
	ICBarCode_Standard2of5,                     /**< Standard2of5 Barcode Type */
	ICBarCode_Matrix2of5,                       /**< Matrix2of5 Barcode Type */
	
	//id 18 reserved
	ICBarCode_CodaBar = 19,                     /**< CodeBar Barcode Type */
	ICBarCode_AmesCode,                         /**< AmesCode Barcode Type */
	ICBarCode_MSI,                              /**< MSI Barcode Type */
	ICBarCode_Plessey,                          /**< Pleassey Barcode Type */
	
	ICBarCode_Code128,                          /**< Code128 Barcode Type */
	ICBarCode_Code16K,                          /**< Code16k Barcode Type */
	ICBarCode_93,                               /**< Code93 Barcode Type */
	ICBarCode_11,                               /**< Code11 Barcode Type */

	ICBarCode_Telepen,                          /**< Telepen Barcode Type */
	ICBarCode_Code49,                           /**< Code49 Barcode Type */
	ICBarCode_Code39_ItalianCPI,                /**< Code39_ItalianCPI Barcode Type */
	
	ICBarCode_CodaBlockA,                       /**< CodeBlockA Barcode Type */
	ICBarCode_CodaBlockF,                       /**< CodaBlockF Barcode Type */
	
	//id 32 reserved
	ICBarCode_PDF417 = 33,                      /**< PDF417 Barcode Type */
	ICBarCode_GS1_128, // Replace EAN128        /**< GS1_128 Barcode Type */
	ICBarCode_ISBT128,                          /**< ISBT128 Barcode Type */
	ICBarCode_MicroPDF,                         /**< MicroPDF Barcode Type */

    ICBarCode_GS1_DataBarOmni,                  /**< GS1_DataBarOmni Barcode Type */
    ICBarCode_GS1_DataBarLimited,               /**< GS1_DataBarLimited Barcode Type */
    ICBarCode_GS1_DataBarExpanded,              /**< GS1_DataBarExpanded Barcode Type */

	ICBarCode_DataMatrix,                       /**< DataMatrix Barcode Type */
    ICBarCode_QRCode,                           /**< QRCode Barcode Type */
	ICBarCode_Maxicode,                         /**< Maxicode Barcode Type */

    ICBarCode_Aztec = 0x4A,                     /**< Aztec Barcode Type */
	
	
	ICBarCode_MaxIndex                          /**< MaxIndex Barcode Type */
};

enum eICBarCode_ScanMode {
	ICBarCodeScanMode_SingleScan,               /**< Single-Scan Mode */
	ICBarCodeScanMode_MultiScan                 /**< Multi-Scan Mode */
};

enum eICBarCode_ImagerMode {
	ICBarCodeImagerMode_1D,                     /**< 1D */
	ICBarCodeImagerMode_1D2D,                   /**< 1D and 2D standard */
	ICBarCodeImagerMode_1D2D_bright,            /**< 1D and 2D bright environment */
	ICBarCodeImagerMode_1D2D_reflective         /**< 11D and 2D reflective surface */
};

#pragma mark -
#pragma mark Imager Configuration
-(void)configureImagerMode:(int)mode; // mode : refers to eICBarCode_ImagerMode

-(void)enableAimerFlashing:(BOOL)enabled;

enum eICBarCode_IlluminationMode {
	aimerAndIlluminiationLeds,              /**< Enable both the aimer and the leds */
	aimerOnly,                              /**< Enable only the aimer */
	illuminationLedsOnly,                   /**< enable only the leds */
	noIllumination                          /**< Disable illumination */
};

-(void)illuminationMode:(int)mode; // mode: eICBarCode_IlluminationMode

-(void)illuminationLevel:(int)level;

-(void)lightingGoal:(int)goal;

enum eICBarCode_LightingMode {
	illuminiationLEDPriority,       /**< Shorter exposure time  */
	aperturePriority                /**< Use aperture priority if you have a shiny bar code label */
};

-(void)lightingMode:(int)priorityType; // priorityType: eICBarCode_LightingMode

-(BOOL)aimerFlashing;

-(int)illuminiationMode;

-(int)illuminationLevel;

-(int)lightingGoal;

-(int)lightingMode;

#pragma mark -
#pragma mark Power Mgmt

-(int)powerOn;

enum eICBarCode_PowerOnStatus {
    ICBarCodeReader_PowerOnSuccess,             /**< The powerOn command was successful */
    ICBarCodeReader_PowerOnFailed,              /**< The powerOn command failed due to a synchronization problem */
    ICBarCodeReader_PowerOnDenied               /**< The powerOn command was forbidden. This happens when the device is charging on the craddle */
};

-(void)powerOff;

-(void)softReset;

-(void)setScanTimeout:(int)timeout; // Timeout in second, from 0 (timeout disabled) to 60 seconds

-(int)getScanTimeout; // -1 if an error occured (timeout)

#pragma mark -
#pragma mark Misc

// Misc
+(NSString*)symbologyToText:(int)type; // type: eICBarCodeSymbologies

-(void)goodScanBeepEnable:(BOOL)enabled;
-(void)setBeep:(BOOL)enabled frequency:(int)frequency andLength:(int)length;

-(void)playBeep:(int)frequency during:(int)onTimeMs andWait:(int)offTimeMs;

-(BOOL)enableTrigger:(BOOL)enabled;

-(BOOL)isTriggerEnabled;

-(NSString *)getFirmwareVersion; // returns the barcode firmware version

-(NSString *)scannerName;

-(NSString *)scannerModel;

#pragma mark -

@end

