//
//  engine2dgame.c
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <assert.h>

#include "engine2dgame.h"
#include "label.h"
#include "fault.h"
#include "shader.h"
#include "texture.h"
#include "ppm.h"
#include "spritepack.h"
#include "sprite.h"
#include "matrix.h"
#include "particle.h"
#include "lmatrix.h"


#define ENGINE_INIT "ENGINE2D_INIT"
#define ENGINE_UPDATE "ENGINE2D_UPDATE"
#define ENGINE_DRAWFRAME "ENGINE2D_DRAWFRAME"
#define ENGINE_TOUCH "ENGINE2D_TOUCH"
#define ENGINE_GESTURE "ENGINE2D_GESTURE"
#define ENGINE_MESSAGE "ENGINE2D_MESSAGE"
#define ENGINE_HANDLE_ERROR "ENGINE2D_HANDLE_ERROR"
#define ENGINE_RESUME "ENGINE2D_RESUME"
#define ENGINE_PAUSE "ENGINE2D_PAUSE"


#define TRACEBACK_FUNCTION  1
#define UPDATE_FUNCTION     2
#define DRAWFRAME_FUNCTION  3
#define TOP_FUNCTION        3

static int LOGIC_FRAME = 30;


static int
_panic(lua_State *L){
    const char *err = lua_tostring(L, -1);
    fault("%s",err);
    return 0;
}


static int
linject(lua_State *L){
    static const char * engine_callback[] = {
        ENGINE_INIT,
        ENGINE_UPDATE,
        ENGINE_DRAWFRAME,
        ENGINE_TOUCH,
        ENGINE_GESTURE,
        ENGINE_MESSAGE,
        ENGINE_HANDLE_ERROR,
        ENGINE_RESUME,
        ENGINE_PAUSE,
    };
    int i ;
    for (i=0; i<sizeof(engine_callback)/sizeof(engine_callback[0]); i++) {
        lua_getfield(L, lua_upvalueindex(i), engine_callback[i]);
        if(!lua_isfunction(L, -1)){
            return luaL_error(L, "%s is not found",engine_callback[i]);
        }
        lua_setfield(L, LUA_REGISTRYINDEX, engine_callback[i]);
    }
    return 0;
}


static int
engine2d_framework(lua_State*L){
    luaL_Reg l[] = {
        {"inject",linject},
        {NULL,NULL},
    };
    luaL_newlibtable(L,l);
    lua_pushvalue(L, -1);
    luaL_setfuncs(L,l,1);
    return 1;
}

static void
checkluaversion(lua_State *L){
    const lua_Number *v = lua_version(L);
    if(v != lua_version(NULL)){
        fault("multiple Lua VMs detected");
    }else if(*v != LUA_VERSION_NUM){
        fault("Lua version mismatch: app. needs %f, Lua core provides %f",LUA_VERSION_NUM,*v);
    }
}
#if __ANDROID__
#define OS_STRING "ANDROID"
#else
#define STR_VALUE(arg)	#arg
#define _OS_STRING(name) STR_VALUE(name)
#define OS_STRING _OS_STRING(ENGINE2D_OS)
#endif



struct game *
engine2d_game(){
    struct game *G = (struct game *)malloc(sizeof(*G));
    lua_State *L = engine2d_lua_init();
    
    G->L = L;
    G->real_time = 0;
    G->logic_time = 0;
    // load lua lib
    luaL_requiref(L, "engine2d.shader.c", engine2d_shader, 0);
    luaL_requiref(L, "engine2d.framework", engine2d_framework, 0);
    luaL_requiref(L, "engine2d.ppm", engine2d_ppm, 0);
    luaL_requiref(L, "engine2d.spritepack.c", engine2d_spritepack, 0);
    luaL_requiref(L, "engine2d.sprite.c", engine2d_sprite, 0);
    luaL_requiref(L, "engine2d.renderbuffer", engine2d_renderbuffer, 0);
    luaL_requiref(L, "engine2d.matrix.c", engine2d_matrix, 0);
    luaL_requiref(L, "ejoy2d.particle.c", engine2d_particle, 0);

    lua_settop(L, 0);
    shader_init();
    label_load();
    
    return G;
}


lua_State *
engine2d_lua_init(){
    lua_State * L = luaL_newstate();
    checkluaversion(L);
    lua_pushliteral(L, OS_STRING);
    lua_setglobal(L, "OS");
    
    lua_atpanic(L, _panic);
    luaL_openlibs(L);
    return L;
}






void
engine2d_game_exit(struct game * g){
    engine2d_close_lua(g);
    //...todo  unload  shader
    label_unload();
    texture_exit();
    shader_unload();
}


void
engine2d_close_lua(struct game * g){
    if(g){
        if(g->L){
            lua_close(g->L);
            g->L = NULL;
        }
        free(g);
    }
}

lua_State *
engine2d_game_lua(struct game *g){
    return g->L;
}


static int
traceback(lua_State *L){
    const char *msg = lua_tostring(L, 1);
    if(msg){
        luaL_traceback(L, L, msg, 1);
    }else if(!lua_isnoneornil(L, 1)){
        if(!luaL_callmeta(L, 1, "__tostring")){
            lua_pushliteral(L, "(no error message)");
        }
    }
    return 1;
}


void
engine2d_game_logicframe(int frame){
    LOGIC_FRAME = frame;
}

void
engine2d_game_start(struct game *g){
    lua_State *L = g->L;
    lua_getfield(L, LUA_REGISTRYINDEX, ENGINE_INIT);
    lua_call(L, 0, 0);
    assert(lua_gettop(L)==0);
    lua_pushcfunction(L, traceback);
    lua_getfield(L,LUA_REGISTRYINDEX, ENGINE_UPDATE);
    lua_getfield(L,LUA_REGISTRYINDEX, ENGINE_DRAWFRAME);
    lua_getfield(L,LUA_REGISTRYINDEX, ENGINE_MESSAGE);
    lua_getfield(L,LUA_REGISTRYINDEX, ENGINE_RESUME);
    lua_getfield(L,LUA_REGISTRYINDEX, ENGINE_PAUSE);

}


void
engine2d_handle_error(lua_State *L,const char * err_type,const char *err_msg){
    lua_getfield(L, LUA_REGISTRYINDEX, ENGINE_HANDLE_ERROR);
    lua_pushstring(L, err_type);
    lua_pushstring(L, err_msg);
    int err = lua_pcall(L, 2, 0,0);
    switch(err) {
        case LUA_OK:
            break;
        case LUA_ERRRUN:
            fault("!LUA_ERRRUN : %s\n", lua_tostring(L,-1));
            break;
        case LUA_ERRMEM:
            fault("!LUA_ERRMEM : %s\n", lua_tostring(L,-1));
            break;
        case LUA_ERRERR:
            fault("!LUA_ERRERR : %s\n", lua_tostring(L,-1));
            break;
        case LUA_ERRGCMM:
            fault("!LUA_ERRGCMM : %s\n", lua_tostring(L,-1));
            break;
        default:
            fault("!Unknown Lua error: %d\n", err);
            break;
    }
}



static int
call(lua_State *L,int n,int r){
    int err = lua_pcall(L, n, r, TRACEBACK_FUNCTION);
    switch(err) {
        case LUA_OK:
            break;
        case LUA_ERRRUN:
            engine2d_handle_error(L, "LUA_ERRRUN", lua_tostring(L,-1));
            fault("!LUA_ERRRUN : %s\n", lua_tostring(L,-1));
            break;
        case LUA_ERRMEM:
            engine2d_handle_error(L, "LUA_ERRMEM", lua_tostring(L,-1));
            fault("!LUA_ERRMEM : %s\n", lua_tostring(L,-1));
            break;
        case LUA_ERRERR:
            engine2d_handle_error(L, "LUA_ERRERR", lua_tostring(L,-1));
            fault("!LUA_ERRERR : %s\n", lua_tostring(L,-1));
            break;
        case LUA_ERRGCMM:
            engine2d_handle_error(L, "LUA_ERRGCMM", lua_tostring(L,-1));
            fault("!LUA_ERRGCMM : %s\n", lua_tostring(L,-1));
            break;
        default:
            engine2d_handle_error(L, "UnknownError", "Unknown");
            fault("!Unknown Lua error: %d\n", err);
            break;
    }
    return err;
}

static void
logic_frame(lua_State *L){
    lua_pushvalue(L, UPDATE_FUNCTION);
    call(L,0,0);
}

void
engine2d_game_update(struct game *g,float dt_time){
    if(g->logic_time == 0){
        g->real_time = 1.0/LOGIC_FRAME;
    } else {
        g->real_time += dt_time;
    }
    while (g->logic_time < g->real_time) {
        logic_frame(g->L);
        g->logic_time += 1.0f/LOGIC_FRAME;
    }
}

void
engine2d_game_drawframe(struct game *g){
    reset_drawcall_count();
    lua_pushvalue(g->L, DRAWFRAME_FUNCTION);
    call(g->L, 0, 0);
    lua_settop(g->L, TOP_FUNCTION);
    shader_flush();
    label_flush();
}


int
engine2d_game_touch(struct game *g, int id, float x, float y, int status){
    int disable_gesture = 0;
    lua_getfield(g->L, LUA_REGISTRYINDEX, ENGINE_TOUCH);
    lua_pushnumber(g->L, x);
    lua_pushnumber(g->L, y);
    lua_pushinteger(g->L, status+1);
    lua_pushinteger(g->L, id);
    int err = call(g->L, 4, 1);
    if(err == LUA_OK){
        disable_gesture = lua_toboolean(g->L, -1);
    }
    lua_settop(g->L, TOP_FUNCTION);
    return disable_gesture;
}

void
engine2d_game_gesture(struct game *g, int type,
                      double x1, double y1, double x2, double y2, int s){
    lua_getfield(g->L, LUA_REGISTRYINDEX, ENGINE_GESTURE);
    lua_pushnumber(g->L, type);
    lua_pushnumber(g->L, x1);
    lua_pushnumber(g->L, y1);
    lua_pushnumber(g->L, x2);
    lua_pushnumber(g->L, y2);
    lua_pushinteger(g->L, s);
    call(g->L, 6, 0);
    lua_settop(g->L, TOP_FUNCTION);
}


void
engine2d_game_message(struct game *g,int id_,const char* state, const char* data, lua_Number n){
    lua_State *L = g->L;
    lua_getfield(L,LUA_REGISTRYINDEX, ENGINE_MESSAGE);
    lua_pushnumber(L, id_);
    lua_pushstring(L, state);
    lua_pushstring(L, data);
    lua_pushnumber(L, n);
    call(L, 4, 0);
    lua_settop(L, TOP_FUNCTION);
}



void
engine2d_game_pause(struct game *G){
    lua_State *L = G->L;
    lua_getfield(L, LUA_REGISTRYINDEX, ENGINE_PAUSE);
    call(L, 0, 0);
    lua_settop(L, TOP_FUNCTION);
}

void
engine2d_game_resume(struct game *G){
    lua_State *L = G->L;
    lua_getfield(L, LUA_REGISTRYINDEX, ENGINE_RESUME);
    call(L, 0, 0);
    lua_settop(L, TOP_FUNCTION);
}

void
engine2d_call_lua(lua_State *L,int n,int r){
    call(L, n, r);
    lua_settop(L, TOP_FUNCTION);
}

