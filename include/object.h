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

/*class Object {
	public:
		float x, y;
		float width, height;

		Object(float init_x, float init_y, float init_width, float init_height, const char* texture_filename);
		Object* objlist_next = nullptr;
		virtual void update();
		virtual void render(Vector camera);
		virtual ~Object();
	private:
		int image_width, image_height;
		unsigned char* image_data;
		GLuint fragmentShader, vertexShader;
		GLuint texture;
		GLuint vertexArrayObject;
		GLuint vertexBufferObject;
		GLuint elementBufferObject;
};*/

#endif
