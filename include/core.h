#ifndef CORE_H
#define CORE_H
#include <GLFW/glfw3.h>
#include <GL/glew.h>

extern float horz_pixel_step, vert_pixel_step;

extern GLFWwindow* window;
extern const GLFWvidmode* videomode;
extern GLuint shaderProgram;
extern GLuint vertexArrayObject;
extern GLuint vertexBufferObject;
extern GLuint elementBufferObject;

void init();
void close();

#endif
