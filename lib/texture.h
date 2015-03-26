//
//  texture.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__texture__
#define __engine2d__texture__

#include <stdio.h>
#include "render.h"

void texture_initrender(struct render *r);

const char* texture_load(int id_,enum TEXTURE_FORMAT type,int width,int height,void *buffer, int reduce);

void texture_unload(int id_);

RID texture_glid(int id);

int
texture_coord(int id , float x,float y,uint16_t *u,uint16_t *v);

void
texture_clearall();

void
texture_exit();

const char *
texture_new_rt(int id,int w,int h);

const char*
texture_active_rt(int id);

void
texture_set_inv(int id,float invw,float invh);

void
texture_swap(int ida, int idb);

void
texture_size(int id ,int *width,int *height);

void
texture_delete_framebuffer(int id);

const char *
texture_update(int id,int pixel_width,int pixel_height,void *data);


const char*
texture_sub_update(int id, int x, int y, int width, int height, void *data) ;

#endif /* defined(__engine2d__texture__) */
