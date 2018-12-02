#pragma once

#include <memory>
#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>

#define SHADER_DIR "res/shaders/"

#define POSITION_LOCATION 0
#define NORMAL_POSITION 1
#define UV_LOCATION 2

class shader {
public:
	shader(std::string shaderName);
	~shader();

	bool compileShader();
	void useShader();

	void setModelMatrix(glm::mat4 matrix);
	void setViewMatrix(glm::mat4 matrix);
	void setProjMatrix(glm::mat4 matrix);
	void setVec3(std::string var, glm::vec3 value);
	void setInt(std::string var, int value);
	void setFloat(std::string var, float value);

	static void createShader(std::string shaderName);
	static std::shared_ptr<shader> &getInstance();
private:
	bool compileShader(GLuint shaderID, std::string file);

	std::string shaderName;

	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	GLuint programID;

	GLint modelMatrixUniform;
	GLint viewMatrixUniform;
	GLint projMatrixUniform;
};