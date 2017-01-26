#ifndef OBJECT_H
#define OBJECT_H
#include <GL/glew.h>
#include "data-types.h"

/** Default object type 
 * @origin: The base positional value 
 * @point_list: A dynamic array of point_tex's which make up the objects
 * collision boundary.
 * @point_count: The number of point in the point_list
 *
 * The type for for physics-interactive, non-particle objects.
 */
typedef struct object object;
struct {
	point origin;
	point_tex* point_list;
	point point_count;
	const char* texture_filename;

	GLuint fragmentShader, vertexShader;
	GLuint texture;
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;

	object* objlist_next = nullptr;
};

/** Allocate new object
 *
 * Allocate an object to memory and return a pointer to it.
 * Remember to object_destroy() it once it's no longer needed.
 */
object* object_new(
	point origin,
	point* point_list,
	unsigned int point_count,
	const char* texture_filename
);

/** Destroy an object
 *
 * Release an object from memory.
 */
void object_destroy(object* o);

#endif
