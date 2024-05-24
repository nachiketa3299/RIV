#include <iostream>
#include <functional>

#include <GL/glut.h>

#include "Viewer.h"

using namespace std;
using namespace rvi;

Viewer vw;

void Initialize() { vw.Initialize(); } 
void Render() { vw.Render(); };
void Reshape(int w, int h) { vw.Reshape(w, h); };
void Mouse(int mouse_event, int state, int x, int y) { vw.Mouse(mouse_event, state, x, y); };
void Motion(int x, int y) {vw.Motion(x, y);};
void Keyboard(unsigned char key, int x, int y) {vw.Keyboard(key, x, y);}
void Update(int value)
{
	vw.Update();
	glutPostRedisplay();
	glutTimerFunc(10, Update, 0);
}

int main(int argc, char** argv)
{

	cout << "Working" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glutInitWindowPosition(400, 100);
	glutInitWindowSize(1024, 800);
	glutCreateWindow("[RIV_SIM]");

	vw.Initialize();

	glutTimerFunc(10,  Update, 0);
	glutDisplayFunc(Render);

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}