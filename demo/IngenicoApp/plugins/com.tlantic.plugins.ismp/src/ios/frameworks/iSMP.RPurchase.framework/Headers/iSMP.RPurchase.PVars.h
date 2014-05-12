//
//  iSMP.RPurchase.PVars.h
//  iSMP.RPurchase.framework
//
//  Created by administrator on 31/01/13.
//  Copyright (c) 2013 administrator. All rights reserved.
//

#ifndef iSMP_RPurchase_framework_iSMP_RPurchase_PVars_h
#define iSMP_RPurchase_framework_iSMP_RPurchase_PVars_h

const int STX = 2;
const int ETX = 3;
const int ACK = 6;
const int NAK = 21;

NSString *const STR_STX = @"\x02";
NSString *const STR_ETX = @"\x03";
NSString *const STR_ACK = @"\x06";
NSString *const STR_NAK = @"\x21";

const int DEFAULT_SPM_PORT = 9;
const int DEFAULT_SPM_SPEED = 2400;
const int DEFAULT_COM_READ_TIMEOUT = 60;
const int DEFAULT_COM_READ_KO = -2;
const int DEFAULT_COM_READ_ACK_TIMEOUT = 3 * 1000;
const int DEFAULT_COM_WRITE_TIMEOUT = 500;
const int DEFAULT_COM_WRITE_KO = -3;
const int DEFAULT_COM_WRITE_ACK_KO = -4;
const int MAX_RETRIES = 3;
const int RET_CODE_ERROR_LRC = -603;
const int RET_CODE_STATUS_NOTIFICATION = -304;
const int RET_CODE_ERROR_NAK = -604;

NSString *const ELEMENT_COMMAND_RESPONSE = @"CommandResponse";
NSString *const ELEMENT_RESPONSE_HEADER = @"ResponseHeader";
NSString *const ELEMENT_RESPONSE_BODY = @"ResponseBody";
NSString *const ELEMENT_TICKET_DATA = @"TicketData";
NSString *const ELEMENT_REMOTE_PURCHASE = @"RemotePurchase";
NSString *const ATTRIBUTE_VERSION = @"version";

NSString *A038_POSITIVE_RESPONSE = @"000";
NSString *STATUS_NOTIFICATION = @"M001";
NSString *A001;  const int LEN_A001 = 8;  NSString *const ELEMENT_A001 = @"POSIdentification";
NSString *A016;  const int LEN_A016 = 2;
NSString *A030;  const int LEN_A030 = 4;  NSString *const ELEMENT_A030 = @"CommandCode";

const int LEN_A029 = 3;  NSString *const ELEMENT_A029 = @"MessageNumber";
const int LEN_A031 = 3;  NSString *const ELEMENT_A031 = @"AccountPeriodNumber";
const int LEN_A032 = 3;  NSString *const ELEMENT_A032 = @"TransactionSequenceNumber";
const int LEN_A037 = 14;  NSString *const ELEMENT_A037 = @"ResponseDateTime";
const int LEN_A063 = 8;  NSString *const ELEMENT_A063 = @"AmountConverted";
const int LEN_A056 = 20;  NSString *const ELEMENT_A056 = @"PAN";
const int LEN_A092 = 20;  NSString *const ELEMENT_A092 = @"SanAuthorisation";
const int LEN_A059 = 20;  NSString *const ELEMENT_A059 = @"IssuerName";
const int LEN_A090 = 1;  NSString *const ELEMENT_A090 = @"ReceiptFormat";
const int LEN_A094 = 20;  NSString *const ELEMENT_A094 = @"RetailerIdentification";
const int LEN_A095 = 20;  NSString *const ELEMENT_A095 = @"AmountText";
const int LEN_A149 = 1;  NSString *const ELEMENT_A149 = @"CommissionSignal";
const int LEN_A102 = 8;  NSString *const ELEMENT_A102 = @"CommissionValue";
const int LEN_A028 = 10;  NSString *const ELEMENT_A028 = @"ShopNumber";

NSString *A034 = @"0000000000000000000000000000000000000";
const int LEN_A038 = 3;  NSString *const ELEMENT_A038 = @"ResponseCode";
NSString *A040;  const int LEN_A040 = 8;
const int LEN_A041 = 9;  NSString *const ELEMENT_A041 = @"RetailerFiscalNumber";
const int LEN_A043 = 20;  NSString *const ELEMENT_A043 = @"RetailerName1";
const int LEN_A044 = 20;  NSString *const ELEMENT_A044 = @"RetailerName2";
const int LEN_A045 = 20;  NSString *const ELEMENT_A045 = @"RetailerAddress1";
const int LEN_A046 = 20;  NSString *const ELEMENT_A046 = @"RetailerAddress2";
const int LEN_A047 = 20;  NSString *const ELEMENT_A047 = @"POSText";
NSString *A061;  const int LEN_A061 = 8;
const int LEN_A077 = 16;  NSString *const ELEMENT_A077 = @"OperatorMessage";
const int LEN_A085 = 10;  NSString *const ELEMENT_A085 = @"ErrorClass";
const int LEN_A104 = 4;
NSString *A105 = @"9782";
const int LEN_A106 = 6;
const int LEN_A109 = 1;
NSString *A159;  const int LEN_A159 = 3;  NSString *const ELEMENT_A159 = @"ControlNumber";
NSString *A160;  const int LEN_A160 = 1;  NSString *const ELEMENT_A160 = @"ReceiptCode";
NSString *A162;  const int LEN_A162 = 2;

NSString *I101 = @"0112";  const int LEN_I101 = 4;// Valor por defecto 01.12

NSString *E188;  const int LEN_E188 = 6;
const int LEN_E189 = 2;  NSString *const ELEMENT_E189 = @"TransactionType";
const int LEN_E034 = 2;  NSString *const ELEMENT_E034 = @"AuthorisationResponseCode";
const int LEN_E024 = 2;  NSString *const ELEMENT_E024 = @"AppliPrimaryAccountNumber(PAN)SeqNumber";
const int LEN_E029 = 5;  NSString *const ELEMENT_E029 = @"ApplicationTransactionCounter";
const int LEN_E064 = 20;  NSString *const ELEMENT_E064 = @"DedicatedFile(DF)Name";
const int LEN_E022 = 16;  NSString *const ELEMENT_E022 = @"ApplicationPreferredName";
NSString *const ELEMENT_A064 = @"TextForClientReceipt";

const int LEN_CONS_16 = 16;
NSString *CONS_2 = @"00";  const int LEN_CONS_2 = 2;

const int LEN_RESPONSE_HEADER_TERMINAL_STATUS = LEN_A030 + LEN_A038 + LEN_A077;
const int LEN_RESPONSE_HEADER_PURCHASE = LEN_A030 + LEN_CONS_2 + LEN_A160 + LEN_A159 + LEN_A038 + LEN_A077; //TambiÈn sirve para Open Accounting Period, Close Accounting Period i Refund.

const int POS_INI_A030 = 0;
const int POS_INI_A038 = LEN_A030;
const int POS_INI_A043 = LEN_RESPONSE_HEADER_TERMINAL_STATUS + LEN_CONS_16;
const int POS_INI_A085 = LEN_RESPONSE_HEADER_PURCHASE;
const int POS_INI_A085_TERMINAL_STATUS = LEN_RESPONSE_HEADER_TERMINAL_STATUS;

const int POS_INI_A160 = LEN_A030 + LEN_CONS_2;


#endif
