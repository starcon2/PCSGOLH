#include "luastate.hpp"

namespace LuaState
{
	LuaHooks::Hooks gHooks;
	lua_State* pLuaState;
	
	void initialize(void)
	{
		if (pLuaState != nullptr)
		{
			lua_close(pLuaState);
			pLuaState = nullptr;
		}

		pLuaState = luaL_newstate();

		luabind::open(pLuaState);
		luaL_openlibs(pLuaState);
	}
}