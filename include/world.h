#ifndef WORLD_H
#define WORLD_H
#include "data-types.h"
#include "object.h"

typedef struct {
	Vector camera;
	Object* object_first;
} World;

World* world_new();

void world_prepend_object(World* world, Object* object);
void world_append_object(World* world, Object* object);

void world_remove_object(World* world, Object* object);

/*class World {
	public:
		void object_add(Object* object);
		void object_remove(Object* object);
		virtual void update();
		virtual void render();
		Object* objlist_first;
		Vector camera = {0, 0};
		World();
		virtual ~World();
	private:
};*/

#endif
