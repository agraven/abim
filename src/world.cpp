#include "world.h"
#include "config.h"
#include <stdio.h>
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
	if (world->object_first == NULL) {
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
	// Check if first object is empty, print warning if so
	if (world->object_first == NULL) {
		return;
		fprintf(stderr, PACKAGE": ERROR: Object removal requested, but no objects allocated.\n");
	}
	// No need to traverse list if first object is matched
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

void world_add_object(world* w, object* obj) {
	// TODO: Find out a way to test successful add, and return the result.
	if (w->obj_first != NULL) {
		obj* index = obj_first;
		while (index->obj_next != NULL) {
			index = index->obj_next;
		}
		index->obj_next = obj;
		return 0;
	}
	w->obj_first = obj;
	return 0;
}

int world_remove_object(world* w, object* obj) {
	if (w->obj_first == NULL) {
		fputs(PACKAGE ": ERROR: couldn't remove object: object list empty", stderr);
		return 1;
	} else {
		if (obj == w->obj_first) {
			object_destroy(obj);
			return 0;
		}
		object* index = w->obj_first, *target;
		// Traverse object list until target is encountered.
		while (index->obj_next != obj) {
			index = index->obj_next;
			if (index->obj_next == NULL) {
				fputs(PACKAGE ": ERROR: couldn't find object assigned for removal", stderr);
			}
		}
		// Remove target from object list and destroy it.
		target = index->obj_next;
		index->obj_next = target->obj_next;
		object_destroy(target);
	}
}

*/
