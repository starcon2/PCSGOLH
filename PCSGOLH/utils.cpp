#include "utils.hpp"
#include "interfaces.h"
#define RAD2DEG(x)  ((float)(x) * (float)(180.f / M_PI_F))

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

	void VectorAngles_2(const Vector& forward, Vector& angles)
	{
		if (forward.x == 0.f && forward.y == 0.f)
		{
			angles.x = forward.z > 0.f ? -90.f : 90.f;
			angles.y = 0.f;
		}
		else
		{
			angles.x = RAD2DEG(atan2(-forward.z, forward.Length2D()));
			angles.y = RAD2DEG(atan2(forward.y, forward.x));
		}

		angles.z = 0.f;
	}

		Vector CalcAngle(Vector src, Vector dst)
		{
			Vector angles;
			Vector delta = src - dst;
			VectorAngles_2(delta, angles);
			delta.Normalize();
			return angles;
		}

		bool worldToScreen(Vector & in, Vector & out)
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
