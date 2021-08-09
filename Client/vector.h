#pragma once

struct Vec2
{
	float x;
	float y;

	Vec2() :x(0.0f), y(0.0f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(int _x, int _y) : x(float(_x)), y(float(_y)) {}
	Vec2(const Vec2& v) :x(v.x), y(v.y) {}
	

	bool operator == (const Vec2& v)
	{
		return x == v.x && y == v.y;
	}

	bool operator != (const Vec2& v)
	{
		return !(*this == v);
	 }
	Vec2 operator + (const Vec2& v) 
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 operator += (const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return Vec2(x ,y);
	}

	Vec2 operator - (const Vec2& v)
	{
		return Vec2(x - v.x, y- v.y);
	}
	Vec2 operator -= (const Vec2& v)
	{

		x -= v.x;
		y -= v.y;
		return Vec2(x, y);
	}

	Vec2 operator *(int i)
	{
		return Vec2(x * i, y * i);
	}

	Vec2 operator *(float f)
	{
		return Vec2(x * f, y * f);
	}

	Vec2 operator *=(int i)
	{
		x *= i;
		y *= i;
		return Vec2(x , y );
	}


	Vec2 operator *=(float f)
	{
		x *= f;
		y *= f;
		return Vec2(x , y);
	}

	Vec2 operator /(int i)
	{
		assert(0 != i);
		return Vec2(x / i, y / i);
	}
	
	Vec2 operator /(float f)
	{
		assert(0 != f);
		return Vec2(x / f, y / f);
	}


	Vec2 operator /=(int i)
	{
		x /= i;
		y /= i;
		return Vec2(x, y);
	}

	Vec2 operator /=(float f)
	{
		x /= f;
		y /= f;
		return Vec2(x, y);
	}
	Vec2 operator /(const Vec2& v)
	{
		assert(!(0.f == v.x || 0.f == v.y));

		return Vec2(x / v.x, y / v.y);
	}

	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}
public:
	bool isZero()
	{
		return (x == 0) && (y == 0);
	}
	float Cross(const Vec2& v)
	{
		return x * v.y - y * v.x;
	}
	float Dot(const Vec2& v)
	{
		return  x * v.x + y * v.y;
	}

	float Distance()
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}
	float Distance(const Vec2& v)
	{
		return sqrtf(powf(x-v.x, 2) + powf(y-v.y, 2));
	}
	Vec2& Normalize()
	{
		float dis = Distance();

		assert(dis != 0.f);

		x /= dis;
		y /= dis;

		return *this;
	}
};
