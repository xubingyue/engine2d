//
//  log.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__log__
#define __engine2d__log__

#include <stdio.h>
struct log{
    FILE *f;
};

void log_init(struct log*log,FILE *f);

void log_printf(struct log*log,const char* format,...);

#endif /* defined(__engine2d__log__) */
