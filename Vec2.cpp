#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {};

Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

bool Vec2::operator == (const Vec2& other) const
{
	return x == other.x && y == other.y;
}

bool Vec2::operator != (const Vec2& other) const
{
	return !(x == other.x && y == other.y);
}

Vec2 Vec2::operator + (const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator - (const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator / (const float val) const
{
	return Vec2(x / val, y / val);
}

Vec2 Vec2::operator * (const float val) const
{
	return Vec2(x * val, y * val);
}

void Vec2::operator += (const Vec2& other)
{
	x += other.x;
	y += + other.y;
}

void Vec2::operator -= (const Vec2& other)
{
	x -= other.x;
	y -= +other.y;
}

void Vec2::operator *= (const Vec2& other)
{
	x *= other.x;
	y *= +other.y;
}

void Vec2::operator /= (const Vec2& other)
{
	x /= other.x;
	y /= +other.y;
}

Vec2 Vec2::length(const Vec2& other)
{
	float x_length = other.x - x; // x distance between points 
	float y_length = other.y - y; // y distance between points
	return Vec2(x_length, y_length);
}

float Vec2::dist(const Vec2& other) const // return the un-normalized distance between two vectors
{
	float x_length = other.x - x; // x distance between points 
	float y_length = other.y - y; // y distance between points
	return sqrtf((x_length * x_length) + (y_length * y_length));
}

Vec2 Vec2::normalize(float hypot)
{
	return Vec2(x / hypot, y / hypot);
}
 
float Vec2::theta()
{
	return atan2f(x, y);
}
