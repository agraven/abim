#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "draw.h"
#include "world.h"
#include "object.h"

#define RENDERS_PER_SECOND 60

double timediff(clock_t time1, clock_t time2) {
	return ((double)time1 - time2) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]) {
	init();
	state->world = world_new();
	world_prepend_object(state->world, object_new({2.0f, 2.0f}, {200.0f, 394.0f}, "splash.png"));
	world_prepend_object(state->world, object_new({500.0f, 200.0f}, {-200.0f, 194.0f}, "splash2.png"));

	// Main loop
	clock_t initial = clock(), start, end;
	while(!glfwWindowShouldClose(state->window)) {
		start = clock();

		// Rendering
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		draw_world(state->world);

		glfwSwapBuffers(state->window);

		// Event handling
		glfwPollEvents();

		// Wait if frame finished rendering early
		end = clock();
		if (timediff(end, start) < 1.0 / RENDERS_PER_SECOND) {
			usleep((1.0 / RENDERS_PER_SECOND - timediff(end, start)) * 1000000);
		}
	}

	close();
	return 0;
}
