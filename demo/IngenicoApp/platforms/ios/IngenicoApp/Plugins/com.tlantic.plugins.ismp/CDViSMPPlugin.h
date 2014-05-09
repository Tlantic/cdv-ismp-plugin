#import <Cordova/CDV.h>
#import "iSMP.h"

@interface CDViSMPPlugin : CDVPlugin <iSMPDelegate>

@property(nonatomic, retain) iSMP * terminal;

-(void) loadTerminal: (CDVInvokedUrlCommand *) command;
-(void) isTerminalConnected: (CDVInvokedUrlCommand *) command;
-(void) getTerminalStatus: (CDVInvokedUrlCommand *) command;

@end