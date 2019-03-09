#include "hooks.hpp"
#include "cusercmdwrapper.hpp"

namespace Hooks
{
	bool __stdcall CreateMove(float sample_input_frametime, CUserCmd* pCmd)
	{
		auto oCreateMove = Interfaces::vmtClient.get_original<CreateMoveFn>(24);
		oCreateMove(sample_input_frametime, pCmd);

		if (!Interfaces::pEngine->IsInGame())
			return false;

		CBaseEntity* pLocal = (CBaseEntity*)Interfaces::pEntityList->GetClientEntity(Interfaces::pEngine->GetLocalPlayer());
		if (!pLocal) 
			return false;

		if (pCmd)
		{
			if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_CREATEMOVE))
			{
				auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_CREATEMOVE);
				for (auto it = v.begin(); it != v.end(); it++)
					luabind::call_function<void>(*it, CUserCMDWrapper(pCmd));
			}
		}

		if (!pCmd || pCmd->command_number == 0)
			return false;
	}
}