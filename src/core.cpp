#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "shader/fragment-shader.h"
#include "shader/vertex-shader.h"
float horz_pixel_step, vert_pixel_step;

GLFWwindow* window;
const GLFWvidmode* videomode;
GLuint fragmentShader, vertexShader;
GLuint shaderProgram;
GLuint vertexArrayObject;
GLuint vertexBufferObject;
GLuint elementBufferObject;
GLuint texture;
float vertices[] = { // Format: x, y, red, green, blue, alpha, tex-x, tex-y
	 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-left
	 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom-right
	-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom-left
};
GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};


void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	horz_pixel_step = 2.0f / videomode->width;
	vert_pixel_step = 2.0f / videomode->height;
	window = glfwCreateWindow(1024, 768, "OpenGL", nullptr, nullptr); // Windowed
	//window = glfwCreateWindow(videomode->width, videomode->height, PACKAGE_NAME, glfwGetPrimaryMonitor(), nullptr); // Fullscreen
	if (!window) {
		fprintf(stderr, PACKAGE ": Fatal error: could not create window\n");
		exit(1);
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Store attribute links in vertex array object
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

	// Compile vertex and fragment shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_src, NULL);
	glCompileShader(fragmentShader);

	// Link shader program from vertex and fragment shader
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Linking vertex data with attributes
	GLint positionAttributes = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(positionAttributes);
	glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0); // Fifth argument is for values per vertex

	GLint colorAttributes = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttributes);
	glVertexAttribPointer(colorAttributes, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(2*sizeof(float))); // Sixth argument is values to skip (x,y)

	GLint textureAttributes = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(textureAttributes);
	glVertexAttribPointer(textureAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
}

void close() {
	glDeleteTextures(1, &texture);
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);

	glfwDestroyWindow(window);
	glfwTerminate();
}

