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

#ifndef LOGIC_FRAME
#define LOGIC_FRAME 30
#endif

struct WINDOWGAME {
    struct game *game;
    int intouch;
};

static struct WINDOWGAME *G = NULL;
static struct STARTUP_INFO *STARTUP = NULL;

static const char * startscript =
"local path, script = ...\n"
"require(\"engine2d.framework\").WorkDir = path..'/'\n"
"assert(script, 'I need a script name')\n"
"script = path..[[/]]..script\n"
"package.path = path .. [[/?.lua;]] .. path .. [[/?/init.lua;./?.lua;./?/init.lua]]\n"
"package.path = package.path..'/src/?.lua;'\n"

"print(\"package.path==> \",package.path)"
"local f = loadfile(script)\n"
"f(script)\n";


//static const char * startscript =
//"local path, script, sw, sh, ss = ...\n"
//"local fw = require('engine2d.framework')\n"
//"fw.WorkDir = path..'/'\n"
//"fw.ScreenWidth, fw.ScreenHeight, fw.ScreenScale = sw, sh, ss\n"
//"assert(script, 'I need a script name')\n"
//"script = path..'/'..script\n"
//"package.path = './?.lua;./?/init.lua;'\n"
//"package.path = package.path..path..'/?.lua;'\n"
//"package.path = package.path..path..'/?/init.lua;'\n"
//"package.path = package.path..path..'/src/?.lua;'\n"
//"print(\"package.path==> \",package.path)"
//"local f = loadfile(script)\n"
//"f(script)\n";

static struct WINDOWGAME *
create_game() {
    struct WINDOWGAME * g = (struct WINDOWGAME *)malloc(sizeof(*g));
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
engine2d_win_init(struct STARTUP_INFO* startup) {
    STARTUP = startup;
    G = create_game();
    
    lua_State *L = engine2d_game_lua(G->game);
    
    lua_pushcfunction(L, traceback);
    
    int tb = lua_gettop(L);
    int err = luaL_loadstring(L, startscript);
    if (err) {
        const char *msg = lua_tostring(L,-1);
        fault("%s", msg);
    }
    
    lua_pushstring(L, startup->folder);
    lua_pushstring(L, startup->script);
    err = lua_pcall(L, 2, 0, tb);
    if (err) {
        const char *msg = lua_tostring(L,-1);
        fault("%s", msg);
    }
    
    lua_pop(L,1);
    
    screen_init(startup->width, startup->height, startup->scale);

    //engine2d_game_logicframe(LOGIC_FRAME);

    engine2d_game_start(G->game);
}

void
engine2d_win_update(float delta) {
    engine2d_game_update(G->game, delta);
}

void
engine2d_win_frame() {
    engine2d_game_drawframe(G->game);
}

void
engine2d_win_resume(){
    engine2d_game_resume(G->game);
}

int
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
                return 0;
            }
            break;
    }
    // windows only support one touch id (0)
    int id = 0;
   return  engine2d_game_touch(G->game, id, x,y,touch);
}

void
engine2d_win_gesture(int type, float x1, float y1, float x2, float y2, int state){
    engine2d_game_gesture(G->game, type, x1, y1, x2, y2, state);
}

void
engine2d_win_view_layout(int start, float x, float y, float w, float h){
    engine2d_game_view_layout(G->game, start, x, y, w, h);
}







