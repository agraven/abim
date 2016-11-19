#include "shader/vertex-shader.h"
const GLchar* vertex_shader_src = GLSL(
	in vec2 position;

	void main() {
		gl_Position = vec4(position, 0.0, 1.0);
	}
);
