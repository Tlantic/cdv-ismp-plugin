#import "iSMP.RPurchase.framework/Headers/iSMP_RPurchase_framework.h"

@interface iSMP : NSObject<ICISMPDeviceDelegate, ICNetworkDelegate, ICAdministrationDelegate> {
@private
    BOOL connected;
    NSString* statusDetails;
}

// iSMP fw instance
@property (nonatomic, strong) iSMP_RPurchase_framework      *rPurchase;
@property XMLWriter* xWriter;

// Network Gateway
@property (nonatomic, retain) ICNetwork * network;
@property (nonatomic, retain) ICAdministration * control;


-(id) initTerminal;
-(void)setConnectionState:(BOOL)state;
-(BOOL)getConnectionState;

-(BOOL) getStatus;
-(NSString *) getStatusDetails;

@end