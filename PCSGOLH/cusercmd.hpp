#pragma once

#include "vector.h"

class CUserCmd
{
public:
	char pad_0x0000[0x4];
	int		command_number;
	int		tick_count;
	Vector	viewangles;
	Vector	aimdirection;
	float	forwardmove;
	float	sidemove;
	float	upmove;
	int		buttons;
	unsigned char impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;
	short	mousedx;
	short	mousedy;
	bool	hasbeenpredicted;
	char	pad_0x4C[0x18];
};

class CVerifiedUserCmd
{
public:
	CUserCmd	m_cmd;
	unsigned long	m_crc;
};