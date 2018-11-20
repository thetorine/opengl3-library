#version 330 core

in vec3 position;
in vec2 uv;

out vec2 texPos;
out vec3 fragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main() {
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

	texPos = uv;
	fragPos = position;
}
