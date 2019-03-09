#include <Windows.h>

#include "sdk.hpp"
#include "loader.hpp"

DWORD WINAPI load(LPVOID base)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	Loader::initialize();

	return 0;
}

BOOL APIENTRY DllMain(_In_ HINSTANCE hDll, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hDll);
		CreateThread(nullptr, 0, load, hDll, 0, nullptr);

		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}