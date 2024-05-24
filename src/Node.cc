#include "Node.h"
#include <GL/glut.h>

namespace rvi
{

Node::Node(const Vec3& position): position(position) {}
void Node::AddForce(const Vec3 & f)
{
	force += f;
}
void Node::Integrate(double dt)
{
	if (!is_fixed)
	{
		acceleration = force / mass;
		velocity += acceleration * dt;
		position += velocity * dt;
	}

	force.Clear();
}
void Node::draw() const
{
	glDisable(GL_LIGHTING);
	glColor3f(0.97f, 0.95f, 0.15f);
	glPointSize(2.0f);

	glBegin(GL_POINTS);
	glVertex3f(position.x, position.y, position.z);
	glEnd();

	glEnable(GL_LIGHTING);
}

}; // namespace rvi