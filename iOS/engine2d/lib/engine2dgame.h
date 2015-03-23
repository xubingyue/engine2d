//
//  engine2dgame.h
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#ifndef __engine2d__engine2dgame__
#define __engine2d__engine2dgame__

#include "lua.h"
struct game{
    lua_State *L;
    float real_time;
    float logic_time;
};


struct game * engine2d_game();

lua_State * engine2d_lua_init();

void engine2d_game_exit(struct game * g);

void engine2d_close_lua(struct game * g);

lua_State * engine2d_game_lua(struct game *g);

void engine2d_handle_error(lua_State *L,const char * err_type,const char *err_msg);

void engine2d_game_logicframe(int frame);

void engine2d_game_start(struct game *g);

void engine2d_game_update(struct game *g,float dt);

void engine2d_game_drawframe(struct game *g);

int engine2d_game_touch(struct game *, int id, float x, float y, int status);

void engine2d_game_gesture(struct game *, int type,
                         double x1, double y1, double x2, double y2, int s);

void engine2d_game_message(struct game *G,int id_,const char* state, const char* data, lua_Number n);

void engine2d_game_pause(struct game *G);

void engine2d_game_resume(struct game *G);

void engine2d_call_lua(lua_State *L,int n,int r);



#endif /* defined(__engine2d__engine2dgame__) */
