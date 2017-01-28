#include "config.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "world.h"
#include "object.h"

int main(int argc, char* argv[]) {
	init();
	a_world = world_new();
	a_world->object_add(object_new(2.0f, 2.0f, 200.0f, 394.0f, "splash.png"));
	a_world->object_add(new Object(500.0f, 200.0f, -200.0f, 194.0f, "splash.png"));

	// Main loop
	while(!glfwWindowShouldClose(a_window)) {
		a_world->update();

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
