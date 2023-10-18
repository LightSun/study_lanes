//
// Created by Administrator on 2019/7/24.
//

#ifndef COMMONLUAAPP_LUA_INTERNAL_H
#define COMMONLUAAPP_LUA_INTERNAL_H

#include "lua.h"
#include "string.h"
#include "stdio.h"

#define pro_concatStr(s1, s2, x) \
      const char* __str = concatStr(s1, s2); \
      (x); \
      free((void*)__str)

typedef void (*Lua_print)(void* ud, char* cs, int len, int flag);
const char* concatStr(const char *s1, const char *s2);

LUALIB_API void ext_setLua_print(Lua_print lp, void* ud);
/**
 * print the string . if success return 1. or else return 0.
 * @param cs
 * @param len
 * @param flag the flag of this print. if 1 means print right now. or else concat str
 */
LUALIB_API void ext_print(const char *cs, int len, int flag);

//static means internal func in c
LUALIB_API int luaB_dumpStack(lua_State* L);

//--------------------------
#define EXIT_PRINT

#ifdef EXIT_PRINT
#define __printImpl(s, l, f) \
        ext_print(s, l, f)
#define __flushPrint()  \
        ext_print("", 0, 1)
#else
#define __printImpl(s, l, f) \
       lua_writestring(s,l)
#define __flushPrint()  \
       lua_writeline();
#endif

#define ext_prints(cs) \
        ext_print(cs, 0, 0)
#define ext_println(cs) \
        ext_print((char* )cs, 0, 1)

#endif //COMMONLUAAPP_LUA_INTERNAL_H
