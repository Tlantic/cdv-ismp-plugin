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
            
            // parsing status
            NSString *respcode = [self extractNode:details :@"ResponseCode"];
            NSString *opmessage = [self extractNode:details :@"OperatorMessage"];
            NSString *posId = [self extractNode:details :@"POSIdentification"];
            
            // building result
            NSString *response = [NSString stringWithFormat:@"{ \"status\": %@, \"message\": \"%@\", \"posId\": \"%@\" }", respcode, opmessage, posId];
            
            
            
            result = [CDVPluginResult resultWithStatus:status messageAsString:response];
            
        } else {
            NSLog(@"- Terminal is not connected!");
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal is not connected!"];
            
        }
        
        // resolving cordova callback stack
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

-(NSString*) extractNode: (NSString*)chunk :(NSString*) node {

    NSString* content = nil;

    @try {
        NSLog(@"- Parsing XML looking for %@ ...", node);
        NSString* openTag  = [[@"<"  stringByAppendingString:node] stringByAppendingString:@">"];
        NSString* closeTag = [[@"</" stringByAppendingString:node] stringByAppendingString:@">"];
        
        content = [[[[chunk componentsSeparatedByString:openTag] objectAtIndex:1] componentsSeparatedByString:closeTag] objectAtIndex:0];
    }
    @catch (NSException *exception) {
        NSLog(@"- Error parsing XML...");
    }
    @finally {
        NSLog(@"- Parsing process completed!");
        return content;
    }
}

-(void) getPOSId: (CDVInvokedUrlCommand *) command
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
            
            // parsing POS Id
            NSString* posid = [self extractNode:details :@"POSIdentification"];
            
            result = [CDVPluginResult resultWithStatus:status messageAsString:posid];
            
        } else {
            NSLog(@"- Terminal is not connected!");
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal is not connected!"];
            
        }
        
        // resolving cordova callback stack
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}


-(void) doPurchase: (CDVInvokedUrlCommand *) command
{
    // validating parameters
    if ([command.arguments count] < 2) {
        
        // triggering parameter error
        CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Missing arguments when calling 'doPurchase' action."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    } else {
        
        // running in background to avoid thread locks
        [self.commandDelegate runInBackground:^{
        
            CDVPluginResult* result = nil;
            CDVCommandStatus status;
            NSString* receiptCode = [command.arguments objectAtIndex:0];
            NSString* amount = [command.arguments objectAtIndex:1];
            NSString* details = nil;
        
            NSLog(@"- Checking terminal connection...");
            
            if ([terminal getConnectionState]) {
            
                
                // purchasing
                NSLog(@"- Purchasing receipt...");
            
                if ([terminal purchase:receiptCode :amount]) {
                    status = CDVCommandStatus_OK;
                } else {
                    status = CDVCommandStatus_ERROR;
                }
            
                // getting returned info
                details = [terminal getPurchaseDetails];
                result = [CDVPluginResult resultWithStatus:status messageAsString:details];
            
            } else {
                NSLog(@"- Terminal is not connected!");
                result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal is not connected!"];
            }
            
            // resolving cordova callback stack
            [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        }];
    }
}


-(void) doRefund: (CDVInvokedUrlCommand *) command
{
    // validating parameters
    if ([command.arguments count] < 5) {
        
        // triggering parameter error
        CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Missing arguments when calling 'doRefund' action."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    } else {
        
        // running in background to avoid thread locks
        [self.commandDelegate runInBackground:^{
            
            CDVPluginResult* result = nil;
            CDVCommandStatus status;
            NSString* posId = [command.arguments objectAtIndex:0];
            NSString* receiptCode = [command.arguments objectAtIndex:1];
            NSString* amount = [command.arguments objectAtIndex:2];
            NSString* originalDate = [command.arguments objectAtIndex:3];
            NSString* originalTime = [command.arguments objectAtIndex:4];
            NSString* details = nil;
            
            NSLog(@"- Checking terminal connection...");
            
            if ([terminal getConnectionState]) {
                
                
                // purchasing
                NSLog(@"- Refunding receipt...");
                
                if ([terminal refund:posId  :receiptCode :amount  :originalDate  :originalTime]) {
                    status = CDVCommandStatus_OK;
                } else {
                    status = CDVCommandStatus_ERROR;
                }
                
                // getting returned info
                details = [terminal getRefundDetails];
                result = [CDVPluginResult resultWithStatus:status messageAsString:details];
                
            } else {
                NSLog(@"- Terminal is not connected!");
                result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal is not connected!"];
            }
            
            // resolving cordova callback stack
            [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        }];
    }
}


-(void) openAP: (CDVInvokedUrlCommand *) command
{
    // validating parameters
    if ([command.arguments count] < 1) {
        
        // triggering parameter error
        CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Missing arguments when calling 'openAP' action."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    } else {
        
        // running in background to avoid thread locks
        [self.commandDelegate runInBackground:^{
            
            CDVPluginResult* result = nil;
            CDVCommandStatus status;
            NSString* receiptCode = [command.arguments objectAtIndex:0];
            NSString* details = nil;
            
            NSLog(@"- Checking terminal connection...");
            
            if ([terminal getConnectionState]) {
                
                
                // purchasing
                NSLog(@"- Opening accounting period receipt...");
                
                if ([terminal openPeriod:receiptCode]) {
                    status = CDVCommandStatus_OK;
                } else {
                    status = CDVCommandStatus_ERROR;
                }
                
                // getting returned info
                details = [terminal getOpenDetails];
                result = [CDVPluginResult resultWithStatus:status messageAsString:details];
                
            } else {
                NSLog(@"- Terminal is not connected!");
                result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal is not connected!"];
            }
            
            // resolving cordova callback stack
            [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        }];
    }
}

-(void) closeAP: (CDVInvokedUrlCommand *) command
{
    // validating parameters
    if ([command.arguments count] < 1) {
        
        // triggering parameter error
        CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Missing arguments when calling 'closeAP' action."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    } else {
        
        // running in background to avoid thread locks
        [self.commandDelegate runInBackground:^{
            
            CDVPluginResult* result = nil;
            CDVCommandStatus status;
            NSString* receiptCode = [command.arguments objectAtIndex:0];
            NSString* details = nil;
            
            NSLog(@"- Checking terminal connection...");
            
            if ([terminal getConnectionState]) {
                
                
                // purchasing
                NSLog(@"- Closing accounting period receipt...");
                
                if ([terminal closePeriod:receiptCode]) {
                    status = CDVCommandStatus_OK;
                } else {
                    status = CDVCommandStatus_ERROR;
                }
                
                // getting returned info
                details = [terminal getCloseDetails];
                result = [CDVPluginResult resultWithStatus:status messageAsString:details];
                
                
            } else {
                NSLog(@"- Terminal is not connected!");
                result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Terminal is not connected!"];
            }
            
            // resolving cordova callback stack
            [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        }];
    }
}



-(void) dispatchConnectionStatus :(BOOL) status {
    
    // handling escape chars
    NSString *param = (status ? @"YES" : @"NO");
    
    // relay to webview
    NSString *receiveHook= [NSString stringWithFormat:@"window.tlantic.plugins.ismp.yieldConnectionChange('%@');", param];
    [self writeJavascript:receiveHook];
}

@end