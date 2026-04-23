#include <GL/glew.h>
// #include <math.h>
// #include <stdio.h>
#include <GLFW/glfw3.h>
#include "camera.h"

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Camera *cam = glfwGetWindowUserPointer(window);
	cameraProcessMouse(cam, xpos, ypos);
}
