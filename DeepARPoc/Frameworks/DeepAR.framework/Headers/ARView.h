//
//  ARView.h
//
//  Copyright © 2017 DeepAR. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "DeepAR.h"

@interface ARView : UIView

@property (nonatomic, strong) DeepAR* deepAR;

@property (nonatomic, readonly) BOOL initialized;
@property (nonatomic, readonly) BOOL faceVisible;
@property (nonatomic, readonly) CGSize renderingResolution;

@property (nonatomic, weak) id<DeepARDelegate> delegate;

// You can get your license key on https://developer.deepar.ai
- (void)setLicenseKey:(NSString*)key;

// Starts the engine initialization.
- (void)initialize;

// Resumes the rendering
- (void)resume;

// Pauses the rendering.
- (void)pause;

// Load and switch to effect.
// slot - this parameter is used to specify a "namespace" for effect. No two effects can be in
// one slot, so if we load new effect into already occupied slot, the old effect will be
// removed.
// path - The absolute path to the effect file.
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path;

// Switch effect for the face. Allowed values for face parameters are 0,1,2,3.
// This will only work if the DeepAR SDK build has multi face tracking enabled
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path face:(uint32_t)face;
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path face:(uint32_t)face targetGameObject:(NSString*)targetGameObject;

// Captures the screen. Delegate method didTakeScreenshot will be called when capture is finished.
- (void)takeScreenshot;

//Video recording helper functions
- (int)getMinSupportedHeight;
- (int)getMaxSupportedHeight;
- (int)getMinSupportedWidth;
- (int)getMaxSupportedWidth;

// Starts video recording of ARView in outputWidth x outputHeight resoulution
// CGRect subframe defines the area of ARView we want to record in normalized coordinates (from 0.0 to 1.0)
// Video compression properties is a NSDictionary used as value for key AVVideoCompressionPropertiesKey
// Audio recording can be disabled/enabled using the recordAudio parameter
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight;
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe;
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe videoCompressionProperties:(NSDictionary*)videoCompressionProperties;
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe videoCompressionProperties:(NSDictionary*)videoCompressionProperties recordAudio:(BOOL)recordAudio;

// Finishes the video recording. Delegate method didFinishVideoRecording will be called when the recording is done.
- (void)finishVideoRecording;

// Set she audio processing (pitch change) for video recording enabled.
- (void)enableAudioProcessing:(BOOL)enabled;

// Sets the pitch change amount. Negative values will make the recorded audio lower in pitch and positive values will make it higher in pitch.
- (void)setAudioProcessingSemitone:(float)sts;

// Shutdowns the engine
- (void)shutdown;

// Starts streaming the subframes to delegate method frameAvailable.
- (void)startFrameOutputWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe;

// Stops streaming
- (void)stopFrameOutput;

// Passes the camera frame into the engine. This should only be called after initializeWithCustomCameraUsingPreset.
- (void)enqueueCameraFrame:(CMSampleBufferRef)sampleBuffer mirror:(BOOL)mirror;

// Passes the audo sample into the engine. This is used for the video/audio recording and only if initialized with initializeWithCustomCameraUsingPreset.
- (void)enqueueAudioSample:(CMSampleBufferRef)sampleBuffer;

- (void)pauseVideoRecording;
- (void)resumeVideoRecording;

// Change a float parameter on a GameObject, the parameter variable contains parameter name, eg. blendshape name
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter floatValue:(float)value;
// Change a vector4 parameter on a GameObject, the parameter variable contains parameter name, eg. uniform name 
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vectorValue:(Vector4)value;
// Change a vector3 parameter on a GameObject, the parameter variable contains parameter name, eg. transform name
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vector3Value:(Vector3)value;
// Change a bool parameter on a GameObject, the parameter variable contains parameter name, eg. uniform name 
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter boolValue:(bool)value;
// Change an image parameter on a GameObject, the parameter variable contains parameter name, eg. uniform name
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter image:(UIImage*)image;

// Fire trigger for all animation controllers
- (void)fireTrigger:(NSString*)trigger;

// Change face detection sensitivity
- (void)setFaceDetectionSensitivity:(int)sensitivity;

// Display debuging stats on screen
- (void)showStats:(bool)enabled;

// Sets the internal SDK parameter
- (void)setParameterWithKey:(NSString*)key value:(NSString*)value;
@end

#import "ARView.h"
#import "CameraController.h"
