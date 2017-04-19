#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "world.h"
#include "shader/fragment-shader.h"
#include "shader/vertex-shader.h"
float horz_pixel_step, vert_pixel_step;
State* state;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
     if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) /*world_remove_object(state->world, state->world->object_first);*/ state->world->object_first->position.x += 100;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
	//glfwSetWindowSize(window, width, height);
}

void init() {
	state = (State*) malloc(sizeof(State));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	state->videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	horz_pixel_step = 2.0f / state->videomode->width;
	vert_pixel_step = 2.0f / state->videomode->height;
	//state->window = glfwCreateWindow(1024, 768, PACKAGE_STRING, nullptr, nullptr); // Windowed
	state->window = glfwCreateWindow(state->videomode->width, state->videomode->height, PACKAGE_NAME, glfwGetPrimaryMonitor(), NULL); // Fullscreen
	if (state->window == NULL) {
		fprintf(stderr, PACKAGE ": Fatal error: could not create window\n");
		exit(1);
	}
	glfwSetWindowSizeLimits(state->window, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwMakeContextCurrent(state->window);
	glfwSetKeyCallback(state->window, key_callback);
	//glfwSetWindowSizeCallback(a_window, window_size_callback);

	glewExperimental = GL_TRUE;
	glewInit();
	state->videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Compile vertex and fragment shaders
	GLuint fragmentShader, vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_src, NULL);
	glCompileShader(fragmentShader);

	// Link shader program from vertex and fragment shader
	state->default_shader = glCreateProgram();
	glAttachShader(state->default_shader, vertexShader);
	glAttachShader(state->default_shader, fragmentShader);
	glBindFragDataLocation(state->default_shader, 0, "outColor");
	glLinkProgram(state->default_shader);
	glUseProgram(state->default_shader);
}

void close() {
	glDeleteProgram(state->default_shader);

	glfwDestroyWindow(state->window);
	glfwTerminate();
}
