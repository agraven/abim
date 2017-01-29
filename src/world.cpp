#include "world.h"
#include "config.h"
#include "data-types.h"
#include "object.h"
world* world_new() {
	world* w = malloc(sizeof(world));
	return w;
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
	a_free(w);
}

/*void World::update() {
	if (objlist_first != nullptr) {
		Object* index = objlist_first;
		index->update();
		while (index->objlist_next != nullptr) {
			index = index->objlist_next;
			index->update();
		}
	}
}*/
