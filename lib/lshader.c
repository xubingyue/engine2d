//
//  lshader.c
//  engine2d
//
//  Created by TTc on 14-3-19.
//  Copyright (c) 2015年 liutianshx. All rights reserved.
//

#include "lua.h"
#include "lauxlib.h"
#include <string.h>

#include "shader.h"
#include "screen.h"
#include "texture.h"
#include "array.h"
#include "render.h"
#include "material.h"
#include "fault.h"


static int
lload(lua_State *L){
    int prog = (int)luaL_checkinteger(L, 1);
    const char *fs = luaL_checkstring(L, 2);
    const char *vs = luaL_checkstring(L, 3);
    if(lua_istable(L, 4)){
        int texture_number = lua_rawlen(L, 4);
        ARRAY(const char *, name, texture_number);
        luaL_checkstack(L, texture_number +1, NULL);
        int i;
        for (i=0; i<texture_number; i++) {
            lua_rawgeti(L, -1-i, i+1);
            name[i] = luaL_checkstring(L, -1);
        }
        shader_load(prog, fs, vs, texture_number, name);
    }else{
        shader_load(prog, fs, vs, 0, NULL);
    }
    return 0;
}


static int
lunload(lua_State *L){
    shader_unload();
    return 0;
}



static int
ldraw(lua_State *L){


    return 0;
}

static int
lblend(lua_State *L){
    if(lua_isnoneornil(L, 1)){
        shader_defaultblend();
    }else{
        int m1 = (int)luaL_checkinteger(L, 1);
        int m2 = (int)luaL_checkinteger(L, 2);
        shader_blend(m1, m2);
    }
    return 0;
}

static int
lversion(lua_State*L){
    lua_pushinteger(L, shader_version());
    return 1;
}

static int
lclear(lua_State *L){
    lua_pushinteger(L, shader_version());
    return 1;
}

static int
luniform_bind(lua_State *L){
    int prog = luaL_checkinteger(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    int n = lua_rawlen(L, 2);
    int i ;
    for (i=0; i<n; i++) {
        lua_rawgeti(L, -1, i+1);
        lua_getfield(L, -1, "name");
        const char *name = luaL_checkstring(L, -1);
        lua_getfield(L, -2, "type");
        enum UNIFORM_FORMAT format = (enum UNIFORM_FORMAT)luaL_checkinteger(L, -1);
        int loc = shader_adduniform(prog, name, format);
        if(loc != i){
            fault("!waring : Invalid uniform local");
        }
        lua_pop(L, 3);
    }
    return 0;
}

static int
luniform_set(lua_State *L){
    int prog = luaL_checkinteger(L, 1);
    int index = luaL_checkinteger(L, 2);
    enum UNIFORM_FORMAT format = (enum UNIFORM_FORMAT)luaL_checkinteger(L, 3);
    float v[16];
    int n = shader_uniformsize(format);
    if(n == 0){
        return luaL_error(L, "Invalid uniform format %d",format);
    }
    int top = lua_gettop(L);
    if(top != n + 3){
        return luaL_error(L, "Need float %d,only %d passed",top,n-3);
    }
    int i;
    for(i=0;i<n;i++){
        v[i] = luaL_checknumber(L, 4+i);
    }
    shader_setuniform(prog, index, format, v);
    return 0;
}


static int
lmaterial_setuniform(lua_State *L){
    struct material * m = (struct material *)lua_touserdata(L, 1);
    int index = luaL_checkinteger(L, 2);
    float v[16];
    int top = lua_gettop(L);
    if(top > sizeof(v) / sizeof(v[0]) + 2){
        return luaL_error(L, "too many agrument");
    }
    int n = top -2 ;
    int i;
    for (i=0; i<n; i++) {
        v[i] = luaL_checknumber(L, 3 + i);
    }
    if(material_setuniform(m, index, n, v)){
        return luaL_error(L, "Invaild argument number %d",n);
    }
    return 0;
}

static int
lmaterial_settexture(lua_State *L){
    struct material * m = (struct material *)lua_touserdata(L, 1);
    int id = (int)luaL_checkinteger(L, 2);
    int channel = luaL_optinteger(L, 3, 0);
    if(material_settexture(m, channel, id)){
        return luaL_error(L, "Invaild argument texture channel%d",channel);
    }
    return 0;
}

static int
lshader_texture(lua_State *L){
    RID id = 0;
    if(!lua_isnoneornil(L, 1)){
        int texid = luaL_checkinteger(L, 1);
        id = texture_glid(texid);
    }
    int channel = luaL_optinteger(L, 2, 0);
    shader_texture(id, channel);
    return 0;
}

int
engine2d_shader(lua_State *L){
    luaL_Reg l[] ={
        {"load",lload},
        {"unload",lunload},
        {"draw",ldraw},
        {"blend",lblend},
        {"version",lversion},
        {"clear",lclear},
        {"uniform_bind",luniform_bind},
        {"uniform_set",luniform_set},
        {"material_setuniform",lmaterial_setuniform},
        {"material_settexture",lmaterial_settexture},
        {"shader_texture",lshader_texture},
        {NULL,NULL},
    };
    luaL_newlib(L, l);
    return 1;
}