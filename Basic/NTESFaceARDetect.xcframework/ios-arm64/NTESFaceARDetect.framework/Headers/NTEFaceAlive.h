//
//  NTEFaceAlive.h
//  NTESFaceARDetect
//
//  Created by 徐国智 on 2021/6/22.
//

#ifndef NTEFaceAlive_h
#define NTEFaceAlive_h

#import <Foundation/Foundation.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <stdio.h>

/**
 v1.0 20211207
 */


@interface FaceARDetectIOS : NSObject


- (BOOL)reset_FaceAR;

- (BOOL)clear_FaceAR;

- (BOOL)update_Frontal;

- (BOOL)run_NENNLiveness:(unsigned char *)captured_image
               command__:(std::string)command
            action_mun__:(int)action_num
          notification__:(std::string &)notification
face_detection_success__:(bool &)face_detection_success
                 frame__:(int)frame_count
      saved_image_path__:(std::string)saved_image_path
      detect_exception__:(bool &)detect_exception
              imgWidth__:(int)imgWidth
             imgHeight__:(int)imgHeight
               degrade__:(bool)bDegrade
               encrypt__:(bool)encrypt
  allow_multiple_faces__:(bool)allow_multiple_faces;



- (NSData *)getPicDataWithFilePath:(const char *)filePath;

- (id)initWithSensitivityType:(int)type;


- (NSString *)getSDKVersion;

@end

#endif /* NTEFaceAlive_h */
