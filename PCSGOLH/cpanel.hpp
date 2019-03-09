#pragma once

#include "vmt.hpp"

class CPanel
{
public:
	const char* GetName(unsigned int Panel)
	{
		typedef const char*(__thiscall* Fn)(void*, unsigned int);
		return (callClass<Fn>(this, 36))(this, Panel);
	}

	void SetMouseInputEnabled(unsigned int iPanel, bool bState)
	{
		return (callClass<void(__thiscall *)(PVOID, int, bool)>(this, 32))(this, iPanel, bState);
	}
};