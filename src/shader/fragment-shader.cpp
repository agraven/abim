#include "shader/fragment-shader.h"
const GLchar* fragment_shader_src = GLSL(
	out vec4 outColor;

	void main() {
		outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
);
