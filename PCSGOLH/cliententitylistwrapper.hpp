#pragma once
#include "baseentitywrapper.hpp"
#include "sdk.hpp"
#include "interfaces.h"

class ClientEntityListWrapper 
{
public:
	ClientEntityListWrapper(CClientEntityList* pEntityList)
	{
		m_pEntityList = pEntityList;
	}

	BaseEntityWrapper GetEntityFromIndex(int index) {
		return BaseEntityWrapper((CBaseEntity*)Interfaces::pEntityList->GetClientEntity(index));
	}

	int GetHighestEntityIndex() 
	{
		return m_pEntityList->GetHighestEntityIndex();
	}

private:
	CClientEntityList* m_pEntityList;
};