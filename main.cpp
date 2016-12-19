#include "config.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "world.h"
#include "object.h"

int main(int argc, char* argv[]) {
	init();
	World* world = new World();
	world->object_add(new Object(2.0f, 2.0f, 20.0f, 20.0f, "splash.png"));
	world->object_add(new Object(50.0f, 200.0f, 20.0f, 20.0f, "splash.png"));

	// Main loop
	while(!glfwWindowShouldClose(window)) {
		world->update();
		// Rendering
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		world->render();

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
