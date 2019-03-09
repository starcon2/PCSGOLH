#pragma once

#include "vmt.hpp"
#include "vector.h"

struct player_info_t
{
	char __pad0[0x8];

	int xuidlow;
	int xuidhigh;

	char name[128];
	int userid;
	char guid[33];

	char __pad1[0x17B];
};

class IEngine
{
public:
	bool GetPlayerInfo(int Index, player_info_t* PlayerInfo)
	{
		typedef bool(__thiscall* Fn)(void*, int, player_info_t*);
		return ((Fn)callClass<Fn>(this, 8))(this, Index, PlayerInfo);
	}
	
	bool IsInGame()
	{
		typedef bool(__thiscall* Fn)(void*);
		return ((Fn)callClass<Fn>(this, 26))(this);
	}
	
	bool IsConnected()
	{
		typedef bool(__thiscall* Fn)(void*);
		return ((Fn)callClass<Fn>(this, 27))(this);
	}
	
	void GetViewAngles(Vector& angle)
	{
		typedef void(__thiscall* Fn)(void*, Vector&);
		return ((Fn)callClass<Fn>(this, 18))(this, angle);
	}
	
	const matrix3x4& WorldToScreenMatrix()
	{
		typedef const matrix3x4& (__thiscall* Fn)(PVOID);
		return ((Fn)callClass<Fn>(this, 37))(this);
	}
	
	void GetScreenSize(int& Width, int& Height)
	{
		typedef void(__thiscall* Fn)(void*, int&, int&);
		return ((Fn)callClass<Fn>(this, 5))(this, Width, Height);
	}
	
	int GetLocalPlayer()
	{
		typedef int(__thiscall* Fn)(void*);
		return ((Fn)callClass<Fn>(this, 12))(this);
	}
};
