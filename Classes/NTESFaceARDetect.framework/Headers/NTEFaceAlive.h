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
  v1.2 20220422
 */


@interface FaceARDetectIOS : NSObject


- (BOOL)reset_FaceAR;

- (BOOL)clear_FaceAR;

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
             degrade__:(bool)bDegrade;

- (id)initWithSensitivityType:(int)type;

@end

#endif /* NTEFaceAlive_h */
