
#include <cmath>
#include "gl.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
#include "draw.hpp"

#pragma pack(pop)

static unsigned char *loadFile(const char *filename, size_t *fileSizeOut)
{
    unsigned char *data = nullptr;

    // Open file
    std::ifstream file(filename, std::ios_base::binary);
    if (!file.is_open())
    {
        printf("Error to open file '%s'\n", filename);
        return nullptr;
    }

    // Read filesize
    file.seekg(0, std::ios_base::end);
    *fileSizeOut = file.tellg();
    file.seekg(0, std::ios_base::beg);

    // Allocate memory
    data = new unsigned char[*fileSizeOut];
    file.read((char *)data, *fileSizeOut);

    file.close();

    return data;
}

unsigned char *utils::loadBMP24(const char *filename, int *widthOut, int *heightOut)
{
    size_t sizeOut;
    unsigned char *file = loadFile(filename, &sizeOut);

    if (file[0] != 'B' || file[1] != 'M')
    {
        printf("Not a NMP file\n");
        return 0;
    }

    /*     *widthOut = *(int *)&(header[0x12]);
    *heightOut = *(int *)&(header[0x16]); */
    BMPHeader bmp;
    DIBHeader dib;
    std::memcpy(&bmp, file, sizeof(BMPHeader));
    std::memcpy(&dib, file + sizeof(BMPHeader), sizeof(DIBHeader));

    *widthOut = dib.width;
    *heightOut = dib.height;
    unsigned char *data = new unsigned char[dib.width * (dib.height) * 3];

    std::memcpy(data + bmp.fileOffsetToPixelArray, file, dib.width * (dib.height) * 3);

    return data;
}

GLuint gl::loadTexture(const char *filename)
{
    GLuint text;
    int width = 0;
    int height = 0;
    glGenTextures(1, &text);
    glBindTexture(GL_TEXTURE_2D, text);
    unsigned char *data = utils::loadBMP24(filename, &width, &height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] data;
    return text;
}

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
void gl::drawQuad(GLuint texture)
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.1f, -0.1f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.1f, -0.1f, 0.f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.1f, 0.1f, 0.f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.1f, 0.1f, 0.f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void gl::drawCube(float a, float b, float c, GLuint texture)
{

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);

    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(a * (-1), b * (-1), c * (-1));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(a, b * (-1), c * (-1));
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(a, b, c * (-1));
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a * (-1), b, c * (-1));

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(a * (-1), b * (-1), c);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(a, b * (-1), c);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(a, b, c);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a * (-1), b, c);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(a, b, c * (-1));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(a, b, c);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(a * (-1), b, c);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a * (-1), b, c * (-1));

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(a, b * (-1), c * (-1));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(a, b * (-1), c);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(a, b, c);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a, b, c * (-1));

    glNormal3f(0.0f, -1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(a, b * (-1), c * (-1));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(a, b * (-1), c);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(a * (-1), b * (-1), c);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a * (-1), b * (-1), c * (-1));

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(a * (-1), b * (-1), c * (-1));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(a * (-1), b * (-1), c);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(a * (-1), b, c);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(a * (-1), b, c * (-1));

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
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

void gl::drawCone(int res, float size)
{
    float r = 0.5f;
    float height = 1.7f;
    glBegin(GL_QUADS);

    for (int j = 0; j < 1; ++j)
    {
        float theta0 = ((j + 0) / (float)2) * M_PI * height;
        float theta1 = ((j + 1) / (float)2) * M_PI * height;

        for (int i = 0; i < res; ++i)
        {
            float phi0 = ((i + 0) / (float)res) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)res) * 2.f * M_PI;

            float3 c0 = getSphericalCoords(fmod(r, size), theta0, phi0);
            float3 c1 = getSphericalCoords(fmod(r, size), theta0, phi1);
            float3 c2 = getSphericalCoords(fmod(r, size), theta1, phi1);
            float3 c3 = getSphericalCoords(fmod(r, size), theta1, phi0);

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
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.5, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0.5, 0, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0.5);

    glEnd();

    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0.5, 0);
    drawCone(15, 0.025);
    glTranslatef(0, -0.5, 0);
    glRotatef(90, -1, 0, 0);

    glColor3f(0, 1, 0);
    glRotatef(270, 0, 0, 1);
    glTranslatef(0, 0.5, 0);
    drawCone(15, 0.025);
    glTranslatef(0, -0.5, 0);
    glRotatef(270, 0, 0, -1);

    glColor3f(1, 0, 0);

    glTranslatef(0, 0.5, 0);
    drawCone(15, 0.025);
    glTranslatef(0, -0.5, 0);

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

void gl::drawMaze(const GLuint Texture,const int maze[10][10],const float width)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (maze[i][j] == 1)
            {

                glPushMatrix();
                glTranslatef(j, 0, i);
                gl::drawCube(0.5, width, 0.5, Texture);
                glPopMatrix();
            }
        }
    }
}