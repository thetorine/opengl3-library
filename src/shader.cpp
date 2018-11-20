#include <stdio.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

GLuint vertexShaderID;
GLuint fragmentShaderID;
GLuint programID;

GLint modelMatrixUniform;
GLint viewMatrixUniform;
GLint projMatrixUniform;

bool compileShader(GLuint shaderID, std::string file);
std::string readFile(std::string file);

bool compileShader() {
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    bool r1 = compileShader(vertexShaderID, VERTEX_SHADER);
    bool r2 = compileShader(fragmentShaderID, FRAGMENT_SHADER);

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

bool compileShader(GLuint shaderID, std::string file) {
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

std::string readFile(std::string file) {
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

GLuint getProgramID() {
    return programID;
}

void setModelMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
}

void setViewMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
}

void setProjMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE, &matrix[0][0]);
}

void setInt(std::string var, int value) {
    GLint location = glGetUniformLocation(programID, var.c_str());
    glUniform1i(location, value);
}