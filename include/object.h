#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include "data-types.h"

class Object {
	public:
		Object(float x = 0, float y = 0, float width = 0, float height = 0, const char* texture_filename = nullptr);
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
