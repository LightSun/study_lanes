//
// Created by Administrator on 2019/7/24.
//

#include "lua_internal.h"

#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

const char* concatStr(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    if (result == NULL) exit (1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

LUALIB_API int luaB_dumpStack(lua_State* L){
    __printImpl("\nbegin dump lua stack: ", 0, 1);
    int i = 0;
    int top = lua_gettop(L);

    char buf[20]; //if string is to long. may cause stack exception.
    for (i = 1; i <= top; ++i) {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:
            {
                pro_concatStr(lua_tostring(L, i), " ", __printImpl(__str, 0, 0));
            }
                break;
            case LUA_TBOOLEAN:
            {
                __printImpl(lua_toboolean(L, i) ? "true " : "false ", 0, 0);
            }
                break;

            case LUA_TNUMBER:
            {
                sprintf(buf, "%g ", lua_tonumber(L, i));
                __printImpl(buf, 0, 0);
            }
                break;
            default:
            {
                sprintf(buf, "%s ", lua_typename(L, t));
                __printImpl(buf, 0, 0);
            }
                break;
        }
    }
    __flushPrint();
    return 0;
}
//---------------------------
Lua_print _func_print = NULL;
void* _ud;
void ext_setLua_print(Lua_print lp, void* ud){
    _func_print = lp;
    _ud = ud;
}
void ext_print(const char *cs, int len, int flag){
    _func_print(_ud, (char*)cs, len ,flag);
}
