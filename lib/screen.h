//
//  screen.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__screen__
#define __engine2d__screen__

#include <stdbool.h>
struct render;

void screen_initrender(struct render *R);
void screen_init(float w,float h,float scale);
void screen_trans(float *x,float *y);
void screen_scissor(int x,int y ,int w,int h);
bool screen_is_visible(float x,float y);


#endif /* defined(__engine2d__screen__) */
