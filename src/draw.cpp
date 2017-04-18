#include "draw.h"
#include "core.h"

void draw_world(World* world) {
	// Iterate through object list, rendering each one
	Object* object_index = world->object_first;
	while (object_index != NULL) {
		draw_object(object_index, world);
		object_index = object_index->object_next;
	}
}

void draw_object(Object* object, World* world) {
	float x1 = (object->position.x - world->camera.x) * horz_pixel_step - 1.0f;
	float x2 = (object->position.x - world->camera.x + object->size.x) * horz_pixel_step - 1.0f;
	float y1 = (object->position.y - world->camera.y) * vert_pixel_step - 1.0f;
	float y2 = (object->position.y - world->camera.y + object->size.y) * vert_pixel_step - 1.0f;
	float vertices[] = { // Format: x, y, red, green, blue, alpha, tex-x, tex-y
		x1, y1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-left
		x2, y1, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-right
		x2, y2, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom-right
		x1, y2, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Bottom-left
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glUseProgram(state->default_shader);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
