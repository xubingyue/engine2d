//
//  platform_print.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef engine2d_platform_print_h
#define engine2d_platform_print_h


#ifdef __ANDROID__
    #include <android/log.h>
    #include <jni.h>
    #define  LOG_TAG                    "ejoy2d"
    #define  pf_log(...)                __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
    #define  pf_vprint(format, ap)      __android_log_vprint(ANDROID_LOG_DEBUG, LOG_TAG, (format), (ap))
#else
    #define pf_log                      printf
    #define pf_vprint                   vprintf
#endif

#endif
