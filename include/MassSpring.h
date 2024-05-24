#pragma once

namespace rvi
{
	struct Node;
	struct MassSpring
	{
		MassSpring(Node* p1, Node* p2);
		MassSpring(Node* p1, Node* p2, double spring_coef);

		void InternalForce(double dt);
		void draw() const;

		Node *p1, *p2;

		double initial_length;
		double spring_coef;
		double damping_coef = 0.1;
	};

}; // namespace rvi