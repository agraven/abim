#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
GLFWwindow* window;
const GLFWvidmode* videomode;

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
}

void close() {
	glfwTerminate();
}

int main(int argc, char* argv[]) {
	init();

	// Main loop
	while(!glfwWindowShouldClose(window)) {
		// Rendering
		glClear(GL_COLOR_BUFFER_BIT);
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