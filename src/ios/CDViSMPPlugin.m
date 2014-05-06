#import "CDViSMPPlugin.h"

@implementation CDViSMPPlugin : CDVPlugin

@synthesize terminal;


-(void) loadTerminal: (CDVInvokedUrlCommand *) command {
    
    // running in background to avoid thread locks
    [self.commandDelegate runInBackground:^{

        CDVPluginResult* result = nil;
        
        
        // checking terminal load status
        NSLog(@"- Checking terminal instance...");

        if (terminal) {
            NSLog(@"- Terminal has been loaded already!");
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal already loaded."];
        } else {
            
            // creating terminal instance
            NSLog(@"- Creating terminal instance...");
            terminal = [[iSMP alloc] initTerminal];

            NSLog(@"- Instance has been created successfully!");
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        
        // resolving cordova callback stack
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

-(void) isTerminalConnected: (CDVInvokedUrlCommand *) command
{
    // running in background to avoid thread locks
    [self.commandDelegate runInBackground:^{
        
        CDVPluginResult* result = nil;
        BOOL status = NO;
        
        
        NSLog(@"- Checking terminal connection...");

        if (terminal) {
            status = [terminal getConnectionState];
            NSLog(@"- Current terminal connection status: %@", (status ? @"YES" : @"NO"));
            
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:status];
        } else {
            NSLog(@"- Terminal has not been initialized!");
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal has not been initialized."];
        }
        
        
        // resolving cordova callback stack
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

-(void) getTerminalStatus: (CDVInvokedUrlCommand *) command
{
    // running in background to avoid thread locks
    [self.commandDelegate runInBackground:^{
        
    }];
}

@end