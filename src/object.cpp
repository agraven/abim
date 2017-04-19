#include "object.h"
#include <GL/glew.h>
#include <SOIL.h>
#include <stdlib.h>
#include "data-types.h"
#include "core.h"
static GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};

Object* object_new(Vector position, Vector size, const char* texture_filename) {
	Object* object = (Object*) malloc(sizeof(Object));
	object->position = position;
	object->size = size;

	// Store attribute links in vertex array object
	glGenVertexArrays(1, &object->vertexArrayObject);
	glBindVertexArray(object->vertexArrayObject);

	glGenBuffers(1, &object->vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertexBufferObject);

	glGenBuffers(1, &object->elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Linking vertex data with attributes
	GLint positionAttributes = glGetAttribLocation(state->default_shader, "position");
	glEnableVertexAttribArray(positionAttributes);
	glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0); // Fifth argument is for values per vertex

	GLint colorAttributes = glGetAttribLocation(state->default_shader, "color");
	glEnableVertexAttribArray(colorAttributes);
	glVertexAttribPointer(colorAttributes, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(2*sizeof(float))); // Sixth argument is values to skip (x,y)

	GLint textureAttributes = glGetAttribLocation(state->default_shader, "texcoord");
	glEnableVertexAttribArray(textureAttributes);
	glVertexAttribPointer(textureAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

	// Load texture
	int image_width, image_height;
	unsigned char* image_data = SOIL_load_image(texture_filename, &image_width, &image_height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &object->texture);
	glBindTexture(GL_TEXTURE_2D, object->texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return object;
}

void object_destroy(Object* object) {
	glDeleteTextures(1, &object->texture);
	glDeleteShader(object->fragmentShader);
	glDeleteShader(object->vertexShader);
	glDeleteBuffers(1, &object->elementBufferObject);
	glDeleteBuffers(1, &object->vertexBufferObject);
	glDeleteVertexArrays(1, &object->vertexArrayObject);
	safe_free(object);
}

/*Object::Object(float x, float y, float width, float height, const char* texture_filename) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	// Store attribute links in vertex array object
	glGenVertexArrays(1, &object.vertexArrayObject);
	glBindVertexArray(object.vertexArrayObject);

	glGenBuffers(1, &object.vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, object.vertexBufferObject);

	glGenBuffers(1, &object.elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

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

	// Load texture
	int image_width, image_height;
	unsigned char* image_data = SOIL_load_image(texture_filename, &image_width, &image_height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &obj->texture);
	glBindTexture(GL_TEXTURE_2D, obj->texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}
object_destroy(object* obj) {
	glDeleteTextures(1, &obj->texture);
	glDeleteBuffers(1, &obj->elementBufferObject);
	glDeleteBuffers(1, &obj->vertexBufferObject);
	glDeleteVertexArrays(1, &obj->vertexArrayObject);
	a_free(obj);
}
void Object::render(Vector camera) {
	float x1 = (x - camera.x) * horz_pixel_step - 1.0f;
	float x2 = (x - camera.x + width) * horz_pixel_step - 1.0f;
	float y1 = (y - camera.y) * vert_pixel_step - 1.0f;
	float y2 = (y - camera.y + height) * vert_pixel_step - 1.0f;
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
Object::~Object() {
	glDeleteTextures(1, &texture);
	//glDeleteProgram(a_shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
}*/
