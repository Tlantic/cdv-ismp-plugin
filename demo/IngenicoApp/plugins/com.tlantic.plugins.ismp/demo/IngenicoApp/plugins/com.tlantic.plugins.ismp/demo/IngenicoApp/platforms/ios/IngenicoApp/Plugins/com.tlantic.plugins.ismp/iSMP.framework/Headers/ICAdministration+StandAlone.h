//
//  ICAdministration+StandAlone.h
//  iSMP Library
//
//  Created by Christophe Fontaine on 23/02/2011.
//  Copyright 2010 Ingenico. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ICISMPDevice.h"
#import "ICAdministration.h"

#pragma mark ICAdministration Constants & Structures

typedef struct {
	unsigned short	posNumber;                              /**< The POS number (should be within the range [0 - 255]) */
	char			amount[8];                              /**< The amount for the transaction (left completed with '0'). If the ISO2 track needs to be read, amount should be '0' */
	unsigned char	specificField;                          /**< This field is always set to '1', meaning that PAN (for a card) or the CMC7 field (for a cheque) is asked for */
	unsigned char	accountType;                            /**< The kind of payment the POS wishes to use */
	unsigned char	transactionType;                        /**< The type of transaction */
	char			currency[3];                            /**< The currency code in ISO4217 format */
	char			privateData[10];                        /**< Application specific data to be passed to payment application */
	unsigned char	delay;                                  /**< Indicates if the SPM should answer immediately or at the end of the transaction ('0' for immediate answer and '1' for a reported answer) */
	unsigned char	authorization;                          /**< The authorization that the POS asks the SPM for */
} ICTransactionRequest;

typedef struct {
	unsigned short	posNumber;                              /**< The same as in the request */
	unsigned char	operationStatus;                        /**< The status of the payment process */
	char			amount[8];                              /**< The real amount used for the transaction */
	unsigned char	accountType;                            /**< The account type used for the transaction. Should be one of the enumerations defined within ICTransactionAccountType */
	char			currency[3];                            /**< The currency code in ISO4217 format (the same as in the transaction request) */
	char			privateData[10];                        /**< Application specific data to be passed to POS application */
	char			PAN[19];                                /**< The primary account number */
	char			cardValidity[4];                        /**< The card's validity date */
	char			authorizationNumber[9];                 /**< The authorization number */
	char			CMC7[35];                               /**< The CMC7 track */
	char			ISO2[38];                               /**< The ISO2 track */
	char			FNCI[10];                               /**< FNCI */
	char			guarantor[10];                          /**< The guarantor */
    char            zoneRep[55];                            /**<  */
    char            zonePriv[10];                           /**<  */
} ICTransactionReply;

typedef struct {
	NSUInteger		screenX;                                /**< The X position of the screen */
	NSUInteger		screenY;                                /**< The Y position of the screen */
	NSUInteger		screenWidth;                            /**< The Width of the capture screen */
	NSUInteger		screenHeight;                           /**< The Height of the capture screen */
	NSUInteger		userSignTimeout;                        /**< The timeout for the signature to be captured and sent to the iSMP */
} ICSignatureData;

#pragma mark -
@protocol ICAdministrationDelegate;

@interface ICAdministration (StandAlone)

-(void)doTransaction:(ICTransactionRequest)request;

-(void)doTransaction:(ICTransactionRequest)request withData:(NSData *)extendedData andApplicationNumber:(NSUInteger)appNum;

-(void)setDoTransactionTimeout:(NSUInteger)timeout;

-(NSUInteger)getDoTransactionTimeout;

-(BOOL)submitSignatureWithImage:(UIImage *)image;

-(BOOL)sendMessage:(NSData *)data;

@end

#pragma mark ICAdministrationDelegateStandAlone

@protocol ICAdministrationStandAloneDelegate <ICAdministrationDelegate>
@optional

-(void)didSpmRespondedToDoTransaction:(BOOL)response withParameters:(ICTransactionReply)transactionReply __attribute__((deprecated));

-(void)transactionDidEndWithTimeoutFlag:(BOOL)replyReceived result:(ICTransactionReply)transactionReply andData:(NSData *)extendedData;

-(void)shouldDoSignatureCapture:(ICSignatureData)signatureData;

-(void)signatureTimeoutExceeded;

-(void)messageReceivedWithData:(NSData *)data;

-(void)shouldPrintText:(NSString *)text withFont:(UIFont *)font andAlignment:(UITextAlignment)alignment;

-(void)shouldPrintText:(NSString *)text withFont:(UIFont *)font alignment:(UITextAlignment)alignment XScaling:(NSInteger)xFactor YScaling:(NSInteger)yFactor underline:(BOOL)underline;

-(void)shouldPrintText:(NSString *)text withFont:(UIFont *)font alignment:(UITextAlignment)alignment XScaling:(NSInteger)xFactor YScaling:(NSInteger)yFactor underline:(BOOL)underline bold:(BOOL)bold;

-(void)shouldPrintImage:(UIImage *)image;

-(void)shouldFeedPaper;

-(void)shouldCutPaper;

-(void)printingDidEnded;

@end

#pragma mark -
