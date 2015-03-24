//
//  material.h
//  engine2d
//
//  Created by TTc on 14-3-18.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__material__
#define __engine2d__material__


//the implemention is in shader.c

struct material;
struct render;

int material_size(int prog);

struct material * material_init(void*self,int size,int prog);

void material_apply(int prog,struct material *m);

int material_setuniform(struct material *,int index,int n,const float *v);

int material_settexture(struct material *,int channel,int texture);
// todo: change alpha blender mode, change attrib layout, etc.


#endif /* defined(__engine2d__material__) */
