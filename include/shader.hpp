#pragma once

#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>

#define VERTEX_SHADER "res/shaders/vertex_shader.glsl"
#define FRAGMENT_SHADER "res/shaders/fragment_shader.glsl"

#define POSITION_LOCATION 0
#define NORMAL_POSITION 1
#define UV_LOCATION 2

bool compileShader();
GLuint getProgramID();

void setModelMatrix(glm::mat4 matrix);
void setViewMatrix(glm::mat4 matrix);
void setProjMatrix(glm::mat4 matrix);
void setVec3(std::string var, glm::vec3 value);
void setInt(std::string var, int value);
void setFloat(std::string var, float value);