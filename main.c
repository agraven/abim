#include "config.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "world.h"
#include "object.h"

int main(int argc, char* argv[]) {
	init();
	a_world = world_new();
	point origin = {0.0f, 0.0f};
	point_tex* pointlist = {
		{1.0f, 1.0f, 0.0f, 0.0f},
		{1.0f. 200.0f, 0.0f, 1.0f},
		{200.0f, 200.0f, 1.0f, 1.0f},
		{200.0f, 1.0f, 1.0f, 0.0f}
	};

	world_add_object(a_world, object_new(origin, pointlist, 4, "splash.png"));

	// Main loop
	while(!glfwWindowShouldClose(a_window)) {

		// Rendering
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		a_world->render();

		glfwSwapBuffers(a_window);

		// Event handling
		glfwPollEvents();
	}

	close();
	return 0;
}
