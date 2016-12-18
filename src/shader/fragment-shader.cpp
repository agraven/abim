#include "shader/fragment-shader.h"
const GLchar* fragment_shader_src = GLSL(
	in vec4 Color;
	in vec2 Texcoord;

	out vec4 outColor;

	uniform sampler2D tex;

	void main() {
		outColor = texture(tex, Texcoord) * vec4(Color);
	}
);
