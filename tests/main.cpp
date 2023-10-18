extern "C"{
   #include "lanes.h"
}
#include "lua.hpp"

#define _LUA_SCRIPT_DIR "/home/heaven7/heaven7/study/github/thirds/lanes/tests/"
//http://lualanes.github.io/lanes/

int load_lanes_lua( lua_State* L)
{
    // retrieve lanes.lua from wherever it is stored and return the result of its execution
    // trivial example 1:
    luaL_dofile( L, _LUA_SCRIPT_DIR "lanes.lua");

    // trivial example 2:
   // luaL_dostring( L, bin2c_lanes_lua);
    return 0;
}

void embed_lanes( lua_State* L)
{
    // we need base libraries for Lanes for work
    luaL_openlibs( L);
    // will attempt luaL_dofile( L, "lanes.lua");
    //luaopen_lanes_embedded( L, NULL);
    //lua_pop( L, 1);
    // another example with a custom loader
    luaopen_lanes_embedded( L, load_lanes_lua);
    lua_pop( L, 1);

    // a little test to make sure things work as expected
    luaL_dostring( L, "local lanes = require 'lanes'.configure{with_timers = false}; print('lanes:', lanes); local l = lanes.linda()");
}

int main(int argc, char* argv[]){
    setbuf(stdout, NULL);
    auto L = luaL_newstate();
    embed_lanes(L);

    lua_close(L);
    return 0;
}
