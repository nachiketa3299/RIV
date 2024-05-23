#include "Vec2.h"

#include <cassert> // assert
#include <cmath> // sqrt

using namespace std;

namespace rvi 
{

Vec2::Vec2() : x(0.f), y(0.f) {}
Vec2::Vec2(double x, double y) : x(x), y(y) { }

Vec2& Vec2::operator=(const Vec2 & o)
{
	x = o.x; y = o.y;
	return *this;
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}
Vec2 Vec2::operator+(const Vec2 & o) const
{
	return Vec2(x + o.x, y + o.y);
}
Vec2 Vec2::operator-(const Vec2 & o) const
{
	return Vec2(x - o.x, y - o.y);
}
Vec2 operator*(double c, const Vec2 & v)
{
	return Vec2(c * v.x, c * v.y);
}
Vec2 operator*(const Vec2 & v, double c)
{
	return operator*(c, v);
}
Vec2 Vec2::operator/(double c) const
{
	assert(c != 0.f);
	return Vec2(x / c, y / c);
}
Vec2& Vec2::operator+=(const Vec2 & o)
{
	x += o.x; 
	y += o.y;
	return *this;
}
Vec2& Vec2::operator-=(const Vec2 & o)
{
	x -= o.x;
	y -= o.y;
	return *this;
}
Vec2& Vec2::operator*=(double c)
{
	x *= c;
	y *= c;
	return *this;
}
bool Vec2::operator==(const Vec2 & o) const
{
	return x == o.x && y == o.y;
}
bool Vec2::operator!=(const Vec2 & o) const
{
	return !operator==(o);
}
double Vec2::length_squared() const
{
	return x * x + y * y;
}
double Vec2::length() const
{
	return sqrt(length_squared());
}
double Vec2::distance_squared(const Vec2& o) const
{
	auto dx = x - o.x;
	auto dy = y - o.y;
	return dx * dx + dy * dy;
}
double Vec2::distance(const Vec2& o) const
{
	return sqrt(distance_squared(o));
}
double Vec2::dot(const Vec2& o) const
{
	return x * o.x + y * o.y;
}
Vec2 Vec2::cross(const Vec2& o) const
{
	return Vec2(y * o.x, -x * o.y);
}
Vec2 Vec2::normalized_unsafe() const
{
	return operator/(length());
}
Vec2 Vec2::normalized(double tol=0.000001f) const
{
	auto l = length();
	return l < tol ? Vec2() : operator/(l);
}
Vec2& Vec2::Normalize_Unsafe()
{
	auto l = length();
	x /= l;
	y /= l;
	return *this;
}
Vec2& Vec2::Normalize(double tol = 0.000001f)
{
	auto l = length();

	if (l < tol)
		Clear();
	else
	{
		x /= l;
		y /= l;
	}

	return *this;
}
Vec2& Vec2::Clear()
{
	x = 0.f;
	y = 0.f;
	return *this;
}

string Vec2::to_string() const
{
	auto sx = std::to_string(x);
	auto sy = std::to_string(y);

	return "(" + sx + ", " + sy + ")";
}

} // namespace rvi