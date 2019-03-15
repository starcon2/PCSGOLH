#include "loader.hpp"
#include "interfaces.h"
#include "luastate.hpp"
#include "binds.hpp"

#include <luabind/luabind.hpp>

namespace Loader
{
	void initialize(void)
	{
		printf("=================[PCSGOLH]=================\n");
		printf("Github: www.github.com/xrivendell/pcsgolh\n");
		printf("Compiled: %s @ %s\n\n", __DATE__, __TIME__);
		printf("Press F5 to refresh a lua script\n");
		printf("=================[PCSGOLH]=================\n\n");

		Logger::append(Logger::kLogType::SUCCESS, "Initializing LuaState...\n");
		LuaState::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Initializing Interfaces...\n");
		Interfaces::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Initializing Binds...\n");
		Binds::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Loading script...\n");

		if (luaL_dofile(LuaState::pLuaState, SCRIPT_DIR) != 0)
		{
			Logger::append(Logger::kLogType::ERROR, "Error: %s\n", lua_tostring(LuaState::pLuaState, -1));
			return;
		}
	}
}