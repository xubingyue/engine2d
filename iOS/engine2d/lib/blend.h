//
//  blend.h
//  engine2d
//
//  Created by TTc on 14-3-17.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef engine2d_blend_h
#define engine2d_blend_h
#include "render.h"


#define BLEND_GL_ZERO               0
#define BLEND_GL_ONE                1
#define BLEND_GL_SRC_COLOR          0x0300
#define BLEND_GL_ONE_MINUS_SRC_COLOR 0x0301
#define BLEND_GL_SRC_ALPHA 0x0302
#define BLEND_GL_ONE_MINUS_SRC_ALPHA 0x0303
#define BLEND_GL_DST_ALPHA 0x0304
#define BLEND_GL_ONE_MINUS_DST_ALPHA 0x0305
#define BLEND_GL_DST_COLOR 0x0306
#define BLEND_GL_ONE_MINUS_DST_COLOR 0x0307
#define BLEND_GL_SRC_ALPHA_SATURATE 0x0308

static enum BLEND_FORMAT
blend_mode(int gl_mode){
    switch(gl_mode){
        case BLEND_GL_ZERO:
            return BLEND_ZERO;
        case BLEND_GL_ONE:
            return BLEND_ONE;
        case BLEND_GL_SRC_COLOR:
            return BLEND_SRC_COLOR;
        case BLEND_GL_ONE_MINUS_SRC_COLOR:
            return BLEND_ONE_MINUS_SRC_COLOR;
        case BLEND_GL_SRC_ALPHA:
            return BLEND_SRC_ALPHA;
        case BLEND_GL_ONE_MINUS_SRC_ALPHA:
            return BLEND_ONE_MINUS_SRC_ALPHA;
        case BLEND_GL_DST_ALPHA:
            return BLEND_DST_ALPHA;
        case BLEND_GL_ONE_MINUS_DST_ALPHA:
            return BLEND_ONE_MINUS_DST_ALPHA;
        case BLEND_GL_DST_COLOR:
            return BLEND_DST_COLOR;
        case BLEND_GL_ONE_MINUS_DST_COLOR:
            return BLEND_ONE_MINUS_DST_COLOR;
        case BLEND_GL_SRC_ALPHA_SATURATE:
            return BLEND_SRC_ALPHA_SATURATE;
    }
    return BLEND_DISABLE;
}

#endif