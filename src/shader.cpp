#include <stdio.h>


#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "utilities.hpp"

static std::shared_ptr<shader> shaderObj;

shader::shader(std::string shaderName)
	:shaderName(shaderName) {
	if (!compileShader()) {
		printf("Unable to compile shader\n");
		exit(-1);
	}
}

shader::~shader() {

}

bool shader::compileShader() {
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    bool r1 = compileShader(vertexShaderID, SHADER_DIR + shaderName + "/vertex.glsl");
    bool r2 = compileShader(fragmentShaderID, SHADER_DIR + shaderName + "/fragment.glsl");

    if (!r1 || !r2) {
        printf("Unable to compile shaders\n");
        glDeleteShader(fragmentShaderID);
        glDeleteShader(vertexShaderID);
        return false;
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glBindAttribLocation(programID, POSITION_LOCATION, "position");
	glBindAttribLocation(programID, NORMAL_POSITION, "normal");
	glBindAttribLocation(programID, UV_LOCATION, "uv");
    glLinkProgram(programID);

    GLint linkStatus = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar *errorLog = new GLchar[maxLength];
	    glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

        printf("%s\n", (char *)errorLog);

        glDeleteProgram(programID);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        return false;
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    modelMatrixUniform = glGetUniformLocation(programID, "modelMatrix");
    viewMatrixUniform = glGetUniformLocation(programID, "viewMatrix");
    projMatrixUniform = glGetUniformLocation(programID, "projMatrix");

    return true;
}

bool shader::compileShader(GLuint shaderID, std::string file) {
    GLint success = 0;
    std::string shaderCode = readFile(file);
    const GLchar *shaderString = (GLchar *)shaderCode.c_str();

    glShaderSource(shaderID, 1, &shaderString, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
	    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar *errorLog = new GLchar[maxLength];
	    glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

        printf("%s\n", (char *)errorLog);

        glDeleteShader(shaderID);
        return false;
    }

    return true;
}

void shader::useShader() {
	glUseProgram(programID);
}

void shader::setModelMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
}

void shader::setViewMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
}

void shader::setProjMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
}

void shader::setVec3(std::string var, glm::vec3 value) {
	GLint location = glGetUniformLocation(programID, var.c_str());
	glUniform3fv(location, 1, &value[0]);
}

void shader::setInt(std::string var, int value) {
    GLint location = glGetUniformLocation(programID, var.c_str());
    glUniform1i(location, value);
}

void shader::setFloat(std::string var, float value) {
	GLint location = glGetUniformLocation(programID, var.c_str());
	glUniform1f(location, value);
}

void shader::createShader(std::string shaderName) {
	shaderObj = std::make_shared<shader>(shaderName);
}

std::shared_ptr<shader> &shader::getInstance() {
	return shaderObj;
}