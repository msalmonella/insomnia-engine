#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>

// camera state
typedef struct {
    float x, y, z;
    float yaw, pitch;
    float speed;
    float mouseSensitivity;
} Camera;

// initialize camera with default values
void cameraInit(Camera* cam);

// apply projection and view matrices
void cameraSetupPerspective(Camera* cam, int windowWidth, int windowHeight);
void cameraSetupView(Camera* cam);

// input handlers
void cameraProcessKeyboard(Camera* cam, GLFWwindow* window);
void cameraProcessMouse(Camera* cam, double xpos, double ypos);

#endif
