#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include "data-types.h"

class Object {
	public:
		Object(float init_x, float init_y, float init_width, float init_height, const char* texture_filename);
		Object* objlist_next = nullptr;
		point position;
		virtual void update();
		virtual void render(point camera);
		virtual ~Object();
	private:
		float x, y;
		float width, height;
		int image_width, image_height;
		unsigned char* image_data;
};

#endif
