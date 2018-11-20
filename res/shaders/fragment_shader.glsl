#version 330 core

in vec2 texPos;
in vec3 fragPos;

out vec4 color;

uniform sampler2D tex;
uniform bool wireframe;

void main() {
	if (wireframe)
		color = vec4(0.5f, 1.0f, 0.0f, 1.0f);
	else
		color = texture(tex, texPos);
}
