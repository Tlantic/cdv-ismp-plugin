#import "iSMP.h"

@implementation iSMP: NSObject

@synthesize xWriter;
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


- (void)setDelegate:(id<iSMPDelegate>)callbackRef {
    _hook = callbackRef;
}

//Network Gateway
-(void)setConnectionState:(BOOL)state
{
    if (state == YES) {
        NSLog(@"[setConnectionState] # Network Channel Ready");
    } else {
        NSLog(@"[setConnectionState] # Network Channel Not ready");
    }
    connected = state;
    [_hook dispatchConnectionStatus:state];
}

-(BOOL)getConnectionState
{
    return connected;
}


// TERMINAL STATUS
-(BOOL) getStatus
{
    int exitCode = 0;
    statusDetails = nil;
    xWriter= [[XMLWriter alloc] init];

    NSLog(@"- Sending Terminal Status to iSMP...");
    
    // sending request
    exitCode = [rPurchase fDll_RP_TerminalStatus:@"03" cECRModel:@"MM" cECRSpecVersion:@"0114" xmlWriter:xWriter iMaxXMLResponseSize:65536];
    NSLog(@"- Terminal status received: %d", exitCode);
    
    // storing details
    statusDetails = [xWriter toString];
        
    NSLog(@"- Received buffer: %@", statusDetails);
    
    return (exitCode == 0 ? YES : NO);
}

-(NSString *) getStatusDetails
{
    return statusDetails;
}


// PURCHASE
-(BOOL) purchase: (NSString*)receipt :(NSString*)amount {
    int exitCode = 0;
    purchaseDetails = nil;
    xWriter= [[XMLWriter alloc] init];
    
    NSLog(@"- Sending Purchase to iSMP...");
    
    // sending request
    exitCode = [rPurchase fDll_RP_Purchase:@"02" cReceiptCode:receipt cControlNumber:@"000" cAmount:amount xmlWriter:xWriter iMaxXMLResponseSize:65536];
    NSLog(@"- Terminal purchase received: %d", exitCode);
    
    // storing details
    purchaseDetails = [xWriter toString];
    NSLog(@"- Received buffer: %@", purchaseDetails);
    
    return (exitCode == 0 ? YES : NO);
}

-(NSString *) getPurchaseDetails {
    return purchaseDetails;
}


// REFUND
-(BOOL) refund: (NSString*)posId :(NSString*)receipt :(NSString*)amount  :(NSString*)originalDate  :(NSString*)originalTime {
    int exitCode = 0;
    purchaseDetails = nil;
    xWriter= [[XMLWriter alloc] init];
    
    NSLog(@"- Sending Refund to iSMP...");
    
    // sending request
    exitCode = [rPurchase fDll_RP_Refund:@"02" cReceiptCode:receipt cControlNumber:@"000" cAmount:amount cOriginalPOSIdent:posId cOriginalReceiptDate:originalDate cOriginalReceiptTime:originalTime xmlWriter:xWriter iMaxXMLResponseSize:65536];
    NSLog(@"- Terminal refund received: %d", exitCode);
    
    // storing details
    refundDetails = [xWriter toString];
    NSLog(@"- Received buffer: %@", refundDetails);
    
    return (exitCode == 0 ? YES : NO);
}

-(NSString *) getRefundDetails {
    return refundDetails;
}

// OPEN ACCOUNT PERIOD
-(BOOL) openPeriod: (NSString*)receipt {
    int exitCode = 0;
    openDetails = nil;
    xWriter= [[XMLWriter alloc] init];
    
    NSLog(@"- Sending OpenAccountPeriod to iSMP...");
    
    // sending request
    exitCode = [rPurchase fDll_RP_OpenAccountingPeriod:@"02" cReceiptCode:receipt cControlNumber:@"000" xmlWriter:xWriter iMaxXMLResponseSize:65536];
    NSLog(@"- Terminal OpenAccountPeriod received: %d", exitCode);
    
    // storing details
    openDetails = [xWriter toString];
    NSLog(@"- Received buffer: %@", openDetails);
    
    return (exitCode == 0 ? YES : NO);
}

-(NSString *) getOpenDetails {
    return openDetails;
}

// CLOSE ACCOUNT PERIOD
-(BOOL) closePeriod: (NSString*)receipt  {
    int exitCode = 0;
    closeDetails = nil;
    xWriter= [[XMLWriter alloc] init];
    
    NSLog(@"- Sending CloseAccountPeriod to iSMP...");
    
    // sending request
    exitCode = [rPurchase fDll_RP_CloseAccountingPeriod:@"02" cReceiptCode:receipt cControlNumber:@"000" xmlWriter:xWriter iMaxXMLResponseSize:65536];
    NSLog(@"- Terminal CloseAccountPeriod received: %d", exitCode);
    
    // storing details
    closeDetails = [xWriter toString];
    NSLog(@"- Received buffer: %@", closeDetails);
    
    return (exitCode == 0 ? YES : NO);
}

-(NSString *) getCloseDetails {
    return closeDetails;
}


#pragma mark ICNetworkDelegate Protocol Implementation

-(void)networkData:(NSData *)data incoming:(BOOL)isIncoming
{
	NSString * log = [NSString stringWithFormat:@"[Data: %@, Length: %d]\r\n\t%@\r\n", (isIncoming==YES?@"Network -> iPhone":@"iPhone -> Network"), [data length], [data hexDump]];
	NSLog(@"%@", log);
}

-(void)networkWillConnectToHost:(NSString *)host onPort:(NSUInteger)port
{
    NSString * logMessage = [NSString stringWithFormat:@"Trying to connect to %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^
    {
        // do stuff
    }];
}

-(void)networkDidConnectToHost:(NSString *)host onPort:(NSUInteger)port
{
    NSString * logMessage = [NSString stringWithFormat:@"Connected to %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        NSLog(@"### NETWORK DID CONNECT TO HOST");
    }];
}

-(void)networkFailedToConnectToHost:(NSString *)host onPort:(NSUInteger)port
{
    NSString * logMessage = [NSString stringWithFormat:@"Failed to connect to %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        NSLog(@"### NETWORK FAILED TO CONNECT TO HOST");
    }];
}

-(void)networkDidDisconnectFromHost:(NSString *)host onPort:(NSUInteger)port
{
    NSString * logMessage = [NSString stringWithFormat:@"Disconnected from %@:%d", host, port];
    NSLog(@"%@", logMessage);
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        NSLog(@"### NETWORK DID DISCONNECT TO HOST");
    }];
}
#pragma mark -




#pragma mark ICDeviceDelegate Protocol Implementation

// this method write traces to iPod's console (viewable within Xcode, Organizer or iPhone Configuration Utility)
-(void)logEntry:(NSString *)message withSeverity:(int)severity
{
    NSLog(@"%s [%@][%@]", __FUNCTION__, [ICISMPDevice severityLevelString:severity], message);
}

// this method logs serial data exchanged between iPhone and iSMP
-(void)logSerialData:(NSData *)data incomming:(BOOL)isIncoming
{
    NSLog(@"%s [Length: %d] %@", __FUNCTION__, [data length], [data hexDump]);
}

// network gateway awareness
-(void)accessoryDidConnect:(ICISMPDevice *)sender
{
    if (sender == network) {
        [self setConnectionState:YES];
    }
}

-(void)accessoryDidDisconnect:(ICISMPDevice *)sender
{
    if (sender == network) {
        [self setConnectionState:NO];
    }
}

#pragma mark -


#pragma mark ICAdministrationDelegate

-(void)confLogEntry:(NSString *)message withSeverity:(int)severity
{
    NSLog(@"%s [%@][%@]", __FUNCTION__, [ICISMPDevice severityLevelString:severity], message);
}

#pragma mark -

@end