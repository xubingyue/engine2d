//
//  carray.c
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#include "carray.h"

#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "array.h"

// align to qword
#define ALIGN(n) (((n) + 7) & ~7)

struct array_node{
    struct array_node *next;
};

int
array_size(int n, int sz){
    sz = ALIGN(sz);
    return n * sz;
}
void
array_init(struct array *p ,void *buffer, int n, int nsz){
    int sz = ALIGN(nsz);
    char *ptr = (char*)buffer;
    int i ;
    for (i=0; i<n-1; i++) {
        struct array_node *node = (struct array_node*)(ptr+ i*sz);
        struct array_node *node_next = (struct array_node*)(ptr + (i+1)*sz);
        node->next = node_next;
    }
    struct array_node *node =(struct array_node*)(ptr + (n-1)*sz);
    node->next = NULL;
    p->n = n;
    p->sz = sz;
    p->buffer = (char*)buffer;
    p->freelist = (struct array_node*)buffer;
}

void *
array_alloc(struct array *p){
    struct array_node *node = p->freelist;
    if(node == NULL){
        return NULL;
    }
    p->freelist = node->next;
    memset(node, 0, p->sz);
    return node;
}

void
array_free(struct array *p,void *v){
    struct array_node *node = (struct array_node*)v;
    if(node){
        node->next = p->freelist;
        p->freelist = node;
    }
}

int
array_id(struct array *p ,void *v){
    if(v ==  NULL){
        return 0;
    }
    int idx = ((char*)v - p->buffer) / p->sz;
    assert(idx >= 0 && idx < p->n);
    return idx +1;
}
void *
array_ref(struct array *p,int id_){
    if(id_ == 0){
        return NULL;
    }
    --id_;
    assert(id_ >= 0 && id_ < p->n);
    void *ptr = p->buffer + p->sz * id_;
    return ptr;
}
void
array_exit(struct array *p,void (*close)(void *p ,void *ud),void *ud){
    ARRAY(char, flag, p->n);
    memset(flag, 0, p->n);
    struct array_node* node = p->freelist;
    while (node) {
        int idx = array_id(p, node) -1;
        flag[idx] = 1;
        node = node->next;
    }
    int i ;
    for (i=0; i<p->n; i++) {
        if(flag[i] == 0){
            struct array_node * n = (struct array_node *)array_ref(p, i + 1);
            close(n,ud);
        }
    }
}







