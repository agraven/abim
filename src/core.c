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

GLFWwindow* a_window;
const GLFWvidmode* videomode;
GLuint fragmentShader, vertexShader;
GLuint a_shaderProgram;

World* a_world;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
     if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) a_world->objlist_first->x += 100;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
	glfwSetWindowSize(window, width, height);
}

void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	horz_pixel_step = 2.0f / videomode->width;
	vert_pixel_step = 2.0f / videomode->height;
	a_window = glfwCreateWindow(1024, 768, PACKAGE_STRING, nullptr, nullptr); // Windowed
	//a_window = glfwCreateWindow(videomode->width, videomode->height, PACKAGE_NAME, glfwGetPrimaryMonitor(), nullptr); // Fullscreen
	if (!a_window) {
		fprintf(stderr, PACKAGE ": Fatal error: could not create window\n");
		exit(1);
	}
	glfwSetWindowSizeLimits(a_window, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwMakeContextCurrent(a_window);
	glfwSetKeyCallback(a_window, key_callback);
	//glfwSetWindowSizeCallback(a_window, window_size_callback);

	glewExperimental = GL_TRUE;
	glewInit();
	videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Compile vertex and fragment shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_src, NULL);
	glCompileShader(fragmentShader);

	// Link shader program from vertex and fragment shader
	a_shaderProgram = glCreateProgram();
	glAttachShader(a_shaderProgram, vertexShader);
	glAttachShader(a_shaderProgram, fragmentShader);
	glBindFragDataLocation(a_shaderProgram, 0, "outColor");
	glLinkProgram(a_shaderProgram);
	glUseProgram(a_shaderProgram);
}

void close() {
	glDeleteProgram(a_shaderProgram);

	glfwDestroyWindow(a_window);
	glfwTerminate();
}
