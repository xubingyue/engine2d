//
//  winfw.c
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#include "opengl.h"
#include "engine2dgame.h"
#include "fault.h"
#include "screen.h"
#include "winfw.h"

#include "lauxlib.h"

#include <stdlib.h>
#include <stdio.h>

struct WINDOWGAME {
    struct game *game;
    int intouch;
};

static struct WINDOWGAME *G = NULL;

static const char * startscript =
"local path, script = ...\n"
"require(\"engine2d.framework\").WorkDir = path..'/'\n"
"assert(script, 'I need a script name')\n"
"script = path..[[/]]..script\n"
"package.path = path .. [[/?.lua;]] .. path .. [[/?/init.lua;./?.lua;./?/init.lua]]\n"
"local f = loadfile(script)\n"
"f(script)\n";

static struct WINDOWGAME *
create_game() {
    struct WINDOWGAME * g = malloc(sizeof(*g));
    g->game = engine2d_game();
    g->intouch = 0;
    return g;
}

static int
traceback(lua_State *L) {
    const char *msg = lua_tostring(L, 1);
    if (msg)
        luaL_traceback(L, L, msg, 1);
    else if (!lua_isnoneornil(L, 1)) {
        if (!luaL_callmeta(L, 1, "__tostring"))
            lua_pushliteral(L, "(no error message)");
    }
    return 1;
}


void
engine2d_win_init(int orix, int oriy, int width, int height, float scale, const char* folder) {
    G = create_game();
    lua_State *L = engine2d_game_lua(G->game);
    lua_pushcfunction(L, traceback);
    int tb = lua_gettop(L);
    int err = luaL_loadstring(L, startscript);
    if (err) {
        const char *msg = lua_tostring(L,-1);
        fault("%s", msg);
    }
    
    lua_pushstring(L, folder);
    lua_pushstring(L, "examples/test001.lua");
    //lua_pushstring(L, "examples/ex01.lua");
    //lua_pushstring(L, "examples/flappybird.lua");
    err = lua_pcall(L, 2, 0, tb);
    if (err) {
        const char *msg = lua_tostring(L,-1);
        fault("%s", msg);
    }
    
    lua_pop(L,1);
    
    screen_init(width,height,scale);
    engine2d_game_start(G->game);
}

void
engine2d_win_update() {
    engine2d_game_update(G->game, 0.01f);
}

void
engine2d_win_frame() {
    engine2d_game_drawframe(G->game);
}

void
engine2d_win_resume(){
    engine2d_game_resume(G->game);
}

void
engine2d_win_touch(int x, int y,int touch) {
    switch (touch) {
        case TOUCH_BEGIN:
            G->intouch = 1;
            break;
        case TOUCH_END:
            G->intouch = 0;
            break;
        case TOUCH_MOVE:
            if (!G->intouch) {
                return;
            }
            break;
    }
    // windows only support one touch id (0)
    int id = 0;
    engine2d_game_touch(G->game, id, x,y,touch);
}
