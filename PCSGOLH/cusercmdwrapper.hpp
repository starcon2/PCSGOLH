#pragma once

#include "interfaces.h"
#include "sdk.hpp"

class CUserCMDWrapper
{
public:
	CUserCMDWrapper(CUserCmd* cmd) 
	{
		pCmd = cmd;
	}
	int GetButtons() 
	{
		return pCmd->buttons;
	}
	int GetTickCount()
	{
		return pCmd->tick_count;
	}
	Vector GetViewAngles() 
	{
		return pCmd->viewangles;
	}
	float GetForwardMove() 
	{
		return pCmd->forwardmove;
	}
	float GetSideMove() 
	{
		return pCmd->sidemove;
	}
	float GetUpMove() 
	{
		return pCmd->upmove;
	}
	void SetButtons(int buttons) 
	{
		pCmd->buttons = buttons;
	}
	void SetViewAngles(Vector va) 
	{
		pCmd->viewangles = va;
	}
	void SetForwardMove(float f) 
	{
		pCmd->forwardmove = f;
	}
	void SetSideMove(float f) 
	{
		pCmd->sidemove = f;
	}
	void SetUpMove(float f) 
	{
		pCmd->upmove = f;
	}
private:
	CUserCmd* pCmd;
};