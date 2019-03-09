#pragma once
#include "sdk.hpp"

class EngineWrapper
{
public:
	EngineWrapper(IEngine* pEngine)
	{
		m_pEngine = pEngine;
	}

	bool IsInGame()
	{
		return m_pEngine->IsInGame();
	}

	bool IsConnected()
	{
		return m_pEngine->IsConnected();
	}

	int GetLocalPlayer()
	{
		return m_pEngine->GetLocalPlayer();
	}

	const char* GetClientName(int entNum)
	{
		static player_info_t pInfo;
		m_pEngine->GetPlayerInfo(entNum, &pInfo);
		return pInfo.name;
	}

	Vector2D GetScreenSize()
	{
		int w, h;
		m_pEngine->GetScreenSize(w, h);
		return Vector2D(w, h);
	}

	Vector GetViewAngles()
	{
		Vector va;
		m_pEngine->GetViewAngles(va);
		return va;
	}
private:
	IEngine* m_pEngine;
};