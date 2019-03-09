#pragma once

#include <Windows.h>
#include <process.h>
#include <Psapi.h>
#include <string.h>
#include <stdio.h>

#include "vector.h"

typedef void* (*CreateInterfaceFn)(const char *kName, int *iReturnCode);

namespace Utils
{
	void* findInterface(const char* kModule, const char* kName);
	bool worldToScreen(Vector &in, Vector &out);
}