//
//  fault.c
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


#include "fault.h"
#include "platform_print.h"

void
fault(const char * format,...){
    if(format[0] == '!'){
        va_list ap;
        va_start(ap, format);
        pf_vprint(format+1,ap);
        va_end(ap);
    }else{
        va_list ap;
        va_start(ap, format);
        pf_vprint(format,ap);
        va_end(ap);
        exit(1);
    }
}