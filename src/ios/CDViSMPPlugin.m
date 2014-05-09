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
            [terminal setDelegate:self];

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
 
        CDVPluginResult* result = nil;
        CDVCommandStatus status;
        NSString* details = nil;
 
        NSLog(@"- Checking terminal connection...");
        if ([terminal getConnectionState]) {
        
            // getting status
            NSLog(@"- Getting status from terminal...");
            
            if ([terminal getStatus]) {
                status = CDVCommandStatus_OK;
            } else {
                status = CDVCommandStatus_ERROR;
            }
        
            // getting returned info
            details = [terminal getStatusDetails];
            result = [CDVPluginResult resultWithStatus:status messageAsString:details];
            
        } else {
            NSLog(@"- Terminal is not connected!");
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal is not connected!"];
            
        }
        
        // resolving cordova callback stack
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

-(void) dispatchConnectionStatus :(BOOL) status {
    
    // handling escape chars
    NSString *param = (status ? @"YES" : @"NO");
    
    // relay to webview
    NSString *receiveHook= [NSString stringWithFormat:@"window.tlantic.plugins.ismp.yieldConnectionChange('%@');", param];
    [self writeJavascript:receiveHook];
}

@end