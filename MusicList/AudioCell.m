
#import "AudioCell.h"

#define TableViewRowHeight 50

@implementation AudioCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    
    if (self)
    {
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        
        int gap = 10, height = 40;
        _audioButton = [[AudioButton alloc] initWithFrame:CGRectMake(gap, (TableViewRowHeight - height)/2, height, height)];
        [_audioButton setBackgroundColor:[UIColor clearColor]];
        [self.contentView addSubview:_audioButton];
        
        _titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(CGRectGetMaxX(_audioButton.frame) + gap, (TableViewRowHeight - height)/2, CGRectGetWidth(self.bounds) - CGRectGetWidth(_audioButton.bounds) - 3*gap, height)];
        _titleLabel.textColor = [UIColor blackColor];
        _titleLabel.font = [UIFont boldSystemFontOfSize:15.0f];
        _titleLabel.textAlignment = NSTextAlignmentLeft;
        _titleLabel.backgroundColor = [UIColor clearColor];
        [self.contentView addSubview:_titleLabel];
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
