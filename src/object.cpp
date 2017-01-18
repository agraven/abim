#include "object.h"
#include <GL/glew.h>
#include <SOIL.h>
#include "data-types.h"
#include "core.h"
GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};
Object::Object(float x, float y, float width, float height, const char* texture_filename) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	// Store attribute links in vertex array object
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Linking vertex data with attributes
	GLint positionAttributes = glGetAttribLocation(a_shaderProgram, "position");
	glEnableVertexAttribArray(positionAttributes);
	glVertexAttribPointer(positionAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0); // Fifth argument is for values per vertex

	GLint colorAttributes = glGetAttribLocation(a_shaderProgram, "color");
	glEnableVertexAttribArray(colorAttributes);
	glVertexAttribPointer(colorAttributes, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(2*sizeof(float))); // Sixth argument is values to skip (x,y)

	GLint textureAttributes = glGetAttribLocation(a_shaderProgram, "texcoord");
	glEnableVertexAttribArray(textureAttributes);
	glVertexAttribPointer(textureAttributes, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

	// Load texture
	image_data = SOIL_load_image(texture_filename, &image_width, &image_height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}
void Object::update() {
}
void Object::render(point camera) {
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
	glUseProgram(a_shaderProgram);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
Object::~Object() {
	glDeleteTextures(1, &texture);
	glDeleteProgram(a_shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
}
