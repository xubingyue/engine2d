//
//  renderbuffer.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__renderbuffer__
#define __engine2d__renderbuffer__

#include <stdio.h>
#include "render.h"

#include "lua.h"
#define MAX_COMMBINE 1024


struct sprite;

struct vertex_pack{
    float vx;
    float vy;
    uint16_t tx;
    uint16_t ty;
};

struct vertex{
    struct vertex_pack vp;
    uint8_t rgba[4];
    uint8_t add[4];
};

struct quad{
    struct vertex p[4];
};

struct render_buffer{
    int object;
    int texid;
    RID vbid;
    struct quad vb[MAX_COMMBINE];
};


void renderbuffer_initrender(struct render *R);

void renderbuffer_init(struct render_buffer *rb);

void renderbuffer_upload(struct render_buffer *rb);

void renderbuffer_unload(struct render_buffer *rb);

int renderbuffer_add (struct  render_buffer *rb ,const struct vertex_pack vb[4], uint32_t color, uint32_t additive);


int renderbuffer_drawsprite(struct render_buffer *rb , struct sprite *s);

int
engine2d_renderbuffer(lua_State *L);

#endif /* defined(__engine2d__renderbuffer__) */
