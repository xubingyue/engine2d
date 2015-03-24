//
//  render.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__render__
#define __engine2d__render__

#include <stdio.h>
#include "opengl.h"
typedef unsigned int RID;

struct render;
/**
 *  渲染配置
 */
struct render_init_args{
    int max_buffer;
    int max_layout;
    int max_target;
    int max_texture;//max 256
    int max_shader;
};

/**
 *  顶点
 */
struct vertex_attib {
    const char * name;
    int vbslot;
    int n;
    int size;
    int offset;
};

/**
 *  shader 配置
 */
struct shader_init_args{
    const char *vs;
    const char *fs;
    int texture;
    const char **texture_uniform;
};


enum RENDER_OBJ{
    INVALID = 0,
    VERTEXLAYOUT,
    VERTEXBUFFER,
    INDEXBUFFER,
    TEXTURE,
    TARGET,
    SHADER,
};


enum TEXTURE_TYPE{
    TEXTURE_2D = 0,
    TEXTURE_CUBE,
};

enum TEXTURE_FORMAT{
    TEXTURE_INVALID = 0,
    TEXTURE_RGBA8,
    TEXTURE_RGBA4,
    TEXTURE_RGB,
    TEXTURE_RGB565,
    TEXTURE_A8,
    TEXTURE_DEPTH,  // use for render target
    TEXTURE_PVR2,
    TEXTURE_PVR4,
    TEXTURE_ETC1,
};


enum BLEND_FORMAT{
    BLEND_DISABLE =0,
    BLEND_ZERO,
    BLEND_ONE,
    BLEND_SRC_COLOR,
    BLEND_ONE_MINUS_SRC_COLOR,
    BLEND_SRC_ALPHA,
    BLEND_ONE_MINUS_SRC_ALPHA,
    BLEND_DST_ALPHA,
    BLEND_ONE_MINUS_DST_ALPHA,
    BLEND_DST_COLOR,
    BLEND_ONE_MINUS_DST_COLOR,
    BLEND_SRC_ALPHA_SATURATE,
};

enum DEPTH_FORMAT{
    DEPTH_DISABLE = 0,
    DEPTH_LESS_EQUAL,
    DEPTH_LESS,
    DEPTH_EQUAL,
    DEPTH_GREATER,
    DEPTH_GREATER_EQUAL,
    DEPTH_ALWAYS,
};

enum CLEAR_MASK{
    MASKC = 0X1,
    MASKD = 0X2,
    MASKS = 0X4,
};

enum UNIFORM_FORMAT{
    UNIFORM_INVALID = 0,
    UNIFORM_FLOAT1,
    UNIFORM_FLOAT2,
    UNIFORM_FLOAT3,
    UNIFORM_FLOAT4,
    UNIFORM_FLOAT33,
    UNIFORM_FLOAT44,
};

enum DRAW_MODE{
    DRAW_TRIANGLE = 0,
    DRAW_LINE,
};

enum CULL_MODE{
    CULL_DISABLE = 0,
    CULL_FRONT,
    CULL_BACK,
};


int render_version(struct render *R);

int render_size(struct render_init_args *args);

struct render *
render_init(struct render_init_args *args,void *buffer,int sz);

void
render_exit(struct render *R);

void
render_set(struct render *R,enum RENDER_OBJ what,RID id, int slot);

void
render_release(struct render *R,enum RENDER_OBJ what,RID id);


RID
render_register_vertexlayout(struct render *R,int n, struct  vertex_attib * attrib);

//buffer
RID
render_buffer_create(struct render *R,enum RENDER_OBJ what,const void *data,
                     int n,int stride);
void
render_buffer_update(struct render *R,RID id,const void *data,int n);

//texture
RID
render_texture_create(struct render *R, int width, int height, enum TEXTURE_FORMAT format, enum TEXTURE_TYPE type, int mipmap);

void
render_texture_update(struct render *R,RID id ,int width,int height,const void *pixels,int slice,int miplevel);

void
render_texture_subupdate(struct render *R,RID id,const void *pixels,int x,int y,int w,int h);

//target
RID
render_target_create(struct render *R,int width,int height,enum TEXTURE_FORMAT format);
//render_release TARGET would not release the texture attchment
RID
render_target_texture(struct render *R,RID rt);


//shader
RID
render_shader_create(struct render *R, struct shader_init_args *args);

void
render_shader_bind(struct render *R,RID id);


int
render_shader_locuniform(struct render *R,const char *name);

void
render_shader_setuniform(struct render * R,int loc , enum UNIFORM_FORMAT format,const float *v);


void
render_setviewport(struct render *R,int x,int y,int width,int height);

void
render_setscissor(struct render *R , int x, int y,int w,int h);

void
render_setblend(struct render *R,enum BLEND_FORMAT src,enum BLEND_FORMAT dst);

void
render_setdepth(struct render *R, enum DEPTH_FORMAT d);

void
render_setcull(struct render *R, enum CULL_MODE c);

void
render_enabledepthmask(struct render *R,int enable);

void
render_enablescissor(struct render *R,int enable);

void
render_state_reset(struct render *R);

void
render_clear(struct render *R,enum CLEAR_MASK mask,unsigned long c);

void
render_draw(struct render *R,enum DRAW_MODE mode,int fromidx,int ni);



















#endif /* defined(__engine2d__render__) */
