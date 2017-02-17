//
// Created by xijezu on 17.02.17.
//

#ifndef POKEMON_XICI_XLUA_H
#define POKEMON_XICI_XLUA_H

#include <string>
#include <lua5.2/lua.hpp>
#include <memory>

class XLua {
public:
	static XLua &GetInstance() {
		static XLua instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	// De-constructor
	XLua(XLua const &) = delete;

	void operator=(XLua const &) = delete;

	XLua() {};

	bool Init();

	void Execute(std::string, ...);

private:
	lua_State *m_lState;
};

#define g_XLua XLua::GetInstance()

#endif //POKEMON_XICI_XLUA_H
