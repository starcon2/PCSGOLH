#pragma once

class CColor
{
public:
	unsigned char RGBA[4];
	
	CColor()
	{
		*((int *)this) = 0;
	}
	
	CColor(float _rgb[3])
	{
		SetColor((int)(_rgb[0] * 255.0f), (int)(_rgb[1] * 255.0f), (int)(_rgb[2] * 255.0f), (int)(_rgb[3] * 255.0f));
	}
	
	CColor(int color32)
	{
		*((int *)this) = color32;
	}
	
	CColor(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b, 255);
	}
	
	CColor(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}
	
	void SetColor(int _r, int _g, int _b, int _a = 255)
	{
		RGBA[0] = (unsigned char)_r;
		RGBA[1] = (unsigned char)_g;
		RGBA[2] = (unsigned char)_b;
		RGBA[3] = (unsigned char)_a;
	}
	
	void GetColor(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = RGBA[0];
		_g = RGBA[1];
		_b = RGBA[2];
		_a = RGBA[3];
	}
	
	void SetRawColor(int color32)
	{
		*((int*)this) = color32;
	}
	
	int GetRawColor() const
	{
		return *((int*)this);
	}
	
	int GetD3DColor() const
	{
		return ((int)((((RGBA[3]) & 0xff) << 24) | (((RGBA[0]) & 0xff) << 16) | (((RGBA[1]) & 0xff) << 8) | ((RGBA[2]) & 0xff)));
	}
	
	inline int r() const
	{
		return RGBA[0];
	}
	
	inline int g() const
	{
		return RGBA[1];
	}
	
	inline int b() const
	{
		return RGBA[2];
	}
	
	inline int a() const
	{
		return RGBA[3];
	}
	
	inline float rBase() const
	{
		return RGBA[0] / 255.0f;
	}
	
	inline float gBase() const
	{
		return RGBA[1] / 255.0f;
	}
	
	inline float bBase() const
	{
		return RGBA[2] / 255.0f;
	}
	
	inline float aBase() const
	{
		return RGBA[3] / 255.0f;
	}
	
	unsigned char& operator[](int index)
	{
		return RGBA[index];
	}
	
	const unsigned char& operator[](int index) const
	{
		return RGBA[index];
	}
	
	bool operator ==(const CColor& rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}
	
	bool operator !=(const CColor& rhs) const
	{
		return !(operator==(rhs));
	}
	
	CColor& operator=(const CColor& rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}
	
	float* Base()
	{
		float clr[3];
		clr[0] = RGBA[0] / 255.0f;
		clr[1] = RGBA[1] / 255.0f;
		clr[2] = RGBA[2] / 255.0f;
		return &clr[0];
	}
	
	float* BaseAlpha()
	{
		float clr[4];
		clr[0] = RGBA[0] / 255.0f;
		clr[1] = RGBA[1] / 255.0f;
		clr[2] = RGBA[2] / 255.0f;
		clr[3] = RGBA[3] / 255.0f;
		return &clr[0];
	}
	
	float Hue() const
	{
		if (RGBA[0] == RGBA[1] && RGBA[1] == RGBA[2])
		{
			return 0.0f;
		}

		float r = RGBA[0] / 255.0f;
		float g = RGBA[1] / 255.0f;
		float b = RGBA[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if (r == max)
		{
			hue = (g - b) / delta;
		}
		else if (g == max)
		{
			hue = 2 + (b - r) / delta;
		}
		else if (b == max)
		{
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.0f)
		{
			hue += 360.0f;
		}
		return hue;
	}
	
	float Saturation() const
	{
		float r = RGBA[0] / 255.0f;
		float g = RGBA[1] / 255.0f;
		float b = RGBA[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if (max != min)
		{
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}
	
	float Brightness() const
	{
		float r = RGBA[0] / 255.0f;
		float g = RGBA[1] / 255.0f;
		float b = RGBA[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}
	
	static CColor FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return CColor(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return CColor(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return CColor(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return CColor(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return CColor(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return CColor(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}
private:

};