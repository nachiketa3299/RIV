#pragma once

#include <string>

namespace rvi
{

struct Vec3
{
	Vec3();
	Vec3(double x, double y, double z);

	Vec3& operator=(const Vec3& o);

	Vec3 operator-() const;
	Vec3 operator+(const Vec3& o) const;
	Vec3 operator-(const Vec3& o) const;
	friend Vec3 operator*(double c, const Vec3& v);
	friend Vec3 operator*(const Vec3& v, double c);
	Vec3 operator/(double c) const;

	Vec3& operator+=(const Vec3& o);
	Vec3& operator-=(const Vec3& o);
	Vec3& operator*=(double c);

	bool operator==(const Vec3& o) const;
	bool operator!=(const Vec3& o) const;

	double length_squared() const;
	double length() const;
	double distance_squared(const Vec3& o) const;
	double distance(const Vec3& o) const;

	double dot(const Vec3& o) const;
	Vec3 cross(const Vec3& o) const;
	Vec3 normalized_unsafe() const;
	Vec3 normalized(double tol=0.000001f) const;

	Vec3& Normalize_Unsafe();
	Vec3& Normalize(double tol=0.000001f);
	Vec3& Clear();

	std::string to_string() const;

	double x;
	double y;
	double z;
};

} // namespace rvi