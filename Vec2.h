#pragma once
namespace rvi {

struct Vec2
{
	Vec2();
	Vec2(double x, double y);

	void operator=(const Vec2& o);

	Vec2 operator-() const;
	Vec2 operator+(const Vec2& o) const;
	Vec2 operator-(const Vec2& o) const;
	friend Vec2 operator*(double c, const Vec2& v);
	friend Vec2 operator*(const Vec2& v, double c);
	void operator/(double c);

	Vec2& operator+=(const Vec2& o);
	Vec2& operator-=(const Vec2& o);
	Vec2& operator*=(double c);

	bool operator==(const Vec2& o) const;
	bool operator!=(const Vec2& o) const;

	double length_squared() const;
	double length() const;
	double distance_squared(const Vec2& o) const;
	double distance(const Vec2& o) const;

	double dot(const Vec2& o) const;
	Vec2 cross(const Vec2& o) const;
	Vec2 normalize() const;

	Vec2& Normalize_Unsafe();
	Vec2& Normalize();
	void Clear();

	double x;
	double y;
};

} // namespace rvi