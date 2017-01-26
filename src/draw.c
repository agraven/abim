#include "draw.h"
void draw_polygon_tex(polygon_tex pol) {
	float vertices = {
		pol[0].x, pol[0].y, 1.0f, 1.0f, 1.0f, 1.0f, pol[0].tex_x, pol[0].tex_y
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glUseProgram(a_shaderProgram);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
