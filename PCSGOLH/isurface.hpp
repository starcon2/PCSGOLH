#pragma once

#include "color.hpp"
#include "vmt.hpp"

class ISurface
{
public:
	void SetDrawColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* Fn)(void*, int, int, int, int);
		return ((Fn)callClass<Fn>(this, 15))(this, r, g, b, a);
	}
	
	unsigned long ICreateFont()
	{
		typedef unsigned int(__thiscall* OriginalFn)(PVOID);
		return callClass<OriginalFn>(this, 66)(this);
	}
	
	void SetDrawColor(CColor color)
	{
		typedef void(__thiscall* Fn)(void*, CColor);
		return ((Fn)callClass<Fn>(this, 14))(this, color);
	}
	
	void DrawFilledRect(int x, int y, int x2, int y2)
	{
		typedef void(__thiscall* Fn)(void*, int, int, int, int);
		return ((Fn)callClass<Fn>(this, 16))(this, x, y, x2, y2);
	}
	
	void DrawOutlinedRect(int x, int y, int x2, int y2)
	{
		typedef void(__thiscall* Fn)(void*, int, int, int, int);
		return (callClass<Fn>(this, 18))(this, x, y, x2, y2);
	}
	
	void DrawLine(int x, int y, int x2, int y2)
	{
		typedef void(__thiscall* Fn)(void*, int, int, int, int);
		return ((Fn)callClass<Fn>(this, 19))(this, x, y, x2, y2);
	}
	
	void DrawOutlinedCircle(int x, int y, int radius, int segments)
	{
		typedef void(__thiscall* Fn)(void*, int, int, int, int);
		return ((Fn)callClass<Fn>(this, 103))(this, x, y, radius, segments);
	}
	
	unsigned long SCreateFont()
	{
		typedef unsigned int(__thiscall* OriginalFn)(PVOID);
		return callClass< OriginalFn >(this, 71)(this);
	}
	
	void SetFontGlyphSet(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		callClass< OriginalFn >(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	
	void DrawSetTextFont(unsigned int Font)
	{
		typedef void(__thiscall* Fn)(void*, unsigned int);
		return ((Fn)callClass<Fn>(this, 23))(this, Font);
	}
	
	void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void(__thiscall* Fn)(PVOID, unsigned long, const wchar_t*, int&, int&);
		return ((Fn)callClass<Fn>(this, 23))(this, font, text, wide, tall);
	}

	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* Fn)(void*, int, int, int, int);
		return ((Fn)callClass<Fn>(this, 25))(this, r, g, b, a);
	}
	
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* Fn)(void*, int, int);
		return ((Fn)callClass<Fn>(this, 26))(this, x, y);
	}
	
	void DrawPrintText(const wchar_t* Text, int Len, int DrawType = 0)
	{
		typedef void(__thiscall* Fn)(void*, wchar_t const*, int, int);
		return ((Fn)callClass<Fn>(this, 28))(this, Text, Len, DrawType);
	}
	
	void DrawSetTextColor(CColor Color)
	{
		typedef void(__thiscall* Fn)(void*, CColor);
		return ((Fn)callClass<Fn>(this, 24))(this, Color);
	}
	
	void DrawTexturedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall *Fn)(void*, int, int, int, int);
		callClass<Fn>(this, 40)(this, x0, y0, x1, y1);
	}
	
	void IPlaySound(const char* fileName)
	{
		typedef void(__thiscall* OriginalFn)(void*, const char*);
		return callClass<OriginalFn>(this, 82)(this, fileName);
	}
};