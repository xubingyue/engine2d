//
//  filesystem.c
//  engine2d_ios
//
//  Created by TTc on 15-3-26.
//  Copyright (c) 2015年 liutianshx. All rights reserved.
//

#include "filesystem.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <stdarg.h>
const char * BundlePath(const char * filename, const char *type, const char *directory);

struct FileHandle{
    FILE *fp;
};

struct FileHandle* pf_fileopen(const char *path, const char* format) {
    FILE* _fp = fopen(path, format);
    //    printf("\nopen path: %s\n", path);
    if(_fp){
        struct FileHandle* ret = malloc(sizeof(*ret));
        ret->fp = _fp;
        return ret;
    }else
        return NULL;
}


struct FileHandle* pf_bundleopen(const char* filename, const char* format){
    //    const char* path = BundlePath(filename, "", NULL);
    //    return (path)?(pf_fileopen(path, format)):(NULL);
    return NULL;
}

size_t pf_filesize(struct FileHandle* h) {
    size_t save_pos = ftell(h->fp);
    fseek(h->fp, 0, SEEK_END);
    size_t sz = ftell(h->fp);
    fseek(h->fp, save_pos, SEEK_SET);
    return sz;
}

int pf_fileread(struct FileHandle* h, void *buffer, size_t size) {
    return fread(buffer, size, 1, h->fp);
}

size_t pf_fread(void *ptr, size_t size, size_t nmemb, struct FileHandle *h) {
    return fread(ptr, size, nmemb, h->fp);
}

void pf_fileseek_from_cur(struct FileHandle* h, int offset) {
    fseek(h->fp, offset, SEEK_CUR);
}

void pf_fileseek_from_head(struct FileHandle* h, int offset) {
    fseek(h->fp, offset, SEEK_SET);
}

void pf_fileclose(struct FileHandle* h) {
    if(h==NULL) return;
    
    if(h->fp)
        fclose(h->fp);
    free(h);
}

int pf_feof(struct FileHandle* h) {
    return feof(h->fp);
}

void pf_log(const char * format, ...) {
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}
