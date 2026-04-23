#include <GL/glew.h>
#include "camera.h"
#include <math.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

#define M_PI 3.14159265358979323846

static double lastMouseX = 0.0;
static double lastMouseY = 0.0;
static int firstMouse = 1;

void cameraInit(Camera* cam) {
    cam->x = 0.0f;
    cam->y = 0.0f;
    cam->z = 3.0f;
    cam->yaw = 0.0f;
    cam->pitch = 0.0f;
    cam->speed = 0.05f;
    cam->mouseSensitivity = -0.05f;
}

void cameraSetupPerspective(Camera* cam, int windowWidth, int windowHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float fov = 70.0f;
    float aspect = (float)windowWidth / windowHeight;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    float top = nearPlane * tan(fov * M_PI / 360.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    glFrustum(left, right, bottom, top, nearPlane, farPlane);
}

void cameraSetupView(Camera* cam) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-cam->pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-cam->yaw,   0.0f, 1.0f, 0.0f);
    glTranslatef(-cam->x, -cam->y, -cam->z);
}

void cameraProcessKeyboard(Camera* cam, GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    float yawRad = -cam->yaw * M_PI / 180.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam->x += sin(yawRad) * cam->speed;
        cam->z -= cos(yawRad) * cam->speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam->x -= sin(yawRad) * cam->speed;
        cam->z += cos(yawRad) * cam->speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam->x -= cos(yawRad) * cam->speed;
        cam->z -= sin(yawRad) * cam->speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam->x += cos(yawRad) * cam->speed;
        cam->z += sin(yawRad) * cam->speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam->y += cam->speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam->y -= cam->speed;

    // debug print every 120 frames
    static int frameCount = 0;
    if (++frameCount % 120 == 0)
        printf("Position: X=%.2f, Y=%.2f, Z=%.2f, Yaw=%.2f\n",
               cam->x, cam->y, cam->z, cam->yaw);
}

void cameraProcessMouse(Camera* cam, double xpos, double ypos) {
    if (firstMouse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = 0;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos;
    lastMouseX = xpos;
    lastMouseY = ypos;

    cam->yaw   += xoffset * cam->mouseSensitivity;
    cam->pitch -= yoffset * cam->mouseSensitivity;

    if (cam->pitch >  89.0f) cam->pitch =  89.0f;
    if (cam->pitch < -89.0f) cam->pitch = -89.0f;
}
