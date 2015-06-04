//
//  CommonDefine.h
//  VideoReflection
//
//  Created by Johnny Xu on 5/19/15.
//  Copyright (c) 2015 Johnny Xu. All rights reserved.
//

#ifndef ScreenRecorder_CommonDefine_h
#define ScreenRecorder_CommonDefine_h

// Google Ads
#define kGoogleBannerAdUnitID @"ca-app-pub-7841133407354896/4811226962"
#define kGoogleInterstitialAdUnitID @"ca-app-pub-4954715608308009/6853577774"

// Color
#define RGBCOLOR(r,g,b) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:1]
#define RGBACOLOR(r,g,b,a) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:(a)]
#define kNavigationBarBottomSeperatorColor RGBCOLOR(255, 207, 51)
#define kTableViewSeperatorColor RGBCOLOR(75, 72, 72)
#define kBackgroundColor RGBCOLOR(40, 39, 37)
#define kTableViewCellTitleColor RGBCOLOR(172, 171, 169)
#define kTextGrayColor RGBCOLOR(148, 147, 146)
#define kLightBlue [UIColor colorWithRed:155/255.0f green:188/255.0f blue:220/255.0f alpha:1]
#define kBrightBlue [UIColor colorWithRed:100/255.0f green:100/255.0f blue:230/255.0f alpha:1]

// OS Version
#define iPad (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#define IOS7 [[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0
#define iOS6 ((([[UIDevice currentDevice].systemVersion intValue] >= 6) && ([[UIDevice currentDevice].systemVersion intValue] < 7)) ? YES : NO )
#define iOS5 ((([[UIDevice currentDevice].systemVersion intValue] >= 5) && ([[UIDevice currentDevice].systemVersion intValue] < 6)) ? YES : NO )

// Progress Bar
#define ProgressBarShowLoading(_Title_) [SNLoading showWithTitle:_Title_]
#define ProgressBarDismissLoading(_Title_) [SNLoading hideWithTitle:_Title_]
#define ProgressBarUpdateLoading(_Title_, _DetailsText_) [SNLoading updateWithTitle:_Title_ detailsText:_DetailsText_]

#define degreesToRadians(degrees) ((degrees) / 180.0 * M_PI)

// Callback
typedef void(^GenericCallback)(BOOL success, id result);


#pragma mark - String
static inline BOOL isStringEmpty(NSString *value)
{
    BOOL result = FALSE;
    if (!value || [value isKindOfClass:[NSNull class]])
    {
        // null object
        result = TRUE;
    }
    else
    {
        NSString *trimedString = [value stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
        if ([value isKindOfClass:[NSString class]] && [trimedString length] == 0)
        {
            // empty string
            result = TRUE;
        }
    }
    
    return result;
}

#pragma mark - App Info
static inline NSString* getAppVersion()
{
    NSDictionary *infoDict = [[NSBundle mainBundle] infoDictionary];
    NSString *versionNum =[infoDict objectForKey:@"CFBundleVersion"];
    NSLog(@"App version: %@", versionNum);
    return versionNum;
}

static inline NSString* getAppName()
{
    NSDictionary *infoDict = [[NSBundle mainBundle] infoDictionary];
    NSString *appName = [infoDict objectForKey:@"CFBundleDisplayName"];
    NSLog(@"App name: %@", appName);
    return appName;
}

static inline NSString* getAppNameByInfoPlist()
{
    NSString *appName = NSLocalizedStringFromTable(@"CFBundleDisplayName", @"InfoPlist", nil);
    NSLog(@"App name: %@", appName);
    return appName;
}

/* 获取本机正在使用的语言  * en:英文  zh-Hans:简体中文   zh-Hant:繁体中文    ja:日本 ...... */
static inline NSString* getPreferredLanguage()
{
    NSUserDefaults* defs = [NSUserDefaults standardUserDefaults];
    NSArray* languages = [defs objectForKey:@"AppleLanguages"];
    NSString* preferredLang = [languages objectAtIndex:0];
    
    NSLog(@"Preferred Language: %@", preferredLang);
    return preferredLang;
}

static inline NSString* getCurrentlyLanguage()
{
    NSArray *languages = [NSLocale preferredLanguages];
    NSString *currentLanguage = [languages objectAtIndex:0];
    
    NSLog(@"currentLanguage: %@", currentLanguage);
    return currentLanguage;
}

static inline BOOL isZHHansFromCurrentlyLanguage()
{
    BOOL bResult = FALSE;
    NSString *curLauguage = getCurrentlyLanguage();
    NSString *cnLauguage = @"zh-Hans";
    if ([curLauguage compare:cnLauguage options:NSCaseInsensitiveSearch | NSNumericSearch] == NSOrderedSame)
    {
        bResult = TRUE;
    }
    
    return bResult;
}

#define CURR_LANG ([[NSLocale preferredLanguages] objectAtIndex: 0])
static inline NSString* GBLocalizedString(NSString *translation_key)
{
    NSString * string = NSLocalizedString(translation_key, nil );
    if (![CURR_LANG isEqual:@"en"] && ![CURR_LANG isEqualToString:@"zh-Hans"])
    {
        NSString * path = [[NSBundle mainBundle] pathForResource:@"en" ofType:@"lproj"];
        NSBundle * languageBundle = [NSBundle bundleWithPath:path];
        string = [languageBundle localizedStringForKey:translation_key value:@"" table:nil];
    }
    
    return string;
}

#pragma mark - File Manager
static inline NSArray* getFilelistBySymbol(NSString *symbol, NSString *dirPath)
{
    NSMutableArray *filelist = [NSMutableArray arrayWithCapacity:1];
    NSArray *tmplist = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:dirPath error:nil];
    for (NSString *filename in tmplist)
    {
        NSString *fullpath = [dirPath stringByAppendingPathComponent:filename];
        BOOL fileExisted = [[NSFileManager defaultManager] fileExistsAtPath:fullpath];
        if (fileExisted)
        {
            if ([[filename lastPathComponent] hasPrefix:symbol])
            {
                [filelist  addObject:filename];
            }
        }
    }
    
    return filelist;
}

static inline BOOL isFileExistAtPath(NSString *fileFullPath)
{
    BOOL isExist = NO;
    isExist = [[NSFileManager defaultManager] fileExistsAtPath:fileFullPath];
    return isExist;
}

#pragma mark - Delete Files/Directory
static inline void deleteFilesAt(NSString *directory, NSString *suffixName)
{
    NSError *err = nil;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSDirectoryEnumerator *dirEnum = [fileManager enumeratorAtPath:directory];
    NSString *toDelFile;
    while (toDelFile = [dirEnum nextObject])
    {
        NSComparisonResult result = [[toDelFile pathExtension] compare:suffixName options:NSCaseInsensitiveSearch|NSNumericSearch];
        if (result == NSOrderedSame)
        {
            NSLog(@"removing file：%@", toDelFile);
            
            if(![fileManager removeItemAtPath:[directory stringByAppendingPathComponent:toDelFile] error:&err])
            {
                NSLog(@"Error: %@", [err localizedDescription]);
            }
        }
    }
}

#pragma mark - Screen Bounds

// iOS 8 way of returning bounds for all SDK's and OS-versions
#ifndef NSFoundationVersionNumber_iOS_7_1
# define NSFoundationVersionNumber_iOS_7_1 1047.25
#endif
static inline CGRect screenBounds()
{
    CGRect screenBounds = [UIScreen mainScreen].bounds;
    
    static BOOL isNotRotatedBySystem;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        BOOL OSIsBelowIOS8 = [[[UIDevice currentDevice] systemVersion] floatValue] < 8.0;
        BOOL SDKIsBelowIOS8 = floor(NSFoundationVersionNumber) <= NSFoundationVersionNumber_iOS_7_1;
        isNotRotatedBySystem = OSIsBelowIOS8 || SDKIsBelowIOS8;
    });
    
    BOOL needsToRotate = isNotRotatedBySystem && UIInterfaceOrientationIsLandscape([UIApplication sharedApplication].statusBarOrientation);
    if(needsToRotate)
    {
        CGRect bounds = screenBounds;
        bounds.size.width = screenBounds.size.height;
        bounds.size.height = screenBounds.size.width;
        return bounds;
    }
    else
    {
        return screenBounds;
    }
}

#pragma mark - Save Image
static inline NSString* getTempImageOutputFile()
{
    NSString *path = NSTemporaryDirectory();
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"yyyyMMddHHmmss";
    NSString *nowTimeStr = [formatter stringFromDate:[NSDate dateWithTimeIntervalSinceNow:0]];
    
    NSString *imageOutputFile = [[path stringByAppendingPathComponent:nowTimeStr] stringByAppendingString:@"image.jpg"];
    return imageOutputFile;
}

static inline BOOL saveImage(UIImage *image)
{
    NSData *data = UIImageJPEGRepresentation(image, 0.8);
    NSString *imageOutputFile = getTempImageOutputFile();
    unlink([imageOutputFile UTF8String]);
    NSLog(@"Save Image: %@", imageOutputFile);
    return [data writeToFile:imageOutputFile atomically:YES];
}

static inline NSString* saveImageData(NSData *imageData)
{
    UIImage *image = [[UIImage alloc] initWithData:imageData];
    NSData *data = UIImageJPEGRepresentation(image, 0.8);
    NSString *imageOutputFile = getTempImageOutputFile();
    unlink([imageOutputFile UTF8String]);
    if (![data writeToFile:imageOutputFile atomically:YES])
    {
        imageOutputFile = nil;
    }
    
    NSLog(@"saveImageData: %@", imageOutputFile);
    return imageOutputFile;
}

#pragma mark - Square Image
static inline UIImage* squareImageFromImage(UIImage *image)
{
    UIImage *squareImage = nil;
    CGSize imageSize = [image size];
    
    if (imageSize.width == imageSize.height)
    {
        squareImage = image;
    }
    else
    {
        // Compute square crop rect
        CGFloat smallerDimension = MIN(imageSize.width, imageSize.height);
        CGRect cropRect = CGRectMake(0, 0, smallerDimension, smallerDimension);
        
        // Center the crop rect either vertically or horizontally, depending on which dimension is smaller
        if (imageSize.width <= imageSize.height)
        {
            cropRect.origin = CGPointMake(0, rintf((imageSize.height - smallerDimension) / 2.0));
        }
        else
        {
            cropRect.origin = CGPointMake(rintf((imageSize.width - smallerDimension) / 2.0), 0);
        }
        
        CGImageRef croppedImageRef = CGImageCreateWithImageInRect([image CGImage], cropRect);
        squareImage = [UIImage imageWithCGImage:croppedImageRef];
        CGImageRelease(croppedImageRef);
    }
    
    return squareImage;
}

#pragma mark - Thumbnail
static inline UIImage* generateThumbnail(UIImage *image, CGFloat width, CGFloat height)
{
    // Create a thumbnail image
    CGSize size = image.size;
    CGSize croppedSize;
    CGFloat ratioX = 75.0;
    CGFloat ratioY = 75.0;
    CGFloat offsetX = 0.0;
    CGFloat offsetY = 0.0;
    
    if (width > 0)
    {
        ratioX = width;
    }
    
    if (height > 0)
    {
        ratioY = height;
    }
    
    // Check the size of the image, we want to make it a square with sides the size of the smallest dimension
    if (size.width > size.height)
    {
        offsetX = (size.height - size.width) / 2;
        croppedSize = CGSizeMake(size.height, size.height);
    }
    else
    {
        offsetY = (size.width - size.height) / 2;
        croppedSize = CGSizeMake(size.width, size.width);
    }
    
    
    // Crop the image before resize
    CGRect clippedRect = CGRectMake(offsetX * -1, offsetY * -1, croppedSize.width, croppedSize.height);
    CGImageRef imageRef = CGImageCreateWithImageInRect([image CGImage], clippedRect);
    // Done cropping
    
    // Resize the image
    CGRect rect = CGRectMake(0.0, 0.0, ratioX, ratioY);
    UIGraphicsBeginImageContext(rect.size);
    [[UIImage imageWithCGImage:imageRef] drawInRect:rect];
    UIImage *thumbnail = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    // Done Resizing
    
    return thumbnail;
}

static inline UIImage* generateThumbnailPhoto(UIImage *image)
{
    UIImage *thumbnail = nil;
    if (image)
    {
        thumbnail = generateThumbnail(image, 0, 0);
    }
    else
    {
        NSLog(@"Image is empty!");
    }
    
    return thumbnail;
}

static inline UIImage* imageWithColor(UIColor *color)
{
    CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage*theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return theImage;
}

#pragma mark - JailBreak Device

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
const char* jailbreak_tool_pathes[] =
{
    "/Applications/Cydia.app",
    "/Library/MobileSubstrate/MobileSubstrate.dylib",
    "/bin/bash",
    "/usr/sbin/sshd",
    "/etc/apt"
};

static inline BOOL isJailBreak()
{
    for (int i=0; i<ARRAY_SIZE(jailbreak_tool_pathes); i++)
    {
        if ([[NSFileManager defaultManager] fileExistsAtPath:[NSString stringWithUTF8String:jailbreak_tool_pathes[i]]])
        {
            NSLog(@"The device is jail broken!");
            return YES;
        }
    }
    
    NSLog(@"The device is NOT jail broken!");
    return NO;
}

#endif
