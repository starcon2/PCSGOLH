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
	Vector CalcAngle(Vector src, Vector dst) 
	{
		return Utils::CalcAngle(src, dst);
	}
};