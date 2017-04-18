#ifndef CORE_H
#define CORE_H
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <world.h>

typedef struct {
	GLFWwindow* window;
	const GLFWvidmode* videomode;
	World* world;
	GLuint default_shader;
} State;

extern State* state;

extern float horz_pixel_step, vert_pixel_step;

void init();
void close();

#endif
