#include "renderer.h"
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

void drawCube(float x, float y, float z, float size) 
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(size, size, size);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f,  0.5f);
	glVertex3f( 0.5f, -0.5f,  0.5f);
	glVertex3f( 0.5f,  0.5f,  0.5f);
	glVertex3f(-0.5f,  0.5f,  0.5f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f,  0.5f, -0.5f);
	glVertex3f( 0.5f,  0.5f, -0.5f);
	glVertex3f( 0.5f, -0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f,  0.5f, -0.5f);
	glVertex3f(-0.5f,  0.5f,  0.5f);
	glVertex3f( 0.5f,  0.5f,  0.5f);
	glVertex3f( 0.5f,  0.5f, -0.5f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f( 0.5f, -0.5f, -0.5f);
	glVertex3f( 0.5f, -0.5f,  0.5f);
	glVertex3f(-0.5f, -0.5f,  0.5f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f( 0.5f, -0.5f, -0.5f);
	glVertex3f( 0.5f,  0.5f, -0.5f);
	glVertex3f( 0.5f,  0.5f,  0.5f);
	glVertex3f( 0.5f, -0.5f,  0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f,  0.5f);
	glVertex3f(-0.5f,  0.5f,  0.5f);
	glVertex3f(-0.5f,  0.5f, -0.5f);

	glEnd();
	glPopMatrix();
}

void drawFloor() 
{
	glBegin(GL_QUADS);

	for (int i = -5; i <= 5; i++) {
		for (int j = -5; j <= 5; j++) {
			float x1 = i * 2.0f, x2 = (i + 1) * 2.0f;
			float z1 = j * 2.0f, z2 = (j + 1) * 2.0f;

			if ((i + j) % 2 == 0)
				glColor3f(0.6f, 0.6f, 0.6f);
			else
				glColor3f(0.3f, 0.3f, 0.3f);

			glVertex3f(x1, -1.0f, z1);
			glVertex3f(x2, -1.0f, z1);
			glVertex3f(x2, -1.0f, z2);
			glVertex3f(x1, -1.0f, z2);
		}
	}

	glEnd();
}
