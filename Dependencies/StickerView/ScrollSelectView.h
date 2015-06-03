
#import <UIKit/UIKit.h>

@protocol ScrollSelectViewDelegate;

@interface ScrollSelectView : UIView

@property (nonatomic, strong) UIScrollView  *ContentView;
@property (nonatomic, assign) id<ScrollSelectViewDelegate> delegateSelect;
@property (nonatomic, assign) NSInteger selectStyleIndex;

- (id)initWithFrameFromGif:(CGRect)frame;

+ (void)getDefaultFilelist;

@end

@protocol ScrollSelectViewDelegate <NSObject>

@optional
- (void)didSelectedGifIndex:(NSInteger)styleIndex;

@end
