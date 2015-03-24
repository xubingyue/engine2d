//
//  carray.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__carray__
#define __engine2d__carray__

struct array_node;

struct array{
    int n;        //下标
    int sz;       //长度
    char * buffer;//数据
    struct array_node * freelist;
};

void array_init(struct array *p ,void *buffer, int n, int sz);

void * array_alloc(struct array *p);

void array_free(struct array *p,void *v);

void array_exit(struct array *p,void (*close)(void *p ,void *ud),void *ud);

int array_id(struct array *p ,void *);

int array_size(int n, int sz);

void * array_ref(struct array *p,int id_);



#endif /* defined(__engine2d__carray__) */
