#include "world.h"
#include "data-types.h"
#include "object.h"
World::World() {
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
}
