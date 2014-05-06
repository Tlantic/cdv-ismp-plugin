#import "iSMP.h"

@implementation iSMP: NSObject

@synthesize rPurchase;
@synthesize network;
@synthesize control;

- (id) initTerminal
{
    self = [super init];
    
    if (self)
    {
        rPurchase = [[iSMP_RPurchase_framework alloc] init];

        //Network Gateway
        network = [ICNetwork sharedChannel];
        network.delegate = self;
        
        //The control channel is required when setting up a gateway since it provides the iPhone's network interface state when asked by the iSMP
        control = [ICAdministration sharedChannel];
        control.delegate = self;
        
        if (network.isAvailable) {
            [self setConnectionState:YES];
        } else {
            [self setConnectionState:NO];
        }
        
        //Prevent iPhone from going into sleep mode when the application is running
        [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    }
    
    return self;
}


//Network Gateway
-(void)setConnectionState:(BOOL)state {
    if (state == YES) {
        NSLog(@"- Network Channel Ready");
    } else {
        NSLog(@"- Network Channel Not ready");
    }
    connected = state;
}



#pragma mark ICNetworkDelegate Protocol Implementation

-(void)networkData:(NSData *)data incoming:(BOOL)isIncoming {
	NSString * log = [NSString stringWithFormat:@"[Data: %@, Length: %d]\r\n\t%@\r\n", (isIncoming==YES?@"Network -> iPhone":@"iPhone -> Network"), [data length], [data hexDump]];
	NSLog(@"%@", log);
}

-(void)networkWillConnectToHost:(NSString *)host onPort:(NSUInteger)port {
    NSString * logMessage = [NSString stringWithFormat:@"Trying to connect to %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        // do stuff
    }];
}

-(void)networkDidConnectToHost:(NSString *)host onPort:(NSUInteger)port {
    NSString * logMessage = [NSString stringWithFormat:@"Connected to %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        // do stuff
    }];
}

-(void)networkFailedToConnectToHost:(NSString *)host onPort:(NSUInteger)port {
    NSString * logMessage = [NSString stringWithFormat:@"Failed to connect to %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        // do stuff/
    }];
}

-(void)networkDidDisconnectFromHost:(NSString *)host onPort:(NSUInteger)port {
    NSString * logMessage = [NSString stringWithFormat:@"Disconnected from %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        // do stuff
    }];
}
#pragma mark -




#pragma mark ICDeviceDelegate Protocol Implementation

// this method write traces to iPod's console (viewable within Xcode, Organizer or iPhone Configuration Utility)
-(void)logEntry:(NSString *)message withSeverity:(int)severity {
    NSLog(@"%s [%@][%@]", __FUNCTION__, [ICISMPDevice severityLevelString:severity], message);
}

// this method logs serial data exchanged between iPhone and iSMP
-(void)logSerialData:(NSData *)data incomming:(BOOL)isIncoming {
    NSLog(@"%s [Length: %d] %@", __FUNCTION__, [data length], [data hexDump]);
}

// 
-(void)accessoryDidConnect:(ICISMPDevice *)sender {
    if (sender == network) {
        [self setConnectionState:YES];
    }
}

-(void)accessoryDidDisconnect:(ICISMPDevice *)sender {
    if (sender == network) {
        [self setConnectionState:NO];
    }
}

#pragma mark -


#pragma mark ICAdministrationDelegate

-(void)confLogEntry:(NSString *)message withSeverity:(int)severity {
    NSLog(@"%s [%@][%@]", __FUNCTION__, [ICISMPDevice severityLevelString:severity], message);
}

#pragma mark -

@end