
#include <GL/glut.h>
void display_callback();
void reshape_callback(int,int);
void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Helloworld");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	init();
	glutMainLoop();
	return 0;

}
void reshape_callback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
