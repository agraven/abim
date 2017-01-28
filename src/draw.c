#include "draw.h"
#include <GL/glew.h>
void draw_object(object* obj) {
	glBindBuffer(GL_ARRAY_BUFFER, obj->vertexBufferObject);
	glUseProgram(a_shaderProgram);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
