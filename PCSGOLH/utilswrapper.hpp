#pragma once
#include "vector.h"
#include "utils.hpp"

class UtilsWrapper
{
public:
	bool WorldToScreen(Vector &in, Vector &out)
	{
		return Utils::worldToScreen(in, out);
	}
};