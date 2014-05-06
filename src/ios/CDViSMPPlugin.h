#import <Cordova/CDV.h>
#import "iSMP.h"

@interface CDViSMPPlugin : CDVPlugin

@property(nonatomic, retain) iSMP * terminal;

-(void) loadTerminal: (CDVInvokedUrlCommand *) command;

@end