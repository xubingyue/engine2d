//
//  opengl.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef engine2d_opengl_h
#define engine2d_opengl_h


#if defined( __APPLE__ ) && !defined(__MACOSX)

#define OPENGLES 2
#include <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#elif defined(linux) || defined(__linux) || defined(__linux__)

#define OPENGLES 2
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else
#define OPENGLES 0
#include <GL/glew.h>

#endif

#endif
