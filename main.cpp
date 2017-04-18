#include "config.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "draw.h"
#include "world.h"
#include "object.h"

int main(int argc, char* argv[]) {
	init();
	state->world = world_new();
	world_prepend_object(state->world, object_new({2.0f, 2.0f}, {200.0f, 394.0f}, "splash.png"));
	world_prepend_object(state->world, object_new({500.0f, 200.0f}, {-200.0f, 194.0f}, "splash.png"));

	// Main loop
	while(!glfwWindowShouldClose(state->window)) {
		//state->world->update();

		// Rendering
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		draw_world(state->world);

		glfwSwapBuffers(state->window);

		// Event handling
		glfwPollEvents();
	}

	close();
	return 0;
}
