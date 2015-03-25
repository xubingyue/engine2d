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


struct STARTUP_INFO{
    float orix,oriy;
    float width,height;
    float scale;
    char *folder;
    char *script;
    void *serialized;
    int reload_count;
};

void engine2d_win_init(struct STARTUP_INFO* startup);

void engine2d_win_frame();

void engine2d_win_update(float delta);

int engine2d_win_touch(int x,int y,int touch);

void engine2d_win_resume();

void engine2d_win_gesture(int type, float x1, float y1, float x2, float y2, int state);

void engine2d_win_view_layout(int start, float x, float y, float w, float h);


#endif /* defined(__engine2d__winfw__) */
