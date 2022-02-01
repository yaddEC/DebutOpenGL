
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"


// Dans le gl.cpp
PFNGLGENTEXTURESPROC glGenTextures = nullptr;
PFNGLBINDTEXTUREPROC glBindTexture = nullptr;
PFNGLTEXIMAGE2DPROC glTexImage2D = nullptr;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D = nullptr;
PFNGLTEXPARAMETERIPROC glTexParameteri = nullptr;
PFNGLTEXCOORD2FPROC glTexCoord2f = nullptr;
PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;
PFNGLNORMAL3FPROC glNormal3f = nullptr;
PFNGLLIGHTFVPROC glLightfv = nullptr;
PFNGLGETSTRINGPROC glGetString = nullptr;
PFNGLCLEARPROC glClear = nullptr;
PFNGLCLEARCOLORPROC glClearColor = nullptr;
PFNGLENABLEPROC glEnable = nullptr;
PFNGLDISABLEPROC glDisable = nullptr;
PFNGLBEGINPROC glBegin = nullptr;
PFNGLENDPROC glEnd = nullptr;
PFNGLVERTEX3FPROC glVertex3f = nullptr;
PFNGLCOLOR3FPROC glColor3f = nullptr;
PFNGLCOLOR3FVPROC glColor3fv = nullptr;
PFNGLCOLOR3UBPROC glColor3ub = nullptr;
PFNGLLOADIDENTITYPROC glLoadIdentity = nullptr;
PFNGLMATRIXMODEPROC glMatrixMode = nullptr;
PFNGLTRANSLATEFPROC glTranslatef = nullptr;
PFNGLROTATEFPROC glRotatef = nullptr;
PFNGLSCALEFPROC glScalef = nullptr;
PFNGLPUSHMATRIXPROC glPushMatrix = nullptr;
PFNGLPOPMATRIXPROC glPopMatrix = nullptr;
PFNGLORTHOPROC glOrtho = nullptr;
PFNGLPOLYGONMODEPROC glPolygonMode = nullptr;

void loadGLFunctions()
{
    // Assign function pointers
    glLightfv = (PFNGLLIGHTFVPROC) glfwGetProcAddress("glLightfv");
    glNormal3f = (PFNGLNORMAL3FPROC )glfwGetProcAddress("glNormal3f");
    glGetString = (PFNGLGETSTRINGPROC)glfwGetProcAddress("glGetString");
    glClear = (PFNGLCLEARPROC)glfwGetProcAddress("glClear");
    glClearColor = (PFNGLCLEARCOLORPROC)glfwGetProcAddress("glClearColor");
    glEnable = (PFNGLENABLEPROC)glfwGetProcAddress("glEnable");
    glDisable = (PFNGLDISABLEPROC)glfwGetProcAddress("glDisable");
    glBegin = (PFNGLBEGINPROC)glfwGetProcAddress("glBegin");
    glEnd = (PFNGLENDPROC)glfwGetProcAddress("glEnd");
    glVertex3f = (PFNGLVERTEX3FPROC)glfwGetProcAddress("glVertex3f");
    glColor3f = (PFNGLCOLOR3FPROC)glfwGetProcAddress("glColor3f");
    glColor3fv = (PFNGLCOLOR3FVPROC)glfwGetProcAddress("glColor3fv");
    glColor3ub = (PFNGLCOLOR3UBPROC)glfwGetProcAddress("glColor3ub");
    glLoadIdentity = (PFNGLLOADIDENTITYPROC)glfwGetProcAddress("glLoadIdentity");
    glMatrixMode = (PFNGLMATRIXMODEPROC)glfwGetProcAddress("glMatrixMode");
    glTranslatef = (PFNGLTRANSLATEFPROC)glfwGetProcAddress("glTranslatef");
    glRotatef = (PFNGLROTATEFPROC)glfwGetProcAddress("glRotatef");
    glScalef = (PFNGLSCALEFPROC)glfwGetProcAddress("glScalef");
    glPushMatrix = (PFNGLPUSHMATRIXPROC)glfwGetProcAddress("glPushMatrix");
    glPopMatrix = (PFNGLPOPMATRIXPROC)glfwGetProcAddress("glPopMatrix");
    glOrtho = (PFNGLORTHOPROC)glfwGetProcAddress("glOrtho");
    glPolygonMode = (PFNGLPOLYGONMODEPROC)glfwGetProcAddress("glPolygonMode");
    glGenTextures = (PFNGLGENTEXTURESPROC)glfwGetProcAddress("glGenTextures");
    glBindTexture = (PFNGLBINDTEXTUREPROC)glfwGetProcAddress("g lBindTexture");
    glTexImage2D = (PFNGLTEXIMAGE2DPROC)glfwGetProcAddress("glTexImage2D");
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)glfwGetProcAddress("glTexSubImage2D");
    glTexParameteri = (PFNGLTEXPARAMETERIPROC)glfwGetProcAddress("glTexParameteri");
    glTexCoord2f = (PFNGLTEXCOORD2FPROC)glfwGetProcAddress("glTexCoord2f");
    glDeleteTextures = (PFNGLDELETETEXTURESPROC)glfwGetProcAddress("glDeleteTextures");
}