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
				.def("Length", &Vector::Length)
				.def("Length2D", &Vector::Length2D)
				.property("X", &Vector::x, &Vector::x)
				.property("Y", &Vector::y, &Vector::y)
				.property("Z", &Vector::z, &Vector::z),
			luabind::class_<QAngle>("QAngle")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float, float>())
				.def(luabind::const_self + luabind::const_self)
				.def(luabind::const_self - luabind::const_self)
				.def(luabind::const_self * luabind::const_self)
				.def(luabind::const_self / luabind::const_self)
				.def(luabind::const_self * luabind::other<float>())
				.def(luabind::const_self / luabind::other<float>())
				.def("IsValid", &QAngle::IsValid)
				.def("Clamp", &QAngle::Clamp)
				.def("Length", &QAngle::Length)
				.property("X", &QAngle::pitch, &QAngle::pitch)
				.property("Y", &QAngle::yaw, &QAngle::yaw)
				.property("Z", &QAngle::roll, &QAngle::roll),
			luabind::class_<BaseEntityWrapper>("BaseEntityWrapper")
				.def("GetAbsOrigin", &BaseEntityWrapper::GetAbsOrigin)
				.def("GetAbsAngles", &BaseEntityWrapper::GetAbsAngles)
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
				.def("GetViewAngles", &CUserCMDWrapper::GetViewAngles)
				.def("SetViewAngles", &CUserCMDWrapper::SetViewAngles)
				.property("Buttons", &CUserCMDWrapper::GetButtons, &CUserCMDWrapper::SetButtons),
			luabind::class_<UtilsWrapper>("__Utils")
				.def("WorldToScreen", &UtilsWrapper::WorldToScreen),
			luabind::class_<Events::EventMouse>("EventMouse")
				.property("X", &Events::EventMouse::GetX)
				.property("Y", &Events::EventMouse::GetY)
				.property("Type", &Events::EventMouse::GetType)
				.property("Button", &Events::EventMouse::GetButton),
			luabind::class_<Events::EventKeyboard>("EventMouse")
				.property("Type", &Events::EventKeyboard::GetType)
				.property("KeyCode", &Events::EventKeyboard::GetKeyCode)
		];

		try
		{
			luabind::globals(LuaState::pLuaState)["KEY_NONE"] = Events::KEY_NONE;
			luabind::globals(LuaState::pLuaState)["BUTTON_LEFT"] = Events::BUTTON_LEFT;
			luabind::globals(LuaState::pLuaState)["BUTTON_RIGHT"] = Events::BUTTON_RIGHT;
			luabind::globals(LuaState::pLuaState)["BUTTON_MIDDLE"] = Events::BUTTON_MIDDLE;
			luabind::globals(LuaState::pLuaState)["BUTTON_MOUSE4"] = Events::BUTTON_MOUSE4;
			luabind::globals(LuaState::pLuaState)["BUTTON_MOUSE5"] = Events::BUTTON_MOUSE5;
			luabind::globals(LuaState::pLuaState)["KEY_BACK"] = Events::KEY_BACK;
			luabind::globals(LuaState::pLuaState)["KEY_TAB"] = Events::KEY_TAB;
			luabind::globals(LuaState::pLuaState)["KEY_CLEAR"] = Events::KEY_CLEAR;
			luabind::globals(LuaState::pLuaState)["KEY_RETURN"] = Events::KEY_RETURN;
			luabind::globals(LuaState::pLuaState)["KEY_SHIFT"] = Events::KEY_SHIFT;
			luabind::globals(LuaState::pLuaState)["KEY_CONTROL"] = Events::KEY_CONTROL;
			luabind::globals(LuaState::pLuaState)["KEY_ALT"] = Events::KEY_ALT;
			luabind::globals(LuaState::pLuaState)["KEY_PAUSE"] = Events::KEY_PAUSE;
			luabind::globals(LuaState::pLuaState)["KEY_CAPITAL"] = Events::KEY_CAPITAL;
			luabind::globals(LuaState::pLuaState)["KEY_ESCAPE"] = Events::KEY_ESCAPE;
			luabind::globals(LuaState::pLuaState)["KEY_SPACE"] = Events::KEY_SPACE;
			luabind::globals(LuaState::pLuaState)["KEY_PRIOR"] = Events::KEY_PRIOR;
			luabind::globals(LuaState::pLuaState)["KEY_NEXT"] = Events::KEY_NEXT;
			luabind::globals(LuaState::pLuaState)["KEY_END"] = Events::KEY_END;
			luabind::globals(LuaState::pLuaState)["KEY_HOME"] = Events::KEY_HOME;
			luabind::globals(LuaState::pLuaState)["KEY_LEFT"] = Events::KEY_LEFT;
			luabind::globals(LuaState::pLuaState)["KEY_UP"] = Events::KEY_UP;
			luabind::globals(LuaState::pLuaState)["KEY_RIGHT"] = Events::KEY_RIGHT;
			luabind::globals(LuaState::pLuaState)["KEY_DOWN"] = Events::KEY_DOWN;
			luabind::globals(LuaState::pLuaState)["KEY_PRINT"] = Events::KEY_PRINT;
			luabind::globals(LuaState::pLuaState)["KEY_INSERT"] = Events::KEY_INSERT;
			luabind::globals(LuaState::pLuaState)["KEY_DELETE"] = Events::KEY_DELETE;
			luabind::globals(LuaState::pLuaState)["KEY_0"] = Events::KEY_0;
			luabind::globals(LuaState::pLuaState)["KEY_1"] = Events::KEY_1;
			luabind::globals(LuaState::pLuaState)["KEY_2"] = Events::KEY_2;
			luabind::globals(LuaState::pLuaState)["KEY_3"] = Events::KEY_3;
			luabind::globals(LuaState::pLuaState)["KEY_4"] = Events::KEY_4;
			luabind::globals(LuaState::pLuaState)["KEY_5"] = Events::KEY_5;
			luabind::globals(LuaState::pLuaState)["KEY_6"] = Events::KEY_6;
			luabind::globals(LuaState::pLuaState)["KEY_7"] = Events::KEY_7;
			luabind::globals(LuaState::pLuaState)["KEY_8"] = Events::KEY_8;
			luabind::globals(LuaState::pLuaState)["KEY_9"] = Events::KEY_9;
			luabind::globals(LuaState::pLuaState)["KEY_A"] = Events::KEY_A;
			luabind::globals(LuaState::pLuaState)["KEY_B"] = Events::KEY_B;
			luabind::globals(LuaState::pLuaState)["KEY_C"] = Events::KEY_C;
			luabind::globals(LuaState::pLuaState)["KEY_D"] = Events::KEY_D;
			luabind::globals(LuaState::pLuaState)["KEY_E"] = Events::KEY_E;
			luabind::globals(LuaState::pLuaState)["KEY_F"] = Events::KEY_F;
			luabind::globals(LuaState::pLuaState)["KEY_G"] = Events::KEY_G;
			luabind::globals(LuaState::pLuaState)["KEY_H"] = Events::KEY_H;
			luabind::globals(LuaState::pLuaState)["KEY_I"] = Events::KEY_I;
			luabind::globals(LuaState::pLuaState)["KEY_J"] = Events::KEY_J;
			luabind::globals(LuaState::pLuaState)["KEY_K"] = Events::KEY_K;
			luabind::globals(LuaState::pLuaState)["KEY_L"] = Events::KEY_L;
			luabind::globals(LuaState::pLuaState)["KEY_M"] = Events::KEY_M;
			luabind::globals(LuaState::pLuaState)["KEY_N"] = Events::KEY_N;
			luabind::globals(LuaState::pLuaState)["KEY_O"] = Events::KEY_O;
			luabind::globals(LuaState::pLuaState)["KEY_P"] = Events::KEY_P;
			luabind::globals(LuaState::pLuaState)["KEY_Q"] = Events::KEY_Q;
			luabind::globals(LuaState::pLuaState)["KEY_R"] = Events::KEY_R;
			luabind::globals(LuaState::pLuaState)["KEY_S"] = Events::KEY_S;
			luabind::globals(LuaState::pLuaState)["KEY_T"] = Events::KEY_T;
			luabind::globals(LuaState::pLuaState)["KEY_U"] = Events::KEY_U;
			luabind::globals(LuaState::pLuaState)["KEY_V"] = Events::KEY_V;
			luabind::globals(LuaState::pLuaState)["KEY_W"] = Events::KEY_W;
			luabind::globals(LuaState::pLuaState)["KEY_X"] = Events::KEY_X;
			luabind::globals(LuaState::pLuaState)["KEY_Y"] = Events::KEY_Y;
			luabind::globals(LuaState::pLuaState)["KEY_Z"] = Events::KEY_Z;
			luabind::globals(LuaState::pLuaState)["KEY_LWIN"] = Events::KEY_LWIN;
			luabind::globals(LuaState::pLuaState)["KEY_RWIN"] = Events::KEY_RWIN;
			luabind::globals(LuaState::pLuaState)["KEY_APPS"] = Events::KEY_APPS;
			luabind::globals(LuaState::pLuaState)["KEY_SLEEP"] = Events::KEY_SLEEP;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD0"] = Events::KEY_NUMPAD0;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD1"] = Events::KEY_NUMPAD1;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD2"] = Events::KEY_NUMPAD2;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD3"] = Events::KEY_NUMPAD3;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD4"] = Events::KEY_NUMPAD4;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD5"] = Events::KEY_NUMPAD5;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD6"] = Events::KEY_NUMPAD6;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD7"] = Events::KEY_NUMPAD7;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD8"] = Events::KEY_NUMPAD8;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD9"] = Events::KEY_NUMPAD9;
			luabind::globals(LuaState::pLuaState)["KEY_MULTIPLY"] = Events::KEY_MULTIPLY;
			luabind::globals(LuaState::pLuaState)["KEY_ADD"] = Events::KEY_ADD;
			luabind::globals(LuaState::pLuaState)["KEY_SEPARATOR"] = Events::KEY_SEPARATOR;
			luabind::globals(LuaState::pLuaState)["KEY_SUBTRACT"] = Events::KEY_SUBTRACT;
			luabind::globals(LuaState::pLuaState)["KEY_DECIMAL"] = Events::KEY_DECIMAL;
			luabind::globals(LuaState::pLuaState)["KEY_DIVIDE"] = Events::KEY_DIVIDE;
			luabind::globals(LuaState::pLuaState)["KEY_F1"] = Events::KEY_F1;
			luabind::globals(LuaState::pLuaState)["KEY_F2"] = Events::KEY_F2;
			luabind::globals(LuaState::pLuaState)["KEY_F3"] = Events::KEY_F3;
			luabind::globals(LuaState::pLuaState)["KEY_F4"] = Events::KEY_F4;
			luabind::globals(LuaState::pLuaState)["KEY_F5"] = Events::KEY_F5;
			luabind::globals(LuaState::pLuaState)["KEY_F6"] = Events::KEY_F6;
			luabind::globals(LuaState::pLuaState)["KEY_F7"] = Events::KEY_F7;
			luabind::globals(LuaState::pLuaState)["KEY_F8"] = Events::KEY_F8;
			luabind::globals(LuaState::pLuaState)["KEY_F9"] = Events::KEY_F9;
			luabind::globals(LuaState::pLuaState)["KEY_F10"] = Events::KEY_F10;
			luabind::globals(LuaState::pLuaState)["KEY_F11"] = Events::KEY_F11;
			luabind::globals(LuaState::pLuaState)["KEY_F12"] = Events::KEY_F12;
			luabind::globals(LuaState::pLuaState)["KEY_LMENU"] = Events::KEY_LMENU;
			luabind::globals(LuaState::pLuaState)["KEY_RMENU"] = Events::KEY_RMENU;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_1"] = Events::KEY_OEM_1;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_PLUS"] = Events::KEY_OEM_PLUS;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_COMMA"] = Events::KEY_OEM_COMMA;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_MINUS"] = Events::KEY_OEM_MINUS;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_PERIOD"] = Events::KEY_OEM_PERIOD;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_2"] = Events::KEY_OEM_2;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_3"] = Events::KEY_OEM_3;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_4"] = Events::KEY_OEM_4;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_5"] = Events::KEY_OEM_5;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_6"] = Events::KEY_OEM_6;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_7"] = Events::KEY_OEM_7;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_8"] = Events::KEY_OEM_8;

			luabind::globals(LuaState::pLuaState)["HOOK_MOUSE"] = LuaHooks::HookType::HOOK_MOUSE;
			luabind::globals(LuaState::pLuaState)["HOOK_KEYBOARD"] = LuaHooks::HookType::HOOK_KEYBOARD;
			luabind::globals(LuaState::pLuaState)["HOOK_PAINTTRAVERSE"] = LuaHooks::HookType::HOOK_PAINTTRAVERSE;
			luabind::globals(LuaState::pLuaState)["HOOK_CREATEMOVE"] = LuaHooks::HookType::HOOK_CREATEMOVE;

			luabind::globals(LuaState::pLuaState)["EVENT_UNKNOWN"] = Events::EVENT_UNKNOWN;
			luabind::globals(LuaState::pLuaState)["EVENT_KEYDOWN"] = Events::EVENT_KEYDOWN;
			luabind::globals(LuaState::pLuaState)["EVENT_KEYUP"] = Events::EVENT_KEYUP;
			luabind::globals(LuaState::pLuaState)["EVENT_MOUSEDOWN"] = Events::EVENT_MOUSEDOWN;
			luabind::globals(LuaState::pLuaState)["EVENT_MOUSEUP"] = Events::EVENT_MOUSEUP;
			luabind::globals(LuaState::pLuaState)["EVENT_MOUSEMOVE"] = Events::EVENT_MOUSEMOVE;

			luabind::globals(LuaState::pLuaState)["FL_ONGROUND"] = FL_ONGROUND;
			luabind::globals(LuaState::pLuaState)["FL_DUCKING"] = FL_DUCKING;
			luabind::globals(LuaState::pLuaState)["IN_JUMP"] = IN_JUMP;

			luabind::globals(LuaState::pLuaState)["Interfaces"] = &interfacesWrapper;
			luabind::globals(LuaState::pLuaState)["DrawManager"] = &drawManagerWrapper;
			luabind::globals(LuaState::pLuaState)["Utils"] = &utilsWrapper;
			luabind::globals(LuaState::pLuaState)["Hooks"] = &LuaState::gHooks;

			Logger::append(Logger::kLogType::SUCCESS, "Loading script...\n");

			if (luaL_dofile(LuaState::pLuaState, SCRIPT_DIR) != 0)
			{
				Logger::append(Logger::kLogType::ERROR, "Error: %s\n", lua_tostring(LuaState::pLuaState, -1));
				return;
			}
		}
		catch (const std::exception& TheError)
		{
			Logger::append(Logger::kLogType::ERROR, "Error: %s\n", TheError.what());
		}
	}
}