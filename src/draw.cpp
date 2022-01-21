
#include <cmath>

#include "gl.hpp"

#include "draw.hpp"

struct float3
{
    float x;
    float y;
    float z;
};

static float3 getSphericalCoords(float r, float theta, float phi)
{
    return {r * sinf(theta) * cosf(phi),
            r * cosf(theta),
            r * sinf(theta) * sinf(phi)};
}

void gl::drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.1f, 0.f);
    glVertex3f(0.1f, -0.1f, 0.f);
    glVertex3f(0.0f, 0.1f, 0.f);
    glEnd();
}
void gl::drawQuad()
{
    glBegin(GL_QUADS);
    glVertex3f(-0.1f, -0.1f, 0.f);
    glVertex3f(0.1f, -0.1f, 0.f);
    glVertex3f(0.1f, 0.1f, 0.f);
    glVertex3f(-0.1f, 0.1f, 0.f);
    glEnd();
}

void gl::drawCube(float a, float b, float c)
{
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex3f(a * (-1), b * (-1), c * (-1));
    glVertex3f(a, b * (-1), c * (-1));
    glVertex3f(a, b, c * (-1));
    glVertex3f(a * (-1), b, c * (-1));

    glVertex3f(a * (-1), b * (-1), c);
    glVertex3f(a, b * (-1), c);
    glVertex3f(a, b, c);
    glVertex3f(a * (-1), b, c);

    glVertex3f(a, b, c * (-1));
    glVertex3f(a, b, c);
    glVertex3f(a * (-1), b, c);
    glVertex3f(a * (-1), b, c * (-1));

    glVertex3f(a, b * (-1), c * (-1));
    glVertex3f(a, b * (-1), c);
    glVertex3f(a, b, c);
    glVertex3f(a, b, c * (-1));

    glVertex3f(a, b * (-1), c * (-1));
    glVertex3f(a, b * (-1), c);
    glVertex3f(a * (-1), b * (-1), c);
    glVertex3f(a * (-1), b * (-1), c * (-1));

    glColor3f(1, 0, 0);
    glVertex3f(a * (-1), b * (-1), c * (-1));
    glVertex3f(a * (-1), b * (-1), c);
    glVertex3f(a * (-1), b, c);
    glVertex3f(a * (-1), b, c * (-1));

    glEnd();
}

void gl::drawPointSphere(int lon, int lat)
{
    float r = 0.5f;
    glBegin(GL_POINTS);

    for (int j = 0; j < lat; ++j)
    {
        float theta = (j / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi = (i / (float)lon) * 2.f * M_PI;

            float3 coords = getSphericalCoords(r, theta, phi);

            glVertex3f(coords.x, coords.y, coords.z);
        }
    }
    glEnd();
}

void gl::drawCone(int res,float size)
{
    float r = 0.5f;
    float height= 1.7f;
    glBegin(GL_QUADS);

    for (int j = 0; j < 1; ++j)
    {
        float theta0 = ((j + 0) / (float)2) * M_PI*height;
        float theta1 = ((j + 1) / (float)2) * M_PI*height;

        for (int i = 0; i < res; ++i)
        {
            float phi0 = ((i + 0) / (float)res) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)res) * 2.f * M_PI;

            float3 c0 = getSphericalCoords(fmod(r,size), theta0, phi0);
            float3 c1 = getSphericalCoords(fmod(r,size), theta0, phi1);
            float3 c2 = getSphericalCoords(fmod(r,size), theta1, phi1);
            float3 c3 = getSphericalCoords(fmod(r,size), theta1, phi0);

            glVertex3f(c0.x, c0.y, c0.z);
            glVertex3f(c1.x, c1.y, c1.z);
            glVertex3f(c2.x, c2.y, c2.z);
            glVertex3f(c3.x, c3.y, c3.z);

            glVertex3f(c0.x, c2.y, c0.z);
            glVertex3f(c1.x, c2.y, c1.z);
            glVertex3f(c2.x, c2.y, c2.z);
            glVertex3f(c3.x, c2.y, c3.z);
        }
    }
    glEnd();
}

void gl::drawGizmo()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(0,0.5,0);
   
    glColor3f(0, 1, 0);
    glVertex3f(0,0,0);
    glVertex3f(0.5,0,0);
    
    glColor3f(0, 0, 1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,0.5);
    
    glEnd();

    glRotatef(90,1,0,0);
    glTranslatef(0,0.5,0);
    drawCone(15,0.025);
    glTranslatef(0,-0.5,0);
    glRotatef(90,-1,0,0);

    glColor3f(0, 1, 0);
    glRotatef(270,0,0,1);
    glTranslatef(0,0.5,0);
    drawCone(15,0.025);
    glTranslatef(0,-0.5,0);
    glRotatef(270,0,0,-1);

    glColor3f(1, 0, 0);

    glTranslatef(0,0.5,0);
    drawCone(15,0.025);
    glTranslatef(0,-0.5,0);
   


    //glRotatef();
}

void gl::drawSphere(int lon, int lat)
{
    float r = 0.5f;
    glBegin(GL_QUADS);

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j + 0) / (float)lat) * M_PI;
        float theta1 = ((j + 1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i + 0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)lon) * 2.f * M_PI;

            float3 c0 = getSphericalCoords(r, theta0, phi0);
            float3 c1 = getSphericalCoords(r, theta0, phi1);
            float3 c2 = getSphericalCoords(r, theta1, phi1);
            float3 c3 = getSphericalCoords(r, theta1, phi0);

            glVertex3f(c0.x, c0.y, c0.z);
            glVertex3f(c1.x, c1.y, c1.z);
            glVertex3f(c2.x, c2.y, c2.z);
            glVertex3f(c3.x, c3.y, c3.z);
        }
    }
    glEnd();
}