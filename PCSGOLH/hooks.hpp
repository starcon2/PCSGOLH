#pragma once
#include "sdk.hpp"
#include "interfaces.h"

namespace Hooks
{
	typedef void(__thiscall* PaintTraverseFn)(void*, unsigned int, bool, bool);
	typedef bool(__stdcall* CreateMoveFn)(float, CUserCmd*);

	void __fastcall PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool bForceRepaint, bool bAllowForce);
	bool __stdcall CreateMove(float sample_input_frametime, CUserCmd* pCmd);
}