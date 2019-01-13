#version 330 core

in vec3 position;
in vec3 normal;
in vec3 uv;

out vec3 m;
out vec4 viewPos;
out vec3 vertColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main() {
    mat4 mv = viewMatrix * modelMatrix;

    gl_Position = projMatrix * mv * vec4(position, 1.0);

    m = normalize(mv * vec4(normal, 0.0)).xyz;
    viewPos = mv * vec4(position, 1.0);

    vertColor = uv;
}