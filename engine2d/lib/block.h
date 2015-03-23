//
//  block.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef engine2d_block_h
#define engine2d_block_h

#include <stdlib.h>

struct block{
    char  *buffer;
    int sz;
};

static inline void
block_init(struct block *b ,void *buffer, int sz){
    b->buffer = buffer;
    b->sz = sz;
}

static inline void *
block_slice(struct block *b ,int sz){
    if(b->sz < sz){
        return NULL;
    }
    void *ret = b->buffer;
    b->buffer += sz;
    b->sz -= sz;
    return ret;
}

#endif
