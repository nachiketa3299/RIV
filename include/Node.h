#pragma once

#include "Vec3.h"

namespace rvi
{
	struct Node
	{
		Node() = default;
		Node(const Vec3& position);
		~Node() = default;

		void AddForce(const Vec3& f);
		void Integrate(double dt);

		void draw() const;

		Vec3 position;
		double mass = 1.f;
		Vec3 force;
		Vec3 velocity;
		Vec3 acceleration;
		Vec3 normal;
		bool is_fixed = false;
	};
};