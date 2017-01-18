#ifndef OBJECT_H
#define OBJECT_H
#include <GL/glew.h>
#include "data-types.h"

class Object {
	public:
		float x, y;
		float width, height;

		Object(float init_x, float init_y, float init_width, float init_height, const char* texture_filename);
		Object* objlist_next = nullptr;
		virtual void update();
		virtual void render(point camera);
		virtual ~Object();
	private:
		int image_width, image_height;
		unsigned char* image_data;
		GLuint fragmentShader, vertexShader;
		GLuint texture;
		GLuint vertexArrayObject;
		GLuint vertexBufferObject;
		GLuint elementBufferObject;
};

#endif
