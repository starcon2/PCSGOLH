#pragma once

#include "cbaseentity.hpp"
#include "vmt.hpp"

class CClientEntityList
{
public:
	CBaseEntity* GetClientEntity(int index)
	{
		typedef CBaseEntity*(__thiscall* Fn)(void*, int);
		return callClass<Fn>(this, 3)(this, index);
	}
	
	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* Fn)(void*);
		return callClass<Fn>(this, 8)(this);
	}
	
	CBaseEntity* GetClientEntityFromHandle(ULONG handle)
	{
		typedef CBaseEntity*(__thiscall* Fn)(void*, void*);
		return callClass<Fn>(this, 4)(this, (void*)handle);
	}
	
	CBaseEntity* GetClientEntityFromHandle(void* handle)
	{
		typedef CBaseEntity*(__thiscall* Fn)(void*, void*);
		return callClass<Fn>(this, 7)(this, handle);
	}
	
};