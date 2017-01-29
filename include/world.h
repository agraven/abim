#ifndef WORLD_H
#define WORLD_H
#include "data-types.h"
#include "object.h"

/** World structure
 * @obj_first: The first instance in the linked list of the world's objects.
 * @camera: The position of the world's current rendering offset.
 *
 * An instance of a world state. Some software refers to this as a scene.
 */
typedef struct {
	object* obj_first;
	point camera;
} world;

/** Allocate new world
 *
 * Return a pointer to a newly allocated world.
 */
world* world_new();

// TODO: world_new_from_name(const char* name);

/** Destroy world
 *
 * Removes a world and all its member objects from memory.
 * TODO: Implement persistent objects that remain accross worlds.
 */
void world_destroy(world* w);

/** Add object to world
 *
 * Adds object obj to world w's linked list of objects.
 */
int world_add_object(world* w, obj* obj);

/** Remove object from world
 *
 * Removes object obj from world w's linked list of objects.
 */
int world_add_object(world* w, obj* obj);

#endif
