#pragma once

struct Vec3
{
	Vec3();
	Vec3(double x, double y);

	void operator=(const Vec3& o);

	Vec3 operator-() const;
	Vec3 operator+(const Vec3& o) const;
	Vec3 operator-(const Vec3& o) const;
	friend Vec3 operator*(double c, const Vec3& v);
	friend Vec3 operator*(const Vec3& v, double c);
	void operator/(double c);

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
	Vec3 normalize() const;

	Vec3& Normalize_Unsafe();
	Vec3& Normalize();
	void Clear();
	double x;
	double y;
	double z;
};