#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"

const int WINDOW_WIDTH  = 1200;
const int WINDOW_HEIGHT = 900;

Camera cam;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	cameraProcessMouse(&cam, xpos, ypos);
}

void drawCube(float x, float y, float z, float size);
void drawFloor();

int main() {
	printf("welcome...\n");

	if (!glfwInit()) {
		printf("Failed to initialize GLFW\n");
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FPS Engine", NULL, NULL);
	if (!window) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW\n");
		return -1;
	}

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Controls: WASD to move, Mouse to look, ESC to exit\n");

	cameraInit(&cam);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		cameraProcessKeyboard(&cam, window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

		cameraSetupPerspective(&cam, WINDOW_WIDTH, WINDOW_HEIGHT);
		cameraSetupView(&cam);

		drawFloor();
		drawCube( 0.0f, 0.0f,  0.0f, 1.0f);
		drawCube( 0.0f, 2.0f,  0.0f, 1.0f);
		drawCube(1.0f, 0.0f,  0.0f, 1.0f);
		drawCube( -1.0f, 0.0f, 0.0f, 1.0f);
		drawCube( 0.0f, 1.0f,  0.0f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	printf("farewell...\n");
	glfwTerminate();
	return 0;
}

void drawCube(float x, float y, float z, float size) {
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

void drawFloor() {
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
