#import <Cordova/CDV.h>
#import "iSMP.h"

@interface CDViSMPPlugin : CDVPlugin <iSMPDelegate>

@property(nonatomic, retain) iSMP * terminal;

-(void) loadTerminal: (CDVInvokedUrlCommand *) command;
-(void) isTerminalConnected: (CDVInvokedUrlCommand *) command;
-(void) getTerminalStatus: (CDVInvokedUrlCommand *) command;
-(void) doPurchase: (CDVInvokedUrlCommand *) command;
-(void) doRefund: (CDVInvokedUrlCommand *) command;
-(void) openAP: (CDVInvokedUrlCommand *) command;
-(void) closeAP: (CDVInvokedUrlCommand *) command;

-(NSString*) extractNode: (NSString*)chunk :(NSString*) node;
-(void) getPOSId: (CDVInvokedUrlCommand *) command;

@end