//
//  sprite.h
//  engine2d
//
//  Created by TTc on 14-3-19.
//  Copyright (c) 2015年 liutianshx. All rights reserved.
//

#ifndef __engine2d__sprite__
#define __engine2d__sprite__
#include "spritepack.h"
#include "matrix.h"

#include "lua.h"
#include <stdint.h>
#include <stdbool.h>

struct material;

struct anchor_data{
    struct particle_system *ps;
    struct pack_picture *pic;
    struct matrix mat;
};

struct sprite{
    struct sprite *parent;
    uint16_t type;
    uint16_t   id;
    struct sprite_trans t;
    union{
        struct pack_animation *ani;
        struct pack_picture   *pic;
        struct pack_polygon   *poly;
        struct pack_label     *label;
        struct pack_pannel    *pannel;
        struct matrix         *mat;
    } s;
    struct  matrix mat;
    int start_frame;
    int total_frame;
    int frame;
    bool visible;
    bool message;
    bool multimount;
    const char *name;
    struct material *material;
    union{
        struct sprite * children[1];
        struct rich_text* rich_text;
        int scissor;
        
        struct anchor_data *anchor;
    } data;
};


const char *
sprite_childname(struct sprite *s, int index);

void
sprite_init(struct sprite *s,struct sprite_pack * pack,int id,int sz);

int
sprite_action(struct sprite *s ,const char *action);

int
sprite_size(struct sprite_pack *pack ,int id);


struct sprite_trans *
sprite_trans_mul(struct sprite_trans *a,struct sprite_trans *b,
                 struct sprite_trans *t,struct matrix *tmp_matrix);

void
sprite_drawquad(struct pack_picture *picture ,const struct srt *srt ,
                const struct sprite_trans *arg);

void
sprite_drawpolygon(struct pack_polygon *poly, const struct srt *srt,
                   const struct sprite_trans *arg);

void sprite_draw(struct sprite *s,struct srt * srt);

void
sprite_draw_as_child(struct sprite *s,struct srt *srt,struct matrix *mat, uint32_t color);


// todo: maybe unused, use sprite_matrix instead
int
sprite_pos(struct sprite *s,struct srt *srt,struct matrix *mat , int pos[2]);

void
sprite_matrix(struct sprite * self, struct matrix *mat);

bool
sprite_child_visible(struct sprite *s,const char *childname);

int
sprite_material_size(struct sprite *s);

void
sprite_aabb(struct sprite *s, struct srt *srt, bool world_aabb, int aabb[4]);

void
sprite_mount(struct sprite *parent, int index, struct sprite *child);

int
sprite_setframe(struct sprite *s, int frame, bool force_child);

// return sprite id in pack, -1 for end
int
sprite_component(struct sprite *s, int index);

int
sprite_child_ptr(struct sprite *s, struct sprite *child);

// return child index, -1 means not found
int
sprite_child(struct sprite *s, const char * childname);

struct sprite *
sprite_test(struct sprite *s, struct srt *srt, int x, int y);

int
engine2d_sprite(lua_State *L);


#endif /* defined(__engine2d__sprite__) */
