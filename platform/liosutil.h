//
//  liosutil.h
//  engine2d_ios
//
//  Created by TTc on 15-3-26.
//  Copyright (c) 2015年 liutianshx. All rights reserved.
//

#ifndef __engine2d_ios__liosutil__
#define __engine2d_ios__liosutil__

#include "lua.h"
#include "lauxlib.h"

int luaopen_osutil(lua_State* L);
int luaopen_ejoyplatform(lua_State *L);

#endif /* defined(__engine2d_ios__liosutil__) */
