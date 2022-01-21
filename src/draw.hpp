#pragma once

// Utils to draw with OpenGL
namespace gl
{
    // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawTriangle();
    // Draw quad centered (halfSize = 0.5)
    void drawQuad();
    // Draw a cube (res = number of subdivision on each axes)
    void drawCube(float resX, float resY, float resZ);
    // Draw sphere (longitudes, lattitudes)
    void drawSphere(int lon, int lat);
    // Draw a sphere with points
    void drawPointSphere(int lon, int lat);
    // Draw cone primitive (res = )
    void drawCone(int res,float size);
    // Draw gizmo (3 axes from 0.0 to 1.0 of different color)
    void drawGizmo();
}