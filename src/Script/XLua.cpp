//
// Created by xijezu on 17.02.17.
//

#include "XLua.h"

bool XLua::Init() {
	/* initialize Lua */
	m_lState = luaL_newstate();
	return !(luaL_loadfile(m_lState, "data/script/main.lua") || lua_pcall(m_lState, 0, 0, 0));
}