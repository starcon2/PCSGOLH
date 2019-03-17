#pragma once

#include "interfaces.h"
#include <string>
#include <wchar.h>
#include <codecvt>

class DrawManagerWrapper
{
public:
	unsigned long CreateNewFont(const char* fontFace, int size, bool bold, bool italic, bool outlined, bool dropShadow) 
	{
		unsigned long font = Interfaces::pSurface->SCreateFont();
		int flags = (italic ? 0x001 : 0) | (outlined ? 0x200 : 0) | (dropShadow ? 0x080 : 0);
		Interfaces::pSurface->SetFontGlyphSet(font, fontFace, size, bold ? FW_BOLD : 0, 0, 0, flags);
		
		return font;
	}

	void SDrawText(unsigned long fontId, int x, int y, const char* text, int r, int g, int b, int a = 255) 
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wtext = converter.from_bytes(text);

		Interfaces::pSurface->DrawSetTextColor(r, g, b, a);
		Interfaces::pSurface->DrawSetTextPos(x, y);

		Interfaces::pSurface->DrawSetTextFont(fontId);
		Interfaces::pSurface->DrawPrintText(wtext.c_str(), wtext.size());
	}

	Vector2D MeasureText(unsigned long fontId, const char* text) 
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wtext = converter.from_bytes(text);
		int w, h;
		Interfaces::pSurface->GetTextSize(fontId, wtext.c_str(), w, h);
		return Vector2D(w, h);
	}

	void DrawLine(int x, int y, int x1, int y1, int r, int g, int b, int a = 255)
	{
		Interfaces::pSurface->DrawLine(x, y, x1, y1);
		Interfaces::pSurface->SetDrawColor(r, g, b, a);
	}

	void DrawFilledRect(int x, int y, int w, int h, int r, int g, int b, int a = 255)
	{
		Interfaces::pSurface->SetDrawColor(r, g, b, a);
		Interfaces::pSurface->DrawFilledRect(x, y, x + w, y + h);
	}

	void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a = 255)
	{
		Interfaces::pSurface->SetDrawColor(r, g, b, a);
		Interfaces::pSurface->DrawOutlinedRect(x, y, x + w, y + h);
	}
};