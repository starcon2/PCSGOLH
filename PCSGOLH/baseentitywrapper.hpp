#pragma once
#include "sdk.hpp"

class BaseEntityWrapper 
{
public:
	BaseEntityWrapper(CBaseEntity* pBaseEntity)
	{
		m_pBaseEntity = pBaseEntity;
	}

	bool IsValid() 
	{
		return m_pBaseEntity != nullptr;
	}

	Vector GetAbsOrigin() 
	{
		return m_pBaseEntity->GetAbsOrigin();
	}

	Vector GetAbsAngles()
	{
		return m_pBaseEntity->GetAbsAngles();
	}

	int GetHealth()
	{
		return m_pBaseEntity->GetHealth();
	}

	int GetFlags() 
	{
		return m_pBaseEntity->GetFlags();
	}

	Vector GetEyePos()
	{
		return m_pBaseEntity->GetEyePosition();
	}

	bool IsDormant() 
	{
		return m_pBaseEntity->IsDormant();
	}

	bool IsAlive() 
	{
		return m_pBaseEntity->IsAlive();
	}

	int GetTeam() 
	{
		return m_pBaseEntity->GetTeam();
	}

	int GetClassId()
	{
		return m_pBaseEntity->GetClientClass()->m_ClassID;
	}

	Vector GetPunchAngles() 
	{
		return m_pBaseEntity->GetPunchAngles();
	}
	
	operator CBaseEntity*() 
	{
		return m_pBaseEntity;
	}
private:
	CBaseEntity* m_pBaseEntity;
};