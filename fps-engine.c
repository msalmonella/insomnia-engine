#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// window 
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;

// camera/Player variables
float playerX = 0.0f, playerY = 0.0f, playerZ = 3.0f;
float playerYaw = 0.0f, playerPitch = 0.0f;
float playerSpeed = 0.05f;
float mouseSensitivity = -0.05f;

// mouse traking
double lastMouseX = WINDOW_WIDTH / 2.0;
double lastMouseY = WINDOW_HEIGHT / 2.0;
int firstMouse = 1;

void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void drawCube(float x, float y, float z, float size);
void drawFloor();
void setupPerspective();
void setupCamera();

int main() {
    printf("starting engine... \n");
    
    // init GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FPS Game - Fixed", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);

    // init GLEW
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Controls: WASD to move, Mouse to look, ESC to exit\n");

    // depth testing
    glEnable(GL_DEPTH_TEST);

	// main
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window);

        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

        // set up perspective and camera
        setupPerspective();
        setupCamera();

        // draw scene
        drawFloor();
        
        // draw cubes at various positions
        drawCube(0.0f, 0.0f, 0.0f, 1.0f);    // Right 
        drawCube(3.0f, 0.0f, 0.0f, 1.0f);    // To the right
        drawCube(-3.0f, 0.0f, 0.0f, 1.0f);   // To the left
        drawCube(0.0f, 0.0f, -3.0f, 1.0f);   // Behind 
        drawCube(0.0f, 2.0f, 0.0f, 1.0f);    // Above

        // swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    printf("farewell...");
	printf("\n");
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    // movemint 
    float moveSpeed = playerSpeed;
	float yawRad = -playerYaw * M_PI / 180.0f;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        playerX += sin(yawRad) * moveSpeed;
        playerZ -= cos(yawRad) * moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        playerX -= sin(yawRad) * moveSpeed;
        playerZ += cos(yawRad) * moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        playerX -= cos(yawRad) * moveSpeed;
        playerZ -= sin(yawRad) * moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        playerX += cos(yawRad) * moveSpeed;
        playerZ += sin(yawRad) * moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        playerY += moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        playerY -= moveSpeed;
    }
    
    // debug output 120fps 
    static int frameCount = 0;
    frameCount++;
    if (frameCount % 120 == 0) {
        printf("Position: X=%.2f, Y=%.2f, Z=%.2f, Yaw=%.2f°\n", 
               playerX, playerY, playerZ, playerYaw);
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = 0;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos;
    lastMouseX = xpos;
    lastMouseY = ypos;

    playerYaw   += xoffset * mouseSensitivity;
    playerPitch -= yoffset * mouseSensitivity;

    if (playerPitch > 89.0f)  playerPitch =  89.0f;
    if (playerPitch < -89.0f) playerPitch = -89.0f;
}

void setupPerspective() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float fov = 70.0f;
    float aspect = (float)WINDOW_WIDTH / WINDOW_HEIGHT;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    float top = nearPlane * tan(fov * M_PI / 360.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    
    glFrustum(left, right, bottom, top, nearPlane, farPlane);
}

void setupCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // apply camera rotation
    glRotatef(-playerPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-playerYaw, 0.0f, 1.0f, 0.0f);
    
    // apply camera translation
    glTranslatef(-playerX, -playerY, -playerZ);
}

void drawCube(float x, float y, float z, float size) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, size);
    
    glBegin(GL_QUADS);
    
    // Front face (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    
    // Back face (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    
    // Top face (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    
    // Bottom face (yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    
    // Right face (magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    
    // Left face (cyan)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    
    glEnd();
    glPopMatrix();
}

void drawFloor() {
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    
    for (int i = -5; i <= 5; i++) {
        for (int j = -5; j <= 5; j++) {
            float x1 = i * 2.0f;
            float x2 = (i + 1) * 2.0f;
            float z1 = j * 2.0f;
            float z2 = (j + 1) * 2.0f;
            
            // Checkerboard pattern
            if ((i + j) % 2 == 0) {
                glColor3f(0.6f, 0.6f, 0.6f);
            } else {
                glColor3f(0.3f, 0.3f, 0.3f);
            }
            
            glVertex3f(x1, -1.0f, z1);
            glVertex3f(x2, -1.0f, z1);
            glVertex3f(x2, -1.0f, z2);
            glVertex3f(x1, -1.0f, z2);
        }
    }
    
    glEnd();
}
