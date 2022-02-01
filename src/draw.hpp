#pragma once
#pragma pack(push, 1)
struct float3
{
    float x;
    float y;
    float z;
};


struct BMPHeader
{
    char signature[2];
    unsigned int fileSize;
    char reserved1[2];
    char reserved2[2];
    unsigned int fileOffsetToPixelArray;
};

struct DIBHeader
{
    unsigned int unused_00;
    unsigned int width;
    unsigned int height;
    unsigned short unused_01;
    unsigned short bpp; // bits per pixel (24,32)
};
// Utils to draw with OpenGL
namespace gl
{
    // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawTriangle();
    //Load the texture and assign it to a numeric value
    GLuint loadTexture(const char *filename);
    //Draw the maze
    void drawMaze(const GLuint Texture,const int maze[10][10],const float width);
    // Draw quad centered (halfSize = 0.5)
    void drawQuad(GLuint texture);
    // Draw a cube (res = number of subdivision on each axes)
    void drawCube(float resX, float resY, float resZ,GLuint texture);
    // Draw sphere (longitudes, lattitudes)
    void drawSphere(int lon, int lat);
    // Draw a sphere with points
    void drawPointSphere(int lon, int lat);
    // Draw cone primitive (res = )
    void drawCone(int res,float size);
    // Draw gizmo (3 axes from 0.0 to 1.0 of different color)
    void drawGizmo();
}
namespace utils
{
unsigned char* loadBMP24(const char* filename, int* widthOut, int* heightOut);
}