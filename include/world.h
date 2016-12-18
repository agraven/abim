#ifndef WORLD_H
#define WORLD_H
#include "data-types.h"
#include "object.h"

class World {
	public:
		void object_add(Object* object);
		void object_remove(Object* object);
		virtual void update();
		virtual void render();
		Object* objlist_first;
		World();
		virtual ~World();
	private:
		point camera = {0, 0};
};

#endif
