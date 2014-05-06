#import "iSMP.h"

@implementation iSMP: NSObject

@synthesize rPurchase;

- (id) initTerminal
{
    self = [super init];
    
    if (self)
    {
        connected = NO;
        rPurchase = [[iSMP_RPurchase_framework alloc] init];
    }
    
    return self;
}
@end