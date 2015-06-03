//
//  AudioViewController
//  VideoReflection
//
//  Created by Johnny Xu on 5/22/15.
//  Copyright (c) 2015 Future Studio. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AudioViewController : UITableViewController <UITableViewDelegate, UITableViewDataSource>
{
}

@property (strong, nonatomic) NSMutableArray *allAudios;

@property (copy, nonatomic) GenericCallback seletedRowBlock;

@end
