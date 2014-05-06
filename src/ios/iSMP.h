#import "iSMP.RPurchase.framework/Headers/iSMP_RPurchase_framework.h"

@interface iSMP : NSObject {
@private
    BOOL connected;
}

@property (nonatomic, strong) iSMP_RPurchase_framework      *rPurchase;

-(id) initTerminal;
@end