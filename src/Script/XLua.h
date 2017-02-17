//
// Created by xijezu on 17.02.17.
//

#ifndef POKEMON_XICI_XLUA_H
#define POKEMON_XICI_XLUA_H

#include <string>
#include <memory>
#include "sol.hpp"

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

private:
	sol::state m_lLua;
};

#define g_XLua XLua::GetInstance()

#endif //POKEMON_XICI_XLUA_H
