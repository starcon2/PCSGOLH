#pragma once

#include "interfaces.h"
#include "sdk.hpp"

class CUserCMDWrapper
{
public:
	CUserCMDWrapper(CUserCmd* cmd) 
	{
		m_pCmd = cmd;
	}
	int GetButtons() 
	{
		return m_pCmd->buttons;
	}
	int GetTickCount()
	{
		return m_pCmd->tick_count;
	}
	Vector GetViewAngles() 
	{
		return m_pCmd->viewangles;
	}
	float GetForwardMove() 
	{
		return m_pCmd->forwardmove;
	}
	float GetSideMove() 
	{
		return m_pCmd->sidemove;
	}
	float GetUpMove() 
	{
		return m_pCmd->upmove;
	}
	void SetButtons(int buttons) 
	{
		m_pCmd->buttons = buttons;
	}
	void SetViewAngles(Vector va) 
	{
		m_pCmd->viewangles = va;
	}
	void SetForwardMove(float f) 
	{
		m_pCmd->forwardmove = f;
	}
	void SetSideMove(float f) 
	{
		m_pCmd->sidemove = f;
	}
	void SetUpMove(float f) 
	{
		m_pCmd->upmove = f;
	}
private:
	CUserCmd* m_pCmd;
};