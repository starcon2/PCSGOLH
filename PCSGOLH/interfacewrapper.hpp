#pragma once
#include "interfaces.h"
#include "enginewrapper.hpp"
#include "cliententitylistwrapper.hpp"

class InterfacesWrapper 
{
public:
	EngineWrapper GetEngine()
	{
		static EngineWrapper engine(Interfaces::pEngine);
		return engine;
	}

	ClientEntityListWrapper GetEntityList()
	{
		static ClientEntityListWrapper entityList(Interfaces::pEntityList);
		return entityList;
	}
};