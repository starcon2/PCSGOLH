#pragma once
#include "sdk.hpp"

namespace Interfaces
{
	extern IBaseClient* pBaseClient;
	extern ISurface* pSurface;
	extern IEngine* pEngine;
	extern CPanel* pPanel;
	extern CGlobalVars* pGlobalVars;
	extern CClientEntityList* pEntityList;

	extern VMTHook vmtPanel;
	extern VMTHook vmtClient;

	void initialize(void);
}