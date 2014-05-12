#import "iSMP.RPurchase.framework/Headers/iSMP_RPurchase_framework.h"

@protocol iSMPDelegate <NSObject>

-(void) dispatchConnectionStatus :(BOOL) status;

@end



@interface iSMP : NSObject<ICISMPDeviceDelegate, ICNetworkDelegate, ICAdministrationDelegate> {
@private
    BOOL connected;
    NSString* statusDetails;
    NSString* purchaseDetails;
    NSString* refundDetails;
    NSString* openDetails;
    NSString* closeDetails;
}

// iSMP fw instance
@property (nonatomic, strong) iSMP_RPurchase_framework      *rPurchase;
@property XMLWriter* xWriter;

// Network Gateway
@property (nonatomic, retain) ICNetwork * network;
@property (nonatomic, retain) ICAdministration * control;

// delegated callbacks
@property (nonatomic, weak) id<iSMPDelegate> hook;

-(id) initTerminal;

-(void)setConnectionState:(BOOL)state;
-(BOOL)getConnectionState;

-(BOOL) getStatus;
-(NSString *) getStatusDetails;

-(BOOL) purchase: (NSString*)receipt :(NSString*)amount;
-(NSString *) getPurchaseDetails;

-(BOOL) refund: (NSString*)posId    :(NSString*)receipt :(NSString*)amount  :(NSString*)originalDate    :(NSString*)originalTime;
-(NSString *) getRefundDetails;

-(BOOL) openPeriod: (NSString*)receipt;
-(NSString *) getOpenDetails;

-(BOOL) closePeriod: (NSString*)receipt;
-(NSString *) getCloseDetails;

- (void)setDelegate:(id<iSMPDelegate>)callbackRef;

@end