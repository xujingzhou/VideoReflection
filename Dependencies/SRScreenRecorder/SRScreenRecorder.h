
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <TargetConditionals.h>

typedef NSString *(^SRScreenRecorderOutputFilenameBlock)();

typedef UIImage *(^SRCaptureViewBlock)();
typedef void (^SRFinishRecordingBlock)(BOOL success, id result);
typedef CMTime (^SRCaptureVideoSampleTime)();

@interface SRScreenRecorder : NSObject

@property(nonatomic, copy) NSNumber *audioSampleRate;
@property(nonatomic, copy) NSNumber *numberOfAudioChannels;
@property(nonatomic, copy) NSString *audioOutPath;

@property (assign, nonatomic) NSInteger frameInterval;
@property (assign, nonatomic) NSUInteger autosaveDuration; // in second, default value is 600 (10 minutes).

@property (copy, nonatomic) SRScreenRecorderOutputFilenameBlock filenameBlock;

@property (copy, nonatomic) SRFinishRecordingBlock finishRecordingBlock;
@property (copy, nonatomic) SRCaptureViewBlock captureViewBlock;
@property (copy, nonatomic) SRCaptureVideoSampleTime captureVideoSampleTimeBlock;


+ (SRScreenRecorder *)sharedInstance;
- (void)startRecording;
- (void)stopRecording;

- (void)writeExportedVideoToAssetsLibrary:(NSString *)outputPath;

@end
