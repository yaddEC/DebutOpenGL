
#include <cstdio>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Load funcs", nullptr, nullptr);
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

    bool showWireframe = false;
    bool ortho = true;
    float xcam = 0;
    float ycam = 0;

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
        glClearColor(0.f, 0.f, 0.f, 0.f);

        // Send projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Send modelview matrix

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            xcam += 0.01;

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            xcam -= 0.01;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            ycam += 0.01;

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            ycam -= 0.01;

        if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
            ortho = false;
        else if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
            ortho = true;

        if (ortho)
        {
            gluPerspective(90.f, (float)screenWidth / screenHeight, 0.5f, 50.f);
        }
        else
        {
            glOrtho(-2, 2, -2, 2, 0.10f, 100.f);
        }
        gluLookAt(xcam, ycam, 1, xcam, ycam, 0, 0, 1, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f /* + xcam */, 0.f /* +ycam */, -1.f);
        static float rotation = 0.f;

        glRotatef(rotation, 0.0f, 1.f, 0.f);

        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
            rotation += 1;

        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
            rotation -= 1;

        glColor3f(0.7, 0, 0);
        // Draw primitive
        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);
        glTranslatef(-1, 0, 0);
        gl::drawCone(15, 0.3);
        glTranslatef(0.2, 0, 0);
        glColor3f(0, 1, 0);
        gl::drawTriangle();
        glTranslatef(0.2, 0, 0);
        glColor3f(0, 0, 1);
        gl::drawQuad();
        glTranslatef(0.2, 0, 0);
        gl::drawCube(0.1f, 0.1f, 0.1f);
        glTranslatef(0.2, 0, 0);
        gl::drawGizmo();
        glTranslatef(0.4, 0, 0);
        glColor3f(1, 1, 0);
        gl::drawPointSphere(15, 150);
        glTranslatef(0.4, 0, 0);

        glTranslatef(0.4, 0, 0);
        glColor3f(0, 1, 1);
        gl::drawSphere(10, 13);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}