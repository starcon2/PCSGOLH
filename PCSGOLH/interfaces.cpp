#include "interfaces.h"
#include "hooks.hpp"

namespace Interfaces
{
	class COverrideView;

	IBaseClient* pBaseClient;
	ISurface* pSurface;
	IEngine* pEngine;
	CPanel* pPanel;
	CGlobalVars* pGlobalVars;
	COverrideView* pClientMode;
	CClientEntityList* pEntityList;

	VMTHook vmtPanel;
	VMTHook vmtClient;

	void initialize(void)
	{
		pBaseClient = reinterpret_cast<IBaseClient*>(Utils::findInterface("client_panorama.dll", "VClient"));
		pSurface = reinterpret_cast<ISurface*>(Utils::findInterface("vguimatsurface.dll", "VGUI_Surface"));
		pPanel = reinterpret_cast<CPanel*>(Utils::findInterface("vgui2.dll", "VGUI_Panel"));
		pEngine = reinterpret_cast<IEngine*>(Utils::findInterface("engine.dll", "VEngineClient"));
		pEntityList = reinterpret_cast<CClientEntityList*>(Utils::findInterface("client_panorama.dll", "VClientEntityList"));
		pGlobalVars = **reinterpret_cast<CGlobalVars***>((*reinterpret_cast<DWORD**>(pBaseClient))[0] + 0x1B);
		void** pClientTable = *reinterpret_cast<void***>(pBaseClient);
		pClientMode = **reinterpret_cast<COverrideView***>(reinterpret_cast<DWORD>(pClientTable[10]) + 5);

		vmtPanel.setup(pPanel, "vgui2.dll");
		vmtPanel.hook_index(41, Hooks::PaintTraverse);

		vmtClient.setup(pClientMode, "client_panorama.dll");
		vmtClient.hook_index(24, Hooks::CreateMove);
	}
}