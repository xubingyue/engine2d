//
//  lualibs.c
//  engine2d_ios
//
//  Created by TTc on 15-3-26.
//  Copyright (c) 2015年 liutianshx. All rights reserved.
//

#include "lualibs.h"
#include "lauxlib.h"

int luaopen_image(lua_State *L);
int luaopen_serialize(lua_State *L);
int luaopen_osutil(lua_State *L);
int luaopen_monitor(lua_State*L);

static void
_register(lua_State *L,lua_CFunction func,const char*libname){
    luaL_requiref(L, libname, func, 0);
    lua_pop(L, 1);
}


void
init_lua_libs(lua_State *L){
    _register(L, luaopen_image, "engine2d.image.c");
    _register(L, luaopen_osutil, "engine2d.osutils.c");
    _register(L, luaopen_serialize, "engine2d.serialize.c");

#ifdef DEBUG
    _register(L, luaopen_monitor, "engine2d.lmonitor.c");
#endif
    
}