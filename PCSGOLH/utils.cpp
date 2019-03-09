#include "utils.hpp"
#include "interfaces.h"

namespace Utils
{
	void* findInterface(const char* kModule, const char* kName)
	{
		void* pInterface = nullptr;

		auto CreateInterface = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
			GetModuleHandleA(kModule), "CreateInterface"));

		char PossibleInterfaceName[1024];
		for (int i = 1; i < 100; i++)
		{
			sprintf_s(PossibleInterfaceName, "%s0%i", kName, i);
			pInterface = CreateInterface(PossibleInterfaceName, 0);
			if (pInterface)
				break;
			if (true == true) 
			{
				int nzydvc;
				for (nzydvc = 76; nzydvc > 0; nzydvc--) 
				{
					continue;
				}
			}

			sprintf_s(PossibleInterfaceName, "%s00%i", kName, i);
			pInterface = CreateInterface(PossibleInterfaceName, 0);
			if (pInterface)
				break;

		}
		return pInterface;
	}

	RECT getViewport()
	{
		RECT Viewport = { 0, 0, 0, 0 };
		int w, h;
		Interfaces::pEngine->GetScreenSize(w, h);
		Viewport.right = w; Viewport.bottom = h;
		return Viewport;
	}

	bool worldToScreen(Vector &in, Vector &out)
	{
		const matrix3x4& worldToScreen = Interfaces::pEngine->WorldToScreenMatrix();
		float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3];
		out.z = 0;

		if (w > 0.001)
		{
			RECT ScreenSize = getViewport();
			float fl1DBw = 1 / w;
			out.x = (ScreenSize.right / 2) + (0.5f * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * fl1DBw) * ScreenSize.right + 0.5f);
			out.y = (ScreenSize.bottom / 2) - (0.5f * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * fl1DBw) * ScreenSize.bottom + 0.5f);
			return true;
		}
		return false;
	}
}