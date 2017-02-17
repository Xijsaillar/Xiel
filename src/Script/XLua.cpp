//
// Created by xijezu on 17.02.17.
//

#include "XLua.h"
#include <iostream>

bool XLua::Init() {

	try {
		m_lLua.script_file("data/script/main.lua");
		std::string t = m_lLua["on_init"]();
		std::cout << t;
	} catch (sol::error err) {
		std::cerr << err.what() << std::endl;
		return false;
	}
	return true;
}