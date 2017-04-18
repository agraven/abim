#include "world.h"
#include <stdlib.h>
#include "data-types.h"
#include "object.h"
World* world_new() {
	// allocate memory for world
	World* world = (World*) malloc(sizeof(World));
	// initialize default values
	world->object_first = NULL;
	world->camera = {0.0f, 0.0f};
	// return the result
	return world;
}

void world_prepend_object(World* world, Object* object) {
	object->object_next = world->object_first;
	world->object_first = object;
}

void world_append_object(World* world, Object* object) {
	// If first link is empty, just put the object there
	if (world->object_first = NULL) {
		world->object_first = object;
		return;
	}
	// Traverse the object list until final link is reached
	Object* index = world->object_first;
	while (index->object_next != NULL) {
		index = index->object_next;
	}
	// End if list reached, append the object to the last link
	index->object_next = object;
}

void world_remove_object(World* world, Object* object) {
	// No need to traverse list if first object is matched
	if (world->object_first == NULL) return;
	if (world->object_first == object) {
		world->object_first = world->object_first->object_next;
		object_destroy(object);
	}

	// Traverse list until just before target
	Object* index = world->object_first;
	while (index->object_next != NULL && index->object_next != object) {
		index = index->object_next;
	}
	// De-couple target from list
	index->object_next = object->object_next;
	object_destroy(object);
}

/*World::World() {
	objlist_first = nullptr;
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
void World::object_remove(Object* object) {
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
}*/
