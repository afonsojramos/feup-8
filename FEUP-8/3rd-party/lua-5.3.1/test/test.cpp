// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

int _tmain(int argc, _TCHAR* argv[])
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	return 0;
}

