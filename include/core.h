#ifndef CORE_H
#define CORE_H
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <world.h>

extern float horz_pixel_step, vert_pixel_step;

extern GLFWwindow* a_window;
extern const GLFWvidmode* a_videomode;
extern GLuint a_shaderProgram;

extern World* a_world;

void init();
void close();

#endif
