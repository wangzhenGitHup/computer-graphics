#ifndef  __COLOR__H__
#define  __COLOR__H__


class Color
{
public:
	Color();
	Color(float r, float g, float b, float alpha) : _r(r), _g(g), _b(b), _alpha(alpha){}
	Color(const float* value);
	Color(const Color& clr);
	~Color();

	void Set(float r, float g, float b, float alpha = 0.0f);
	void SetR(float r);
	void SetG(float g);
	void SetB(float b);
	void SetAlpha(float alpha);
	float GetR()const;
	float GetG()const;
	float GetB()const;
	float GetAlpha()const;
	void ClampTo01();
	void SetBlack();
	void SetWhite();
	void SetGrey(float shade);

	Color Lerp(const Color& clr, float factor);
	Color operator+(const Color& clr)const;
	Color operator-(const Color& clr)const;
	Color operator*(const Color& clr)const;
	Color operator/(const Color& clr)const;
	Color operator*(const float v)const;
	Color operator/(const float v)const;
	friend Color operator*(float factor, const Color& clr);

	bool operator==(const Color& clr)const;
	bool operator!=(const Color& clr)const;

	Color operator+=(const Color& clr);
	Color operator-=(const Color& clr);
	Color operator*=(const Color& clr);
	Color operator/=(const Color& clr);
	Color operator*=(const float v);
	Color operator/=(const float v);
	Color operator-()const;
	Color operator+()const;

	operator float*()const{ return (float*)this; }
	operator const float*()const{ return (const float*)this; }

private:
	float _r;
	float _g;
	float _b;
	float _alpha;
};

const Color WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const Color BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color RED(1.0f, 0.0f, 0.0f, 1.0f);
const Color GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const Color BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const Color CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const Color MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
#endif