//
//  winfw.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__winfw__
#define __engine2d__winfw__

#define WIDTH 1024
#define HEIGHT 768

#define TOUCH_BEGIN 0
#define TOUCH_END 1
#define TOUCH_MOVE 2


void engine2d_win_init(int orix,int oriy,int width,int height,float scale,const char* folder);

void engine2d_win_frame();

void engine2d_win_update();

void engine2d_win_touch(int x,int y,int touch);

void engine2d_win_resume();


#endif /* defined(__engine2d__winfw__) */
