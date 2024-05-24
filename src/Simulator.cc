#include <GL/glut.h>

#include "Simulator.h"

namespace rvi
{

void Simulator::Initialize()
{
	// TODO Impl Each Initialize
}
void Simulator::Update()
{
	// TODO After Cloth
}
void Simulator::Render()
{
	Lighting();
	DrawGround();
	// cloth->Draw();
	// Cyliner->Draw;
}
void Simulator::Lighting()
{
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_EMISSION, li_.no_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, li_.mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, li_.front_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, li_.front_color);
	glMaterialf(GL_FRONT, GL_SHININESS, li_.mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, li_.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, li_.diffuse);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 80.f);

	glLightfv(GL_LIGHT0, GL_POSITION, li_.position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, li_.direction);
	glLightfv(GL_LIGHT0, GL_SPECULAR, li_.specular);
}
void Simulator::DrawGround()
{
	glBegin(GL_QUADS);
	glColor3f(1.f, 1.f, 1.f);
	static auto cal = [](int x) { return -250.f + 250.f / 64.f * x;};
	for (auto x = 0; x < 128; ++x)
	{
		for (auto y = 0; y < 128; ++y)
		{
			glNormal3f(0.f, 1.f, 0.f);
			glVertex3f(-cal(x), ground_.y, -cal(7));
			glVertex3f(-cal(x + 1), ground_.y, -cal(y));
			glVertex3f(-cal(x + 1), ground_.y, -cal(y + 1));
			glVertex3f(-cal(x), ground_.y, -cal(y + 1));
		}
	}
	glEnd();
}

}; // namespace rvi