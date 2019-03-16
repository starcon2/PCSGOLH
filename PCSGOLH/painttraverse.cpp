#include "hooks.hpp"
#include "binds.hpp"

int _p;

void _() // :)
{
	Logger::append(Logger::kLogType::NORMAL, "Reloading script...\n");
	LuaState::gHooks.Reset();
	Sleep(500);
	LuaState::initialize();
	Binds::initialize();

	Logger::append(Logger::kLogType::SUCCESS, "Reloaded!\n");
}

namespace Hooks
{
	void __fastcall PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool bForceRepaint, bool bAllowForce)
	{
		if ((GetAsyncKeyState(VK_F5) & 0x8000))
		{
			if (_p + 500 > Interfaces::pGlobalVars->tickcount)
				return;

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)_, NULL, NULL, NULL);
			_p = Interfaces::pGlobalVars->tickcount;
		}

		static unsigned int iFocusOverlayPanel = 0;
		static bool bFoundPanel = false;
		auto oPaintTraverse = Interfaces::vmtPanel.get_original<PaintTraverseFn>(41);
		oPaintTraverse(pPanels, vguiPanel, bForceRepaint, bAllowForce);

		if (!bFoundPanel)
		{
			PCHAR szPanelName = (PCHAR)Interfaces::pPanel->GetName(vguiPanel);
			if (strstr(szPanelName, "MatSystemTopPanel"))
			{
				iFocusOverlayPanel = vguiPanel;
				bFoundPanel = true;
			}
		}
		else if (iFocusOverlayPanel == vguiPanel)
		{
			if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_PAINTTRAVERSE))
			{
				auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_PAINTTRAVERSE);
				for (auto it = v.begin(); it != v.end(); it++)
					luabind::call_function<void>(*it, vguiPanel);
			}
		}
	}
}