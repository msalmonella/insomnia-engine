#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "input.h"
#include "renderer.h"

const int WINDOW_WIDTH  = 1200;
const int WINDOW_HEIGHT = 900;

Camera cam;

int main(void)
{
	printf("welcome...\n");

	if (!glfwInit()) {
		printf("init fail GLFW\n");
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FPS Engine", NULL, NULL);
	if (!window) {
		printf("glew win fail\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetWindowUserPointer(window, &cam);
	glfwSetCursorPosCallback(window, mouseCallback);

	if (glewInit() != GLEW_OK) 
	{
		printf("glew init fail\n");
		return -1;
	}
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	cameraInit(&cam);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		cameraProcessKeyboard(&cam, window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

		cameraSetupPerspective(&cam, WINDOW_WIDTH, WINDOW_HEIGHT);
		cameraSetupView(&cam);

		drawFloor();
		drawCube( 0.0f, 0.0f,  -3.0f, 1.0f);
		drawCube( 0.0f, 2.0f,  -3.0f, 1.0f);
		drawCube(1.0f, 0.0f,  -3.0f, 1.0f);
		drawCube( -1.0f, 0.0f, -3.0f, 1.0f);
		drawCube( 0.0f, 1.0f,  -3.0f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	printf("farewell...\n");
	glfwTerminate();
	return 0;
}


