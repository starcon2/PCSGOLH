#include "binds.hpp"

#include "luastate.hpp"

#include "drawmanagerwrapper.hpp"
#include "cusercmdwrapper.hpp"
#include "interfacewrapper.hpp"
#include "cliententitylistwrapper.hpp"
#include "baseentitywrapper.hpp"
#include "utilswrapper.hpp"

DrawManagerWrapper drawManagerWrapper;
CUserCMDWrapper* userCmdWrapper;
InterfacesWrapper interfacesWrapper;
UtilsWrapper utilsWrapper;

namespace Binds
{
	void initialize(void)
	{
		luabind::module(LuaState::pLuaState)[
			luabind::class_<InterfacesWrapper>("__Interfaces")
				.def("GetEngine", &InterfacesWrapper::GetEngine)
				.def("GetEntityList", &InterfacesWrapper::GetEntityList),
			luabind::class_<DrawManagerWrapper>("__DrawManager")
				.def("CreateFont", &DrawManagerWrapper::CreateNewFont)
				.def("Text", &DrawManagerWrapper::SDrawText)
				.def("DrawFilledRect", &DrawManagerWrapper::DrawFilledRect)
				.def("DrawRect", &DrawManagerWrapper::DrawRect)
				.def("DrawLine", &DrawManagerWrapper::DrawLine),
			luabind::class_<LuaHooks::Hooks>("__Hooks")
				.def("Register", &LuaHooks::Hooks::RegisterHook),
			luabind::class_<Vector2D>("Size")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float>())
				.def(luabind::const_self + luabind::const_self)
				.def(luabind::const_self - luabind::const_self)
				.property("Width", &Vector2D::x, &Vector2D::x)
				.property("Height", &Vector2D::y, &Vector2D::y),
			luabind::class_<Vector>("Vector")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float, float>())
				.def(luabind::const_self + luabind::const_self)
				.def(luabind::const_self - luabind::const_self)
				.def(luabind::const_self * luabind::const_self)
				.def(luabind::const_self / luabind::const_self)
				.def(luabind::const_self * luabind::other<float>())
				.def(luabind::const_self / luabind::other<float>())
				.property("X", &Vector::x, &Vector::x)
				.property("Y", &Vector::y, &Vector::y)
				.property("Z", &Vector::z, &Vector::z),
			luabind::class_<BaseEntityWrapper>("BaseEntityWrapper")
				.def("GetAbsOrigin", &BaseEntityWrapper::GetAbsOrigin)
				.def("IsAlive", &BaseEntityWrapper::IsAlive)
				.def("GetFlags", &BaseEntityWrapper::GetFlags)
				.def("IsValid", &BaseEntityWrapper::IsValid)
				.def("GetHealth", &BaseEntityWrapper::GetHealth)
				.def("GetClassId", &BaseEntityWrapper::GetClassId)
				.def("IsDormant", &BaseEntityWrapper::IsDormant)
				.def("GetEyePos", &BaseEntityWrapper::GetEyePos)
				.def("GetPunchAngles", &BaseEntityWrapper::GetPunchAngles),
			luabind::class_<EngineWrapper>("EngineWrapper")
				.def("IsInGame", &EngineWrapper::IsInGame)
				.def("IsConnected", &EngineWrapper::IsConnected)
				.def("GetLocalPlayer", &EngineWrapper::GetLocalPlayer)
				.def("GetClientName", &EngineWrapper::GetClientName)
				.def("GetScreenSize", &EngineWrapper::GetScreenSize)
				.def("GetViewAngles", &EngineWrapper::GetViewAngles),
			luabind::class_<ClientEntityListWrapper>("ClientEntityListWrapper")
				.def("GetEntityFromIndex", &ClientEntityListWrapper::GetEntityFromIndex)
				.def("GetHighestEntityIndex", &ClientEntityListWrapper::GetHighestEntityIndex),
			luabind::class_<CUserCMDWrapper>("CUserCMDWrapper")
				.def("GetTickCount", &CUserCMDWrapper::GetTickCount)
				.property("Buttons", &CUserCMDWrapper::GetButtons, &CUserCMDWrapper::SetButtons),
			luabind::class_<UtilsWrapper>("__Utils")
				.def("WorldToScreen", &UtilsWrapper::WorldToScreen)
		];

		luabind::globals(LuaState::pLuaState)["HOOK_PAINTTRAVERSE"] = LuaHooks::HookType::HOOK_PAINTTRAVERSE;
		luabind::globals(LuaState::pLuaState)["HOOK_CREATEMOVE"] = LuaHooks::HookType::HOOK_CREATEMOVE;

		luabind::globals(LuaState::pLuaState)["FL_ONGROUND"] = FL_ONGROUND;
		luabind::globals(LuaState::pLuaState)["FL_DUCKING"] = FL_DUCKING;
		luabind::globals(LuaState::pLuaState)["IN_JUMP"] = IN_JUMP;

		luabind::globals(LuaState::pLuaState)["Interfaces"] = &interfacesWrapper;
		luabind::globals(LuaState::pLuaState)["DrawManager"] = &drawManagerWrapper;
		luabind::globals(LuaState::pLuaState)["Utils"] = &utilsWrapper;
		luabind::globals(LuaState::pLuaState)["Hooks"] = &LuaState::gHooks;
	}
}