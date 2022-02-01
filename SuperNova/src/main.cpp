#include <GL/glut.h>
#include <iostream>

#include "../src/obj/Player.h"


void display_callback();
void reshape_callback(int,int);

Player player1;

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(int argc, char **argv)
{
	//starts the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Helloworld");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	init();
	glutMainLoop();

	return 0;
}

//
//		Update Method
//
void reshape_callback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0f, 50.0f, 0.0f, 50.0f, -1.0f, 1.0f); //Left, Right, Top, Bottom, zNear, zFar

}

//
//		Draw / Render Method
//
void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Drawing goes Here
	player1.draw();

	glutSwapBuffers();
}