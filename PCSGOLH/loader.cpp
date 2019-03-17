#include "loader.hpp"
#include "interfaces.h"
#include "luastate.hpp"
#include "binds.hpp"
#include "hooks.hpp"

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

		if (Hooks::gWindowProc == NULL)
		{
			HWND hWindow = NULL;
			while (!(hWindow = FindWindowA("Valve001", "Counter-Strike: Global Offensive"))) Sleep(200);
			Hooks::gWindowProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)Hooks::NewWndProc);
		}

		Logger::append(Logger::kLogType::SUCCESS, "Initializing LuaState...\n");
		LuaState::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Initializing Interfaces...\n");
		Interfaces::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Initializing Binds...\n");
		Binds::initialize();
	}
}