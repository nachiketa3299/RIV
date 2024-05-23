#include "Vec3.h"

#include <cassert> // assert
#include <cmath> // sqrt

using namespace std;

namespace rvi 
{

Vec3::Vec3(): x(0.f), y(0.f), z(0.f) {}
Vec3::Vec3(double x, double y, double z): x(x), y(y), z(z) { }

Vec3& Vec3::operator=(const Vec3 & o)
{
	x = o.x; y = o.y; z = o.z;
	return *this;
}
Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}
Vec3 Vec3::operator+(const Vec3& o) const
{
	return Vec3(x + o.x, y + o.y, z + o.z);
}
Vec3 Vec3::operator-(const Vec3& o) const
{
	return Vec3(x - o.x, y - o.y, z - o.z);
}
Vec3 operator*(double c, const Vec3& v)
{
	return Vec3(c * v.x, c * v.y, c * v.z);
}
Vec3 operator*(const Vec3& v, double c)
{
	return operator*(c, v);
}

Vec3 Vec3::operator/(double c) const
{
	assert(c != 0.f);
	return Vec3(x / c, y / c, z / c);
}
Vec3& Vec3::operator+=(const Vec3 & o)
{
	x += o.x; 
	y += o.y;
	z += o.z;

	return *this;
}
Vec3& Vec3::operator-=(const Vec3 & o)
{
	x -= o.x;
	y -= o.y;
	z -= o.z;

	return *this;
}
Vec3& Vec3::operator*=(double c)
{
	x *= c;
	y *= c;
	z *= c;

	return *this;
}
bool Vec3::operator==(const Vec3 & o) const
{
	return x == o.x && y == o.y && z == o.z;
}
bool Vec3::operator!=(const Vec3 & o) const
{
	return !operator==(o);
}
double Vec3::length_squared() const
{
	return x * x + y * y + z * z;
}
double Vec3::length() const
{
	return sqrt(length_squared());
}
double Vec3::distance_squared(const Vec3& o) const
{
	auto dx = x - o.x;
	auto dy = y - o.y;
	auto dz = z - o.z;
	return dx * dx + dy * dy + dz * dz;
}
double Vec3::distance(const Vec3& o) const
{
	return sqrt(distance_squared(o));
}
double Vec3::dot(const Vec3& o) const
{
	return x * o.x + y * o.y + z * o.z;
}
Vec3 Vec3::cross(const Vec3& o) const
{
	auto nx = y * o.z - z * o.y;
	auto ny = z * o.x - x * o.z;
	auto nz = x * o.y - y * o.x;
	return Vec3(nx, ny, nz);
}
Vec3 Vec3::normalized_unsafe() const
{
	return operator/(length());
}
Vec3 Vec3::normalized(double tol=0.000001f) const
{
	auto l = length();
	return l < tol ? Vec3() : operator/(l);
}
Vec3& Vec3::Normalize_Unsafe()
{
	auto l = length();
	x /= l;
	y /= l;
	z /= l;
	return *this;
}
Vec3& Vec3::Normalize(double tol = 0.000001f)
{
	auto l = length();

	if (l < tol)
		Clear();
	else
	{
		x /= l;
		y /= l;
		z /= l;
	}

	return *this;
}
Vec3& Vec3::Clear()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	return *this;
}

string Vec3::to_string() const
{
	auto sx = std::to_string(x);
	auto sy = std::to_string(y);
	auto sz = std::to_string(z);

	return "(" + sx + ", " + sy + ", " + sz + ")";
}

} // namespace rvi