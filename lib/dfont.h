//
//  dfont.h
//  engine2d
//
//  Created by TTc on 14-3-20.
//  Copyright (c) 2015年 liutianshx. All rights reserved.
//

#ifndef __engine2d__dfont__
#define __engine2d__dfont__

#include <stdio.h>

struct dfont;

struct dfont_rect {
    int x;
    int y;
    int w;
    int h;
};

struct dfont * dfont_create(int width, int height);

void dfont_release(struct dfont *);

const struct dfont_rect * dfont_lookup(struct dfont *, int c, int font, int edge);

const struct dfont_rect * dfont_insert(struct dfont *, int c, int font, int width, int height, int edge);

void dfont_remove(struct dfont *, int c, int font, int edge);

void dfont_flush(struct dfont *);

void dfont_dump(struct dfont *); // for debug

size_t dfont_data_size(int width, int height);

void dfont_init(void* d, int width, int height);

#endif /* defined(__engine2d__dfont__) */
