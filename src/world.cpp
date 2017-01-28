#include "world.h"
#include "data-types.h"
#include "object.h"
world* world_new() {
	world* w = malloc(sizeof(world));
	return w;
}

int world_add_object(object* obj) {
	if (obj_first != NULL) {
	}
}

void world_destroy(world* w) {
	if (obj_first != NULL) {
		object* target;
		while (obj_first->obj_next != NULL) {
			target = obj_first->obj_next;
			obj_first->obj_next = target->obj_next;
			object_destroy(target);
		}
		object_destroy(obj_first);
	}
	free(w);
}

void World::object_add(Object* object) {
	if (objlist_first == nullptr) {
		objlist_first = object;
	} else {
		Object* index = objlist_first;
		while (index->objlist_next != nullptr) {
			index = index->objlist_next;
		}
		index->objlist_next = object;
	}
}
void World::update() {
	if (objlist_first != nullptr) {
		Object* index = objlist_first;
		index->update();
		while (index->objlist_next != nullptr) {
			index = index->objlist_next;
			index->update();
		}
	}
}
void World::render() {
	if (objlist_first != nullptr) {
		Object* index = objlist_first;
		index->render(camera);
		while (index->objlist_next != nullptr) {
			index = index->objlist_next;
			index->render(camera);
		}
	}
}
World::~World() {
}
