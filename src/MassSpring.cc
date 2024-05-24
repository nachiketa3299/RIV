#include "MassSpring.h"
#include "Node.h"
#include <GL/glut.h>


namespace rvi
{

MassSpring::MassSpring(Node* p1, Node* p2): p1(p1), p2(p2)
{
	initial_length = p1->position.distance(p2->position);
}

MassSpring::MassSpring(Node * p1, Node * p2, double spring_coef)
	: MassSpring(p1, p2)
{
	this->spring_coef = spring_coef;
}

void MassSpring::InternalForce(double dt)
{
	const auto dir = (p1->position - p2->position).normalized();
	const auto dlen = (p1->position).distance(p2->position) - initial_length;
	const auto dv = p2->velocity - p1->velocity;

	const auto spring_s = spring_coef * dlen;
	const auto damping_s = damping_coef * dv.dot(dir);

	const auto f = (spring_s - damping_s) * dir;

	p1->AddForce(f);
	p2->AddForce(-f);
}

void MassSpring::draw() const
{
	glDisable(GL_LIGHTING);

	glColor3f(0.97f, 0.95f, 0.15f);
	glPointSize(2.f);

	glBegin(GL_LINES);
	glVertex3f(p1->position.x, p1->position.y, p1->position.z);
	glVertex3f(p2->position.x, p2->position.y, p2->position.z);
	glEnd();

	glEnable(GL_LIGHTING);
}

}; // namespace rvi