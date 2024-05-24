#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath> // M_PI

#include "Viewer.h"

namespace rvi
{
	void Viewer::Initialize()
	{
		simulator.Initialize();
		simulator.Lighting();

		// NOTE Impl 4-1. OpenGL Init for Texture Mapping
	}
	void Viewer::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glEnable(GL_DEPTH_TEST);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -zoom_);
		glTranslatef(translate_[0], translate_[1], 0.f);
		glPushMatrix();

		glRotatef(rotate_[0], 1.f, 0.f, 0.f);
		glRotatef(rotate_[1], 0.f, 1.f, 0.f);

		simulator.Render();

		glPopMatrix();

		float light_pos[] = { 150.f, 150.f, 0.f, 1.f };

		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glutSwapBuffers();
		glutPostRedisplay();
	}
	void Viewer::Reshape(int w, int h)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		{ // gluPerspective(45f, (float)w / h, 0.f, 500.f)
		  // NOTE glPerspective deprecated
			GLdouble fov_y = 45.f;
			GLdouble z_near = 0.1f, z_far = 500.f;
			GLdouble f_h = tan(fov_y / 360 * M_PI) * z_near;
			auto aspect = (float)w / h;
			GLdouble f_w = f_h * aspect;

			glFrustum(-f_w, f_w, -f_h, f_h, z_near, z_far);
			glViewport(0, 0, w, h);
		}
	}
	void Viewer::Mouse(int mouse_event, int state, int x, int y)
	{
		mouse_coord_[0] = x;
		mouse_coord_[1] = y;

		// TODO 아래로
		// const auto event_val = (GLUT_DOWN == state ? 1 : 0);

		switch (mouse_event)
		{
		case GLUT_LEFT_BUTTON:
			mouse_event_[0] = ((GLUT_DOWN == state) ? 1 : 0);
			break;
		case GLUT_MIDDLE_BUTTON:
			mouse_event_[1] = ((GLUT_DOWN == state) ? 1 : 0);
		case GLUT_RIGHT_BUTTON:
			mouse_event_[2] = ((GLUT_DOWN == state) ? 1 : 0);
			break;
		default:
			break;
		}

		glutPostRedisplay();
	}
	void Viewer::Motion(int x, int y)
	{
		auto dx = x - mouse_coord_[0];
		auto dy = y - mouse_coord_[1];

		mouse_coord_[0] = x;
		mouse_coord_[1] = y;

		if (mouse_event_[0])
		{
			if (!interaction_mode_)
			{
				rotate_[0] += 0.1f * dy;
				rotate_[1] += 0.1f * dx;
			}
			else
			{
				// NOTE Impl 5. User Interaction
			}
		}
		else if (mouse_event_[1])
		{
			translate_[0] += 0.1f * dx;
			translate_[1] -= 0.1f * dy;
		}
		else if (mouse_event_[2])
		{
			zoom_ += 0.1f * dy;
		}

		glutPostRedisplay();
	}
	// TODO impl
	void Viewer::Keyboard(unsigned char key, int x, int y)
	{
		switch(key)
		{

		}
	}
	void Viewer::Update()
	{
		if (start_)
			simulator.Update();
	}
}; // namespace rvi