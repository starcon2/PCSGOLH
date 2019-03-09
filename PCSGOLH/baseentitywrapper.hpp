#pragma once
#include "sdk.hpp"

class BaseEntityWrapper 
{
public:
	BaseEntityWrapper(CBaseEntity* pBaseEntity)
	{
		_pBaseEntity = pBaseEntity;
	}

	bool IsValid() 
	{
		return _pBaseEntity != nullptr;
	}

	Vector GetAbsOrigin() 
	{
		return _pBaseEntity->GetAbsOrigin();
	}

	int GetHealth()
	{
		return _pBaseEntity->GetHealth();
	}

	int GetFlags() 
	{
		return _pBaseEntity->GetFlags();
	}

	Vector GetEyePos()
	{
		return _pBaseEntity->GetEyePosition();
	}

	bool IsDormant() 
	{
		return _pBaseEntity->IsDormant();
	}

	bool IsAlive() 
	{
		return _pBaseEntity->IsAlive();
	}

	int GetTeam() 
	{
		return _pBaseEntity->GetTeam();
	}

	int GetClassId()
	{
		return _pBaseEntity->GetClientClass()->m_ClassID;
	}

	Vector GetPunchAngles() 
	{
		return _pBaseEntity->GetPunchAngles();
	}
	
	operator CBaseEntity*() 
	{
		return _pBaseEntity;
	}
private:
	CBaseEntity* _pBaseEntity;
};