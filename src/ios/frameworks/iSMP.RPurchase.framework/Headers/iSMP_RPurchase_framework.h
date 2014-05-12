//
//  iSMP_RPurchase_framework.h
//  iSMP.RPurchase.framework
//
//  Created by administrator on 25/01/13.
//  Copyright (c) 2013 administrator. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <iSMP/iSMP.h>
#import <iSMP/ICAdministration+StandAlone.h>
#import "XMLWriter.h"


@interface iSMP_RPurchase_framework : NSObject <ICISMPDeviceExtensionDelegate, ICAdministrationStandAloneDelegate>

@property (nonatomic, retain) NSMutableData * receivedData;


-(int) fDll_RP_TerminalStatus:(NSString*) cCommandVersion cECRModel:(NSString*) cECRModel cECRSpecVersion:(NSString*) cECRSpecVersion xmlWriter: (XMLWriter*)_xmlWriter iMaxXMLResponseSize:(NSInteger) iMaxXMLResponseSize;

-(int) fDll_RP_Purchase:(NSString*) cCommandVersion cReceiptCode:(NSString*) cReceiptCode cControlNumber:(NSString*) cControlNumber cAmount:(NSString*) cAmount xmlWriter: (XMLWriter*)_xmlWriter iMaxXMLResponseSize:(NSInteger) iMaxXMLResponseSize;

-(int) fDll_RP_OpenAccountingPeriod:(NSString*) cCommandVersion cReceiptCode:(NSString*) cReceiptCode cControlNumber:(NSString*) cControlNumber xmlWriter: (XMLWriter*)_xmlWriter iMaxXMLResponseSize:(NSInteger) iMaxXMLResponseSize;

-(int) fDll_RP_CloseAccountingPeriod:(NSString*) cCommandVersion cReceiptCode:(NSString*) cReceiptCode cControlNumber:(NSString*) cControlNumber xmlWriter: (XMLWriter*)_xmlWriter iMaxXMLResponseSize:(NSInteger) iMaxXMLResponseSize;

-(int) fDll_RP_Refund:(NSString*) cCommandVersion cReceiptCode:(NSString*) cReceiptCode cControlNumber:(NSString*) cControlNumber cAmount:(NSString*) cAmount cOriginalPOSIdent:(NSString*) cOriginalPOSIdent cOriginalReceiptDate:(NSString*) cOriginalReceiptDate cOriginalReceiptTime:(NSString*) cOriginalReceiptTime xmlWriter: (XMLWriter*)_xmlWriter iMaxXMLResponseSize:(NSInteger) iMaxXMLResponseSize;

-(int) ProcessSendData: (NSString *) cOut;
//-(int) ProcessReceiveData: (NSString *) cOin;

//-(NSString*) ProcessReceiveData: (BOOL) bWaitACK iRet:(int*) iRet;
-(NSString*) ProcessReceiveData: (BOOL) bWaitACK iRet:(int*)iRet;


@end

//Hex Dump category that extends NSData. This interface is implmented inside iSMP library but is private.
@interface NSData ()

-(NSString *)hexDump;


@end


