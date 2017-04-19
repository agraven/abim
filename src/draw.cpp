#include "draw.h"
#include "core.h"

static GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};

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
	// Bind buffers and upload polygons
	glBindVertexArray(object->vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, object->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_DYNAMIC_DRAW);

	// Bind shader
	glUseProgram(state->default_shader);

	// Linking vertex data with attributes
	GLint positionAttributes = glGetAttribLocation(state->default_shader, "position");
	glEnableVertexAttribArray(positionAttributes);
	// Fifth argument is for values per vertex
	glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

	GLint colorAttributes = glGetAttribLocation(state->default_shader, "color");
	glEnableVertexAttribArray(colorAttributes);
	// Sixth argument is values to skip (x,y)
	glVertexAttribPointer(colorAttributes, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(2*sizeof(float)));

	GLint textureAttributes = glGetAttribLocation(state->default_shader, "texcoord");
	glEnableVertexAttribArray(textureAttributes);
	glVertexAttribPointer(textureAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, object->texture);
	// Render polygons
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
