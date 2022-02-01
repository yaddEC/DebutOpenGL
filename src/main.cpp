
#include <cstdio>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <math.h>
#include "gl.hpp"
#include "draw.hpp"

int main(int argc, char *argv[])
{
    int screenWidth = 1920;
    int screenHeight = 1080;

    if (!glfwInit())
        return -1;

    // Target OpenGL 3.3 API in Compatibility mode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Add debug flag in case we want to debug it
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "OPEN_GL", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    loadGLFunctions();

    printf("GLFW_VERSION: %s\n", glfwGetVersionString());
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    float rotx = 0.f;
    float roty = 0.f;
    bool showWireframe = false;
    bool ortho = true;
    float3 camera = {1.f, 0.f, -2.f};
    float3 target = {camera.x + sin(rotx) * cos(roty), camera.y + sin(roty), camera.z + cos(rotx) * cos(roty)};

    //FLASHLIGHT
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    GLfloat lightAmbiante[] = {1, 1, 1, 1};
    GLfloat lightAmbiante2[] = {1, 1, 1, 1};
    GLfloat lightDiffuse[] = {0.8, 0.8, 0.8, 1};
    GLfloat lightPosition[] = {camera.x - 1.5f, camera.y, camera.z + 20, 1};
    GLfloat lightPosition2[] = {1, 0, 9, 1};
    GLfloat lightConstantAttenuation = 0.5;
    GLfloat lightLinearAttenuation = 0.07;
    GLfloat lightSpecular[] = {0.70f, 0.70f, 0.70f, 1.0f};
    GLfloat lightSpotDirection[] = {target.x, target.y, target.z - 40};

    GLfloat lightSpotExponent[] = {90 * M_PI / 180};
    GLfloat lightSpotCutoff[] = {3.5};

    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightSpotDirection);
    glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, lightSpotExponent);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, lightSpotCutoff);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbiante);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, &lightConstantAttenuation);
    glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, &lightLinearAttenuation);

    //END LIGHT
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbiante2);

    //Maze map
    int maze[10][10] =
        {
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        };

    //Floor and ceiling of the maze
    int full[10][10] =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

    GLuint texture = gl::loadTexture("assets/brik.bmp");

    while (glfwWindowShouldClose(window) == false)
    {
        glfwPollEvents();

        // F1-F2 to toggle wireframe
        if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
            showWireframe = false;
        else if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
            showWireframe = true;

        // Clear buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

        // Send projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Camera Movement

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            rotx += M_PI / 180.f;
            target.x = camera.x + sin(rotx) * cos(roty);
            target.z = camera.z + cos(rotx) * cos(roty);
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            rotx -= M_PI / 180.f;
            target.x = camera.x + sin(rotx) * cos(roty);
            target.z = camera.z + cos(rotx) * cos(roty);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.x = camera.x + 0.05f * sin(rotx);
            camera.z = camera.z + 0.05f * cos(rotx);
            target.x = camera.x + sin(rotx) * cos(roty);
            target.z = camera.z + cos(rotx) * cos(roty);
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.x = camera.x - 0.05f * sin(rotx) / 2.f;
            camera.z = camera.z - 0.05f * cos(rotx) / 2.f;
            target.x = camera.x + sin(rotx) * cos(roty);
            target.z = camera.z + cos(rotx) * cos(roty);
        }

        if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
            ortho = false;
        else if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
            ortho = true;

        if (ortho)
        {
            gluPerspective(80.f, (float)screenWidth / screenHeight, 0.005f, 50.f);
        }
        else
        {
            glOrtho(-2, 2, -2, 2, 0.10f, 100.f);
        }
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, 0.f);

        gluLookAt(camera.x, camera.y, camera.z, target.x, target.y, target.z, 0, 1, 0);
        glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);

        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);

        // Draw primitive

      // Maze
        gl::drawMaze(texture, maze, 1);
        glTranslatef(0.f, 1.f, 0.f);
        glColor3f(0.2, 0.2, 0.2);
        gl::drawMaze(texture, full, 0.1);
        glTranslatef(0.f, -2.f, 0.f);
        gl::drawMaze(texture, full, 0.1);


        //Other shapes from previous exercise
        /* 
        gl::drawCone(15, 0.3);
        glTranslatef(0.2, 0, 0);
        glColor3f(0, 1, 0);
        gl::drawTriangle();
        glTranslatef(0.2, 0, 0);
        glColor3f(1, 1, 1);
        gl::drawQuad(texture);
        glTranslatef(0.2, 0, 0);
        gl::drawCube(0.1f, 0.1f, 0.1f, texture);
        glTranslatef(0.2, 0, 0);
        gl::drawGizmo();
        glTranslatef(0.4, 0, 0);
        glColor3f(1, 1, 0);
        gl::drawPointSphere(15, 150);
        glTranslatef(0.4, 0, 0);

        glTranslatef(0.4, 0, 0);
        glColor3f(0, 1, 1);
        gl::drawSphere(10, 13);*/

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}