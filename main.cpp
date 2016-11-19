#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include "shader/fragment-shader.h"
#include "shader/vertex-shader.h"

GLFWwindow* window;
const GLFWvidmode* videomode;
GLuint fragmentShader, vertexShader;
GLint positionAttributes;
GLuint shaderProgram;
GLuint vertexArrayObject;
GLuint vertexBufferObject;
float vertices[] = {
	0.0f, 0.5f,
	0.5f, -0.5f,
	-0.5f, -0.5f
};

void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	window = glfwCreateWindow(videomode->width, videomode->height, PACKAGE_NAME, glfwGetPrimaryMonitor(), nullptr); // Fullscreen
	if (!window) {
		fprintf(stderr, PACKAGE ": Fatal error: could not create window\n");
		exit(1);
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	// Store attribute links in vertex array object
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Compile vertex and fragment shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_src, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Linking vertex data with attributes
	GLint positionAttributes = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttributes);
}

void close() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);

	glfwTerminate();
}

int main(int argc, char* argv[]) {
	init();

	// Main loop
	while(!glfwWindowShouldClose(window)) {
		// Rendering
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Event handling
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	close();
	return 0;
}
