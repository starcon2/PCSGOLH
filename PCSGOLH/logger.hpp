#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>

#ifdef ERROR
#undef ERROR
#endif

namespace Logger
{
	const enum kLogType
	{
		NORMAL,
		WARNING,
		ERROR,
		SUCCESS
	};

	void append(kLogType logType, std::string text, ...);
}