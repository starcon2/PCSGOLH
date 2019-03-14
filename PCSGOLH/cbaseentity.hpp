#pragma once
#include "vmt.hpp"
#include "vector.h"

class CBaseEntity
{
public:
	int GetIndex()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x64);
	}
	
	Vector GetViewOffset()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + 0x108); // m_vecViewOffset
	}
	
	Vector & GetAbsOrigin()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return ((OriginalFn)callClass<OriginalFn>(this, 10))(this);
	}

	Vector& GetAbsAngles()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return ((OriginalFn)callClass<OriginalFn>(this, 11))(this);
	}
	
	int GetLifeState()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x25F); // m_lifeState 
	}

	int GetFlags()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x104); // m_fFlags 
	}
	
	bool IsAlive()
	{
		return this->GetLifeState() == 0;
	}

	int GetHealth()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x100); // m_iHealth 
	}
	
	void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		void* pRenderable = (void*)(this + 0x4);
		typedef void(__thiscall* Fn)(void*, Vector&, Vector&);
		callClass<Fn>(pRenderable, 17)(pRenderable, mins, maxs);
	}
	
	int GetTeam()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xF4); // m_iTeamNum 
	}
	
	bool IsDormant()
	{
		return *reinterpret_cast<bool*>(uintptr_t(this) + 0xED);
	}
	
	Vector GetVecOrigin()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + 0x138); // m_vecOrigin 
	}
	
	Vector GetEyePosition(void)
	{
		return GetVecOrigin() + *(Vector*)((DWORD)this + 0x108); // m_vecViewOffset
	}
	
	Vector GetPunchAngles()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + 0x302C);
	}
	ClientClass* GetClientClass()
	{
		PVOID pNetworkable = (PVOID)((DWORD)(this) + 0x8);
		typedef ClientClass*(__thiscall* OriginalFn)(PVOID);
		return callClass<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}
};