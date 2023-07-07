#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define WINDOW_X_OFFSET 400
#define WINDOW_Y_OFFSET 150

GLfloat window_width = 700;
GLfloat window_height = 700;
GLboolean flag = true;
GLfloat angle = 0;

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	// Reset the view point
	gluLookAt(4.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0); // Set view point

	// Display cube	
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	// Ortho
	if (flag)
	{	
		glRotatef(angle, -3.0, -3.0, -3.0);
		glScalef(1, 1, 1);
		glutWireCube(0.5);
	}
	// Frustum
	else
	{
		glTranslatef(1, 0.0, 0.0);
		glRotatef(angle, -3.0, -3.0, -3.0);
		glScalef(2, 2, 2);
		glutWireCube(0.8);
	}
	glPopMatrix();
	glutSwapBuffers();

	angle += 0.03; // update the angle for rotation
}

// Activate while there is no event
void update() {
	glutPostRedisplay();	// Re call display func
}

void reshape(GLint width, GLint height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	// Reset view point
	if (flag){
		glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, 15.0);
	}
	else{
		glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 15.0);
	}
}

void InitGlut(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X_OFFSET, WINDOW_Y_OFFSET);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Maman 15 - Shai Gal");
}

// change the view point after keyboard pressed
void pressed(unsigned char key, int x, int y){
	flag = !flag;
	reshape(window_width, window_height);
}

int main(int argc, char** argv){
	InitGlut(argc, argv);
	glClearColor(1.0, 1.0, 1.0, 0.0);	// set background
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(pressed);
	glutIdleFunc(update);	// callback handler when there is no other event

	glutMainLoop();
	return 0;
}