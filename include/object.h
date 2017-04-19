#ifndef OBJECT_H
#define OBJECT_H
#include <GL/glew.h>
#include "data-types.h"

typedef struct _object Object;
struct _object {
	Vector position, size;
	GLuint fragmentShader, vertexShader;
	GLuint texture;
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;
	Object* object_next;
};

Object* object_new(Vector position, Vector size, const char* texture_filename);

void object_update(Object* object);

void object_destroy(Object* object);

#endif
